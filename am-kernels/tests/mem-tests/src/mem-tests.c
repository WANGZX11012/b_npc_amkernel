#include <am.h> // 假设包含 halt 等定义

#define TEST_BASE_ADDR  0x0f000000
#define STACK_GUARD 512


static void put_str(const char *s)
{
    while (*s)          /* *s 是当前字符; 字符串末尾的 '\0' 值是 0, 循环自然停 */
        putch(*s++);
}
static void put_hex(uint32_t x)
{
    // 1. 查找表：用 4-bit 值 (0~15) 直接索引对应的十六进制字符
    static const char hex[] = "0123456789abcdef";
    // 2. 打印前缀
    putch('0'); putch('x');
    // 3. 从最高位到最低位，每次取 4 bit（一个十六进制位）
    for (int i = 28; i >= 0; i -= 4)
        putch(hex[(x >> i) & 0xf]);
}
static void put_hex64(uint64_t x)
{
    static const char hex[] = "0123456789abcdef";
    putch('0'); putch('x');
    for (int i = 60; i >= 0; i -= 4)
        putch(hex[(x >> i) & 0xf]);
}

static void error_print(const char *width_name, int addr, uint64_t expected, uint64_t actual)
{
    if (actual != expected)
        {
            put_str("\nFAIL ");
            put_str(width_name);
            putch(' ');
            put_hex(addr);
            putch(' ');
            put_hex64(expected);
            putch(' ');
            put_hex64(actual);
            putch('\n');
            halt(1);
        }
}



static void mem_test(uint32_t start, uint32_t end, int stride,
                     uint32_t mask, const char *width_name) 
{
    int count = (end - start) / stride;   /* 这段内存能放下多少个完整格子
                                             整数除法自动向下取整, 循环不会越过 end */

    // ====== 写入阶段 ======
    for (int i = 0; i < count; i++) 
    {
        uint32_t addr = start + (uint32_t)i * stride;
        uint64_t data = (stride == 8) ? (((uint64_t)addr << 32) | (uint32_t)~addr)
                                      : (uint64_t)(addr & mask);        
        switch (stride) 
        {
            case 1: *(volatile uint8_t  *)addr = (uint8_t )data; break;
            case 2: *(volatile uint16_t *)addr = (uint16_t)data; break;
            case 4: *(volatile uint32_t *)addr = (uint32_t )data; break;
            case 8: *(volatile uint64_t *)addr = (uint64_t )data; break; 
            default: halt(1); // 不支持的宽度
        }
    }

    // ====== 验证阶段 ======
    for (int i = 0; i < count; i++) 
    {
        uint32_t addr = start + (uint32_t)i * stride;
        uint64_t expected = (stride == 8) ? (((uint64_t)addr << 32) | (uint32_t)~addr)
                                          : (uint64_t)(addr & mask);
        uint64_t actual = 0;
        switch (stride)
        {
            case 1: actual = *(volatile uint8_t  *)addr; break;
            case 2: actual = *(volatile uint16_t *)addr; break;
            case 4: actual = *(volatile uint32_t *)addr; break;
            case 8: actual = *(volatile uint64_t *)addr; break;
            default: halt(1);
        }
        error_print(width_name, addr, expected, actual);

   
    }
}

// ====== 主测试入口 ======
void run_mem_tests(void) 
{
    uint32_t start = (uint32_t)heap.start;          /* 堆区起点: bss 之后的第一个可用字节 */
    uint32_t end   = (uint32_t)heap.end - STACK_GUARD;  /* 栈往下留 512 字节不测 */

    put_hex(start); putch(' ');
    put_hex(end);   putch('\n');                    /* 把实际测试范围打出来, 留证据 */

    mem_test(start, end, 1, 0xff,                   "8-bit");
    mem_test(start, end, 2, 0xffff,                 "16-bit");
    mem_test(start, end, 4, 0xffffffff,             "32-bit");
    mem_test((start + 7) & ~7u, end, 8, 0xffffffff, "64-bit");
    put_str("OK\n");
}



int main(const char *args)
{
    run_mem_tests();
    return 0;
}