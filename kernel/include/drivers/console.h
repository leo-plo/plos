#ifndef CONSOLE_H
#define CONSOLE_H

#include <stddef.h>

void console_init();
void console_write_str(const char *str, size_t len);

#endif // CONSOLE_H