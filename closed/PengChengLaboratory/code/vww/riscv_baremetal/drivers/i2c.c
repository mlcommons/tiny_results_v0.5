#include <string.h>
#include <platform.h>
#include <rv_i2c.h>

#define I2C_DRV_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0) /* driver version */

/* Driver Version */
static const DRIVER_VERSION DriverVersion = {
    I2C_API_VERSION,
    I2C_DRV_VERSION
};

/* Driver Capabilities */
static const I2C_CAPABILITIES DriverCapabilities = {
    0  /* supports 10-bit addressing */
};


#ifdef RTE_Drivers_I2C0
/* I2C0 Control Information */
static I2C_CTRL I2C0_Ctrl = { 0 };

/* I2C0 Resources */
static I2C_RESOURCES I2C0_Resources = {
    RV32_I2C0,
    RV32_I2C0_IRQn,
    &I2C0_Ctrl
};
#endif

#ifdef RTE_Drivers_I2C1
/* I2C1 Control Information */
static I2C_CTRL I2C1_Ctrl = { 0 };

/* I2C0 Resources */
static I2C_RESOURCES I2C1_Resources = {
    RV32_I2C1,
    RV32_I2C1_IRQn,
    &I2C1_Ctrl
};
#endif

static DRIVER_VERSION I2C_GetVersion (void)
{
    return DriverVersion;
}

static I2C_CAPABILITIES I2C_GetCapabilities (void)
{
    return DriverCapabilities;
}

static int32_t I2Cx_Initialize (I2C_SignalEvent_t cb_event, I2C_RESOURCES *i2c)
{
    if (i2c->ctrl->flags & I2C_FLAG_INIT) {
        return DRIVER_OK;
    }

    i2c->reg->RX_TL = 0;
    i2c->reg->TX_TL = 0;
    i2c->reg->INTR_MASK = 0;
    i2c->reg->ENABLE = 0;

    /* Reset Run-Time information structure */
    memset (i2c->ctrl, 0x00, sizeof (I2C_CTRL));

    i2c->ctrl->cb_event = cb_event;
    i2c->ctrl->flags    = I2C_FLAG_INIT;

    return DRIVER_OK;
}

static int32_t I2Cx_Uninitialize (I2C_RESOURCES *i2c)
{
    i2c->ctrl->flags = 0;

    return DRIVER_OK;
}

static int32_t I2Cx_PowerControl (POWER_STATE state, I2C_RESOURCES *i2c)
{
    switch (state) {
    case POWER_OFF:
        // Disable SSP IRQ in NVIC
        eu_interrupt_disable(i2c->i2c_irq);

        if (i2c->ctrl->status.busy) {
            /* Master: send STOP to I2C bus */
            if (i2c->reg->CON & I2C_CON_MASTER_Msk) {
                i2c->reg->DATA_CMD = I2C_DATA_CMD_STOP_Msk;
                while (i2c->reg->TXFLR != 0) {}
            }
        }

        // Reset SSP Run-Time Resources
        i2c->ctrl->status.busy             = 0U;
        i2c->ctrl->status.mode             = 0U;
        i2c->ctrl->status.direction        = 0U;
        i2c->ctrl->status.general_call     = 0U;
        i2c->ctrl->status.arbitration_lost = 0U;
        i2c->ctrl->status.bus_error        = 0U;

        i2c->ctrl->stalled = 0U;
        i2c->ctrl->snum    = 0U;

        i2c->reg->ENABLE = 0U;

        break;

    case POWER_FULL:
        if ((i2c->ctrl->flags & I2C_FLAG_INIT)  == 0U) { return DRIVER_ERROR; }
        if ((i2c->ctrl->flags & I2C_FLAG_POWER) != 0U) { return DRIVER_OK; }

        i2c->ctrl->stalled = 0;
        i2c->ctrl->con_aa  = 0;

        /* Enable I2C interrupts */
        eu_interrupt_clear_pending(i2c->i2c_irq);
        eu_interrupt_enable(i2c->i2c_irq);

        i2c->ctrl->flags |= I2C_FLAG_POWER;
        break;

    default:
        return DRIVER_ERROR_UNSUPPORTED;
    }

    return DRIVER_OK;
}

