#include <stdint.h>
#include <stdarg.h>
#include "print.h"

static char digits[] = "01234566789abcdef";

int strlen(char *str)
{
    int count = 0;
    while (*str != '\0') {
        count++;
    }
    return count;
}

void print_char(char c)
{
    *(volatile char*)UART0 = c;
    return;
}

void print_string(char *str)
{
    while(*str){
        print_char(*str++);
    }
    return;
}

// TODO: implement printint. will expand to different base and size later
void printint(long long num, int base)
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
    return;
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
                case '\0':
                    print_string("Error format specifier followed by null");
                    terminate = 1;
                    break;
                case 'd':
                    int num = va_arg(args, int);
                    printint(num, 10);
                    *fmt++;
                    break;
                case 's':
                    char *str = va_arg(args, char*);
                    print_string(str);
                    *fmt++;
                    break;
                case 'c':
                    char *c = va_arg(args, char*);
                    print_char(c);
                    *fmt++;
                    break;
                default:
                    print_string("unknown specifier");
                    break;
            }
        }
        else {
            print_char(*fmt++);
        }
    }
    va_end(args);
    return;
}