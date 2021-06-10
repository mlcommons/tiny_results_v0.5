#include <string.h>
#include <platform.h>
#include <rv_spi.h>

void SSP0_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP0_GPDMA_Rx_SignalEvent (uint32_t event);

void SSP1_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP1_GPDMA_Rx_SignalEvent (uint32_t event);

void SSP2_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP2_GPDMA_Rx_SignalEvent (uint32_t event);

void SSP3_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP3_GPDMA_Rx_SignalEvent (uint32_t event);

void SSP4_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP4_GPDMA_Rx_SignalEvent (uint32_t event);

void SSP5_GPDMA_Tx_SignalEvent (uint32_t event);
void SSP5_GPDMA_Rx_SignalEvent (uint32_t event);

#define SPI_DRV_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0)     // driver version

// Driver Version
static const DRIVER_VERSION DriverVersion = {
    SPI_API_VERSION,
    SPI_DRV_VERSION
};

// Driver Capabilities
static const SPI_CAPABILITIES DriverCapabilities = {
    0,  // Simplex Mode (Master and Slave)
    1,  // TI Synchronous Serial Interface
    1,  // Microwire Interface
    0   // Signal Mode Fault event: \ref SPI_EVENT_MODE_FAULT
};

#if RTE_Drivers_SSP0
static ssp_info_t          ssp0_info = { 0 };
static ssp_transfer_info_t ssp0_xfer;

