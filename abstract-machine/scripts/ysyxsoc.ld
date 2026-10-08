ENTRY(_start)

MEMORY {
  mrom (rx)  : ORIGIN = 0x20000000, LENGTH = 4K
  sram (rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}

SECTIONS {
    /* 存放所有可执行机器指令（函数代码、入口代码及编译器生成的辅助指令） */
    .text :{
        *(entry)
        *(.text*)  
        /* 收集剩余代码 */
    } > mrom
     /* > mrom表示放到mrom里面 */

    /* 存放只读常量（const变量、字符串字面量、switch查找表等） */
     .rodata :{
        *(.rodata*)
        . = ALIGN(4);
     } > mrom AT> mrom
     /* AT后面是加载地址 但是重合时可以省略 */

    /* 已初始化 + 运行时可修改的全局/静态变量 */
    .data : {                    /* 定义名为 .data 的输出段 */
        _data_start = .;         /* 记录该段在 SRAM 中的起始地址（VMA） */
        *(.data*)                /* 收集所有输入文件中以 .data 开头的段 */
        *(.sdata*)               /* 收集小数据段（GCC优化：小对象访问更高效） */
        . = ALIGN(4);            /* 将当前位置对齐到4字节边界，防止后续段访问错位 */
        _data_end = .;           /* 记录该段在 SRAM 中的结束地址（VMA） */
    } > sram AT> mrom            /* VMA=sram, LMA=mrom  存在mrom 但访问去sram*/

    _data_lma = LOADADDR(.data); /* 获取 .data 段的加载地址（LMA），即 mrom 中的实际存储位置 */

    /* 零初始化变量区 0 或者没有初值 */
    .bss : {
        _bss_start = .;
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        *(.scommon*)
        . = ALIGN(4);
        _bss_end = .;
    } > sram

    _heap_start    = ALIGN(8);
    _stack_pointer = ALIGN(ORIGIN(sram) + LENGTH(sram), 8); 
    /* 栈顶固定值  栈向下增加 减来开辟空间 堆是相反的*/

}