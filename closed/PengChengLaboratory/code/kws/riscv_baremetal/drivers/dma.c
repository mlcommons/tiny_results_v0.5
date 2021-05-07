#include <platform.h>
#include <rv_dma.h>
#include <stddef.h>

#if RTE_Drivers_DMA0
static dma_chn_res_t dma0_chn_res[CHANNEL_NUM];
static dma_ctrl_res_t dma0_ctrl_res= {
    dma0_chn_res,
    RV32_DMA0,
    RV32_DMAC0_IRQn
};
#endif // RTE_Drivers_DMA0

#if RTE_Drivers_DMA1
static dma_chn_res_t dma1_chn_res[CHANNEL_NUM];
static dma_ctrl_res_t dma1_ctrl_res = {
    dma1_chn_res,
    RV32_DMA1,
    RV32_DMAC1_IRQn
};
#endif // RTE_Drivers_DMA0

// Check if the channel is enabled or disabled
static uint32_t dma_chn_get_status(dma_chn_res_t *ch)
{
    uint32_t mc, status;

    status = 0;
    mc = ch->reg->MC;

    if (mc & DMAC_MCx_EN_Msk)
        status |= STAT_EN_Msk;
    if (mc & DMAC_MCx_CB_Msk)
        status |= STAT_BUSY_Msk;

    return status;
}

static uint32_t dma_chn_get_count(dma_chn_res_t *ch)
{
    uint32_t remain;

    remain = ch->reg->BC;

    return ch->info.size - remain;
}

static void dma_chn_reset(dma_chn_res_t *ch)
{
    ch->info.src = 0;
    ch->info.dst = 0;
    ch->info.size = 0;
    ch->info.cb_event = NULL;
    ch->reg->MC = DMAC_MCx_EN_Msk | DMAC_MCx_RST_Msk;
}

static int dma_chn_configure(dma_chn_res_t *ch, uint32_t src, uint32_t dst,
                      uint32_t size, uint32_t control,
                      dma_signalevent_t cb_event)
{
    // Check the size value
    if ((size & 0x3) != 0)
        return -1;

    // Save callback pointer
    ch->info.cb_event = cb_event;

    // Enable
    // Set Source and destination address
    ch->reg->SAR = src;
    ch->reg->DAR = dst;
    ch->reg->BC = size;

    // Save channel information
    ch->info.src = src;
    ch->info.dst = dst;
    ch->info.size = size;

    // Set Mode
    if (dma_chn_get_status(ch))
        control |= DMAC_MCx_EN_Msk;
    ch->reg->MC = control;

    return 0;
}

static void dma_chn_start_trans(dma_chn_res_t *ch)
{
    ch->reg->MC |= DMAC_MCx_CS_Msk;
}

static int dma_chn_enable(dma_chn_res_t *ch)
{
    ch->reg->MC |= DMAC_MCx_EN_Msk;
    return 0;
}

static int dma_chn_disable(dma_chn_res_t *ch)
{
    ch->reg->MC &= ~DMAC_MCx_EN_Msk;
    return 0;
}

static int dma_ctrl_initialize(dma_ctrl_res_t *dmac)
{
    int i;
    rv32_dma_t *dmac_reg = dmac->reg;
    // TODO
    // MISC Enable DMAC

    // Reset all DMA channels
    for (i = 0; i < CHANNEL_NUM; i++) {
        dmac->chn[i].reg = DMA_CHANNEL_REG(dmac_reg,i);
        dma_chn_reset(&dmac->chn[i]);
    }

    // Clear and Enable DMA IRQ
    eu_interrupt_clear_pending(dmac->irq_num);
    eu_interrupt_enable(dmac->irq_num);

    return 0;
}

static int dma_ctrl_uninitialize(dma_ctrl_res_t *dmac)
{
    int i;

    // Disable all DMA channels
    for (i = 0; i < CHANNEL_NUM; i++) {
        dma_chn_disable(&dmac->chn[i]);
    }

    // Disable and Clear DMA IRQ
    eu_interrupt_disable(dmac->irq_num);
    eu_interrupt_clear_pending(dmac->irq_num);

    // TODO
    // MISC Disable DMAC

    return 0;
}