static ssp_resources_t ssp0_res = {
    RV32_SPI0,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP0_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP0_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI0_IRQn,  // SSP IRQ number
    &ssp0_info,         // SSP Run-time information
    &ssp0_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP0

#if RTE_Drivers_SSP1
static ssp_info_t          ssp1_info = { 0 };
static ssp_transfer_info_t ssp1_xfer;

static ssp_resources_t ssp1_res = {
    RV32_SPI1,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP1_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP1_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI1_IRQn,  // SSP IRQ number
    &ssp1_info,         // SSP Run-time information
    &ssp1_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP1

#if RTE_Drivers_SSP2
static ssp_info_t          ssp2_info = { 0 };
static ssp_transfer_info_t ssp2_xfer;

static ssp_resources_t ssp2_res = {
    RV32_SPI2,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP2_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP2_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI2_IRQn,  // SSP IRQ number
    &ssp2_info,         // SSP Run-time information
    &ssp2_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP2

#if RTE_Drivers_SSP3
static ssp_info_t          ssp3_info = { 0 };
static ssp_transfer_info_t ssp3_xfer;

static ssp_resources_t ssp3_res = {
    RV32_SPI3,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP3_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP3_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI3_SECIRQn,  // SSP IRQ number
    &ssp3_info,         // SSP Run-time information
    &ssp3_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP3

#if RTE_Drivers_SSP4
static ssp_info_t          ssp4_info = { 0 };
static ssp_transfer_info_t ssp4_xfer;

static ssp_resources_t ssp4_res = {
    RV32_SPI4,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP4_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP4_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI4_SECIRQn,  // SSP IRQ number
    &ssp4_info,         // SSP Run-time information
    &ssp4_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP4

#if RTE_Drivers_SSP5
static ssp_info_t          ssp5_info = { 0 };
static ssp_transfer_info_t ssp5_xfer;

static ssp_resources_t ssp5_res = {
    RV32_SPI5,                // SSP peripheral register interface
    // DMA, TODO: to be enabled
  { 0,                          // Transmit channel enabled
    0,                          // Transmit channel number
    0,                          // Transmit peripheral
    SSP5_GPDMA_Tx_SignalEvent,  // Transmit callback
    0,                          // Receive channel enabled
    0,                          // Receive channel number
    0,                          // Receive peripheral
    SSP5_GPDMA_Rx_SignalEvent   // Receive callback
  },
    RV32_SPI5_SECIRQn,  // SSP IRQ number
    &ssp5_info,         // SSP Run-time information
    &ssp5_xfer          // SSP transfer information
};
#endif // RTE_Drivers_SSP5

// Driver Functions
static DRIVER_VERSION SSPx_GetVersion (void)
{
    return DriverVersion;
}

static SPI_CAPABILITIES SSPx_GetCapabilities (void) {
    return DriverCapabilities;
}

static int32_t SSPx_Initialize (SPI_SignalEvent_t cb_event, ssp_resources_t *ssp) {
  if (ssp->info->state & SSP_INITIALIZED) { return DRIVER_OK; }

  // Initialize SSP Run-Time Resources
  ssp->info->cb_event          = cb_event;
  ssp->info->status.busy       = 0U;
  ssp->info->status.data_lost  = 0U;
  ssp->info->status.mode_fault = 0U;

  // Clear transfer information
  memset(ssp->xfer, 0, sizeof(ssp_transfer_info_t));

  // Configure DMA if it will be used
  //if (ssp->dma.tx_en || ssp->dma.rx_en) { GPDMA_Initialize (); }

  ssp->info->state = SSP_INITIALIZED;   // SSP is initialized

  return DRIVER_OK;
}

static int32_t SSPx_Uninitialize (ssp_resources_t *ssp) {

  // Uninitialize DMA
  //if (ssp->dma.tx_en || ssp->dma.rx_en) { GPDMA_Uninitialize (); }

  ssp->info->state = 0U;                // SSP is uninitialized

  return DRIVER_OK;
}

static int32_t SSPx_PowerControl (POWER_STATE state, ssp_resources_t *ssp) {

  switch (state) {
    case POWER_OFF:
// TODO
        eu_interrupt_disable(ssp->irq_num);

//      if (ssp->info->status.busy) {
 //       // If DMA mode - disable DMA channel
 //       if (ssp->dma.tx_en) { GPDMA_ChannelDisable (ssp->dma.tx_ch); } 
 //       // If DMA mode - disable DMA channel
 //       if (ssp->dma.rx_en) { GPDMA_ChannelDisable (ssp->dma.rx_ch); }
 //     }

      // Reset SSP Run-Time Resources
      ssp->info->status.busy       = 0U;
      ssp->info->status.data_lost  = 0U;
      ssp->info->status.mode_fault = 0U;

      // Clear transfer information
      memset(ssp->xfer, 0, sizeof(ssp_transfer_info_t));

      ssp->info->state &= ~SSP_POWERED; // SSP is not powered
      break;

    case POWER_FULL:
      if ((ssp->info->state & SSP_INITIALIZED) == 0U) { return DRIVER_ERROR; }
      if ((ssp->info->state & SSP_POWERED)     != 0U) { return DRIVER_OK; }

      ssp->reg->IMSC  = 0U;             // Disable SSP interrupts
      ssp->reg->ICR   = 3U;             // Clear SSP interrupts

      // Reset SSP Run-Time Resources
      ssp->info->status.busy       = 0U;
      ssp->info->status.data_lost  = 0U;
      ssp->info->status.mode_fault = 0U;

      ssp->info->state |=  SSP_POWERED; // SSP is powered

      // Enable DMA
      if (ssp->dma.tx_en) { ssp->reg->DMACR |= SPI_DMACR_TXDMAE_Msk; }
      if (ssp->dma.rx_en) { ssp->reg->DMACR |= SPI_DMACR_RXDMAE_Msk; }

      eu_interrupt_clear_pending(ssp->irq_num);
      eu_interrupt_enable(ssp->irq_num);
      break;

    default:
      return DRIVER_ERROR_UNSUPPORTED;
  }

  return DRIVER_OK;
}

static int32_t SSPx_Send (const void *data, uint32_t num, ssp_resources_t *ssp) {
  static uint32_t dummy_data;

  if ((data == NULL) || (num == 0U))        { return DRIVER_ERROR_PARAMETER; }
  if (!(ssp->info->state & SSP_CONFIGURED)) { return DRIVER_ERROR; }
  if (  ssp->info->status.busy)             { return DRIVER_ERROR_BUSY; }
  ssp->info->status.busy       = 1U;
  ssp->info->status.data_lost  = 0U;
  ssp->info->status.mode_fault = 0U;

  ssp->xfer->rx_buf = NULL;
  ssp->xfer->tx_buf = (uint8_t *)data;

  ssp->xfer->num    = num;
  ssp->xfer->rx_cnt = 0U;
  ssp->xfer->tx_cnt = 0U;

  if (ssp->dma.tx_en && ssp->dma.rx_en) {
    // TODO
    //if (GPDMA_ChannelConfigure (ssp->dma.rx_ch,
    //                           (uint32_t)&ssp->reg->DR,
    //                           (uint32_t)&dummy_data,
    //                            num,
    //                            GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
    //                            GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
    //                            GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
    //                            GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
    //                            GPDMA_CH_CONTROL_S                                                |
    //                            GPDMA_CH_CONTROL_D                                                |
    //                            GPDMA_CH_CONTROL_I,
    //                            GPDMA_CH_CONFIG_SRC_PERI(ssp->dma.rx_peri)                        |
    //                            GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_P2M_CTRL_DMA)            |
    //                            GPDMA_CH_CONFIG_IE                                                |
    //                            GPDMA_CH_CONFIG_ITC                                               |
    //                            GPDMA_CH_CONFIG_E,
    //                            ssp->dma.rx_callback) == -1) {
    //  return DRIVER_ERROR;
    //}

    //if (GPDMA_ChannelConfigure (ssp->dma.tx_ch,
    //                           (uint32_t)data,
    //                           (uint32_t)&ssp->reg->DR,
    //                            num,
    //                            GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
    //                            GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
    //                            GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
    //                            GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
    //                            GPDMA_CH_CONTROL_S                                                |
    //                            GPDMA_CH_CONTROL_D                                                |
    //                            GPDMA_CH_CONTROL_SI                                               |
    //                            GPDMA_CH_CONTROL_I,
    //                            GPDMA_CH_CONFIG_DEST_PERI(ssp->dma.tx_peri)                       |
    //                            GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_M2P_CTRL_DMA)            |
    //                            GPDMA_CH_CONFIG_IE                                                |
    //                            GPDMA_CH_CONFIG_ITC                                               |
    //                            GPDMA_CH_CONFIG_E,
    //                            ssp->dma.tx_callback) == -1) {
    //  return DRIVER_ERROR;
    //}
  } else {
    ssp->reg->IMSC = SPI_IMSC_TXIM_Msk | SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk;
  }

  return DRIVER_OK;
}

static int32_t SSPx_Receive (void *data, uint32_t num, ssp_resources_t *ssp) {
  static uint32_t dummy_data;

  if ((data == NULL) || (num == 0U))        { return DRIVER_ERROR_PARAMETER; }
  if (!(ssp->info->state & SSP_CONFIGURED)) { return DRIVER_ERROR; }
  if (  ssp->info->status.busy)             { return DRIVER_ERROR_BUSY; }
  ssp->info->status.busy       = 1U;
  ssp->info->status.data_lost  = 0U;
  ssp->info->status.mode_fault = 0U;

  dummy_data        = ssp->xfer->def_val;

  ssp->xfer->rx_buf = (uint8_t *)data;
  ssp->xfer->tx_buf = NULL;

  ssp->xfer->num    = num;
  ssp->xfer->rx_cnt = 0U;
  ssp->xfer->tx_cnt = 0U;

  if (ssp->dma.tx_en && ssp->dma.rx_en) {
   // if (GPDMA_ChannelConfigure (ssp->dma.rx_ch,
   //                            (uint32_t)&ssp->reg->DR,
   //                            (uint32_t)data,
   //                             num,
   //                             GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
   //                             GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
   //                             GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
   //                             GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
   //                             GPDMA_CH_CONTROL_S                                                |
   //                             GPDMA_CH_CONTROL_D                                                |
   //                             GPDMA_CH_CONTROL_DI                                               |
   //                             GPDMA_CH_CONTROL_I,
   //                             GPDMA_CH_CONFIG_SRC_PERI(ssp->dma.rx_peri)                        |
   //                             GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_P2M_CTRL_DMA)            |
   //                             GPDMA_CH_CONFIG_IE                                                |
   //                             GPDMA_CH_CONFIG_ITC                                               |
   //                             GPDMA_CH_CONFIG_E,
   //                             ssp->dma.rx_callback) == -1) {
   //   return DRIVER_ERROR;
   // }
   // if (GPDMA_ChannelConfigure (ssp->dma.tx_ch,
   //                            (uint32_t)&dummy_data,
   //                            (uint32_t)&ssp->reg->DR,
   //                             num,
   //                             GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
   //                             GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
   //                             GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
   //                             GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
   //                             GPDMA_CH_CONTROL_S                                                |
   //                             GPDMA_CH_CONTROL_D                                                |
   //                             GPDMA_CH_CONTROL_I,
   //                             GPDMA_CH_CONFIG_DEST_PERI(ssp->dma.tx_peri)                       |
   //                             GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_M2P_CTRL_DMA)            |
   //                             GPDMA_CH_CONFIG_IE                                                |
   //                             GPDMA_CH_CONFIG_ITC                                               |
   //                             GPDMA_CH_CONFIG_E,
   //                             ssp->dma.tx_callback) == -1) {
   //   return DRIVER_ERROR;
   // }
  } else {
    ssp->reg->IMSC = SPI_IMSC_TXIM_Msk | SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk;
  }

  return DRIVER_OK;
}

static int32_t SSPx_Transfer (const void *data_out, void *data_in, uint32_t num, ssp_resources_t *ssp) {

  if ((data_out == NULL) || (data_in == NULL) || (num == 0U)) { return DRIVER_ERROR_PARAMETER; }
  if (!(ssp->info->state & SSP_CONFIGURED))                   { return DRIVER_ERROR; }
  if (  ssp->info->status.busy)                               { return DRIVER_ERROR_BUSY; }
  ssp->info->status.busy       = 1U;
  ssp->info->status.data_lost  = 0U;
  ssp->info->status.mode_fault = 0U;

  ssp->xfer->rx_buf = (uint8_t *)data_in;
  ssp->xfer->tx_buf = (uint8_t *)data_out;

  ssp->xfer->num    = num;
  ssp->xfer->rx_cnt = 0U;
  ssp->xfer->tx_cnt = 0U;

  if (ssp->dma.tx_en && ssp->dma.rx_en) {
  //  if (GPDMA_ChannelConfigure (ssp->dma.rx_ch,
  //                             (uint32_t)&ssp->reg->DR,
  //                             (uint32_t)data_in,
  //                              num,
  //                              GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
  //                              GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
  //                              GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
  //                              GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
  //                              GPDMA_CH_CONTROL_S                                                |
  //                              GPDMA_CH_CONTROL_D                                                |
  //                              GPDMA_CH_CONTROL_DI                                               |
  //                              GPDMA_CH_CONTROL_I,
  //                              GPDMA_CH_CONFIG_SRC_PERI(ssp->dma.rx_peri)                        |
  //                              GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_P2M_CTRL_DMA)            |
  //                              GPDMA_CH_CONFIG_IE                                                |
  //                              GPDMA_CH_CONFIG_ITC                                               |
  //                              GPDMA_CH_CONFIG_E,
  //                              ssp->dma.rx_callback) == -1) {
  //    return DRIVER_ERROR;
  //  }
  //  if (GPDMA_ChannelConfigure (ssp->dma.tx_ch,
  //                             (uint32_t)data_out,
  //                             (uint32_t)&ssp->reg->DR,
  //                              num,
  //                              GPDMA_CH_CONTROL_SBSIZE(GPDMA_BSIZE_1)                            |
  //                              GPDMA_CH_CONTROL_DBSIZE(GPDMA_BSIZE_1)                            |
  //                              GPDMA_CH_CONTROL_SWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
  //                              GPDMA_CH_CONTROL_DWIDTH((ssp->reg->CR0 & SSPx_CR0_DSS) > 7)       |
  //                              GPDMA_CH_CONTROL_S                                                |
  //                              GPDMA_CH_CONTROL_D                                                |
  //                              GPDMA_CH_CONTROL_SI                                               |
  //                              GPDMA_CH_CONTROL_I,
  //                              GPDMA_CH_CONFIG_DEST_PERI(ssp->dma.tx_peri)                       |
  //                              GPDMA_CH_CONFIG_FLOWCNTRL(GPDMA_TRANSFER_M2P_CTRL_DMA)            |
  //                              GPDMA_CH_CONFIG_IE                                                |
  //                              GPDMA_CH_CONFIG_ITC                                               |
  //                              GPDMA_CH_CONFIG_E,
  //                              ssp->dma.tx_callback) == -1) { 
  //    return DRIVER_ERROR;
  //  }
  } else {
    ssp->reg->IMSC = SPI_IMSC_TXIM_Msk | SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk;
  }

  return DRIVER_OK;
}

static uint32_t SSPx_GetDataCount (ssp_resources_t *ssp) {
  uint32_t cnt;

  if (!(ssp->info->state & SSP_CONFIGURED)) { return 0U; }

  if (ssp->dma.rx_en) {
    //cnt = GPDMA_ChannelGetCount (ssp->dma.rx_ch);
  } else {
    cnt = ssp->xfer->rx_cnt;
  }

  return cnt;
}

static int32_t SSPx_Control (uint32_t control, uint32_t arg, ssp_resources_t *ssp) {
  uint32_t cpsr, scr, bps = 0U, clk, data_bits;
  uint32_t best_cpsr = 2U, best_scr = 0U, best_bps = 0U;

  if (!(ssp->info->state & SSP_POWERED)) { return DRIVER_ERROR; }

  if ((control & SPI_CONTROL_Msk) == SPI_ABORT_TRANSFER) {
    ssp->reg->CR1 &= ~SPI_CR1_SSE_Msk;         // Disable SSP
    ssp->reg->IMSC =  0U;                   // Disable interrupts
    if (ssp->info->status.busy) {
      // If DMA mode - disable DMA channel
//      if (ssp->dma.tx_en) { GPDMA_ChannelDisable (ssp->dma.tx_ch); }
      // If DMA mode - disable DMA channel
//      if (ssp->dma.rx_en) { GPDMA_ChannelDisable (ssp->dma.rx_ch); }
    }
    memset(ssp->xfer, 0, sizeof(ssp_transfer_info_t));
    ssp->info->status.busy = 0U;
    ssp->reg->CR1 |=  SPI_CR1_SSE_Msk;         // Enable  SSP
    return DRIVER_OK;
  }

  if (ssp->info->status.busy)            { return DRIVER_ERROR_BUSY; }

  switch (control & SPI_CONTROL_Msk) {
    default:
      return DRIVER_ERROR_UNSUPPORTED;

    case SPI_MODE_INACTIVE:             // SPI Inactive
      ssp->reg->CR1    &= ~SPI_CR1_SSE_Msk;    // Disable SSP
      ssp->reg->IMSC    =  0U;              // Disable interrupts
      ssp->info->mode  &= ~SPI_CONTROL_Msk;
      ssp->info->mode  |=  SPI_MODE_INACTIVE;
      ssp->info->state &= ~SSP_CONFIGURED;
      return DRIVER_OK;

    case SPI_MODE_MASTER:               // SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
      ssp->reg->CR1    &= ~SPI_CR1_SSE_Msk;    // Disable SSP
      ssp->reg->IMSC    =  0U;              // Disable interrupts
      ssp->reg->CR1    &= ~SPI_CR1_MS_Msk;     // Set master mode
      ssp->info->mode  &= ~SPI_CONTROL_Msk;
      ssp->info->mode  |=  SPI_MODE_MASTER;
      ssp->info->state |=  SSP_CONFIGURED;
      ssp->reg->CR1    |=  SPI_CR1_SSE_Msk;    // Enable  SSP
      goto set_speed;

    case SPI_MODE_SLAVE:                // SPI Slave  (Output on MISO, Input on MOSI)
      ssp->reg->CR1    &= ~SPI_CR1_SSE_Msk;    // Disable SSP
      ssp->reg->CR1    |=  SPI_CR1_MS_Msk;     // Set slave mode
      ssp->reg->IMSC    =  SPI_IMSC_RORIM_Msk; // Enable receive overrun interrupt
      ssp->info->mode  &= ~SPI_CONTROL_Msk;
      ssp->info->mode  |=  SPI_MODE_SLAVE;
      ssp->info->state |=  SSP_CONFIGURED;
      ssp->reg->CR1    |=  SPI_CR1_SSE_Msk;    // Enable  SSP
      break;

    case SPI_MODE_MASTER_SIMPLEX:       // SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
    case SPI_MODE_SLAVE_SIMPLEX:        // SPI Slave  (Output/Input on MISO)
      return SPI_ERROR_MODE;

    case SPI_SET_BUS_SPEED:             // Set Bus Speed in bps; arg = value
set_speed:
#if 0
      if (arg == 0U) {
        return DRIVER_ERROR;
      }

      clk = get_system_clocks() << 4;
      arg = (arg << 4);
      for (cpsr = 2U; cpsr < 255U; cpsr+= 2U) {// Loop through clock prescaler
        for (scr = 0U; scr < 256U; scr++) {    // Loop through bit prescaler
          bps = clk  / (cpsr * (scr + 1U));
          if (arg == bps) {
            best_bps  = bps;
            best_cpsr = cpsr;
            best_scr  = scr;
            goto found_best;
          } else {
            if (arg > bps) {
              if ((arg - best_bps) > (arg - bps)) {
                best_bps  = bps;
                best_cpsr = cpsr;
                best_scr  = scr;
              }
            }
          }
        }
      }
      if (best_bps == 0U) {
        return DRIVER_ERROR;
      }
#endif
      best_cpsr = 0x2;
      best_scr = 0x13;
found_best:
      ssp->reg->CPSR =  best_cpsr & SPI_CPSR_CPSDVSR_Msk;
      ssp->reg->CR0 &= ~SPI_CR0_SCR_Msk;
      ssp->reg->CR0 |= ((best_scr << 8) & SPI_CR0_SCR_Msk);
      if ((control & SPI_CONTROL_Msk) == SPI_SET_BUS_SPEED) {
        return DRIVER_OK;
      }
      break;

    case SPI_GET_BUS_SPEED:             // Get Bus Speed in bps
      return (get_system_clocks() / ((ssp->reg->CPSR & SPI_CPSR_CPSDVSR_Msk) * (((ssp->reg->CR0 & SPI_CR0_SCR_Msk) >> 8) + 1U)));

    case SPI_SET_DEFAULT_TX_VALUE:      // Set default Transmit value; arg = value
      ssp->xfer->def_val = (uint16_t)(arg & 0xFFFF);
      return DRIVER_OK;

    case SPI_CONTROL_SS:                // Control Slave Select; arg = 0:inactive, 1:active 
      if (((ssp->info->mode & SPI_CONTROL_Msk)        != SPI_MODE_MASTER)  ||
          ((ssp->info->mode & SPI_SS_MASTER_MODE_Msk) != SPI_SS_MASTER_SW)) {
        return DRIVER_ERROR;
      }
      return DRIVER_OK;
  }

  if ((ssp->info->mode & SPI_CONTROL_Msk) == SPI_MODE_MASTER) {
    switch (control & SPI_SS_MASTER_MODE_Msk) {
      case SPI_SS_MASTER_UNUSED:        // SPI Slave Select when Master: Not used (default)
        ssp->info->mode  &= ~SPI_SS_MASTER_MODE_Msk;
        ssp->info->mode  |=  SPI_SS_MASTER_UNUSED;
        break;

      case SPI_SS_MASTER_HW_INPUT:      // SPI Slave Select when Master: Hardware monitored Input
        ssp->info->mode  &= ~SPI_SS_MASTER_MODE_Msk;
        return SPI_ERROR_SS_MODE;

      case SPI_SS_MASTER_SW:            // SPI Slave Select when Master: Software controlled
        ssp->info->mode &= ~SPI_SS_MASTER_MODE_Msk;
        ssp->info->mode |= SPI_SS_MASTER_SW;
        break;

      case SPI_SS_MASTER_HW_OUTPUT:     // SPI Slave Select when Master: Hardware controlled Output
        ssp->info->mode &= ~SPI_SS_MASTER_MODE_Msk;
        ssp->info->mode |= SPI_SS_MASTER_HW_OUTPUT;
      default:
        break;
    }
  }

  if ((ssp->info->mode & SPI_CONTROL_Msk) ==  SPI_MODE_SLAVE) {
    switch (control & SPI_SS_SLAVE_MODE_Msk) {
      case SPI_SS_SLAVE_HW:             // SPI Slave Select when Slave: Hardware monitored (default)
        ssp->info->mode &= ~SPI_SS_SLAVE_MODE_Msk;
        ssp->info->mode |= SPI_SS_SLAVE_HW;
        break;

      case SPI_SS_SLAVE_SW:             // SPI Slave Select when Slave: Software controlled
        ssp->info->mode  &= ~SPI_SS_SLAVE_MODE_Msk;
        return SPI_ERROR_SS_MODE;
      default:
        return SPI_ERROR_SS_MODE;
    }
  }

  // Configure Frame Format
  switch (control & SPI_FRAME_FORMAT_Msk) {
    case SPI_CPOL0_CPHA0:
      ssp->reg->CR0 &=  ~SPI_CR0_FRF_Msk;
      ssp->reg->CR0 &= ~(SPI_CR0_CPOL_Msk | SPI_CR0_CPHA_Msk);
      break;

    case SPI_CPOL0_CPHA1:
      ssp->reg->CR0 &=  ~SPI_CR0_FRF_Msk;
      ssp->reg->CR0 &=  ~SPI_CR0_CPOL_Msk;
      ssp->reg->CR0 |=   SPI_CR0_CPHA_Msk;
      break;

    case SPI_CPOL1_CPHA0:
      ssp->reg->CR0 &=  ~SPI_CR0_FRF_Msk;
      ssp->reg->CR0 |=   SPI_CR0_CPOL_Msk;
      ssp->reg->CR0 &=  ~SPI_CR0_CPHA_Msk;
      break;

    case SPI_CPOL1_CPHA1:
      ssp->reg->CR0 &=  ~SPI_CR0_FRF_Msk;
      ssp->reg->CR0 |=  (SPI_CR0_CPOL_Msk | SPI_CR0_CPHA_Msk);
      break;

    case SPI_TI_SSI:
      ssp->reg->CR0  =  (ssp->reg->CR0 & (~SPI_CR0_FRF_Msk)) | (1U << 4);
      break;

    case SPI_MICROWIRE:
      ssp->reg->CR0  =  (ssp->reg->CR0 & (~SPI_CR0_FRF_Msk)) | (2U << 4);
      break;

    default:
      return SPI_ERROR_FRAME_FORMAT;
  }

  // Configure Number of Data Bits
  data_bits = ((control & SPI_DATA_BITS_Msk) >> SPI_DATA_BITS_Pos);
  if ((data_bits >= 4U) && (data_bits <= 16U)) {
    ssp->reg->CR0 = (ssp->reg->CR0 & (~SPI_CR0_DSS_Msk)) | ((data_bits - 1U) << 0);
  } else {
    return SPI_ERROR_DATA_BITS;
  }

  // Configure Bit Order
  if ((control & SPI_BIT_ORDER_Msk) == SPI_LSB_MSB) {
    return SPI_ERROR_BIT_ORDER;
  }

  return DRIVER_OK;
}

static SPI_STATUS SSPx_GetStatus (ssp_resources_t *ssp) {
  SPI_STATUS status;

  status.busy       = ssp->info->status.busy;
  status.data_lost  = ssp->info->status.data_lost;
  status.mode_fault = ssp->info->status.mode_fault;

  return (status);
}

void SSPx_GPDMA_Tx_SignalEvent (uint32_t event, ssp_resources_t *ssp)
{
}

void SSPx_GPDMA_Rx_SignalEvent (uint32_t event, ssp_resources_t *ssp)
{
}

static void SSPx_IRQHandler (ssp_resources_t *ssp) {
  uint16_t data;
  uint32_t mis;

  mis = ssp->reg->MIS;
  ssp->reg->ICR = mis & 3U;

                                                  // Handle transfer
  if ((ssp->reg->SR & SPI_SR_TNF_Msk) && (ssp->xfer->num > ssp->xfer->tx_cnt)) {
    if (ssp->xfer->tx_buf) {                      // If data available
      data = *(ssp->xfer->tx_buf++);
      if ((ssp->reg->CR0 & SPI_CR0_DSS_Msk) > 7U) {  // If 9..16-bit data frame format
        data |= *(ssp->xfer->tx_buf++) << 8;
      }
    } else {                                      // If default data send
      data = ssp->xfer->def_val;
    }
    ssp->reg->DR = data;                          // Activate send
    ssp->xfer->tx_cnt++;
    ssp->xfer->tx_cnt_total++;
  }

  if (ssp->reg->SR & SPI_SR_RNE_Msk) {
    data = ssp->reg->DR;      // Read data

    if (ssp->xfer->num > ssp->xfer->rx_cnt) {
      if (ssp->xfer->rx_buf) {
        *(ssp->xfer->rx_buf++) = (uint8_t)(data);    // Put data into buffer
        if ((ssp->reg->CR0 & SPI_CR0_DSS_Msk) > 7U) { // If 9..16-bit data frame format
          *(ssp->xfer->rx_buf++) = (uint8_t)(data >> 8);
        }
      }
      ssp->xfer->rx_cnt++;
      ssp->xfer->rx_cnt_total++;
      if (ssp->xfer->rx_cnt == ssp->xfer->num) {  // If all data received
        ssp->reg->IMSC   &= ~(SPI_IMSC_TXIM_Msk | SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk);
        ssp->info->status.busy = 0U;
        if (ssp->info->cb_event) { ssp->info->cb_event(SPI_EVENT_TRANSFER_COMPLETE); }
      }
    }
  }

  if (mis & SPI_MIS_RORMIS_Msk) {                    // Handle errors
    // Overrun flag is set
    ssp->info->status.data_lost = 1U;
    if (ssp->info->cb_event) { ssp->info->cb_event(SPI_EVENT_DATA_LOST); }
  }
}

#if RTE_Drivers_SSP0
static int32_t      SSP0_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp0_res); }
static int32_t      SSP0_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp0_res); }
static int32_t      SSP0_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp0_res); }
static int32_t      SSP0_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp0_res); }
static int32_t      SSP0_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp0_res); }
static int32_t      SSP0_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp0_res); }
static uint32_t     SSP0_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp0_res); }
static int32_t      SSP0_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp0_res); }
static SPI_STATUS   SSP0_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp0_res); }
       void         SSP0_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp0_res); }
       void         SSP0_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp0_res); }

