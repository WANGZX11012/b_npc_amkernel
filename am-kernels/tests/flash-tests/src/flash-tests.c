#include <am.h>
#include <klib-macros.h>

int main(const char *args)
{
    volatile unsigned char *p = (volatile unsigned char *)0x30010000;
    for (int i = 0; i < 4096; i++)
        if (p[i] != (unsigned char)(i * 0x11)) halt(1);
    printf("flash test ok\n");
    halt(0);
}

