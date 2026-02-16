#include <libk/stdio.h>
#include <drivers/serial.h>
#include <drivers/console.h>

#define NANOPRINTF_IMPLEMENTATION
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 0

#include <libk/nanoprintf.h>

void _putchar_callback(int c, void* ctx) 
{
    (void) ctx;
    char ch = (char)c;
    
    serial_write_str(&ch, 1);
    console_write_str(&ch, 1);
}

int printf(const char* format, ...) 
{
    va_list args;
    va_start(args, format);

    int len = npf_vpprintf(_putchar_callback, NULL, format, args);
    va_end(args);
    return len;
}

int snprintf(char* buffer, size_t bufsz, const char* format, ...) 
{
    va_list args;
    va_start(args, format);
    int len = npf_vsnprintf(buffer, bufsz, format, args);
    va_end(args);
    return len;
}

int vsnprintf(char* buffer, size_t bufsz, const char* format, va_list args) 
{
    return npf_vsnprintf(buffer, bufsz, format, args);
}