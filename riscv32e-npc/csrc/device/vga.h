#ifndef NPC_DEVICE_VGA_H
#define NPC_DEVICE_VGA_H

#include <cstdint>

static constexpr uint32_t VGACTL_ADDR = 0xa0000100u;
static constexpr uint32_t SYNC_ADDR   = 0xa0000104u;
static constexpr uint32_t BLIT_BASE   = 0xa0000108u;

bool     vga_in_range(uint32_t addr);
uint32_t vga_read   (uint32_t addr, int len);
void     vga_write  (uint32_t addr, int len, uint32_t data);
bool     vga_quit   (void);
bool     vga_was_ready(void);

#endif
