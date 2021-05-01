#ifndef LIBC_STUB_H
#define LIBC_STUB_H

#ifdef USE_LIBC_STUB
#include <stddef.h>

#undef strcpy
__attribute__((noinline))
static char *strcpy_(char *to, const char *from)
{
    char cur = 0;
    while ((cur = (*from++)))
        *to++ = cur;
    *to++ = 0;
    // XXX: note `to` returned, non ISO
    return to;
}
#define strcpy strcpy_


#undef memcpy
__attribute__((noinline))
static const void *memcpy_(char *dst, char *src, register long n)
{
    while (n)
    {
        *dst++ = *src++;
        n--;
    }
    // XXX: note `dst` returned, non ISO
    return dst;
}
#define memcpy memcpy_


#undef strcmp
__attribute__((noinline))
__unused static int strcmp_(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
#define strcmp strcmp_


#undef strncmp
__attribute__((noinline))
__unused static int strncmp_(const char *s1, const char *s2, register size_t n)
{
    register unsigned char u1, u2;
    while (n-- > 0)
    {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}
#define strncmp strncmp_


#undef strlen
__attribute__((noinline))
__unused static size_t strlen_(const char *str)
{
    register size_t rv = 0;
    while (*str++)
        rv++;
    return rv;
}
#define strlen strlen_


#undef strnlen
__attribute__((noinline))
__unused static size_t strnlen_(const char *s, register size_t n)
{
    register size_t len = 0;
    while (len < n && s[len] != 0)
        len++;
    return len;
}
#define strnlen strnlen_

#endif // USE_LIBC_STUB

#endif // LIBC_STUB_H
