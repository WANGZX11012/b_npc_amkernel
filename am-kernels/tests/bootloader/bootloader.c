#include <am.h>
#include <klib.h>

#define TEST_ADDR 0x80100100u   // 防止和0x8000 0000冲突
#define NOP_ADDR 0x80100100u   // 防止和0x8000 0000冲突

#define RET 0x00008067u // ret 指令
#define NOP 0x00000013u // nop 指令

// 目标程序（5 条指令，手工编码）
static const uint32_t target_code[] = {
  0xa0000537,   // lui  a0, 0xa0000
  0x3f850513,   // addi a0, a0, 1016    → a0 = 0xa00003f8 (UART)
  0x04200593,   // addi a1, x0, 0x42    → a1 = 'B'
  0x00b50023,   // sb   a1, 0(a0)       → 输出 B
  0x00000513,   // addi a0, x0, 0       ← 新增: 让 halt 检查通过
  0x00100073,   // ebreak
};

typedef void (*func_t)(void);

int main()
{
    volatile uint32_t *dst = (volatile uint32_t *)NOP_ADDR;
    for(int i = 0; i < (sizeof(target_code)/ 4); i++)
    {
        dst[i] = NOP;
    }
    dst[6] = RET;
    //搬运完NOP 加return
     ((func_t)NOP_ADDR)(); // 触发函数
    
    for(int i = 0; i < (sizeof(target_code)/ 4); i++)
    {
        dst[i] = target_code[i];
    }
    dst[6] = RET;
    asm volatile("fence.i" ::: "memory");   // ← 三个冒号 + memory clobber 所有 "memory" 之前的 Store/Load 必须在汇编指令之前完成
    ((func_t)TEST_ADDR)(); // 触发函数 

    return 0;
}
