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

// ============================================================================
// 文件: nemu/src/cpu/difftest/ref.c
// 作用: 当 NEMU 被编译为共享库(.so)时, 作为 DiffTest 的 REF(参考模型)
// 
// 整体架构 (优化后, 使用 memcpy 同步内存):
//   NPC (DUT) ──dlopen/dlsym──→ NEMU (.so, 即 REF)
//   
//   初始化:
//     NPC 加载 hex → Verilog 内存 (唯一数据源)
//     NPC pmem_copy_out() → difftest_memcpy(→REF) → NEMU 内存
//     单一数据源, 不重复解析 ✓
//
//   运行:
//     NPC 每周期 → difftest_exec(1) → NEMU 执行 1 条指令
//               → difftest_regcpy(→DUT) → 读回寄存器, 比对
//
// 导出的 API (5 个):
//   difftest_init, difftest_memcpy, difftest_regcpy, difftest_exec, difftest_raise_intr
//   difftest_load_image (npc-nemu dut.c 使用, 加载 hex 到 NEMU 内存)
// ============================================================================

// ── NEMU 核心头文件 ─────────────────────────────────────────────────────────
#include <isa.h>           // CPU_state (cpu.pc, cpu.gpr[]), isa_exec_once()
#include <cpu/cpu.h>       // NEMUTRAP 宏, nemu_state
#include <cpu/decode.h>    // Decode 结构体: pc, snpc, dnpc
#include <difftest-def.h>  // __EXPORT, DIFFTEST_TO_REF, DIFFTEST_TO_DUT
#include <memory/paddr.h>  // guest_to_host(), paddr_write()
#include <common.h>        // nemu_state (NEMU_RUNNING / NEMU_END / ...)
#include <stdio.h>         // fopen, fgets  (difftest_load_image 需要)
#include <stdlib.h>        // strtoul      (difftest_load_image 需要)
#include <string.h>        // strlen, memset (difftest_load_image 需要)

// ============================================================================
// 寄存器传递格式约定
// ============================================================================
// NPC 端用这个结构体传递寄存器:
//   struct RefCPUState { uint32_t pc; uint32_t gpr[32]; uint32_t mcycle_lo; uint32_t mcycle_hi; };
// 它在内存中是连续的 35 个 uint32_t:
//   offset 0  → pc
//   offset 1  → gpr[0] (x0, 硬连线为0)
//   ...
//   offset 32 → gpr[31] (x31/t6)
//   offset 33 → mcycle_lo
//   offset 34 → mcycle_hi
// ============================================================================
enum { IDX_PC = 0, IDX_GPR = 1, IDX_MCYCLE_LO = 33, IDX_MCYCLE_HI = 34 };

// ============================================================================
// difftest_memcpy — 内存批量拷贝 (物理地址 ↔ 宿主缓冲区)
// ============================================================================
// NPC 在初始化时调用此函数, 把 DUT 的内存镜像同步到 REF.
//
// direction 控制方向:
//   DIFFTEST_TO_REF → DUT 的内存数据 写入 REF (NEMU)
//   DIFFTEST_TO_DUT → REF 的内存数据 读给 DUT (NPC)
//
// guest_to_host(addr): 把 NEMU 的物理地址 addr 转换成宿主进程的虚拟地址指针.
//   例如 addr=0x80000000 (RESET_VECTOR) → pmem 数组的偏移 0 处.
// ============================================================================
__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) 
{
  uint8_t *p = (uint8_t *)buf;
  if (direction == DIFFTEST_TO_REF) {
    for (size_t i = 0; i < n; i++) paddr_write(addr + i, 1, p[i]);
  } else {
    for (size_t i = 0; i < n; i++) p[i] = (uint8_t)paddr_read(addr + i, 1);
  }
}


