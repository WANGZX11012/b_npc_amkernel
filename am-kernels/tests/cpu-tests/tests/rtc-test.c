#include <klib.h>
#include <stdint.h>

// #define RTC_LO 0xa0000048u   // uptime 低 32 位（us）
// #define RTC_HI 0xa000004cu   // uptime 高 32 位

// soc的mtime 
#define RTC_LO 0x0200BFF8  
#define RTC_HI 0x0200BFFC  


static inline uint64_t rtc_read(void) {
  uint32_t lo = *(volatile uint32_t *)RTC_LO;
  uint32_t hi = *(volatile uint32_t *)RTC_HI;
  return ((uint64_t)hi << 32) | lo;
}

int main() {
  // 长延时：读两次，差值 = 经过的 us
  uint64_t t0 = rtc_read();
  volatile uint32_t n;
  for (n = 0; n < 200000; n++) ;
  uint64_t t1 = rtc_read();
  printf("RTC long  delta = %d us\n", (int)(uint32_t)(t1 - t0));

  // 短延时：差值应约为长延时的几分之一 → 证明是墙钟在走
  uint64_t a = rtc_read();
  for (n = 0; n < 20000; n++) ;
  uint64_t b = rtc_read();
  printf("RTC short delta = %d us\n", (int)(uint32_t)(b - a));

  return 0;
}
