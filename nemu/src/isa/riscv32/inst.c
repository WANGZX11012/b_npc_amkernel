/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>
#include "ftrace.h"
#include <isa.h>


#define R(i) gpr(i)       // 读/写通用寄存器
#define Mr vaddr_read     // 读内存
#define Mw vaddr_write    // 写内存

enum {
  TYPE_I, TYPE_U, TYPE_S,
  TYPE_N,
  TYPE_J, TYPE_R, TYPE_B,  // none  //NEW J R  B TYPE
};
// 从指令中取寄存器/立即数

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)  //符号位扩展 i是当前取到的32位指令
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = SEXT( (BITS(i, 31, 31)<<20 | BITS(i, 19, 12)<<12 | BITS(i, 20, 20)<<11 | BITS(i, 30, 21)<<1 ) , 21); }while(0)     //new
//这里的最后一个 21 告诉 SEXT 宏："这个数的符号位在第 21 位（即 bit 20），请根据这一位做扩展。"
#define immB() do { *imm = SEXT( (BITS(i, 31, 31)<<12 | BITS(i, 7, 7)<<11 | BITS(i, 30, 25)<<5 | BITS(i, 11, 8)<<1 ) , 13); } while(0)//new 最低位为0


static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J:                   immJ(); break; //new
    case TYPE_R: src1R(); src2R();         break; //new
    case TYPE_B: src1R(); src2R(); immB(); break; //new
    case TYPE_N: break;
    default: panic("unsupported type = %d", type);
  }
}

static word_t my_div(word_t src1, word_t src2)
{
  if(src2 == 0)
    return (word_t)-1;
  else
  {
    if( (int32_t)src1 == INT32_MIN && (int32_t)src2 == -1)
      return (word_t) INT32_MIN;
    else
    {
      return (word_t)((int32_t)src1 / (int32_t)(src2));
    }
  }
}

static word_t my_divu(word_t src1, word_t src2)
{
  if(src2 == 0)
    return (word_t)-1;
  else
  {
    return (word_t)src1 / (word_t)(src2);
  }
}



static word_t my_rem(word_t src1, word_t src2)
{
  if (src2 == 0)
    return src1;
  int32_t a = (int32_t)src1;
  int32_t b = (int32_t)src2;
  if (a == INT32_MIN && b == -1)
    return 0;
  return (word_t)(a % b); // C99: % 符号随被除数，且与 RISC-V 向零舍入匹配
}




static word_t my_remu(word_t src1, word_t src2)
{
  if (src2 == 0)
    return src1;

  return (word_t)(src1 % src2);
}

static word_t my_mul(word_t a, word_t b)
{
  int64_t prod = (int64_t)(int32_t)a * (int64_t)(int32_t)b;
  return (word_t)prod; // 取低 32 位（用 64 位中间值避免宽度问题）
}

static word_t my_mulh(word_t a, word_t b)
{
  int64_t prod = (int64_t)(int32_t)a * (int64_t)(int32_t)b;
  return (word_t)(prod >> 32); // 返回有符号乘积的高 32 位
}

static word_t my_mulhu(word_t a, word_t b)
{
  uint64_t prod = (uint64_t)a * (uint64_t)b;
  return (word_t)(prod >> 32);
}

static word_t *csr_reg(word_t imm)
{
  switch (imm)
  {
  case 0x341:
    return &cpu.csr.mepc;
  case 0x342:
    return &cpu.csr.mcause;
  case 0x300:
    return &cpu.csr.mstatus;
  case 0x305:
    return &cpu.csr.mtvec;
  default:
    panic("Unknown csr");
    break;
  }
}
#define CSR(i) (*csr_reg(i))

