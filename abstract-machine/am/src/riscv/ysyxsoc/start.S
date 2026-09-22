.section entry, "ax"   
#只认entry

# 下面这段代码 放到entry a代表搬到内存 x代表可执行 .section代表下面这些东西属于同一段
.global _start
    _start:
        la sp, _stack_pointer 
        # 把stack pointer地址存到 sp 0x2000_0000的第一条指令
                /* ── 搬运 .data: MROM(存放处) → SRAM(运行处) ── */
        la   t0, _data_start        /* t0 = 目的起始 */
        la   t1, _data_end          /* t1 = 目的结束 */
        la   t2, _data_lma          /* t2 = 源起始   */
    1:  /* 搬运 */
        bgeu t0, t1, 2f             /* 目的 >= 结束 ? → 搬完, 跳出 */
        lw   a0, 0(t2)              /* 从 MROM 读一个 4 字节字 */
        sw   a0, 0(t0)              /* 写进 SRAM */
        addi t0, t0, 4              /* 目的地址 +4 */
        addi t2, t2, 4              /* 源地址   +4 */
        j    1b                     /* 跳回 1, 继续循环 */
    2:  /* ← 搬运结束, 接着清零 .bss */
        la   t0, _bss_start         /* t0 = 起始 */
        la   t1, _bss_end           /* t1 = 结束 */
    3:  bgeu t0, t1, 4f             /* 清完了 → 跳出 */
        sw   zero, 0(t0)            /* 把 0 写进去(一次 4 字节) */
        addi t0, t0, 4              /* 前进 4 字节 */
        j    3b                     /* 跳回 3, 继续循环 */
    4:
        call _trm_init
    5:  j 5b                        /* main 返回后停在这里 */
