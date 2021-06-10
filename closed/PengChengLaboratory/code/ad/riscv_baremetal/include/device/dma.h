#ifndef __dma_h__
#define __dma_h__
#include <device.h>

typedef struct rv32_dma {
    volatile uint32_t MC0;
    volatile uint32_t SAR0;
    volatile uint32_t DAR0;
    volatile uint32_t BC0;
    volatile uint32_t MC1;
    volatile uint32_t SAR1;
    volatile uint32_t DAR1;
    volatile uint32_t BC1;
    volatile uint32_t MC2;
    volatile uint32_t SAR2;
    volatile uint32_t DAR2;
    volatile uint32_t BC2;
    volatile uint32_t MC3;
    volatile uint32_t SAR3;
    volatile uint32_t DAR3;
    volatile uint32_t BC3;
    volatile uint32_t MC4;
    volatile uint32_t SAR4;
    volatile uint32_t DAR4;
    volatile uint32_t BC4;
    volatile uint32_t MC5;
    volatile uint32_t SAR5;
    volatile uint32_t DAR5;
    volatile uint32_t BC5;
    volatile uint32_t RES[40];
    volatile uint32_t CSR;
} rv32_dma_t;

typedef struct _dma_chn_regs {
    volatile uint32_t MC;
    volatile uint32_t SAR;
    volatile uint32_t DAR;
    volatile uint32_t BC;
} rv32_dma_chn_t;

#define CHANNEL_NUM 6

#define DMAC_MCx_RST_Pos            (0UL)
#define DMAC_MCx_RST_Msk            (0x1 << DMAC_MCx_RST_Pos)
#define DMAC_MCx_TR_EN_Pos          (1UL)
#define DMAC_MCx_TR_EN_Msk          (0x1 << DMAC_MCx_TR_EN_Pos)
#define DMAC_MCx_SIZE_Pos           (2UL)
#define DMAC_MCx_SIZE_Msk           (0x3 << DMAC_MCx_SIZE_Pos)
#define DMAC_MCx_SAR_MODE_Pos       (4UL)
#define DMAC_MCx_SAR_MODE_Msk       (0x3 << DMAC_MCx_SAR_MODE_Pos)
#define DMAC_MCx_DAR_MODE_Pos       (6UL)
#define DMAC_MCx_DAR_MODE_Msk       (0x3 << DMAC_MCx_DAR_MODE_Pos)
#define DMAC_MCx_TE_EN_Pos          (8UL)
#define DMAC_MCx_TE_EN_Msk          (0x1 << DMAC_MCx_TE_EN_Pos)
#define DMAC_MCx_TE_Pos             (9UL)
#define DMAC_MCx_TE_Msk             (0x1 << DMAC_MCx_TE_Pos)
#define DMAC_MCx_PE_EN_Pos          (10UL)
#define DMAC_MCx_PE_EN_Msk          (0x1 << DMAC_MCx_PE_EN_Pos)
#define DMAC_MCx_PE_Pos             (11UL)
#define DMAC_MCx_PE_Msk             (0x1 << DMAC_MCx_PE_Pos)
#define DMAC_MCx_CC_EN_Pos          (12UL)
#define DMAC_MCx_CC_EN_Msk          (0x1 << DMAC_MCx_CC_EN_Pos)
#define DMAC_MCx_CC_Pos             (13UL)
#define DMAC_MCx_CC_Msk             (0x1 << DMAC_MCx_CC_Pos)
#define DMAC_MCx_CB_Pos             (14UL)
#define DMAC_MCx_CB_Msk             (0x1 << DMAC_MCx_CB_Pos)
#define DMAC_MCx_CS_Pos             (15UL)
#define DMAC_MCx_CS_Msk             (0x1 << DMAC_MCx_CS_Pos)
#define DMAC_MCx_T_BC_Pos           (16UL)
#define DMAC_MCx_T_BC_Msk           (0x7ff << DMAC_MCx_T_BC_Pos)
#define DMAC_MCx_RA_NUM_Pos         (26UL)
#define DMAC_MCx_RA_NUM_Msk         (0x1f << DMAC_MCx_RA_NUM_Pos)
#define DMAC_MCx_EN_Pos             (31UL)
#define DMAC_MCx_EN_Msk             (0x1 << DMAC_MCx_EN_Pos)

#define DMAC_CSR_TE_INT_Pos         (0UL)
#define DMAC_CSR_TE_INT_Msk         (0x3f << DMAC_CSR_TE_INT_Pos)
#define DMAC_CSR_PE_INT_Pos         (8UL)
#define DMAC_CSR_PE_INT_Msk         (0x3f << DMAC_CSR_PE_INT_Pos)
#define DMAC_CSR_CC_INT_Pos         (16UL)
#define DMAC_CSR_CC_INT_Msk         (0x3f << DMAC_CSR_CC_INT_Pos)
#endif
