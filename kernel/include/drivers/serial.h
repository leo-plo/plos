#ifndef SERIAL_H
#define SERIAL_H

#include <stddef.h>

int serial_init(void);
int serial_received(void);
char serial_read(void);
int is_transmit_empty(void);
void serial_write(char a);
void serial_write_str(const char* str, size_t len);

#endif // SERIAL_H