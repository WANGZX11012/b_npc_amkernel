#include <am.h>
#include <klib-macros.h>
#include <klib.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

void putch(char ch) //最终编成一条 sb a0, 0xa00003f8(zero)，其中 a0=ch。
{
  *(volatile uint8_t*)0xa00003f8 = ch; //魔法读写?
}

void halt(int code) //am平台 根据不同的平台 编译出的二进制也不一样 例如rv32的halt就是会变成这个
{
  asm volatile("mv a0, %0; ebreak" : : "r"(code));
  while (1);
}

/* 读一个 32 位 CSR */
#define csrr(reg) ({ uint32_t __t; asm volatile("csrr %0, " #reg : "=r"(__t)); __t; })
/* 64 位 CSR = 高<<32 | 低 */
#define csr64(lo, hi) ( ((uint64_t)csrr(hi) << 32) | (uint64_t)csrr(lo) )

static void put_hex(uint32_t v) 
{
  static const char *h = "0123456789abcdef";
  for (int i = 7; i >= 0; i--) putch(h[(v >> (i*4)) & 0xf]);
}


void _trm_init() __attribute__((visibility("default")));
void _trm_init() 
{
  uint64_t c0 = csr64(mcycle,   mcycleh);
  uint64_t i0 = csr64(minstret, minstreth);

  int ret = main(mainargs);            // ★ microbench 在这里跑

  uint64_t c1 = csr64(mcycle,   mcycleh);
  uint64_t i1 = csr64(minstret, minstreth);

  uint64_t cyc = c1 - c0;
  uint64_t ins = i1 - i0;
  uint32_t cpi = cyc / ins;

  putch('\n'); 
  // 通过CSR打印的 cpi 只是执行main函数期间的
  putch('[');putch('t');putch('r');putch('m');putch(']');
  putch('C'); putch('='); put_hex((uint32_t)cyc);
  putch(' ');  putch('I'); putch('='); put_hex((uint32_t)ins);
  putch(' ');
  putch('C');putch('P');putch('I');putch('=');
  put_hex(cpi);
  putch('\n');

  halt(ret);

}
