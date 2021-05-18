#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdint.h>

int stdio_init(void);
int stdio_getchar(void);
int stdio_putchar(int);

uint32_t get_systicks(void);

#endif /* __SYSTEM_H__ */
