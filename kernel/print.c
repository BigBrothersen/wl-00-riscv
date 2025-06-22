#include <stdint.h>
#include <stdarg.h>
#include "print.h"
#include "uart.h"

const char *digits = "0123456789abcdef";

uint32_t strlen(char *str)
{
    uint32_t count = 0;
    while (*str != '\0') {
        count++;
    }
    return count;
}

void print_char(char c)
{
    *(volatile char*)UART_0 = c;
}

void print_string(char *str)
{
    while(*str){
        print_char(*str++);
    }
}

void print_addr(uint64_t addr) 
{
    print_string("0x");
    for (int i = 28; i >= 0; i -= 4) {
        int digit = (addr >> i) & 0xF;
        print_char(digits[(addr >> i) & 0xF]);
    }
}

// TODO: implement printint. will expand to different base and size later
void print_uint(uint64_t num, uint8_t base) 
{
    char nums[64]; // larger buffer for 64-bit numbers
    int i = 0;
    do {
        nums[i++] = digits[num % base];
        num /= base;
    } while (num != 0);

    // print in correct order
    while (i > 0) {
        print_char(nums[--i]);
    }
}

void printint(int64_t num, uint8_t base)
{
    char nums[16];
    int i;
    int negative;
    negative = 0;
    if (num < 0){
        negative = 1;
        num = -num;
    }
    i = 0;
    do {
        nums[i++] = digits[num % base];
    } while((num /= base) != 0);
    if (negative) {
        nums[i++] = '-';
    }
    while(--i >= 0) {
        print_char(nums[i]);
    }
}

// TODO: implement printf for booting message and debugging
// TODO: add error handling for each format specifier
void printf(char *fmt, ...)
{
    int terminate = 0;
    va_list args;
    va_start(args, fmt);
    while (*fmt && !terminate){
        if (*fmt == '%'){
            *fmt++;
            switch (*fmt) {
                case '\0':{
                    print_string("Error format specifier followed by null");
                    terminate = 1;
                    break;
                }
                case 'd':{
                    int num = va_arg(args, int);
                    printint(num, 10);
                    *fmt++;
                    break;
                }
                case 'x':{
                    int num = va_arg(args, int) ;
                    printint(num, 16);
                    *fmt++;
                    break;
                }
                case 'p':{
                    char *ptr = va_arg(args, char *);
                    print_addr((int*)ptr);
                    *fmt++;
                    break;
                }
                case 's':{
                    char *str = va_arg(args, char*);
                    print_string(str);
                    *fmt++;
                    break;
                }
                case 'c':{
                    int *c = va_arg(args, int);
                    print_char(c);
                    *fmt++;
                    break;
                }
                default:{
                    print_string("unknown specifier");
                    terminate = 1;
                    break;
                }
            }
        }
        else {
            print_char(*fmt++);
        }
    }
    va_end(args);
}