static int32_t I2Cx_MasterTransmit (uint32_t       addr,
                                    const uint8_t *data,
                                    uint32_t       num,
                                    bool           xfer_pending,
                                    I2C_RESOURCES *i2c)
{
    if (!data || !num || (addr > 0x7F)) {
        /* Invalid parameters */
        return DRIVER_ERROR_PARAMETER;
    }

    if (!(i2c->ctrl->flags & I2C_FLAG_SETUP)) {
        /* Driver not yet configured */
        return DRIVER_ERROR;
    }

    if (i2c->ctrl->status.busy || (i2c->ctrl->stalled & I2C_SLAVE)) {
        /* Transfer operation in progress, or Slave stalled */
        return DRIVER_ERROR_BUSY;
    }

    /* Set control variables */
    i2c->ctrl->sla_rw  = addr << 1;
    i2c->ctrl->pending = xfer_pending;
    i2c->ctrl->data    = (uint8_t *)data;
    i2c->ctrl->num     = num;
    i2c->ctrl->cnt     = -1;
  
    /* Update driver status */
    i2c->ctrl->status.busy             = 1;
    i2c->ctrl->status.mode             = 1;
    i2c->ctrl->status.direction        = 0;
    i2c->ctrl->status.arbitration_lost = 0;
    i2c->ctrl->status.bus_error        = 0;

    i2c->reg->TAR = addr;
    i2c->reg->ENABLE = 1U;
    /* Unmask the Tx interrupt */
    i2c->reg->INTR_MASK |= I2C_INTR_MASK_M_TX_EMPTY_Msk |
                           I2C_INTR_MASK_M_TX_OVER_Msk  |
                           I2C_INTR_MASK_M_TX_ABRT_Msk;

    return DRIVER_OK;
}

static int32_t I2Cx_MasterReceive (uint32_t       addr,
                                   uint8_t       *data,
                                   uint32_t       num,
                                   bool           xfer_pending,
                                   I2C_RESOURCES *i2c)
{
    if (!data || !num || (addr > 0x7F)) {
        /* Invalid parameters */ 
        return DRIVER_ERROR_PARAMETER;
    }

    if (!(i2c->ctrl->flags & I2C_FLAG_SETUP)) {
        /* Driver not yet configured */
        return DRIVER_ERROR;
    }

    if (i2c->ctrl->status.busy || (i2c->ctrl->stalled & I2C_SLAVE)) {
        /* Transfer operation in progress, or Slave stalled */
        return DRIVER_ERROR_BUSY;
    }
  
    /* Set control variables */
    i2c->ctrl->sla_rw  = (addr << 1) | 0x01;
    i2c->ctrl->pending = xfer_pending;
    i2c->ctrl->data    = data;
    i2c->ctrl->num     = num;
    i2c->ctrl->cnt     = -1;

    /* Update driver status */
    i2c->ctrl->status.busy             = 1;
    i2c->ctrl->status.mode             = 1;
    i2c->ctrl->status.direction        = 0;
    i2c->ctrl->status.arbitration_lost = 0;
    i2c->ctrl->status.bus_error        = 0;

    i2c->reg->TAR = addr;
    i2c->reg->RX_TL = 0;
    i2c->reg->ENABLE = 1U;

    /* Unmask the corresponding interrupts */
    i2c->reg->INTR_MASK = I2C_INTR_MASK_M_RX_FULL_Msk |
                          I2C_INTR_MASK_M_RX_OVER_Msk |
                          I2C_INTR_MASK_M_RX_UNDER_Msk;

    /* Send a read request */
    i2c->reg->DATA_CMD = I2C_DATA_CMD_CMD_Msk;

    return DRIVER_OK;
}