void SSP0_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc) { 
    eu_interrupt_disable(RV32_SPI0_IRQn);
    eu_interrupt_clear_pending(RV32_SPI0_IRQn);
    SSPx_IRQHandler(&ssp0_res);
    eu_interrupt_enable(RV32_SPI0_IRQn);
}

DRIVER_SPI Driver_SPI0 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP0_Initialize,
    SSP0_Uninitialize,
    SSP0_PowerControl,
    SSP0_Send,
    SSP0_Receive,
    SSP0_Transfer,
    SSP0_GetDataCount,
    SSP0_Control,
    SSP0_GetStatus
};
#endif

#if RTE_Drivers_SSP1
static int32_t      SSP1_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp1_res); }
static int32_t      SSP1_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp1_res); }
static int32_t      SSP1_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp1_res); }
static int32_t      SSP1_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp1_res); }
static int32_t      SSP1_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp1_res); }
static int32_t      SSP1_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp1_res); }
static uint32_t     SSP1_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp1_res); }
static int32_t      SSP1_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp1_res); }
static SPI_STATUS   SSP1_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp1_res); }
       void         SSP1_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp1_res); }
       void         SSP1_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp1_res); }

void SSP1_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SPI1_IRQn);
    eu_interrupt_clear_pending(RV32_SPI1_IRQn);
    SSPx_IRQHandler(&ssp1_res);
    eu_interrupt_enable(RV32_SPI1_IRQn);
}