static int decode_exec(Decode *s)
{
  s->dnpc = s->snpc; // 默认下一条PC=顺序执行PC(先假定不跳转)

#define INSTPAT_INST(s) ((s)->isa.inst)// 取当前指令字(32-bit)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}

  INSTPAT_START();

  // ====== HOT instructions first (ordered by frequency) ======

  // I-type ALU: addi is the single most frequent instruction
  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = src1 + imm );

  // I-type loads: lw is very frequent
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr(src1 + imm, 4));

  // R-type ALU: sub must be before add (more specific funct7=0100000)
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd) = src1 - src2 );
  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd) = src1 + src2 );

  // S-type stores: sw very frequent (framebuffer writes)
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));

  // Branches: beq/bne most common
  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, s->dnpc = (src1 == src2) ? s->pc + imm : s->dnpc );
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, s->dnpc = (src1 != src2) ? s->pc + imm : s->dnpc );

  // Jumps: jal/jalr very frequent (function calls/returns)
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, R(rd) = s->pc + 4; s->dnpc = s->pc + imm;
  #ifdef CONFIG_FTRACE
  if (rd == 1) ftrace_call(s->pc, s->dnpc);
  #endif
  );
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, R(rd) = s->pc + 4; s->dnpc = (src1 + imm) & ~1;
  #ifdef CONFIG_FTRACE
  {
    int rs1_num = (s->isa.inst >> 15) & 0x1f;
    if (rd == 1) ftrace_call(s->pc, s->dnpc);
    else if (rd == 0 && rs1_num == 1 && imm == 0) ftrace_ret(s->pc, s->dnpc);
  }
  #endif
  );

  // U-type: lui/auipc for address construction
  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui    , U, R(rd) = imm  );
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);

  // Shifts I-type: slli/srli common for address calc
  INSTPAT("0000000 ????? ????? 001 ????? 00100 11", slli   , I, R(rd) = src1 << BITS(imm, 4, 0)  );
  INSTPAT("0000000 ????? ????? 101 ????? 00100 11", srli   , I, R(rd) = src1 >> BITS(imm, 4, 0)  );

  // M-extension: mul frequent in video test inner loop
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul    , R, R(rd) = my_mul(src1, src2) );

  // ====== Medium-frequency instructions ======

  // Other branches
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, s->dnpc = ((int32_t)src1 < (int32_t)src2) ? s->pc + imm : s->dnpc );
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, s->dnpc = ((int32_t)src1 >= (int32_t)src2) ? s->pc + imm : s->dnpc );
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B, s->dnpc = ((src1 < src2) ? s->pc + imm : s->dnpc ) );
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, s->dnpc = (src1 >= src2) ? s->pc + imm : s->dnpc );

  // Bitwise I-type
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & imm );
  INSTPAT("??????? ????? ????? 110 ????? 00100 11", ori    , I, R(rd) = src1 | imm );
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm );

  // Bitwise R-type
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd) = src1 & src2 );
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd) = src1 | src2 );
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd) = src1 ^ src2 );

  // Comparisons
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, R(rd) = (src1 < imm));
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , R, R(rd) = ((int32_t)src1 < (int32_t)src2) );
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, R(rd) = (src1 < src2)  );

  // Shifts R-type
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , R, R(rd) = src1 << BITS(src2, 4, 0)  );
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl    , R, R(rd) = src1 >> BITS(src2, 4, 0)  );

  // srai before srli (more specific funct7=0100000)
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, R(rd) = (int32_t)src1 >> BITS(imm, 4, 0) );
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , R, R(rd) = (int32_t)src1 >> BITS(src2, 4, 0) );

  // ====== Rare instructions ======

  // Byte/halfword loads/stores
  INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb     , I, R(rd) = (int32_t)(int8_t)Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd) = (int32_t)(int16_t)Mr(src1 + imm, 2));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd) = (uint16_t)Mr(src1 + imm, 2));
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw(src1 + imm, 2, src2));

  // M-extension other
  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh   , R, R(rd) = my_mulh(src1, src2) );
  INSTPAT("0000001 ????? ????? 011 ????? 01100 11", mulhu  , R, R(rd) = my_mulhu(src1, src2) );
  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div    , R, R(rd) = my_div(src1, src2) );
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu   , R, R(rd) = my_divu(src1, src2) );
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem    , R, R(rd) = my_rem(src1, src2) );
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu   , R, R(rd) = my_remu(src1, src2) );

  // System / privileged (rare paths)
  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10)));
  INSTPAT("0000000 00000 00000 000 00000 11100 11", ecall  , I, s->dnpc = isa_raise_intr(11, s->pc);
  #ifdef  CONFIG_ETRACE
      printf("[E TRACE] mepc=0x%08x mcause=0x%08x mstatus=0x%08x mtvec=0x%08x\n",
      (uint32_t)cpu.csr.mepc, (uint32_t)cpu.csr.mcause,
      (uint32_t)cpu.csr.mstatus, (uint32_t)cpu.csr.mtvec);
  #endif
  );
  INSTPAT("0011000 00010 00000 000 00000 11100 11", mret   , I, s->dnpc = cpu.csr.mepc;
  cpu.csr.mstatus = set_bit(cpu.csr.mstatus, 3, get_bit(cpu.csr.mstatus, 7));
  cpu.csr.mstatus = set_bit(cpu.csr.mstatus, 7, 1);
  cpu.csr.mstatus =  cpu.csr.mstatus & ~(3u << 11);
  );
  INSTPAT("??????? ????? ????? 001 ????? 11100 11", csrrw  , I,  R(rd) = CSR(imm); CSR(imm) = src1);
  INSTPAT("??????? ????? ????? 010 ????? 11100 11", csrrs  , I, \
  { word_t old = CSR(imm); R(rd) = old; CSR(imm) = old | src1; });

  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));
  //TODO 添加更多指令

  INSTPAT_END();

  R(0) = 0;

  return 0;
}


int isa_exec_once(Decode *s)
{
  s->isa.inst = inst_fetch(&s->snpc, 4);
  return decode_exec(s);
}