static int32_t I2Cx_SlaveTransmit (const uint8_t *data,
                                   uint32_t       num,
                                   I2C_RESOURCES *i2c)
{
    if (!data || !num) {
        /* Invalid parameters */
        return DRIVER_ERROR_PARAMETER;
    }

    if (i2c->ctrl->status.busy || (i2c->ctrl->stalled & (I2C_MASTER | I2C_SLAVE_RX))) {
        /* Transfer operation in progress, Master stalled or Slave receive stalled */
        return DRIVER_ERROR_BUSY;
    }

    /* Set control variables */
    i2c->ctrl->flags &= ~I2C_FLAG_SLAVE_RX;
    i2c->ctrl->sdata  = (uint8_t *)data;
    i2c->ctrl->snum   = num;
    i2c->ctrl->cnt    = -1;

    /* Update driver status */
    i2c->ctrl->status.general_call = 0;
    i2c->ctrl->status.bus_error    = 0;
    i2c->reg->ENABLE = 1U;

    /* Unmask the corresponding interrupts */
    i2c->reg->INTR_MASK = I2C_INTR_MASK_M_RX_DONE_Msk |
                          I2C_INTR_MASK_M_RD_REQ_Msk  |
                          I2C_INTR_MASK_M_TX_ABRT_Msk |
                          I2C_INTR_MASK_M_TX_OVER_Msk;
  
    return DRIVER_OK;
}

static int32_t I2Cx_SlaveReceive (uint8_t       *data,
                                  uint32_t       num,
                                  I2C_RESOURCES *i2c)
{
    if (!data || !num) {
        /* Invalid parameters */ 
        return DRIVER_ERROR_PARAMETER;
    }

    if (i2c->ctrl->status.busy || (i2c->ctrl->stalled & (I2C_MASTER | I2C_SLAVE_TX))) {
        /* Transfer operation in progress, Master stalled or Slave transmit stalled */
        return DRIVER_ERROR_BUSY;
    }

    /* Set control variables */
    i2c->ctrl->flags |= I2C_FLAG_SLAVE_RX;
    i2c->ctrl->sdata  = data;
    i2c->ctrl->snum   = num;
    i2c->ctrl->cnt    = -1;

    /* Update driver status */
    i2c->ctrl->status.general_call = 0;
    i2c->ctrl->status.bus_error    = 0;
    i2c->reg->ENABLE = 1U;
  
    /* Unmask the corresponding interrupt */
    i2c->reg->INTR_MASK |= I2C_INTR_MASK_M_RX_FULL_Msk |
                           I2C_INTR_MASK_M_RX_OVER_Msk  |
                           I2C_INTR_MASK_M_RX_UNDER_Msk;

    return DRIVER_OK;
}

/**
  \fn          int32_t I2Cx_GetDataCount (I2C_RESOURCES *i2c)
  \brief       Get transferred data count.
  \return      number of data bytes transferred; -1 when Slave is not addressed by Master
*/
static int32_t I2Cx_GetDataCount (I2C_RESOURCES *i2c)
{
    return (i2c->ctrl->cnt);
}

