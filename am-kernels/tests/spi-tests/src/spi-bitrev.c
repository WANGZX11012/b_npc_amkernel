#include <am.h>
extern void putch(char ch);              // trm.c 里定义的串口输出

#define SPI_BASE 0x10001000u
#define REG_TXRX (*(volatile uint32_t *)(SPI_BASE + 0x00))   // 写=发 读=收
#define REG_CTRL (*(volatile uint32_t *)(SPI_BASE + 0x10))
#define REG_DIV  (*(volatile uint32_t *)(SPI_BASE + 0x14))
#define REG_SS   (*(volatile uint32_t *)(SPI_BASE + 0x18))

// 主机改成下降沿采 MISO
#define CTRL_GO  (0x1u<<13 | 0x1u<<8 | 0x8u)   // CHAR_LEN=8 → 传 8 位


static uint8_t reverse8(uint8_t x) {
  uint8_t r = 0;
  for (int i = 0; i < 8; i++) r = (r << 1) | ((x >> i) & 1);
  return r;
}

static void put_hex(uint8_t v) {
  static const char *hex = "0123456789abcdef";
  putch(hex[(v >> 4) & 0xf]);
  putch(hex[v & 0xf]);
  putch('\n');
}

int main(const char *args) {
  (void)args;
  uint8_t in     = 0xB2;
  uint8_t expect = reverse8(in);

  REG_DIV = 0x4;                          // 分频：SCK 别和系统时钟同频
  REG_SS  = 0x80;                         // 选通 ss(7)；ASS=1 时只在传输期间拉低
  // REG_TXRX = 0x00;
  // REG_CTRL = CTRL_GO;
  // while (REG_CTRL & (1u<<8)) {}
  // uint8_t got = (uint8_t)REG_TXRX;
  // put_hex(got);
  // putch('\n');
  // return 0;

  // 传输 1：把 in 写进 bitrev（此刻 bitrev 只采样存储，不回传）
  REG_TXRX = in;
  REG_CTRL = CTRL_GO;  // GO为1 后硬件自动移位清零
  while (REG_CTRL & (1u << 8)) {}         // 轮询 GO，硬件传完自动清 0

  // 传输 2：发哑元 0x00，bitrev 把上一次锁存的"反转值"放到 miso 上
  REG_TXRX = 0x00;
  REG_CTRL = CTRL_GO;   //再次启动传输   // 有向TXRX写入或者读出数据 以及GO为1的时候 mst才会产生时钟
  while (REG_CTRL & (1u << 8)) {}

  uint8_t got = (uint8_t)REG_TXRX;        // 读 RX = bitrev 回包

  putch('i'); putch('n'); putch('='); put_hex(in);     putch(' ');
  putch('e'); putch('x'); putch('p'); putch('='); put_hex(expect); putch(' ');
  putch('g'); putch('o'); putch('t'); putch('='); put_hex(got);     putch('\n');

  return (got == expect) ? 0 : 1;         // 0=过 1=挂；_trm_init 会 halt() 变 '0'/'F'
}
