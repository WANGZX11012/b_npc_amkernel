#include <device/map.h>      // add_mmio_map / new_space
#define MROM_BASE  0x20000000u
#define MROM_SIZE  0x1000u      /* 4KB : 和 SoC 的 SRAM 一致 */
static uint8_t *mrom_space = NULL;

void mrom_init()
{
    mrom_space = new_space(MROM_SIZE);
    memset(mrom_space, 0, MROM_SIZE);
    add_mmio_map("mrom", MROM_BASE, mrom_space, MROM_SIZE, NULL);
}