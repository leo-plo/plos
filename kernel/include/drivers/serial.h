#ifndef SERIAL_H
#define SERIAL_H

int init_serial(void);
int serial_received(void);
char read_serial(void);
int is_transmit_empty(void);
void write_serial(char a);
void log_to_serial(char *string);

#endif // SERIAL_H