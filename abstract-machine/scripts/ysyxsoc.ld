ENTRY(_start)

SECTIONS
{
    /* ── 只读区: MROM ── */
    . = 0x20000000;

    .text : {
        *(entry)            /* _start 必须在 0x2000_0000, 所以排最前 */
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    /* ── 可写区: SRAM ── */
    . = ALIGN(4);
    _data_lma = .;          /* .data 初值在 MROM 的存放地址 */

    . = 0x0f000000;         /* 跳到 SRAM */

    .data : AT(_data_lma) /*取变量的值 因为mrom的不可写 */{
        _data_start = .;
        *(.data*)
        *(.sdata*)    
        /* 自动增长 */
        _data_end = .;
    }

    .bss : {
        _bss_start = .;
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        *(.scommon*)
        . = ALIGN(4);        /* 保证 _bss_end 是 4 的倍数 */
        _bss_end = .;
    }
    . = ALIGN(8);
    _heap_start = .;        /* ← 补: 堆从 .bss 之后往上长 */

    /* 栈顶 = SRAM 末尾(0x0f000000 + 8KB); start.S 里 sp 的初值 */
    _stack_pointer = 0x0f002000;
    ASSERT(_bss_end <= _stack_pointer, "SRAM overflow: .data + .bss 超过 8KB!")
}
