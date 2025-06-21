#ifndef __DEBUG__
#define __DEBUG__

#define UART0 0x10000000

void print_char(char c);
void print_string(char *c);
void printf(char *fmt, ...);

#endif