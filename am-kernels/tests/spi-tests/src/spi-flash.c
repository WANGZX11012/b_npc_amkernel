#include <am.h>

#define SPI_BASE 0x10001000u
#define REG_TXRX (*(volatile uint32_t *)(SPI_BASE + 0x00))   // 写=发 读=收
#define REG_CTRL (*(volatile uint32_t *)(SPI_BASE + 0x10))
#define REG_DIV  (*(volatile uint32_t *)(SPI_BASE + 0x14))
#define REG_SS   (*(volatile uint32_t *)(SPI_BASE + 0x18))

static void put_hex_32(uint32_t v) {
    static const char *hex = "0123456789abcdef";

    for(int i = 1; i <= 8; i ++)
        putch(hex[(v >> (32 - 4 * i)) & 0xf]);

    putch('\n');
}


uint32_t flash_read(uint32_t addr)
{
    REG_DIV = 0x4; // 保守的值
    REG_SS = 0x1u; //片选flash
    uint32_t cmd_addr = (0x3u << 24) | (addr & 0x00ffffffu); //cmd在高8位 0x3u代表read， addr放在低24位
    REG_TXRX = cmd_addr; // 传输指令和地址
    uint32_t ctrl_val = (32u << 0)     // CHAR_LEN = 32 bits

                      | (0u  << 9)     // Rx_NEG = 1 (上升沿采样, Mode 0)
                      | (0u  << 10)    // Tx_NEG = 0 (下降沿输出)
                      | (0u  << 11)    // LSB = 0 (MSB first)
                      | (0u  << 13)    // ASS = 0 (手动CS)
                      | (1u  << 8);    // GO = 1
    REG_CTRL = ctrl_val;
    while (REG_CTRL & (1u << 8));  // 等待完成
    REG_TXRX = 0x0u; // 写入0 
    REG_CTRL = ctrl_val;

    while (REG_CTRL & (1u << 8));  // 等待完成

    REG_SS = 0x1u; //拉高CS结束事务（ASS=0时必须手动释放）

    uint32_t flash_r_data = REG_TXRX;
    return flash_r_data;
}


int main()
{
    uint32_t got = flash_read(0x10000u);
    put_hex_32(got);
    return 0;
}
