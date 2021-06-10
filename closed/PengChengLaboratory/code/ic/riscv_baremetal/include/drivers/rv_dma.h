#ifndef __rv_dma_h__
#define __rv_dma_h__
#include <stdint.h>
#include <dma.h>

typedef void (*dma_signalevent_t) (uint32_t event);

typedef struct _dma_chn_info {
    uint32_t src;
    uint32_t dst;
    uint32_t size;
    dma_signalevent_t cb_event;
} dma_chn_info_t;

typedef struct _dma_res {
    dma_chn_info_t info;
    rv32_dma_chn_t *reg;
} dma_chn_res_t;

typedef struct _dma_ctrl_res {
    dma_chn_res_t *chn;
    rv32_dma_t *reg;
    uint32_t irq_num;
} dma_ctrl_res_t;

#define DMA_CHANNEL_REG(d,n) ((rv32_dma_chn_t *) (&(d->MC0) + (n * 4U)))

#define STAT_EN_Pos     (0U)
#define STAT_EN_Msk     (1U << STAT_EN_Pos)
#define STAT_BUSY_Pos   (1U)
#define STAT_BUSY_Msk   (1U << STAT_BUSY_Pos)

#define DMA_EVENT_COMPLETE      1
#define DMA_EVENT_PROGRAM_ERR   2
#define DMA_EVENT_TRANSFER_ERR  4

typedef struct _DRIVER_DMAC {
    int32_t (*initialize)(void);
    int32_t (*uninitialize)(void);
    int32_t (*configure)(uint8_t ch, uint32_t src, uint32_t dst,
                      uint32_t sz, uint32_t ctrl, dma_signalevent_t cb_event);
    void (*start_transfer)(uint8_t ch);
    int32_t (*enable)(uint8_t ch);
    int32_t (*disable)(uint8_t ch);
    uint32_t (*get_status)(uint8_t ch);
    uint32_t (*get_count)(uint8_t ch);
} const DRIVER_DMAC;

extern DRIVER_DMAC driver_dma0;
extern DRIVER_DMAC driver_dma1;

#endif
