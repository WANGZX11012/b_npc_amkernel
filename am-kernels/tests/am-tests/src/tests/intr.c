#include <amtest.h>

Context *simple_trap(Event ev, Context *ctx) //接受一个event 触发原因 和当时寄存器的状态Context
{
  printf("[trap] ev=%d ", ev.event);
  switch(ev.event) 
  {
    case EVENT_IRQ_TIMER:
      putch('t'); putch(' ');  break;
    case EVENT_IRQ_IODEV:
      putch('d'); break;
    case EVENT_YIELD: // 1 是 yield
      putch('y'); putch(' ');  break;
    default:
      panic("Unhandled event"); break;
  }
  return ctx;
}

void hello_intr() 
{
  printf("Hello, AM World @ " __ISA__ "\n");
  printf("  t = timer, d = device, y = yield\n");
  io_read(AM_INPUT_CONFIG);
  iset(1);
  for (int cnt = 0; cnt < 100; cnt++) //取消了while(1)无限循环
  {
    for (volatile int i = 0; i < 100000; i++);
    yield();
  }
}