DRIVER_SPI Driver_SPI1 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP1_Initialize,
    SSP1_Uninitialize,
    SSP1_PowerControl,
    SSP1_Send,
    SSP1_Receive,
    SSP1_Transfer,
    SSP1_GetDataCount,
    SSP1_Control,
    SSP1_GetStatus
};
#endif

#if RTE_Drivers_SSP2
static int32_t      SSP2_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp2_res); }
static int32_t      SSP2_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp2_res); }
static int32_t      SSP2_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp2_res); }
static int32_t      SSP2_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp2_res); }
static int32_t      SSP2_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp2_res); }
static int32_t      SSP2_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp2_res); }
static uint32_t     SSP2_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp2_res); }
static int32_t      SSP2_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp2_res); }
static SPI_STATUS   SSP2_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp2_res); }
       void         SSP2_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp2_res); }
       void         SSP2_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp2_res); }

void SSP2_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SPI2_IRQn);
    eu_interrupt_clear_pending(RV32_SPI2_IRQn);
    SSPx_IRQHandler(&ssp2_res);
    eu_interrupt_enable(RV32_SPI2_IRQn);
}

DRIVER_SPI Driver_SPI2 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP2_Initialize,
    SSP2_Uninitialize,
    SSP2_PowerControl,
    SSP2_Send,
    SSP2_Receive,
    SSP2_Transfer,
    SSP2_GetDataCount,
    SSP2_Control,
    SSP2_GetStatus
};
#endif