// ============================================================================
// difftest_regcpy — 寄存器批量拷贝 (最核心的 API!)
// ============================================================================
// 这是 DiffTest 中使用最频繁的函数 (每条指令后调用两次).
//
// 参数:
//   dut       → 一个 33 个 uint32_t 的 flat array: [pc, gpr[0..31]]
//   direction → DIFFTEST_TO_REF: 把 NPC 寄存器写入 NEMU
//               DIFFTEST_TO_DUT: 从 NEMU 读取寄存器给 NPC
//
// 调用时机:
//   初始化时: regcpy(→REF)  把 NPC 初始寄存器同步给 NEMU
//   每条指令后: regcpy(→DUT)  NPC 读回 NEMU 执行结果, 和自己的比对
//
// RISC-V 规定 x0 硬连线为 0, 即使被写入非零值也读出来是 0.
// 这里在拷贝后强制清零, 防止 bug 掩盖真实错误.
// ============================================================================
__EXPORT void difftest_regcpy(void *dut, bool direction) 
{
  // 把 void* 当作 uint32_t 数组来访问
  // 布局: r[0]=pc, r[1..32]=gpr[0..31], r[33]=mcycle_lo, r[34]=mcycle_hi
  uint32_t *r = (uint32_t *)dut;

  if (direction == DIFFTEST_TO_REF) 
  {
    // ─── 方向: 写入 REF (NPC → NEMU) ───
    cpu.pc = r[IDX_PC];                 // r[0] = NPC 的 PC
    for (int i = 0; i < 32; i++) 
    {
      cpu.gpr[i] = r[IDX_GPR + i];     // r[1..32] = NPC 的 x0..x31
    }
    cpu.gpr[0] = 0;                     // x0 强制清零 (RISC-V 规范)
    // [MODIFIED] 同步 mcycle 值，确保 csrr mcycle 结果一致
    cpu.csr.mcycle_lo = r[IDX_MCYCLE_LO];
    cpu.csr.mcycle_hi = r[IDX_MCYCLE_HI];
  } 
  else 
  {
    // ─── 方向: 读取 REF (NEMU → NPC) ───
    r[IDX_PC] = cpu.pc;                // r[0] = NEMU 的 PC
    for (int i = 0; i < 32; i++) 
    {
      r[IDX_GPR + i] = cpu.gpr[i];    // r[1..32] = NEMU 的 x0..x31
    }
    r[IDX_GPR] = 0;                    // x0 始终报告为 0
    // [MODIFIED] 同步 mcycle 值
    r[IDX_MCYCLE_LO] = cpu.csr.mcycle_lo;
    r[IDX_MCYCLE_HI] = cpu.csr.mcycle_hi;
  }
}

// ============================================================================
// difftest_exec — 执行 n 条指令
// ============================================================================
// NPC 每周期调用 difftest_exec(1), 让 NEMU (REF) 也执行一条指令.
//
// 为什么不用 cpu_exec(1)?
//   cpu_exec() 是 NEMU 作为独立程序时的主执行循环, 内部有:
//   - g_print_step (si 命令的打印逻辑)
//   - trace_and_difftest (itrace 写入 + 自身 difftest 检查)
//   - device_update (外设更新)
//   NEMU 作为 REF 时不需要这些 —— REF 只负责"安静地执行指令并更新状态".
//   如果调用 cpu_exec() 且 CONFIG_DIFFTEST 被意外打开, 会导致 REF 自己
//   也去做 difftest, 造成无限递归.
//
// 因此这里直接用 isa_exec_once(), 绕过所有调试/跟踪/外设逻辑.
//
// 如何检测 NEMU 已经停止?
//   isa_exec_once → decode_exec → 遇到 ebreak →
//   NEMUTRAP(pc, code) → set_nemu_state(NEMU_END, pc, code) →
//   nemu_state.state 变为 NEMU_END → 循环检测到后 break
// ============================================================================
__EXPORT void difftest_exec(uint64_t n) 
{
  Decode s;  // 译码上下文: pc, snpc(顺序下一条), dnpc(动态下一条), isa.inst
  for (uint64_t i = 0; i < n; i++) 
  {
    // 如果 NEMU 已经停止 (ebreak 或 abort), 不再继续执行
    if (nemu_state.state != NEMU_RUNNING) break;

    s.pc = cpu.pc;       // ① 设定当前 PC
    s.snpc = cpu.pc;     // ② snpc 初始值 = pc (isa_exec_once 里会改成 pc+4)
    isa_exec_once(&s);   // ③ 真正的指令执行! (定义在 src/isa/riscv32/inst.c)
                         //    内部调用 inst_fetch 取指 → decode_exec 译码+执行
    cpu.pc = s.dnpc;     // ④ 更新 NEMU 的 PC (dnpc 可能不等于 snpc, 如跳转指令)
    // mcycle 递增已移除（AM trm.c 不再读取 mcycle）
  }
}

