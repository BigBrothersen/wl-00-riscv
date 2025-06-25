#ifndef __DEBUG__
#define __DEBUG__
#include <stdint.h>

// TODO: remove after uart.c is completed
void putchar(char c);
void print_string(char *c);
void printf(char *fmt, ...);
void printint(int64_t num, uint8_t base);
void print_addr(uint64_t addr);
void printint(int64_t num, uint8_t base);
// void print_unsigned_hex(unsigned int n);
#endif