#if RTE_Drivers_SSP3
static int32_t      SSP3_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp3_res); }
static int32_t      SSP3_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp3_res); }
static int32_t      SSP3_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp3_res); }
static int32_t      SSP3_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp3_res); }
static int32_t      SSP3_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp3_res); }
static int32_t      SSP3_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp0_res); }
static uint32_t     SSP3_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp3_res); }
static int32_t      SSP3_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp3_res); }
static SPI_STATUS   SSP3_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp3_res); }
       void         SSP3_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp3_res); }
       void         SSP3_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp3_res); }

void SSP3_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SPI3_SECIRQn);
    eu_interrupt_clear_pending(RV32_SPI3_SECIRQn);
    SSPx_IRQHandler(&ssp3_res);
    eu_interrupt_enable(RV32_SPI3_SECIRQn);
}

DRIVER_SPI Driver_SPI3 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP3_Initialize,
    SSP3_Uninitialize,
    SSP3_PowerControl,
    SSP3_Send,
    SSP3_Receive,
    SSP3_Transfer,
    SSP3_GetDataCount,
    SSP3_Control,
    SSP3_GetStatus
};
#endif

#if RTE_Drivers_SSP4
static int32_t      SSP4_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp4_res); }
static int32_t      SSP4_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp4_res); }
static int32_t      SSP4_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp4_res); }
static int32_t      SSP4_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp4_res); }
static int32_t      SSP4_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp4_res); }
static int32_t      SSP4_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp4_resources); }
static uint32_t     SSP4_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp4_res); }
static int32_t      SSP4_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp4_res); }
static SPI_STATUS   SSP4_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp4_res); }
       void         SSP4_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp4_res); }
       void         SSP4_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp4_res); }

