#ifndef __flash_cache_h__
#define __flash_cache_h__
#include <device.h>

typedef struct rv32_flashcache {
	volatile uint32_t  CCR;
	volatile uint32_t  SR;
	volatile uint32_t  IRQMASK;
	volatile uint32_t  IRQSTAT;
	volatile uint32_t  HWPARAMS;
	volatile uint32_t  CSHR;
	volatile uint32_t  CSMR;
	volatile uint32_t  RES[1005];
	volatile uint32_t  PIDR4;
	volatile uint32_t  PIDR5;
	volatile uint32_t  PIDR6;
	volatile uint32_t  PIDR7;
	volatile uint32_t  PIDR0;
	volatile uint32_t  PIDR1;
	volatile uint32_t  PIDR2;
	volatile uint32_t  PIDR3;
	volatile uint32_t  CIDR0;
	volatile uint32_t  CIDR1;
	volatile uint32_t  CIDR2;
	volatile uint32_t  CIDR3;
} rv32_flashcache_t;

#define FLASHCACHE_CCR_EN_Pos                   (0UL)
#define FLASHCACHE_CCR_EN_Msk                   (0x1UL)
#define FLASHCACHE_CCR_INV_REQ_Pos              (1UL)
#define FLASHCACHE_CCR_INV_REQ_Msk              (0x2UL)
#define FLASHCACHE_CCR_POW_REQ_Pos              (2UL)
#define FLASHCACHE_CCR_POW_REQ_Msk              (0x4UL)
#define FLASHCACHE_CCR_SET_MAN_POW_Pos          (3UL)
#define FLASHCACHE_CCR_SET_MAN_POW_Msk          (0x8UL)
#define FLASHCACHE_CCR_SET_MAN_INV_Pos          (5UL)
#define FLASHCACHE_CCR_SET_MAN_INV_Msk          (0x0UL)
#define FLASHCACHE_CCR_SET_PREFETCH_Pos         (5UL)
#define FLASHCACHE_CCR_SET_PREFETCH_Msk         (0x20UL)
#define FLASHCACHE_CCR_STATISTIC_EN_Pos         (6UL)
#define FLASHCACHE_CCR_STATISTIC_EN_Msk         (0x40UL)

#define FLASHCACHE_SR_CS_Pos                    (0UL)
#define FLASHCACHE_SR_CS_Msk                    (0x3UL)
#define FLASHCACHE_SR_INV_STAT_Pos              (2UL)
#define FLASHCACHE_SR_INV_STAT_Msk              (0x4UL)
#define FLASHCACHE_SR_POW_STAT_Pos              (4UL)
#define FLASHCACHE_SR_POW_STAT_Msk              (0x10UL)

#define FLASHCACHE_IRQMASK_POW_ERR_Pos          (0UL)
#define FLASHCACHE_IRQMASK_POW_ERR_Msk          (0x1UL)
#define FLASHCACHE_IRQMASK_MAN_INV_ERR_Pos      (1UL)
#define FLASHCACHE_IRQMASK_MAN_INV_ERR_Msk      (0x2UL)

#define FLASHCACHE_IRQSTAT_POW_ERR_Pos          (0UL)
#define FLASHCACHE_IRQSTAT_POW_ERR_Msk          (0x1UL)
#define FLASHCACHE_IRQSTAT_MAN_INV_ERR_Pos      (1UL)
#define FLASHCACHE_IRQSTAT_MAN_INV_ERR_Msk      (0x2UL)

#define FLASHCACHE_HWPARAMS_AW_Pos              (0UL)
#define FLASHCACHE_HWPARAMS_AW_Msk              (0x1fUL)
#define FLASHCACHE_HWPARAMS_CW_Pos              (5UL)
#define FLASHCACHE_HWPARAMS_CW_Msk              (0x3e0UL)
#define FLASHCACHE_HWPARAMS_CACHE_WAY_Pos       (10UL)
#define FLASHCACHE_HWPARAMS_CACHE_WAY_Msk       (0xc00UL)
#define FLASHCACHE_HWPARAMS_RESET_ALL_REGS_Pos  (12UL)
#define FLASHCACHE_HWPARAMS_RESET_ALL_REGS_Msk  (0x1000UL)
#define FLASHCACHE_HWPARAMS_GEN_STAT_LOGIC_Pos  (13UL)
#define FLASHCACHE_HWPARAMS_GEN_STAT_LOGIC_Msk  (0x2000UL)

#endif