static int32_t I2Cx_Control (uint32_t control, uint32_t arg, I2C_RESOURCES *i2c)
{
    uint32_t cntl, hcnt, lcnt;

    switch (control) {
    case I2C_OWN_ADDRESS:
        /* Set Own Slave Address */
        i2c->reg->SAR = arg & 0x7F;
        i2c->reg->CON = 0;
        break;

    case I2C_BUS_SPEED:
        /* Set Bus Speed */
        cntl = i2c->reg->CON & ~I2C_CON_SPEED_Msk;

        switch (arg) {
        case I2C_BUS_SPEED_HIGH:
            /* High-speed Mode (3.4MHz) */
            cntl |= IC_CON_SPD_HS;
            hcnt = (IC_CLK * MIN_HS_SCL_HIGHTIME) / NANO_TO_MICRO;
            i2c->reg->HS_SCL_HCNT = hcnt;
            lcnt = (IC_CLK * MIN_HS_SCL_LOWTIME) / NANO_TO_MICRO;
            i2c->reg->HS_SCL_LCNT = lcnt;
            break;

        case I2C_BUS_SPEED_STANDARD:
            /* Standard-mode (100kHz) */
            cntl |= IC_CON_SPD_SS;
            hcnt = (IC_CLK * MIN_SS_SCL_HIGHTIME) / NANO_TO_MICRO;
            i2c->reg->SS_SCL_HCNT = hcnt;
            lcnt = (IC_CLK * MIN_SS_SCL_LOWTIME) / NANO_TO_MICRO;
            i2c->reg->SS_SCL_LCNT = lcnt;
            break;

        case I2C_BUS_SPEED_FAST:
            /* Fast-mode     (400kHz) */
        default:
            cntl |= IC_CON_SPD_FS;
            hcnt = (IC_CLK * MIN_FS_SCL_HIGHTIME) / NANO_TO_MICRO;
            i2c->reg->FS_SCL_HCNT = hcnt;
            lcnt = (IC_CLK * MIN_FS_SCL_LOWTIME) / NANO_TO_MICRO;
            i2c->reg->FS_SCL_LCNT = lcnt;
            break;
        }

        i2c->reg->INTR_MASK = 0;
        i2c->reg->CON = cntl | I2C_CON_MASTER_Msk | I2C_CON_SLAVE_DISABLE_Msk;
        /* Speed configured, I2C Master active */
        i2c->ctrl->flags |= I2C_FLAG_SETUP;
        break;

    case I2C_BUS_CLEAR:
        /* Execute Bus clear */
        eu_interrupt_clear_pending(i2c->i2c_irq);
        eu_interrupt_enable(i2c->i2c_irq);

        break;

    case I2C_ABORT_TRANSFER:
        /* Abort Master/Slave transfer */
        eu_interrupt_disable(i2c->i2c_irq);

        i2c->ctrl->status.busy = 0;
        i2c->ctrl->stalled = 0;
        i2c->ctrl->snum    = 0;
        /* Master: send STOP to I2C bus           */
        if (i2c->reg->CON & I2C_CON_MASTER_Msk) { // Master
            i2c->reg->DATA_CMD = I2C_DATA_CMD_STOP_Msk;
            while (i2c->reg->TXFLR != 0) {}
        }

        i2c->reg->INTR_MASK = 0;
        eu_interrupt_clear_pending(i2c->i2c_irq);
        eu_interrupt_enable(i2c->i2c_irq);

        break;
    default:
        return DRIVER_ERROR_UNSUPPORTED;
    }

    return DRIVER_OK;
}

static I2C_STATUS I2Cx_GetStatus (I2C_RESOURCES *i2c)
{
    return (i2c->ctrl->status);
}

static uint32_t read_clear_intrbits(I2C_RESOURCES *i2c)
{
    uint32_t stat;
    uint32_t read;

    stat = i2c->reg->INTR_STAT;

    if (stat & I2C_INTR_MASK_M_RX_UNDER_Msk)
        read = i2c->reg->CLR_RX_UNDER;
    if (stat & I2C_INTR_MASK_M_RX_OVER_Msk)
        read = i2c->reg->CLR_RX_OVER;
    if (stat & I2C_INTR_MASK_M_TX_OVER_Msk)
        read = i2c->reg->CLR_TX_OVER;
    if (stat & I2C_INTR_MASK_M_RD_REQ_Msk)
        read = i2c->reg->CLR_RD_REQ;
    if (stat & I2C_INTR_MASK_M_TX_ABRT_Msk)
        read = i2c->reg->CLR_TX_ABRT;
    if (stat & I2C_INTR_MASK_M_RX_DONE_Msk)
        read = i2c->reg->CLR_RX_DONE;
    if (stat & I2C_INTR_MASK_M_ACTIVITY_Msk)
        read = i2c->reg->CLR_ACTIVITY;
    if (stat & I2C_INTR_MASK_M_STOP_DET_Msk)
        read = i2c->reg->CLR_STOP_DET;
    if (stat & I2C_INTR_MASK_M_START_DET_Msk)
        read = i2c->reg->CLR_START_DET;
    if (stat & I2C_INTR_MASK_M_GEN_CALL_Msk)
        read = i2c->reg->CLR_GEN_CALL;

    return stat;
}

