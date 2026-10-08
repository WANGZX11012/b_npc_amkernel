#include <am.h>


void _trm_init(void) __attribute__((visibility("default"))); //防止不可见
extern char _heap_start;                              
Area heap = { &_heap_start, (void *)0x0f002000 };     

void    putch(char ch)
{
    *(volatile char*)0x10000000 = ch;
    // *(volatile char*)0x30000000 = 1;   // ★ 临时: 故意制造 DECERR, 验完删掉
    //解释成指针（"这是个地址，指向 1 字节"）
    // *解引用 操作这个地址的内容
}

void    halt(int code)
{
    putch(code == 0 ? '0' : 'F');
    putch('\n');
    asm volatile("mv a0, %0; ebreak" : : "r"(code));
    while (1);                /* 兜底 */
}

/* uart16550 上电后发送器不动: 波特率分频寄存器没配置, TX FIFO(16 字节)只进不出,
 * 装满后再打印的字符会被静默丢弃(见 ysyxSoC/perip/uart16550/rtl/uart_tfifo.v 的 overrun)。
 * 这里把分频设成最快(=1), 再收回 DLAB。对应讲义: 不打印换行符也能立刻看到字符。 */
static void uart_init(void)
{
    *(volatile unsigned char *)(0x10000000 + 3) = 0x80;  /* LCR: DLAB=1 */
    *(volatile unsigned char *)(0x10000000 + 0) = 0x10;  /* DLL = 16 (分频低字节) */
    *(volatile unsigned char *)(0x10000000 + 1) = 0x00;  /* DLM = 0 (分频高字节) */
    *(volatile unsigned char *)(0x10000000 + 3) = 0x03;  /* LCR: 8 数据位 1 停止位, DLAB=0 */
}

extern int main(const char *args);

void _trm_init(void) 
{          /* 4. 转接: start.S → main → halt */
    uart_init();
    halt(main(""));
}