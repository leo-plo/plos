#ifndef LIBK_STDIO_H
#define LIBK_STDIO_H

#include <stdarg.h>
#include <stddef.h>

int printf(const char* format, ...);
int snprintf(char* buffer, size_t bufsz, const char* format, ...);
int vsnprintf(char* buffer, size_t bufsz, const char* format, va_list args);

#endif // LIBK_STDIO_H