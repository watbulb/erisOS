#ifndef LIBC_STUB_H
#define LIBC_STUB_H

#ifdef USE_LIBC_STUB
char* strcpy_(char* to, const char* from)
{
    char cur = 0;
    while ((cur = (*from++)))
        *to++ = cur;
    *to++ = 0;
    // XXX: note `to` returned, non ISO
    return to;
}

const void* memcpy_(char* dst, const char* src, unsigned long n)
{
    while (n) { *dst++ = *src++; n--; }
    // XXX: note `dst` returned, non ISO
    return dst;
}

int strcmp_(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

unsigned long strlen_(const char* str)
{
    unsigned long rv = 0;
    while (*str++)
        rv++;
    return rv;
}

#define strcpy strcpy_
#define memcpy memcpy_
#define strcmp strcmp_
#define strlen strlen_
#endif

#endif // LIBC_STUB_H