static uint32_t I2Cx_MasterHandler (I2C_RESOURCES *i2c)
{
    uint32_t event  = 0;
    uint32_t stat;

    stat = read_clear_intrbits(i2c);
    if (stat & I2C_INTR_MASK_M_TX_ABRT_Msk) {
        event = I2C_EVENT_TRANSFER_INCOMPLETE;
        i2c->ctrl->status.busy = 0;
        i2c->reg->ENABLE = 0;
        i2c->reg->INTR_MASK = 0;
    } else if (stat & I2C_INTR_STAT_R_TX_EMPTY_Msk) { // Tx
        /* Data transmitted, ACK received */
        i2c->ctrl->cnt++;
    
        /* Send a byte */
        i2c->reg->DATA_CMD = i2c->ctrl->data[i2c->ctrl->cnt];
     
        if (i2c->ctrl->cnt >= (i2c->ctrl->num - 1)) {
            while (i2c->reg->TXFLR != 0 || i2c->reg->RXFLR !=0) {}
            event = I2C_EVENT_TRANSFER_DONE;
            i2c->reg->ENABLE = 0;
            i2c->ctrl->status.busy = 0;

            i2c->reg->INTR_MASK &= ~(I2C_INTR_MASK_M_TX_EMPTY_Msk |
                                     I2C_INTR_MASK_M_TX_OVER_Msk  |
                                     I2C_INTR_MASK_M_TX_ABRT_Msk);
        }
    } else if (stat & I2C_INTR_STAT_R_RX_FULL_Msk) { // Rx
        i2c->ctrl->cnt++;
        /* Data received, ACK returned */
        i2c->ctrl->data[i2c->ctrl->cnt] = i2c->reg->DATA_CMD;

        if (i2c->ctrl->cnt >= (i2c->ctrl->num - 1)) {
            while (i2c->reg->TXFLR != 0 || i2c->reg->RXFLR !=0) {}
            event = I2C_EVENT_TRANSFER_DONE;
            i2c->reg->ENABLE = 0;
            i2c->ctrl->status.busy = 0;
            i2c->reg->INTR_MASK &= ~(I2C_INTR_MASK_M_RX_FULL_Msk |
                                     I2C_INTR_MASK_M_RX_OVER_Msk |
                                     I2C_INTR_MASK_M_RX_UNDER_Msk);
        } else {
            /* Send the next read request */
            i2c->reg->DATA_CMD = I2C_DATA_CMD_CMD_Msk;
        }
    }

    return (event);
}

static uint32_t read_clear_intrbits_slave(I2C_RESOURCES *i2c)
{
    uint32_t stat;
    uint32_t read;

    stat = i2c->reg->INTR_STAT;

    if (stat & I2C_INTR_MASK_M_TX_ABRT_Msk)
        read = i2c->reg->CLR_TX_ABRT;
    if (stat & I2C_INTR_MASK_M_RX_UNDER_Msk)
        read = i2c->reg->CLR_RX_UNDER;
    if (stat & I2C_INTR_MASK_M_RX_OVER_Msk)
        read = i2c->reg->CLR_RX_OVER;
    if (stat & I2C_INTR_MASK_M_RD_REQ_Msk)
        read = i2c->reg->CLR_RD_REQ;
    if (stat & I2C_INTR_MASK_M_TX_OVER_Msk)
        read = i2c->reg->CLR_TX_OVER;
    if (stat & I2C_INTR_MASK_M_RX_DONE_Msk)
        read = i2c->reg->CLR_RX_DONE;
    if (stat & I2C_INTR_MASK_M_ACTIVITY_Msk)
        read = i2c->reg->CLR_ACTIVITY;
    if (stat & I2C_INTR_MASK_M_STOP_DET_Msk)
        read = i2c->reg->CLR_STOP_DET;
    if (stat & I2C_INTR_MASK_M_START_DET_Msk)
        read = i2c->reg->CLR_START_DET;
    if (stat & I2C_INTR_MASK_M_GEN_CALL_Msk)
        read = i2c->reg->CLR_GEN_CALL;

    return stat;
}

