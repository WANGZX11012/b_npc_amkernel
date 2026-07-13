#include <cpu/npc_cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include "itbuf.h"
#include "../../../csrc/sim_bridge.h"

/* pc_read: read instruction word from pmem at given address */
extern uint32_t pc_read(uint32_t addr);
#include <stdio.h>
#include <npc_debug.h>
#include <string.h>

#define MAX_INST_TO_PRINT 10

NPC_CPU_state npc_cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0;
static bool g_print_step = false;

extern uint64_t npc_get_time(void);

static void statistic(void) {
  Log("host time spent = %lu us", g_timer);
  Log("total guest instructions = %lu", g_nr_guest_inst);
  if (g_timer > 0)
    Log("simulation frequency = %lu inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else
    Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void npc_set_state(int state, vaddr_t pc, int halt_ret) 
{
  npc_state.state = state;
  npc_state.halt_pc = pc;
  npc_state.halt_ret = halt_ret;
}

static void npc_sync_cpu_state(void) 
{
  npc_cpu.pc = npc_sim_get_pc();
  npc_sim_get_gprs(npc_cpu.gpr);
}

void npc_exec_once(void) 
{
  if(npc_sim_is_aborted())
  {
    npc_set_state(NPC_ABORT, npc_cpu.pc, -1);
  }

  if (npc_state.state == NPC_END || npc_state.state == NPC_ABORT || npc_state.state == NPC_QUIT) 
  {
    return;
  }

  npc_state.state = NPC_RUNNING;

  uint32_t this_pc = npc_sim_get_pc();
  uint32_t this_inst = pc_read(this_pc);

#ifdef CONFIG_ITRACE
  /* Build logbuf: "0x80000000: 13 05 10 00" */
  Decode s;
  s.pc = this_pc;
  char *p = s.logbuf;
  p += snprintf(p, sizeof(s.logbuf), FMT_WORD ":", s.pc);
  int ilen = 4;
  const uint8_t *inst = (const uint8_t *)&this_inst;
  for (int i = ilen - 1; i >= 0; i --) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  memset(p, ' ', 1);
  p += 1;
  /* Capstone disassembly */
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s.logbuf + sizeof(s.logbuf) - p, (uint64_t)this_pc, (uint8_t *)&this_inst, 4);

#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { printf("%s\n", s.logbuf); log_write("%s\n", s.logbuf); }
#endif
#endif

  npc_sim_step_once();
  npc_sync_cpu_state();
  g_nr_guest_inst++;

#ifdef CONFIG_DIFFTEST
  if (!npc_sim_is_aborted()) {
    if (!difftest_step(this_pc, npc_cpu.pc, this_inst)) {
      return;
    }
  }
#endif

  if (npc_sim_is_aborted())
  {
    npc_set_state(NPC_ABORT, npc_cpu.pc, -1);
    return;
  }

#ifdef CONFIG_ITRACE
  itbuf_p(this_pc, s.logbuf);
  if (g_print_step) puts(s.logbuf);
#endif

  // printf(ANSI_FMT("PC:0x%08x inst:0x%08x\n", ANSI_FG_GREEN), this_pc, this_inst); //注释掉打印指令

  if (g_print_step) 
  {
    printf("pc=0x%08x inst=0x%08x next_pc=0x%08x\n",
       this_pc, this_inst, npc_cpu.pc);
  }

  if (npc_sim_is_halted())
  {
    int halt_ret = npc_sim_halt_code();
    npc_set_state(NPC_END, this_pc, halt_ret);
    printf("npc: program ended at pc = " FMT_WORD ", code = %d, total_inst = %lu\n", this_pc, halt_ret, g_nr_guest_inst);
    return;
  }

  npc_state.state = NPC_STOP;
}

void npc_cpu_exec(uint64_t n) 
{
  if (npc_state.state == NPC_ABORT || /*npc_state.state == NPC_END ||*/ npc_state.state == NPC_QUIT)
  {
    return;//直接退出
  }

  if (npc_state.state == NPC_END) 
  {
    printf(ANSI_FMT("Press Q to quit\n", ANSI_FG_RED));
    return;
  }

  if (n == (uint64_t)-1)
  {
        uint64_t timer_start = npc_get_time();
        while (npc_state.state != NPC_END &&
          npc_state.state != NPC_ABORT &&
          npc_state.state != NPC_QUIT)
        {
            npc_exec_once();
        }
        uint64_t timer_end = npc_get_time();
        g_timer += timer_end - timer_start;

        switch (npc_state.state) {
          case NPC_END:
            Log("npc: %s at pc = " FMT_WORD,
                npc_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
                                          ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED),
                npc_state.halt_pc);
            break;
          case NPC_ABORT:
            Log("npc: " ANSI_FMT("ABORT", ANSI_FG_RED) " at pc = " FMT_WORD, npc_state.halt_pc);
            break;
          default: break;
        }
        statistic();

    // 程序退出了但 VGA 窗口可能还开着，等用户关窗
    printf("[CPU] waiting for VGA window close...\n");
    while (!npc_sim_vga_quit()) { /* vga_quit() 内部 poll SDL 事件 */ }
    printf("[CPU] VGA window closed, exiting\n");
    return;
  }

  for (uint64_t i = 0; i < n; i++) 
  {
    if (npc_state.state == NPC_END || npc_state.state == NPC_ABORT || npc_state.state == NPC_QUIT) 
    {
        printf(ANSI_FMT("Press Q to quit\n", ANSI_FG_RED));
        break;
    }
    npc_exec_once();
  }
}

void assert_fail_msg() {
  fprintf(stderr, "npc-nemu assertion failed\n");
}
