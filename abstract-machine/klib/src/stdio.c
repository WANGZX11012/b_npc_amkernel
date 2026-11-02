#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *o = out;
  const char *p = fmt;

  while (*p != '\0') 
  {
    if (*p != '%') 
    {
      *o++ = *p++;
      continue;
    }

    p++; // skip '%'
    if (*p == '%') 
    {
      *o++ = '%';
      p++;
      continue;
    }

    if (*p == 'd') 
    {
      int argint = va_arg(ap, int);
      long long v = argint;
      if (v < 0) 
      {
        *o++ = '-';
        v = -v;
      }

      if (v == 0) 
      {
        *o++ = '0';
      } 
      else 
      {
        char buf[32];
        int i = 0;
        while (v) 
        {
          buf[i++] = '0' + (v % 10);
          v /= 10;
        }
        while (i--) 
        {
          *o++ = buf[i];
        }
      }
      p++;
    }
    else if (*p == 's') 
    {
      const char *s = va_arg(ap, const char *);
      if (!s) s = "(null)";
      while (*s) *o++ = *s++;
      p++;
    }
    else if (*p == 'x')
    {
      unsigned int v = va_arg(ap, unsigned int);
      if(v == 0)
      {
        *o++ = '0';
      }
      else
      {
        char buf[32];
        int i = 0;

        while (v)
        {
          int d = v % 16;
          if(d < 10)  buf[i++] = '0' + d;
          else  buf[i++] = 'a' + (d - 10);
          v /= 16;
        }

        while (i--)
        {
          *o++ = buf[i]; //反向输出符合顺序
        }
      }
      p++;
    }
    else if (*p == 'c')
    {
      char ch = (char)va_arg(ap, int);
      *o++ = ch;
      p++;
    }
    else if (*p == 'p')
    {
      unsigned long v = (unsigned long)va_arg(ap, void*);
      *o++ = '0'; *o++ = 'x';
      if(v == 0)
      {
        *o++ = '0';
      }
      else
      {
        char buf[32];
        int i = 0;
        while (v)
        {
          int d = v % 16;
          if(d < 10)  buf[i++] = '0' + d;
          else  buf[i++] = 'a' + (d - 10);
          v /= 16;
        }
        while (i--)
        {
          *o++ = buf[i];
        }
      }
      p++;
    }
    else 
    {
      *o++ = '%';
      if (*p) *o++ = *p++;
    }
  }

  *o = '\0';
  return (int)(o - out);
}

int sprintf(char *out, const char *fmt, ...) 
{
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(out, fmt, ap);
  va_end(ap);
  return ret;
}

int printf(const char *fmt, ...) 
{
  char buf[4096];
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(buf, fmt, ap);
  va_end(ap);
  /* Behavior:
   * - format the string into `buf` via `vsprintf`
   * - then output each byte by calling `putch(ch)`
   * This is the link between libc-style printf and the platform output.
   * Call chain (simplified):
   *   printf -> vsprintf -> for each char: putch(ch)
   */
  for (int i = 0; i < ret; i++) 
  {
    putch(buf[i]);
  }
  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
