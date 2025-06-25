#ifndef __DEF__
#define __DEF__
#include <stdint.h>

#define NULL (void *)0X0ULL


// Memory section addresses, refer to kernel.ld for more info
extern uint8_t _stext;
extern uint8_t _etext;
extern uint8_t _sdata;
extern uint8_t _edata;
extern uint8_t _sbss;
extern uint8_t _ebss;
extern uint8_t kstack;
extern uint8_t end;



#endif