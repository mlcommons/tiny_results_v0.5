#ifndef __wdt_h__
#define __wdt_h__
#include <device.h>

typedef struct rv32_wdt {
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CTRL;
	volatile uint32_t IC;
	volatile uint32_t RIS;
	volatile uint32_t IS;
	volatile uint32_t RES[762];
	volatile uint32_t LOCK;
	volatile uint32_t RES1[243];
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
} rv32_wdt_t;

#define RV32_WDT_CTRL_INTEN_Pos          (0UL)
#define RV32_WDT_CTRL_INTEN_Msk          (0x1UL)
#define RV32_WDT_CTRL_RESEN_Pos          (1UL)
#define RV32_WDT_CTRL_RESEN_Msk          (0x2UL)

#define RV32_WDT_RIS_INT_Pos             (0UL)
#define RV32_WDT_RIS_INT_Msk             (0x1UL)

#define RV32_WDT_IS_INT_Pos              (0UL)
#define RV32_WDT_IS_INT_Msk              (0x1UL)

#endif
