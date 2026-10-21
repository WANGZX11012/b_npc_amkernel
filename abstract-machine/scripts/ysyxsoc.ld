ENTRY(_start)
EXTERN(_boot)

MEMORY {
  mrom  (rx)  : ORIGIN = 0x20000000, LENGTH = 4K
  flash (rx)  : ORIGIN = 0x30000000, LENGTH = 16M
  sram  (rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}

SECTIONS {
    /* MROM: 只有 8 字节跳转桩 —— 复位后第一拍就走 */
    .boot : { KEEP(*(.boot)) } > mrom

    /* flash: 程序主体, _start 必须落在 0x30000000 */
    .text : { *(entry) *(.text*) } > flash
    .rodata : { *(.rodata*) . = ALIGN(4); } > flash

    _data_lma = LOADADDR(.data);
    .data : { _data_start = .; *(.data*) *(.sdata*) . = ALIGN(4); _data_end = .; } > sram AT> flash
    .bss : { _bss_start = .; *(.bss*) *(.sbss*) *(COMMON) . = ALIGN(4); _bss_end = .; } > sram

    _heap_start    = ALIGN(8);
    _stack_pointer = ORIGIN(sram) + LENGTH(sram);
}
