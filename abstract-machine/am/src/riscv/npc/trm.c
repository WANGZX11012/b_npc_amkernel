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

void _trm_init() __attribute__((visibility("default")));
void _trm_init() 
{
  // uint32_t lo1, lo2;
  // uint32_t hi1, hi2;

  // asm volatile("csrrs %0, mcycle, x0" : "=r"(lo1)); //lo1 = read_csr(mcycle); 
  // asm volatile("csrrs %0, mcycleh, x0" : "=r"(hi1));
  
  int ret = main(mainargs);

  // asm volatile("csrrs %0, mcycle, x0" : "=r"(lo2));
  // asm volatile("csrrs %0, mcycleh, x0" : "=r"(hi2));


  // printf("mcycle before: hi=%d lo=%d\n", hi1, lo1);
  // printf("mcycle after : hi=%d lo=%d\n", hi2, lo2);

  halt(ret);

}