// ============================================================================
// difftest_raise_intr — 中断注入 (预留, 暂不使用)
// ============================================================================
// 预留给将来支持中断/异常时使用. NPC 的 difftest.cpp 当前不调用此函数.
// ============================================================================
__EXPORT void difftest_raise_intr(word_t NO) 
{
  // TODO: 当 NPC 支持中断时, 实现中断注入逻辑
}

// ============================================================================
// difftest_init — 初始化 REF (NEMU)
// ============================================================================
// NPC 在启动时调用此函数一次, 初始化 NEMU 的运行环境.
//
// 关键: 正常 NEMU 作为独立程序时, main() → init_monitor() 会完成所有初始化.
// 但编译为 .so 后 main() 不会被 dlopen 调用, 所以必须在这里手动做初始化.
//
// 初始化顺序:
//   ① init_rand()  — 随机数种子 (某些内存随机化功能需要)
//   ② init_mem()   — 分配 128MB 物理内存空间并清零
//   ③ init_isa()   — 加载内置 dummy 程序 + cpu.pc = RESET_VECTOR (0x80000000)
//                     + 初始化 mstatus = 0x1800
//   ④ nemu_state.state = NEMU_RUNNING — 标记为运行状态
//
//   之后 NPC 会通过 difftest_memcpy(→REF) 把真实程序镜像写入 NEMU 内存,
//   再通过 difftest_regcpy(→REF) 同步真实 PC 和寄存器.
// ============================================================================
__EXPORT void difftest_init(int port) 
{
  // 前置声明 (定义在 NEMU 其他源文件中)
  void init_mem();   // src/memory/paddr.c — 分配物理内存
  void init_rand();  // src/utils/rand.c    — 随机数种子
  void init_map();
  void init_mrom();
  void init_sram();

  init_rand();                          // ① 随机数种子
  init_mem();                           // ② 分配物理内存 (128MB, 从 0x80000000 开始)
  init_isa();                           // ③ ISA 初始化 (加载内置镜像 + 设置 RESET_VECTOR)
  nemu_state.state = NEMU_RUNNING;      // ④ 标记 NEMU 为 "运行中" 状态
  IFDEF(CONFIG_DEVICE,   init_map());
  IFDEF(CONFIG_HAS_MROM, init_mrom());
  IFDEF(CONFIG_HAS_SRAM, init_sram());

}

// ============================================================================// difftest_load_image — 加载 hex 程序 (npc-nemu dut.c 旧接口使用)
// ============================================================================
// npc-nemu 的 dut.c 通过此函数将 hex 文件加载到 NEMU 内存.
// 注意: Verilator NPC (csrc/difftest.cpp) 已改用 difftest_memcpy 方案,
//       不再调用此函数. 但 npc-nemu 的 dut.c 仍需要它.
// ============================================================================
__EXPORT void difftest_load_image(const char *path) 
{
  if (path == NULL || path[0] == '\0') return;

  FILE *fp = fopen(path, "r");
  if (!fp) return;

  char line[512];
  uint32_t cur = 0;  // 当前物理地址

  while (fgets(line, sizeof(line), fp)) {
    char *tok = strtok(line, " \t\r\n");
    while (tok) {
      if (tok[0] == '#') break;  // 注释行
      size_t len = strlen(tok);
      if (len > 0 && tok[len - 1] == ':') {
        tok[len - 1] = '\0';
        // hex 文件使用 "v3.0 hex words addressed" 格式，地址是字索引
        // 需要 <<2 转换为字节地址，再加上物理内存基址 PMEM_LEFT
        cur = ((uint32_t)strtoul(tok, NULL, 16) << 2) + PMEM_LEFT;
      } else {
        char *end = NULL;
        unsigned long v = strtoul(tok, &end, 16);
        if (end != tok && *end == '\0') {
          paddr_write(cur, 4, (uint32_t)v);  // 写入 NEMU 物理内存
          cur += 4;
        }
      }
      tok = strtok(NULL, " \t\r\n");
    }
  }
  fclose(fp);
}