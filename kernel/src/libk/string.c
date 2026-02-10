#include <libk/string.h>
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
    uint8_t *restrict pdest = (uint8_t *restrict)dest;
    const uint8_t *restrict psrc = (const uint8_t *restrict)src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;
    
    // 1. Se stiamo scrivendo pochi byte, non vale la pena ottimizzare
    if (n < 8) {
        while (n--) {
            *p++ = (uint8_t)c;
        }
        return s;
    }

    // 2. Allineamento a 8 byte
    // Scriviamo byte singoli finché l'indirizzo 'p' non è divisibile per 8
    while ((uintptr_t)p & 0x7) {
        *p++ = (uint8_t)c;
        n--;
    }

    // 3. Preparazione del pattern a 64 bit
    // Se c = 0xAB, vogliamo che val64 sia 0xABABABABABABABAB
    uint64_t val64 = (uint8_t)c;
    val64 |= val64 << 8;
    val64 |= val64 << 16;
    val64 |= val64 << 32;

    // 4. Scrittura veloce (8 byte alla volta)
    uint64_t *p64 = (uint64_t *)p;
    while (n >= 8) {
        *p64++ = val64;
        n -= 8;
    }

    // 5. Tail (Coda)
    // Scriviamo i byte rimanenti (sono sicuramente meno di 8)
    p = (uint8_t *)p64;
    while (n--) {
        *p++ = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

size_t strlen(const char *s)
{
    size_t length = 0;
    
    if(!s)
    {
        return 0;
    }
    
    while(s[length])
        length++;
    return length;
}

int strcmp(const char *p1, const char *p2)
{
    register const unsigned char *s1 = (const unsigned char *) p1;
    register const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

int strncmp(const char *s1, const char *s2, register size_t n)
{
    register unsigned char u1, u2;

    while (n-- > 0)
    {
        u1 = (unsigned char) *s1++;
        u2 = (unsigned char) *s2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}