void SSP4_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SPI4_SECIRQn);
    eu_interrupt_clear_pending(RV32_SPI4_SECIRQn);
    SSPx_IRQHandler(&ssp4_res);
    eu_interrupt_enable(RV32_SPI4_SECIRQn)
}

DRIVER_SPI Driver_SPI4 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP4_Initialize,
    SSP4_Uninitialize,
    SSP4_PowerControl,
    SSP4_Send,
    SSP4_Receive,
    SSP4_Transfer,
    SSP4_GetDataCount,
    SSP4_Control,
    SSP4_GetStatus
};
#endif

#if RTE_Drivers_SSP5
static int32_t      SSP5_Initialize          (SPI_SignalEvent_t pSignalEvent)                    { return SSPx_Initialize   (pSignalEvent, &ssp5_res); }
static int32_t      SSP5_Uninitialize        (void)                                              { return SSPx_Uninitialize (&ssp5_res); }
static int32_t      SSP5_PowerControl        (POWER_STATE state)                                 { return SSPx_PowerControl (state, &ssp5_res); }
static int32_t      SSP5_Send                (const void *data, uint32_t num)                    { return SSPx_Send         (data, num, &ssp5_res); }
static int32_t      SSP5_Receive             (void *data, uint32_t num)                          { return SSPx_Receive      (data, num, &ssp5_res); }
static int32_t      SSP5_Transfer            (const void *data_out, void *data_in, uint32_t num) { return SSPx_Transfer     (data_out, data_in, num, &ssp5_res); }
static uint32_t     SSP5_GetDataCount        (void)                                              { return SSPx_GetDataCount (&ssp5_res); }
static int32_t      SSP5_Control             (uint32_t control, uint32_t arg)                    { return SSPx_Control      (control, arg, &ssp5_res); }
static SPI_STATUS   SSP5_GetStatus           (void)                                              { return SSPx_GetStatus    (&ssp5_res); }
       void         SSP5_GPDMA_Tx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Tx_SignalEvent(event, &ssp5_res); }
       void         SSP5_GPDMA_Rx_SignalEvent(uint32_t event)                                    { SSPx_GPDMA_Rx_SignalEvent(event, &ssp5_res); }

void SSP5_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SPI5_SECIRQn);
    eu_interrupt_clear_pending(RV32_SPI5_SECIRQn);
    SSPx_IRQHandler(&ssp5_res);
    eu_interrupt_enable(RV32_SPI5_SECIRQn);
}

DRIVER_SPI Driver_SPI5 = {
    SSPx_GetVersion,
    SSPx_GetCapabilities,
    SSP5_Initialize,
    SSP5_Uninitialize,
    SSP5_PowerControl,
    SSP5_Send,
    SSP5_Receive,
    SSP5_Transfer,
    SSP5_GetDataCount,
    SSP5_Control,
    SSP5_GetStatus
};
#endif