static uint32_t I2Cx_SlaveHandler (I2C_RESOURCES *i2c)
{
    uint32_t event  = 0;
    uint32_t stat;

    stat = read_clear_intrbits_slave(i2c);

    if (stat & I2C_INTR_MASK_M_TX_ABRT_Msk) {
        event = I2C_EVENT_TRANSFER_INCOMPLETE;
        i2c->ctrl->status.busy = 0;
        i2c->reg->ENABLE = 0;
        i2c->reg->INTR_MASK = 0;
    } else if (stat & I2C_INTR_STAT_R_RD_REQ_Msk) { // Tx
        /* Update the counter */
        i2c->ctrl->cnt++;

        /* Send a byte */
        i2c->reg->DATA_CMD = i2c->ctrl->sdata[i2c->ctrl->cnt];

        if (i2c->ctrl->cnt == (i2c->ctrl->snum-1)) {
            while (i2c->reg->TXFLR != 0 || i2c->reg->RXFLR !=0) {}
            event = I2C_EVENT_TRANSFER_DONE;
            i2c->ctrl->status.busy = 0;
            i2c->reg->ENABLE = 0;
            // Mask the Slave Rx interrupts
            i2c->reg->INTR_MASK &= ~(I2C_INTR_MASK_M_RX_DONE_Msk |
                                     I2C_INTR_MASK_M_RD_REQ_Msk  |
                                     I2C_INTR_MASK_M_TX_ABRT_Msk |
                                     I2C_INTR_MASK_M_TX_OVER_Msk);
        }
    } else if (stat & I2C_INTR_STAT_R_RX_FULL_Msk) { // Rx
        /* Update the counter */
        i2c->ctrl->cnt++;
        /* Date received, read a byte */
        i2c->ctrl->sdata[i2c->ctrl->cnt] = i2c->reg->DATA_CMD;

        if (i2c->ctrl->cnt == (i2c->ctrl->snum-1)) {
            while (i2c->reg->TXFLR != 0 || i2c->reg->RXFLR !=0) {}
            event = I2C_EVENT_TRANSFER_DONE;
            i2c->ctrl->status.busy = 0;
            i2c->reg->ENABLE = 0;
            // Mask the Slave Rx interrupts
            i2c->reg->INTR_MASK &= ~(I2C_INTR_MASK_M_RX_FULL_Msk |
                                     I2C_INTR_MASK_M_RX_OVER_Msk |
                                     I2C_INTR_MASK_M_RX_UNDER_Msk);
        }
    }

    return (event);
}

static void I2Cx_IRQHandler (I2C_RESOURCES *i2c)
{
    uint32_t event;

    if (i2c->reg->CON & I2C_CON_MASTER_Msk) {
        event = I2Cx_MasterHandler (i2c);
    } else {
        event = I2Cx_SlaveHandler (i2c);
    }

    /* Callback event notification */
    if (event && i2c->ctrl->cb_event) {
        i2c->ctrl->cb_event (event);
    }
}