static void generic_dmac_irq_handler(dma_ctrl_res_t *dmac)
{
    int i;
    dma_chn_res_t *chnres;
    uint32_t csr, event;
    uint8_t cc, pe, te;

    csr = dmac->reg->CSR;
    cc = (csr & DMAC_CSR_CC_INT_Msk) >> DMAC_CSR_CC_INT_Pos;
    pe = (csr & DMAC_CSR_PE_INT_Msk) >> DMAC_CSR_PE_INT_Pos;
    te = (csr & DMAC_CSR_TE_INT_Msk) >> DMAC_CSR_TE_INT_Pos;

    for (i = 0; i < CHANNEL_NUM; i++) {
        event = 0;
        chnres = &dmac->chn[i];
        if ((cc >> i) & 0x1) {
            event |= DMA_EVENT_COMPLETE;
            chnres->reg->MC |= DMAC_MCx_CC_Msk;
        }
        if ((pe >> i) & 0x1) {
            event |= DMA_EVENT_PROGRAM_ERR;
            chnres->reg->MC |= DMAC_MCx_PE_Msk;
        }
        if ((te >> i) & 0x1) {
            event |= DMA_EVENT_TRANSFER_ERR;
            chnres->reg->MC |= DMAC_MCx_TE_Msk;
        }
        if (chnres->info.cb_event != NULL)
            chnres->info.cb_event(event);
    }
}

#if RTE_Drivers_DMA0
static int32_t dma0_initialize(void)
{
    return dma_ctrl_initialize(&dma0_ctrl_res);
}

static int32_t dma0_uninitialize(void)
{
    return dma_ctrl_uninitialize(&dma0_ctrl_res);
}

static int32_t dma0_configure(uint8_t ch, uint32_t src, uint32_t dst,
                       uint32_t sz, uint32_t ctrl, dma_signalevent_t cb_event)
{
    return dma_chn_configure(&dma0_ctrl_res.chn[ch], src, dst, sz, ctrl, cb_event);
}

static void dma0_start_transfer(uint8_t ch)
{
    dma_chn_start_trans(&dma0_ctrl_res.chn[ch]);
}

static int32_t dma0_enable(uint8_t ch)
{
    return dma_chn_enable(&dma0_ctrl_res.chn[ch]);
}

static int32_t dma0_disable(uint8_t ch)
{
    return dma_chn_disable(&dma0_ctrl_res.chn[ch]);
}

static uint32_t dma0_get_status(uint8_t ch)
{
    return dma_chn_get_status(&dma0_ctrl_res.chn[ch]);
}

static uint32_t dma0_get_count(uint8_t ch)
{
    return dma_chn_get_count(&dma0_ctrl_res.chn[ch]);
}

void dma0_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_DMAC0_IRQn);
    eu_interrupt_clear_pending(RV32_DMAC0_IRQn);
    generic_dmac_irq_handler(&dma0_ctrl_res);
    eu_interrupt_enable(RV32_DMAC0_IRQn);
}

DRIVER_DMAC driver_dma0 = {
    dma0_initialize,
    dma0_uninitialize,
    dma0_configure,
    dma0_start_transfer,
    dma0_enable,
    dma0_disable,
    dma0_get_status,
    dma0_get_count
};
#endif

#if RTE_Drivers_DMA1
static int32_t dma1_initialize(void)
{
    return dma_ctrl_initialize(&dma1_ctrl_res);
}

static int32_t dma1_uninitialize(void)
{
    return dma_ctrl_uninitialize(&dma1_ctrl_res);
}

static int32_t dma1_configure(uint8_t ch, uint32_t src, uint32_t dst,
                       uint32_t sz, uint32_t ctrl, dma_signalevent_t cb_event)
{
    return dma_chn_configure(&dma1_ctrl_res.chn[ch], src, dst, sz, ctrl, cb_event);
}

static void dma1_start_transfer(uint8_t ch)
{
    return dma_chn_start_trans(&dma1_ctrl_res.chn[ch]);
}

static int32_t dma1_enable(uint8_t ch)
{
    return dma_chn_enable(&dma1_ctrl_res.chn[ch]);
}

static int32_t dma1_disable(uint8_t ch)
{
    return dma_chn_disable(&dma1_ctrl_res.chn[ch]);
}

static uint32_t dma1_get_status(uint8_t ch)
{
    return dma_chn_get_status(&dma1_ctrl_res.chn[ch]);
}

static uint32_t dma1_get_count(uint8_t ch)
{
    return dma_chn_get_count(&dma1_ctrl_res.chn[ch]);
}

void dma1_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_DMAC1_IRQn);
    eu_interrupt_clear_pending(RV32_DMAC1_IRQn);
    generic_dmac_irq_handler(&dma1_ctrl_res);
    eu_interrupt_enable(RV32_DMAC1_IRQn);
}

DRIVER_DMAC driver_dma1 = {
    dma1_initialize,
    dma1_uninitialize,
    dma1_configure,
    dma1_start_transfer,
    dma1_enable,
    dma1_disable,
    dma1_get_status,
    dma1_get_count
};
#endif
