#include <am.h>
#include <stdint.h>

// // RTC 墙钟寄存器基地址（低 32 位在 +0, 高 32 位在 +4）, 返回真实时间 us
// #define RTC_ADDR 0xa0000048u

// ── 活动代码：用 CLINT 的 mtime 实现真实时钟（CLINT 任务要求）──
// clint 在 0xa0000050, mtime 是 64 位只读计数器, 每个仿真时钟周期 +1。
// 软件分两次读 +0(低 32 位)/+4(高 32 位) 组合成 64 位, 再按频率系数换算:
//   真实时间(us) = mtime / CLINT_MHZ    （假定时钟为 CLINT_MHZ MHz）
// 注意: 这是"名义频率下的模拟时间", 不是宿主墙钟, 严格 1s=1s 只有 rtc 能给。
//       想验证 mtime 是否递增, 直接看 uptime->us 持续变大即可。


#define CLINT_ADDR     0x0200BFF8u   // mtime 低32位在 +0, 高32位在 +4
#define CLINT_MTIMECMP 0x02004000u   // mtimecmp 低32位在 +0, 高32位在 +4
#define CLINT_MHZ  10u         // 频率系数: 名义时钟 MHz, 调整它即调整 mtime 的时间尺度
#define CLINT_clk_devide 1    // 当前频率 再除的频率 例如现在是1M 除以5
#define TIMER_INTERVAL 10000000u          // 中断间隔, 单位 = mtime 周期数



// void __am_timer_init() {
// }

// void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
//   uint32_t lo = *(volatile uint32_t *)(RTC_ADDR + 0);
//   uint32_t hi = *(volatile uint32_t *)(RTC_ADDR + 4);
//   uptime->us = ((uint64_t)hi << 32) | lo;
// }

// void __am_timer_rtc(AM_TIMER_RTC_T *rtc) 
// {
//   AM_TIMER_UPTIME_T uptime;
//   __am_timer_uptime(&uptime);
//   uint64_t sec = uptime.us / 1000000;

//   rtc->second = sec % 60;
//   rtc->minute = (sec / 60) % 60;
//   rtc->hour   = (sec / 3600) % 24;
//   rtc->day    = 1;
//   rtc->month  = 6;
//   rtc->year   = 2026;
// }

//  把闹钟往后拨。 装载下一次时钟中断: mtimecmp = mtime + TIMER_INTERVAL
// 每次中断都必须调用: 不重设的话 mtip 恒为 1, mret 恢复 MIE 后立刻再次进入中断, 卡死。
void __am_timer_rearm() {
  // ── 第一组: 读 mtime, 知道"现在几点" ──
  uint32_t lo = *(volatile uint32_t *)(CLINT_ADDR + 0);   // 0xa0000050 mtime[31:0]
  uint32_t hi = *(volatile uint32_t *)(CLINT_ADDR + 4);   // 0xa0000054 mtime[63:32]
  uint64_t next = (((uint64_t)hi << 32) | lo) + TIMER_INTERVAL; // 闹钟往后拨

  // ── 第二组: 写 mtimecmp, 定"下一次闹钟" ──
  // 顺序不能变: 先把高 32 位封顶成全 1, 杜绝中间态误触发中断 半新半旧会有bug？可能 没试过
  *(volatile uint32_t *)(CLINT_MTIMECMP + 4) = 0xffffffffu;           // 0xa000005c 封顶
  *(volatile uint32_t *)(CLINT_MTIMECMP + 0) = (uint32_t)next;         // 0xa0000058 低32位
  *(volatile uint32_t *)(CLINT_MTIMECMP + 4) = (uint32_t)(next >> 32); // 0xa000005c 真高32位
}

void __am_timer_init() {
  __am_timer_rearm();   // 装载第一次(由 ioe.c:36 调用)
}


void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t lo = *(volatile uint32_t *)(CLINT_ADDR + 0);
  uint32_t hi = *(volatile uint32_t *)(CLINT_ADDR + 4);
  uint64_t mtime = ((uint64_t)hi << 32) | lo;
  uptime->us = mtime * CLINT_clk_devide / CLINT_MHZ;   // 周期数 → 微秒（乘系数换算成接近真实时间）
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  AM_TIMER_UPTIME_T uptime;
  __am_timer_uptime(&uptime);
  uint64_t sec = uptime.us  / 1000000;

  rtc->second = sec % 60;
  rtc->minute = (sec / 60) % 60;
  rtc->hour   = (sec / 3600) % 24;
  rtc->day    = 1;
  rtc->month  = 6;
  rtc->year   = 2026;
}