#ifdef RTE_Drivers_I2C0
/* I2C0 Driver wrapper functions */
static int32_t I2C0_Initialize (I2C_SignalEvent_t cb_event)
{
//    MISC_Enable_I2C0();

    return (I2Cx_Initialize (cb_event, &I2C0_Resources));
}
static int32_t I2C0_Uninitialize (void)
{
    int32_t ret;

    ret = I2Cx_Uninitialize (&I2C0_Resources);

    //MISC_Disable_I2C0();

    return ret;
}
static int32_t I2C0_PowerControl (POWER_STATE state)
{
    return (I2Cx_PowerControl (state, &I2C0_Resources));
}
static int32_t I2C0_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return (I2Cx_MasterTransmit (addr, data, num, xfer_pending, &I2C0_Resources));
}
static int32_t I2C0_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return (I2Cx_MasterReceive (addr, data, num, xfer_pending, &I2C0_Resources));
}
static int32_t I2C0_SlaveTransmit (const uint8_t *data, uint32_t num)
{
    return (I2Cx_SlaveTransmit (data, num, &I2C0_Resources));
}
static int32_t I2C0_SlaveReceive (uint8_t *data, uint32_t num)
{
    return (I2Cx_SlaveReceive (data, num, &I2C0_Resources));
}
static int32_t I2C0_GetDataCount (void)
{
    return (I2Cx_GetDataCount (&I2C0_Resources));
}
static int32_t I2C0_Control (uint32_t control, uint32_t arg)
{
    return (I2Cx_Control (control, arg, &I2C0_Resources));
}
static I2C_STATUS I2C0_GetStatus (void)
{
    return (I2Cx_GetStatus (&I2C0_Resources));
}
void I2C0_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_I2C0_IRQn);
    eu_interrupt_clear_pending(RV32_I2C0_IRQn);
    I2Cx_IRQHandler (&I2C0_Resources);
    eu_interrupt_enable(RV32_I2C0_IRQn);
}

/* I2C0 Driver Control Block */
DRIVER_I2C Driver_I2C0 = {
    I2C_GetVersion,
    I2C_GetCapabilities,
    I2C0_Initialize,
    I2C0_Uninitialize,
    I2C0_PowerControl,
    I2C0_MasterTransmit,
    I2C0_MasterReceive,
    I2C0_SlaveTransmit,
    I2C0_SlaveReceive,
    I2C0_GetDataCount,
    I2C0_Control,
    I2C0_GetStatus
};
#endif

#ifdef RTE_Drivers_I2C1
/* I2C1 Driver wrapper functions */
static int32_t I2C1_Initialize (I2C_SignalEvent_t cb_event)
{
    //MISC_Enable_I2C1();

    return (I2Cx_Initialize (cb_event, &I2C1_Resources));
}
static int32_t I2C1_Uninitialize (void)
{
    int32_t ret;

    ret = I2Cx_Uninitialize (&I2C1_Resources);

    //MISC_Disable_I2C1();

    return ret;
}
static int32_t I2C1_PowerControl (POWER_STATE state)
{
    return (I2Cx_PowerControl (state, &I2C1_Resources));
}
static int32_t I2C1_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return (I2Cx_MasterTransmit (addr, data, num, xfer_pending, &I2C1_Resources));
}
static int32_t I2C1_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return (I2Cx_MasterReceive (addr, data, num, xfer_pending, &I2C1_Resources));
}
static int32_t I2C1_SlaveTransmit (const uint8_t *data, uint32_t num)
{
    return (I2Cx_SlaveTransmit (data, num, &I2C1_Resources));
}
static int32_t I2C1_SlaveReceive (uint8_t *data, uint32_t num)
{
    return (I2Cx_SlaveReceive (data, num, &I2C1_Resources));
}
static int32_t I2C1_GetDataCount (void)
{
    return (I2Cx_GetDataCount (&I2C1_Resources));
}
static int32_t I2C1_Control (uint32_t control, uint32_t arg)
{
    return (I2Cx_Control (control, arg, &I2C1_Resources));
}
static I2C_STATUS I2C1_GetStatus (void)
{
    return (I2Cx_GetStatus (&I2C1_Resources));
}
void I2C1_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_I2C1_IRQn);
    eu_interrupt_clear_pending(RV32_I2C1_IRQn);
    I2Cx_IRQHandler (&I2C1_Resources);
    eu_interrupt_enable(RV32_I2C1_IRQn);
}

/* I2C0 Driver Control Block */
DRIVER_I2C Driver_I2C1 = {
    I2C_GetVersion,
    I2C_GetCapabilities,
    I2C1_Initialize,
    I2C1_Uninitialize,
    I2C1_PowerControl,
    I2C1_MasterTransmit,
    I2C1_MasterReceive,
    I2C1_SlaveTransmit,
    I2C1_SlaveReceive,
    I2C1_GetDataCount,
    I2C1_Control,
    I2C1_GetStatus
};
#endif
