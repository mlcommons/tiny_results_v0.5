#ifndef __systick_h__
#define __systick_h__
#include <device.h>

typedef struct rv32_system_tick {
	volatile uint32_t CTRL;
	volatile uint32_t VAL;
	volatile uint32_t RELOAD;
	union {
		volatile uint32_t IS;
		volatile uint32_t IC;
	};
	volatile uint32_t RES[1008];
	volatile uint32_t PIDR4;
	volatile uint32_t PIDR5;
	volatile uint32_t PIDR6;
	volatile uint32_t PIDR7;
	volatile uint32_t PIDR0;
	volatile uint32_t PIDR1;
	volatile uint32_t PIDR2;
	volatile uint32_t PIDR3;
	volatile uint32_t CIDR0;
	volatile uint32_t CIDR1;
	volatile uint32_t CIDR2;
	volatile uint32_t CIDR3;
} rv32_system_tick_t;

#endif
