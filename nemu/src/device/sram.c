#include <device/map.h>      // add_mmio_map / new_space
#define SRAM_BASE  0x0f000000u
#define SRAM_SIZE  0x2000u      /* 8KB : 和 SoC 的 SRAM 一致 */
static uint8_t *sram_space = NULL;

void sram_init()
{
    sram_space = new_space(SRAM_SIZE);
    memset(sram_space, 0, SRAM_SIZE);
    add_mmio_map("sram", SRAM_BASE, sram_space, SRAM_SIZE, NULL);
}