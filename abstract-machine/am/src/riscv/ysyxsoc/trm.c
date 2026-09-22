#include <am.h>


void _trm_init(void) __attribute__((visibility("default"))); //防止不可见
extern char _heap_start;                              
Area heap = { &_heap_start, (void *)0x0f002000 };     

void    putch(char ch)
{
    *(volatile char*)0x10000000 = ch;
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

extern int main(const char *args);

void _trm_init(void) 
{          /* 4. 转接: start.S → main → halt */
  halt(main(""));
}