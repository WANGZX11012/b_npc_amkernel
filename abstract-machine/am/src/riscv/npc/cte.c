#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;
extern void __am_timer_rearm(void);   // 定义在 timer.c: 每次中断都要重新装载 mtimecmp


Context* __am_irq_handle(Context *c) 
{
  if (user_handler) 
  {
    Event ev = {0};
    switch (c->mcause) 
    {
      case 11:
        if ((uintptr_t)c->GPR1 == (uintptr_t)-1) 
        {
          ev.event = EVENT_YIELD;
        } 
        else 
        {
          ev.event = EVENT_SYSCALL;
        }
        c->mepc += 4;   // ecall 保存的是自身 PC，mret 需 +4 返回下一条
        break;

      case  0x80000007:
        ev.event = EVENT_IRQ_TIMER;
        __am_timer_rearm(); // 往后拨时钟
        break;
      
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) 
{
  Context *c = (Context*)kstack.end - 1; //在这块内核栈的最高地址往下放一个 Context。
  c->mepc = (uintptr_t)entry ; //将来 mret 时，PC 会变成 entry，线程就从 f() 开始跑
  c->pdir = NULL;
  c->mcause = 0x1800;
  c->gpr[10] = (uintptr_t)arg;  // a0 第一个参数放在 a0，也就是 x10。所以 f(void *arg) 以后能拿到参数。
  return c;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() // 查询中断是否开启: 读 mstatus 的 bit3 (MIE)
{
  uint32_t mstatus;
  asm volatile("csrr %0, mstatus" : "=r"(mstatus));   // 读硬件 mstatus
  return (mstatus & 0x8u) != 0;                       // 取 bit3, 非 0 即"开着"
}


void iset(bool enable) // 设置中断 开/关 iset(1) 即开中断 
{
  // mstatus.MIE = bit3 = 0x8
  // 必须用 csrr + csrw: IDU 只译 csrrw/csrrs, 没有 csrc/csrrci
  uint32_t mstatus;   // c变量 作为中间变量 草稿纸
  asm volatile("csrr %0, mstatus" : "=r"(mstatus));   //%0是分配的寄存器 =r表示是输出  输出在前面 如果没有输入 就不用后面那个冒号 下面的就要
  // 把%0自动分配的寄存器的值存给这个临时变量mstatus 也就是读硬件的mstatus 读出来给c这个变量
  
  if (enable) mstatus |=  0x8u;   // MIE <- 1, 开中断 按位
  else        mstatus &= ~0x8u;   // MIE <- 0, 关中断
  asm volatile("csrw mstatus, %0" : : "r"(mstatus));   //写回到硬件的mstatus
}
