#ifndef __gpio_h__
#define __gpio_h__
#include <device.h>

typedef struct rv32_gpio {
	volatile uint32_t  DATA[256];
	volatile uint32_t  DIR;
	volatile uint32_t  IS;
	volatile uint32_t  IBE;
	volatile uint32_t  IEV;
	volatile uint32_t  IE;
	volatile uint32_t  RIS;
	volatile uint32_t  MIS;
	volatile uint32_t  IC;
	volatile uint32_t  AFSEL;
	volatile uint32_t  RES[751];
	volatile uint32_t  PIDR0;
	volatile uint32_t  PIDR1;
	volatile uint32_t  PIDR2;
	volatile uint32_t  PIDR3;
	volatile uint32_t  CIDR0;
	volatile uint32_t  CIDR1;
	volatile uint32_t  CIDR2;
	volatile uint32_t  CIDR3;
} rv32_gpio_t;

#endif
