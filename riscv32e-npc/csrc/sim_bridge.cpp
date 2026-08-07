#include "sim_bridge.h"

#include "Vtop.h"
#include "Vtop___024root.h"
#include "dpic.h"
#include "npc_device.h"
#include "device/vga.h"
#include "verilated.h"

#include <cstdio>

//这里可以访问电路vtop

static Vtop *top = nullptr;
static bool sim_halted = false;
static int sim_halt_ret = 0;

static bool sim_abort = false;

// 记录最近一次取到的 PC/指令，用于非法指令时输出现场信息
static uint32_t last_pc = 0;
static uint32_t last_inst = 0;

// 由 main.cpp 在每拍取指后调用，更新当前拍的 PC/inst
extern "C" void npc_sim_set_trace(uint32_t pc, uint32_t inst)
{
  last_pc = pc;
  last_inst = inst;
}

extern "C" void npc_sim_mark_halt(int code) 
{
  sim_halted = true;
  sim_halt_ret = code;
}

extern "C" void npc_sim_mark_abort(void)
{
  // 发生非法指令时，打印最近一次记录到的 PC/inst
  std::fprintf(stderr, "NPC abort at 0x%08x INST:0x%08x\n", last_pc, last_inst);
  sim_abort = true;
}

extern "C" bool npc_sim_is_aborted(void)
{
  return sim_abort;
}

extern "C" bool npc_sim_vga_quit(void) { return npc_vga_quit(); }
extern "C" bool npc_sim_vga_was_ready(void) { return vga_was_ready(); }



extern "C" void npc_sim_init(void) 
{
  if (top != nullptr) return;

  top = new Vtop;

  top->clk = 0;
  top->reset = 1;
  top->inst = 0;
  top->eval(); //先重置 相当于main.cpp

  top->clk = 1;
  top->eval();

  top->clk = 0;
  top->reset = 0;
  top->eval();
}

extern "C" void npc_sim_step_once(void) //npc 电路时钟脉冲一次
{
  if (top == nullptr || sim_abort) return;
  if (npc_vga_quit()) { sim_halted = true; sim_halt_ret = 0; return; }
  if (sim_halted) return;

  uint32_t pc = top->pc;
  last_pc   = pc;
  last_inst = pc_read(pc);
  top->inst = last_inst;

  // 打印每周期一次的 PC 和取到的指令（避免在 pc_read 中重复打印）
  // printf("pc_trace: pc=0x%08x inst=0x%08x\n", pc, last_inst);

  top->clk = 1;
  top->eval();

  // Clear the instruction before the falling-edge eval. Architectural state
  // has already been committed on the rising edge; keeping the same load/store
  // on the combinational path during the low phase can trigger a second
  // non-architectural DPI memory access in the same step.
  //下降沿清零
  top->inst = 0;
  top->clk = 0;
  top->eval();
}

extern "C" uint32_t npc_sim_get_pc(void) 
{
  return (top != nullptr) ? top->pc : 0;
}

extern "C" uint32_t npc_sim_get_inst(void) 
{
  return last_inst;
}

extern "C" void npc_sim_get_gprs(uint32_t *gpr)
{
  if (top == nullptr || gpr == nullptr) return;

  gpr[0] = 0;
  for (int i = 1; i < 32; i++) {
    gpr[i] = top->rootp->top__DOT__u_core__DOT__u_regfile__DOT__rf[i];
  }
}

// [MODIFIED] 读取 NPC 的 mcycle (64-bit) 用于 difftest CSR 同步
extern "C" void npc_sim_get_mcycle(uint32_t *lo, uint32_t *hi)
{
  if (top == nullptr || lo == nullptr || hi == nullptr) return;
  uint64_t mcycle = top->rootp->top__DOT__u_core__DOT__u_CSRFile__DOT__mcycle;
  *lo = (uint32_t)(mcycle & 0xFFFFFFFFu);
  *hi = (uint32_t)(mcycle >> 32);
}

extern "C" bool npc_sim_is_halted(void) 
{
  return sim_halted;
}

extern "C" int npc_sim_halt_code(void) 
{
  return sim_halt_ret;
}
