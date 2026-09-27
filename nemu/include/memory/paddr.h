/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/
#ifdef CONFIG_DIFFTEST_SOC
/* 
* SoC 的物理内存是分散的:
 *     SRAM 0x0f000000 (8KB)  /  UART 0x10000000  /  MROM 0x20000000 (4KB)
 * 和 NEMU 默认的 [0x80000000, 0x88000000) 完全不重叠
 */
#define SOC_WIN_BASE 0x0f000000u        /* 最低: SRAM 基址        */
#define SOC_WIN_SIZE 0x11002000u        /* 覆盖到 0x20002000      */
static inline bool in_soc_win(paddr_t addr) { return addr - SOC_WIN_BASE < SOC_WIN_SIZE; }
#endif

#ifndef __MEMORY_PADDR_H__
#define __MEMORY_PADDR_H__

#include <common.h>

#define PMEM_LEFT  ((paddr_t)CONFIG_MBASE)
#define PMEM_RIGHT ((paddr_t)CONFIG_MBASE + CONFIG_MSIZE - 1)
#define RESET_VECTOR (PMEM_LEFT + CONFIG_PC_RESET_OFFSET)

/* convert the guest physical address in the guest program to host virtual address in NEMU */
uint8_t* guest_to_host(paddr_t paddr);
/* convert the host virtual address in NEMU to guest physical address in the guest program */
paddr_t host_to_guest(uint8_t *haddr);

static inline bool in_pmem(paddr_t addr) 
{
#ifdef CONFIG_DIFFTEST_SOC
  if (in_soc_win(addr)) return true;     
#endif
  return addr - CONFIG_MBASE < CONFIG_MSIZE;
}


word_t paddr_read(paddr_t addr, int len);
void paddr_write(paddr_t addr, int len, word_t data);

#endif
