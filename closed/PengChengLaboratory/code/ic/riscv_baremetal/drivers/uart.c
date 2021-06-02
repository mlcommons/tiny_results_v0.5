#include <platform.h>
#include <rv_uart.h>


#define CLOCK_FREQ 48000000

#define USART_DRV_VERSION    DRIVER_VERSION_MAJOR_MINOR(1, 0)  /* driver version */

/* Driver Version */
static const DRIVER_VERSION DriverVersion = { 
	USART_API_VERSION,
	USART_DRV_VERSION
};

// UART0
#if RTE_Drivers_UART0
static usart_info_t usart0_info = { 0 };

static usart_resources_t usart0_res = {
    {
        1,  // supports UART (Asynchronous) mode
        0,  // supports Synchronous Master mode
        0,  // supports Synchronous Slave mode
        0,  // supports UART Single-wire mode
        0,  // supports UART IrDA mode
        0,  // supports UART Smart Card mode
        0,  // Smart Card Clock generator
        0,  // RTS Flow Control available
        0,  // CTS Flow Control available
        1,  // Transmit completed event: \ref USART_EVENT_TX_COMPLETE
        1,  // Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
        0,  // RTS Line: 0=not available, 1=available
        0,  // CTS Line: 0=not available, 1=available
        0,  // DTR Line: 0=not available, 1=available
        0,  // DSR Line: 0=not available, 1=available
        0,  // DCD Line: 0=not available, 1=available
        0,  // RI Line:  0=not available, 1=available
        0,  // Signal CTS change event: \ref USART_EVENT_CTS
        0,  // Signal DSR change event: \ref USART_EVENT_DSR
        0,  // Signal DCD change event: \ref USART_EVENT_DCD
        0,  // Signal RI  change event: \ref USART_EVENT_RI
    },                  // Capabilities
    RV32_UART0,       // Pointer to UART peripheral
    0,                  // Clock frequency
    RV32_UART0_IRQn,  // IRQ Number
    0,                  // Transmit FIFO Trigger level
    3,                  // Receive FIFO Trigger level
    NULL,               // TODO: TX DMA
    NULL,               // TODO: RX DMA
    &usart0_info         // Run-Time Information
};
#endif // RTE_Drivers_UART0

// UART1
#if RTE_Drivers_UART1
static usart_info_t usart1_info = { 0 };

static usart_resources_t usart1_res = {
    {
        1,  // supports UART (Asynchronous) mode
        0,  // supports Synchronous Master mode
        0,  // supports Synchronous Slave mode
        0,  // supports UART Single-wire mode
        0,  // supports UART IrDA mode
        0,  // supports UART Smart Card mode
        0,  // Smart Card Clock generator
        0,  // RTS Flow Control available
        0,  // CTS Flow Control available
        1,  // Transmit completed event: \ref USART_EVENT_TX_COMPLETE
        1,  // Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
        0,  // RTS Line: 0=not available, 1=available
        0,  // CTS Line: 0=not available, 1=available
        0,  // DTR Line: 0=not available, 1=available
        0,  // DSR Line: 0=not available, 1=available
        0,  // DCD Line: 0=not available, 1=available
        0,  // RI Line:  0=not available, 1=available
        0,  // Signal CTS change event: \ref USART_EVENT_CTS
        0,  // Signal DSR change event: \ref USART_EVENT_DSR
        0,  // Signal DCD change event: \ref USART_EVENT_DCD
        0,  // Signal RI  change event: \ref USART_EVENT_RI
    },                  // Capabilities
    RV32_UART1,       // Pointer to UART peripheral
    0,                  // Clock frequency
    RV32_UART1_IRQn,  // IRQ Number
    0,                  // Transmit FIFO Trigger level
    3,                  // Receive FIFO Trigger level
    NULL,               // TODO: TX DMA
    NULL,               // TODO: RX DMA
    &usart1_info         // Run-Time Information
};
#endif // RTE_Drivers_UART1

// UART2
#if RTE_Drivers_UART2
static usart_info_t usart2_info = { 0 };

static usart_resources_t usart2_res = {
    {
        1,  // supports UART (Asynchronous) mode
        0,  // supports Synchronous Master mode
        0,  // supports Synchronous Slave mode
        0,  // supports UART Single-wire mode
        0,  // supports UART IrDA mode
        0,  // supports UART Smart Card mode
        0,  // Smart Card Clock generator
        0,  // RTS Flow Control available
        0,  // CTS Flow Control available
        1,  // Transmit completed event: \ref USART_EVENT_TX_COMPLETE
        1,  // Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
        0,  // RTS Line: 0=not available, 1=available
        0,  // CTS Line: 0=not available, 1=available
        0,  // DTR Line: 0=not available, 1=available
        0,  // DSR Line: 0=not available, 1=available
        0,  // DCD Line: 0=not available, 1=available
        0,  // RI Line:  0=not available, 1=available
        0,  // Signal CTS change event: \ref USART_EVENT_CTS
        0,  // Signal DSR change event: \ref USART_EVENT_DSR
        0,  // Signal DCD change event: \ref USART_EVENT_DCD
        0,  // Signal RI  change event: \ref USART_EVENT_RI
    },                  // Capabilities
    RV32_UART2,       // Pointer to UART peripheral
    0,                  // Clock frequency
    RV32_UART2_IRQn,  // IRQ Number
    0,                  // Transmit FIFO Trigger level
    3,                  // Receive FIFO Trigger level
    NULL,               // TODO: TX DMA
    NULL,               // TODO: RX DMA
    &usart2_info         // Run-Time Information
};
#endif // RTE_Drivers_UART2

// UART3
#if RTE_Drivers_UART3
static usart_info_t usart3_info = { 0 };

static usart_resources_t usart3_res = {
    {
        1,  // supports UART (Asynchronous) mode
        0,  // supports Synchronous Master mode
        0,  // supports Synchronous Slave mode
        0,  // supports UART Single-wire mode
        0,  // supports UART IrDA mode
        0,  // supports UART Smart Card mode
        0,  // Smart Card Clock generator
        0,  // RTS Flow Control available
        0,  // CTS Flow Control available
        1,  // Transmit completed event: \ref USART_EVENT_TX_COMPLETE
        1,  // Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
        0,  // RTS Line: 0=not available, 1=available
        0,  // CTS Line: 0=not available, 1=available
        0,  // DTR Line: 0=not available, 1=available
        0,  // DSR Line: 0=not available, 1=available
        0,  // DCD Line: 0=not available, 1=available
        0,  // RI Line:  0=not available, 1=available
        0,  // Signal CTS change event: \ref USART_EVENT_CTS
        0,  // Signal DSR change event: \ref USART_EVENT_DSR
        0,  // Signal DCD change event: \ref USART_EVENT_DCD
        0,  // Signal RI  change event: \ref USART_EVENT_RI
    },                  // Capabilities
    RV32_UART3,       // Pointer to UART peripheral
    0,                  // Clock frequency
    RV32_UART3_IRQn,  // IRQ Number
    0,                  // Transmit FIFO Trigger level
    3,                  // Receive FIFO Trigger level
    NULL,               // TODO: TX DMA
    NULL,               // TODO: RX DMA
    &usart3_info         // Run-Time Information
};
#endif // RTE_Drivers_UART3

// UART4
#if RTE_Drivers_UART4
static usart_info_t usart4_info = { 0 };

static usart_resources_t usart4_res = {
    {
        1,  // supports UART (Asynchronous) mode
        0,  // supports Synchronous Master mode
        0,  // supports Synchronous Slave mode
        0,  // supports UART Single-wire mode
        0,  // supports UART IrDA mode
        0,  // supports UART Smart Card mode
        0,  // Smart Card Clock generator
        0,  // RTS Flow Control available
        0,  // CTS Flow Control available
        1,  // Transmit completed event: \ref USART_EVENT_TX_COMPLETE
        1,  // Signal receive character timeout event: \ref USART_EVENT_RX_TIMEOUT
        0,  // RTS Line: 0=not available, 1=available
        0,  // CTS Line: 0=not available, 1=available
        0,  // DTR Line: 0=not available, 1=available
        0,  // DSR Line: 0=not available, 1=available
        0,  // DCD Line: 0=not available, 1=available
        0,  // RI Line:  0=not available, 1=available
        0,  // Signal CTS change event: \ref USART_EVENT_CTS
        0,  // Signal DSR change event: \ref USART_EVENT_DSR
        0,  // Signal DCD change event: \ref USART_EVENT_DCD
        0,  // Signal RI  change event: \ref USART_EVENT_RI
    },                  // Capabilities
    RV32_UART4,       // Pointer to UART peripheral
    0,                  // Clock frequency
    RV32_UART4_SECIRQn,  // IRQ Number
    0,                  // Transmit FIFO Trigger level
    3,                  // Receive FIFO Trigger level
    NULL,               // TODO: TX DMA
    NULL,               // TODO: RX DMA
    &usart4_info         // Run-Time Information
};
#endif // RTE_Drivers_UART4

// Local Functions
static int32_t USART_SetBaudrate (uint32_t baudrate, usart_resources_t *usart)
{
  uint32_t Temp, Divider, Remainder, Fraction;

  /*
   * Set baud rate
   *
   * IBRD = UART_CLK / (16 * BAUD_RATE)
   * FBRD = RND((64 * MOD(UART_CLK,(16 * BAUD_RATE)))
   *               / (16 * BAUD_RATE))
   */
  Temp = 16 * baudrate;
  Divider = usart->base_clk / Temp;
  Remainder = usart->base_clk % Temp;
  Temp = (8 * Remainder) / baudrate;
  Fraction = (Temp >> 1) + (Temp & 1);

  usart->reg->IBDR = Divider;
  usart->reg->FBDR = Fraction;

  usart->info->baudrate = baudrate;

  return 0;
}

static uint32_t USART_RxLineIntHandler (usart_resources_t *usart)
{
  uint32_t rsr, event;

  event = 0U;
  rsr   = usart->reg->RSR;

  // OverRun error
  if (rsr & UART_RSR_OE_Msk) {
    usart->info->rx_status.rx_overflow = 1U;
    event |= USART_EVENT_RX_OVERFLOW;
  }

  // Parity error
  if (rsr & UART_RSR_PE_Msk) {
    usart->info->rx_status.rx_parity_error = 1U;
    event |= USART_EVENT_RX_PARITY_ERROR;
  }

  // Break detected
  if (rsr & UART_RSR_BE_Msk) {
    usart->info->rx_status.rx_break = 1U;
    event |= USART_EVENT_RX_BREAK;
  }
  // Framing error
  else if (rsr & UART_RSR_FE_Msk) {
    usart->info->rx_status.rx_framing_error = 1U;
    event |= USART_EVENT_RX_FRAMING_ERROR;
  }

  return event;
}

//   Functions

static DRIVER_VERSION USARTx_GetVersion(void)
{
	return DriverVersion;
}

static USART_CAPABILITIES USARTx_GetCapabilities(usart_resources_t *usart)
{
    return usart->capabilities;
}

static int32_t USARTx_Initialize(USART_SignalEvent_t cb_event, usart_resources_t *usart)
{
    if (usart->info->flags & USART_FLAG_INITIALIZED) {
        // Driver is already initialized
        return DRIVER_OK;
    }

    usart->base_clk = CLOCK_FREQ;

    // Initialize USART Run-time Resources
    usart->info->cb_event = cb_event;

    usart->info->rx_status.rx_busy          = 0U;
    usart->info->rx_status.rx_overflow      = 0U;
    usart->info->rx_status.rx_break         = 0U;
    usart->info->rx_status.rx_framing_error = 0U;
    usart->info->rx_status.rx_parity_error  = 0U;

    usart->info->xfer.send_active           = 0U;
    usart->info->xfer.tx_def_val            = 0U;

    // Configure CTS pin
    if (usart->capabilities.cts)
      usart->reg->CR |= UART_CR_CTSEN_Msk;

    // Configure RTS pin
    if (usart->capabilities.rts) {
      usart->reg->CR |= UART_CR_RTSEN_Msk;
    }

    // TODO: DMA Initialize
    // if (usart->dma_tx || usart->dma_rx) {
    //   GPDMA_Initialize ();
    // }

    // FIFO Enable, 8 bits, No Parity, 1 Stop bits
    usart->reg->LCR_H = UART_LCR_H_FEN_Msk | UART_LCR_H_WLEN_Msk;

    // Set FIFO trigger level
    usart->reg->IFLS  = (usart->tx_trig_lvl << UART_IFLS_TXIFLSEL_Pos) |
                        (usart->rx_trig_lvl << UART_IFLS_RXIFLSEL_Pos);

    // Clear RTS/CTS and Enable the UART
    usart->reg->CR   &= ~(UART_CR_RTSEN_Msk | UART_CR_CTSEN_Msk);
    usart->reg->CR   |= UART_CR_UARTEN_Msk  | UART_CR_TXE_Msk |
                        UART_CR_RXE_Msk;

    // Enable interrupt other than TX/RX
    usart->reg->IMSC |= UART_IMSC_OEIM_Msk   | UART_IMSC_BEIM_Msk |
                        UART_IMSC_PEIM_Msk   | UART_IMSC_FEIM_Msk |
                        UART_IMSC_DSRMIM_Msk | UART_IMSC_CTSMIM_Msk;

    // Enable UART Interrupt
    // TODO: NVIC_EnableIRQ(usart->irq_num);

    usart->info->flags = USART_FLAG_INITIALIZED;

	return 0;
}

static int32_t USARTx_Uninitialize(usart_resources_t *usart)
{
    // Reset CTS pin configuration
    if (usart->capabilities.cts) {
      usart->reg->CR &= ~UART_CR_CTSEN_Msk;
    }

    // Reset RTS pin configuration
    if (usart->capabilities.rts) {
      usart->reg->CR &= ~UART_CR_RTSEN_Msk;
    }

    // DMA Uninitialize
    // TODO: if (usart->dma_tx || usart->dma_rx) {
    //  GPDMA_Uninitialize ();
    // }

    // Disable UART Interrupt
    // TODO: NVIC_DisableIRQ(usart->irq_num);

    // Finally, disable the UART
    usart->reg->CR &= ~(UART_CR_UARTEN_Msk | UART_CR_TXE_Msk | UART_CR_RXE_Msk);

    // Disable all interrupt
    usart->reg->IMSC = 0U;

    // Reset USART status flags
    usart->info->flags = 0U;

	return 0;
}

static int32_t USARTx_PowerControl(POWER_STATE state, usart_resources_t *usart)
{
    return DRIVER_OK;
}

static int32_t USARTx_Send(const void *data, uint32_t num, usart_resources_t *usart)
{
    if ((data == NULL) || (num == 0U)) {
        // Invalid parameters
        return DRIVER_ERROR_PARAMETER;
    }

    if (!(usart->info->flags & USART_FLAG_CONFIGURED)) {
        // USART is not configured (mode not selected)
        return DRIVER_ERROR;
    }

    if (usart->info->xfer.send_active != 0U) {
        // Send is not completed yet
        return DRIVER_ERROR_BUSY;
    }

    // Set Send active flag
    usart->info->xfer.send_active = 1U;

    // Save transmit buffer info
    usart->info->xfer.tx_buf = (uint8_t *)data;
    usart->info->xfer.tx_num = num;
    usart->info->xfer.tx_cnt = 0U;

    // UART Console
    // XXX: At the moment, we hard-coded UART1 as the console.
    //      It should be configurable in the future.
    if (usart == &usart1_res) {
        // Fill TX FIFO
        while (usart->info->xfer.tx_cnt != usart->info->xfer.tx_num) {
            if (!(usart->reg->FR & UART_FR_TXFF_Msk)) {
                usart->reg->DR = usart->info->xfer.tx_buf[usart->info->xfer.tx_cnt];
                usart->info->xfer.tx_cnt++;
            }
        }

        usart->info->xfer.send_active = 0U;

        return DRIVER_OK;
    }

    if (usart->dma_tx) {    // DMA mode
        // TODO: DMA mode should be re-implemented

    } else {    // Interrupt mode
        // Fill TX FIFO
        while (!(usart->reg->FR & UART_FR_TXFF_Msk) &&
                (usart->info->xfer.tx_cnt != usart->info->xfer.tx_num)) {
            usart->reg->DR = usart->info->xfer.tx_buf[usart->info->xfer.tx_cnt];
            usart->info->xfer.tx_cnt ++;
        }

        // Enable transmit interrupt if not complete
        if (usart->info->xfer.tx_cnt != usart->info->xfer.tx_num)
            usart->reg->IMSC |= UART_IMSC_TXIM_Msk;
        else
            usart->info->xfer.send_active = 0U;
    }

    return DRIVER_OK;
}

static int32_t USARTx_Receive(void *data, uint32_t num, usart_resources_t *usart)
{
    if ((data == NULL) || (num == 0U)) {
        // Invalid parameters
        return DRIVER_ERROR_PARAMETER;
    }

    if (!(usart->info->flags & USART_FLAG_CONFIGURED)) {
        // USART is not configured (mode not selected)
        return DRIVER_ERROR;
    }

    // Check if receiver is busy
    if (usart->info->rx_status.rx_busy == 1U) {
        return DRIVER_ERROR_BUSY;
    }

    // Set RX busy flag
    usart->info->rx_status.rx_busy = 1U;

    // Clear RX statuses
    usart->info->rx_status.rx_break          = 0U;
    usart->info->rx_status.rx_framing_error  = 0U;
    usart->info->rx_status.rx_overflow       = 0U;
    usart->info->rx_status.rx_parity_error   = 0U;

    // Save receive buffer info
    usart->info->xfer.rx_buf = (uint8_t *)data;
    usart->info->xfer.rx_num = num;
    usart->info->xfer.rx_cnt = 0U;

    if (usart->dma_rx) {  // DMA mode
        // TODO: DMA mode should be re-implemented

    } else {              // Interrupt mode
        // Enable receive data available interrupt
        usart->reg->IMSC |= UART_IMSC_RXIM_Msk;
    }

	return DRIVER_OK;
}

static int32_t USARTx_Transfer(const void *data_out,
                                    void *data_in,
                                    uint32_t num,
                                    usart_resources_t *usart)
{
    if ((data_out == NULL) || (data_in == NULL) || (num == 0U)) {
        // Invalid parameters
        return DRIVER_ERROR_PARAMETER;
    }

    // Only in synchronouse mode
	return DRIVER_ERROR;
}

static uint32_t USARTx_GetTxCount(usart_resources_t *usart)
{
    uint32_t cnt;

    if (usart->dma_tx) {
        // TODO: DMA is to be implemented
    } else {
        cnt = usart->info->xfer.tx_cnt;
    }

    return cnt;
}

static uint32_t USARTx_GetRxCount(usart_resources_t *usart)
{
    uint32_t cnt;

    if (usart->dma_rx) {
        // TODO: DMA is to be implemented
    } else {
        cnt = usart->info->xfer.rx_cnt;
    }

    return cnt;
}

static int32_t USARTx_Control(uint32_t control, uint32_t arg, usart_resources_t *usart)
{
    uint32_t lcr, cr;

    switch (control & USART_CONTROL_Msk) {
    // Control break
    case USART_CONTROL_BREAK:
        if (arg) {
            if (usart->info->xfer.send_active != 0U)
    	        return DRIVER_ERROR_BUSY;
            usart->reg->LCR_H |= UART_LCR_H_BRK_Msk;
            // Set Send active flag
            usart->info->xfer.send_active = 1U;
        } else {
            usart->reg->LCR_H &= ~UART_LCR_H_BRK_Msk;
            // Clear Send active flag
            usart->info->xfer.send_active = 0U;
        }
        return DRIVER_OK;
    default:
        break;
    }

    // Check if Receiver/Transmitter is busy
    if ( usart->info->rx_status.rx_busy ||
        (usart->info->xfer.send_active != 0U)) {
        return DRIVER_ERROR_BUSY;
    }

    lcr = UART_LCR_H_FEN_Msk;

    // USART Data bits
    switch (control & USART_DATA_BITS_Msk) {
    case USART_DATA_BITS_5:
        lcr |= (0U << UART_LCR_H_WLEN_Pos);
        break;
    case USART_DATA_BITS_6:
        lcr |= (1U << UART_LCR_H_WLEN_Pos);
        break;
    case USART_DATA_BITS_7:
        lcr |= (2U << UART_LCR_H_WLEN_Pos);
        break;
    case USART_DATA_BITS_8:
        lcr |= (3U << UART_LCR_H_WLEN_Pos);
        break;
    default:
        return USART_ERROR_DATA_BITS;
    }

    // USART Parity
    switch (control & USART_PARITY_Msk) {
    case USART_PARITY_NONE:
        break;
    case USART_PARITY_EVEN:
        lcr |= UART_LCR_H_EPS_Msk | UART_LCR_H_PEN_Msk;
        break;
    case USART_PARITY_ODD:
        lcr |= UART_LCR_H_PEN_Msk;
        break;
    default:
        return (USART_ERROR_PARITY);
    }

    // USART Stop bits
    switch (control & USART_STOP_BITS_Msk) {
    case USART_STOP_BITS_1:
        break;
    case USART_STOP_BITS_2:
        lcr |= UART_LCR_H_STP2_Msk;
        break;
    default:
        return USART_ERROR_STOP_BITS;
    }

    // USART Flow control
    cr = usart->reg->CR & ~(UART_CR_RTSEN_Msk | UART_CR_CTSEN_Msk);
    switch (control & USART_FLOW_CONTROL_Msk) {
    case USART_FLOW_CONTROL_NONE:
        break;
    case USART_FLOW_CONTROL_RTS:
        if (usart->capabilities.flow_control_rts)
            cr |= UART_CR_RTSEN_Msk;
        else
            return USART_ERROR_FLOW_CONTROL;
        break;
    case USART_FLOW_CONTROL_CTS:
        if (usart->capabilities.flow_control_cts)
            cr |= UART_CR_CTSEN_Msk;
        else
            return USART_ERROR_FLOW_CONTROL;
        break;
    case USART_FLOW_CONTROL_RTS_CTS:
        if (usart->capabilities.flow_control_rts &&
            usart->capabilities.flow_control_cts)
            cr |= (UART_CR_RTSEN_Msk | UART_CR_CTSEN_Msk);
        else
            return USART_ERROR_FLOW_CONTROL;
        break;
    default:
        return USART_ERROR_FLOW_CONTROL;
    }

    // USART Baudrate
    if (USART_SetBaudrate (arg, usart) == -1) {
        return USART_ERROR_BAUDRATE;
    }

    // Configure CR register
    usart->reg->CR = cr;

    // Configure Line control register
    usart->reg->LCR_H = lcr;

    // Set configured flag
    usart->info->flags |= USART_FLAG_CONFIGURED;

    return DRIVER_OK;
}

static USART_STATUS USARTx_GetStatus(usart_resources_t *usart)
{
    USART_STATUS stat;

    stat.tx_busy          = usart->reg->FR & UART_FR_BUSY_Msk ? (0U) : (1U);
    stat.rx_busy          = usart->info->rx_status.rx_busy;
    stat.tx_underflow     = 0U;
    stat.rx_overflow      = usart->info->rx_status.rx_overflow;
    stat.rx_break         = usart->info->rx_status.rx_break;
    stat.rx_framing_error = usart->info->rx_status.rx_framing_error;
    stat.rx_parity_error  = usart->info->rx_status.rx_parity_error;

    return stat;
}

static int32_t USARTx_SetModemControl(USART_MODEM_CONTROL control, usart_resources_t *usart)
{
    if (!(usart->info->flags & USART_FLAG_CONFIGURED)) {
        // USART is not configured
        return DRIVER_ERROR;
    }

    if (control == USART_RTS_CLEAR) {
        if (usart->capabilities.rts) {
            usart->reg->CR &= ~UART_CR_RTS_Msk;
        } else {
            return DRIVER_ERROR_UNSUPPORTED;
        }
    }

    if (control == USART_RTS_SET) {
        if (usart->capabilities.rts) {
            usart->reg->CR |=  UART_CR_RTS_Msk;
        } else {
            return DRIVER_ERROR_UNSUPPORTED;
        }
    }

    if (control == USART_DTR_CLEAR) {
        if (usart->capabilities.dtr) {
            usart->reg->CR &= ~UART_CR_DTR_Msk;
        } else {
            return DRIVER_ERROR_UNSUPPORTED;
        }
    }

    if (control == USART_DTR_SET) {
        if (usart->capabilities.dtr) {
            usart->reg->CR |=  UART_CR_DTR_Msk;
        } else {
            return DRIVER_ERROR_UNSUPPORTED;
        }
    }

    return DRIVER_OK;
}

static USART_MODEM_STATUS USARTx_GetModemStatus(usart_resources_t *usart)
{
    USART_MODEM_STATUS modem_status;
    uint32_t fr;

    if (usart->info->flags & USART_FLAG_CONFIGURED) {

        fr = usart->reg->FR;

        if (usart->capabilities.cts) {
            modem_status.cts = (fr & UART_FR_CTS_Msk ? (1U) : (0U));
        } else {
            modem_status.cts = 0U;
        }

        if (usart->capabilities.dsr) {
            modem_status.dsr = (fr & UART_FR_DSR_Msk ? (1U) : (0U));
        } else {
            modem_status.dsr = 0U;
        }

        if (usart->capabilities.ri ) {
            modem_status.ri  = (fr & UART_FR_RI_Msk  ? (1U) : (0U));
        } else {
            modem_status.ri  = 0U;
        }

        if (usart->capabilities.dcd) {
            modem_status.dcd = (fr & UART_FR_DCD_Msk ? (1U) : (0U));
        } else {
            modem_status.dcd = 0U;
        }
    } else {
        modem_status.cts = 0U;
        modem_status.dsr = 0U;
        modem_status.ri  = 0U;
        modem_status.dcd = 0U;
    }

    return modem_status;
}

void UARTx_IRQHandler (usart_resources_t *usart)
{
    uint32_t mis, event;

    event = 0U;
    mis   = usart->reg->MIS;

    // Clear All Interrupt
    usart->reg->ICR |= 0x7FF;

    // Transmit Interupt
    if (mis & UART_RIS_TXRIS_Msk) {
        while (!(usart->reg->FR & UART_FR_TXFF_Msk) &&
               (usart->info->xfer.tx_num != usart->info->xfer.tx_cnt)) {
            // Write data to Tx FIFO
            usart->reg->DR = usart->info->xfer.tx_buf[usart->info->xfer.tx_cnt];
            usart->info->xfer.tx_cnt ++;
        }

        // Check if all data is transmitted
        if (usart->info->xfer.tx_num == usart->info->xfer.tx_cnt) {
            // Mask Transmit Interrupt
            usart->reg->IMSC &= ~UART_IMSC_TXIM_Msk;

            // Clear TX busy flag
            usart->info->xfer.send_active = 0U;

            // Set send complete event
            event |= USART_EVENT_SEND_COMPLETE;
        }
    }

    // Receive line status
    if (mis & (UART_RIS_OERIS_Msk | UART_RIS_BERIS_Msk |
                 UART_RIS_PERIS_Msk | UART_RIS_FERIS_Msk)) {
        event |= USART_RxLineIntHandler(usart);
    }

    // Receive data available interrupt
    if (mis & UART_RIS_RXRIS_Msk) {
        // Get available data from RX FIFO
        while (!(usart->reg->FR & UART_FR_RXFE_Msk)) {
            // Read data from RX FIFO into receive buffer
            usart->info->xfer.rx_buf[usart->info->xfer.rx_cnt] = usart->reg->DR;
            usart->info->xfer.rx_cnt++;

            // Check RX line interrupt for errors
            event |= USART_RxLineIntHandler (usart);

            // Check if requested amount of data is received
            if (usart->info->xfer.rx_cnt == usart->info->xfer.rx_num) {
                // Disable Receive interrupt
                usart->reg->IMSC &= ~UART_IMSC_RXIM_Msk;

                // Clear RX busy flag and set receive transfer complete event
                usart->info->rx_status.rx_busy = 0U;
                event |= USART_EVENT_RECEIVE_COMPLETE;

                break;
            }
        }
    }

    // Receive character time-out indicator
    if (mis & UART_RIS_RTRIS_Msk) {
        // Signal RX Time-out event, if not all requested data received
        if (usart->info->xfer.rx_cnt != usart->info->xfer.rx_num) {
            event |= USART_EVENT_RX_TIMEOUT;
        }
    }

    // Modem Status interrupt
    if (mis & (UART_RIS_RIRMIS_Msk  | UART_RIS_CTSRMIS_Msk |
               UART_RIS_DCDRMIS_Msk |UART_RIS_DSRRMIS_Msk)) {
        // CTS state changed
        if (usart->capabilities.cts && (mis & UART_RIS_CTSRMIS_Msk)) {
            event |= USART_EVENT_CTS;
        }
        // DSR state changed
        if (usart->capabilities.dsr && (mis & UART_RIS_DSRRMIS_Msk)) {
            event |= USART_EVENT_DSR;
        }
        // Ring indicator
        if (usart->capabilities.ri  && (mis & UART_RIS_RIRMIS_Msk)) {
            event |= USART_EVENT_RI;
        }
        // DCD state changed
        if (usart->capabilities.dcd && (mis & UART_RIS_DCDRMIS_Msk)) {
            event |= USART_EVENT_DCD;
        }
    }

    if ((usart->info->cb_event != NULL) && (event != 0U)) {
        usart->info->cb_event(event);
    }
}

// End USART Interface

// UART0 Wrapper/
#if RTE_Drivers_UART0
static USART_CAPABILITIES USART0_GetCapabilities (void)
{
    return USARTx_GetCapabilities(&usart0_res);
}

static int32_t USART0_Initialize (USART_SignalEvent_t cb_event)
{
    // misc_enable_uart0();
    return USARTx_Initialize(cb_event, &usart0_res);
}

static int32_t USART0_Uninitialize (void)
{
    int32_t ret;
    ret = USARTx_Uninitialize(&usart0_res);
    // misc_disable_uart0();
    return ret;
}

static int32_t USART0_PowerControl (POWER_STATE state)
{
    return USARTx_PowerControl(state, &usart0_res);
}

static int32_t USART0_Send (const void *data, uint32_t num)
{
    return USARTx_Send(data, num, &usart0_res);
}

static int32_t USART0_Receive (void *data, uint32_t num)
{
    return USARTx_Receive(data, num, &usart0_res);
}

static int32_t USART0_Transfer (const void      *data_out,
                                      void      *data_in,
                                      uint32_t   num) {
    return USARTx_Transfer(data_out, data_in, num, &usart0_res);
}

static uint32_t USART0_GetTxCount (void)
{
    return USARTx_GetTxCount(&usart0_res);
}

static uint32_t USART0_GetRxCount (void)
{
    return USARTx_GetRxCount(&usart0_res);
}

static int32_t USART0_Control (uint32_t control, uint32_t arg)
{
    return USARTx_Control(control, arg, &usart0_res);
}

static USART_STATUS USART0_GetStatus (void)
{
  return USARTx_GetStatus(&usart0_res);
}

static int32_t USART0_SetModemControl (USART_MODEM_CONTROL control)
{
  return USARTx_SetModemControl(control, &usart0_res);
}

static USART_MODEM_STATUS USART0_GetModemStatus (void) {
  return USARTx_GetModemStatus(&usart0_res);
}

void UART0_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    UARTx_IRQHandler(&usart0_res);
}

DRIVER_USART driver_uart0 = {
	USARTx_GetVersion,
	USART0_GetCapabilities,
	USART0_Initialize,
	USART0_Uninitialize,
	USART0_PowerControl,
	USART0_Send,
	USART0_Receive,
	USART0_Transfer,
	USART0_GetTxCount,
	USART0_GetRxCount,
	USART0_Control,
	USART0_GetStatus,
	USART0_SetModemControl,
	USART0_GetModemStatus
};
#else
void UART0_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
}
#endif // RTE_Drivers_UART0

// UART1 Wrapper
#if RTE_Drivers_UART1
static USART_CAPABILITIES USART1_GetCapabilities (void)
{
    return USARTx_GetCapabilities(&usart1_res);
}

static int32_t USART1_Initialize (USART_SignalEvent_t cb_event)
{
    // misc_enable_uart0();
    return USARTx_Initialize(cb_event, &usart1_res);;
}

static int32_t USART1_Uninitialize (void)
{
    int32_t ret;
    ret = USARTx_Uninitialize(&usart1_res);
    // misc_disable_uart0();
    return ret;
}

static int32_t USART1_PowerControl (POWER_STATE state)
{
    return USARTx_PowerControl(state, &usart1_res);
}

static int32_t USART1_Send (const void *data, uint32_t num)
{
    return USARTx_Send(data, num, &usart1_res);
}

static int32_t USART1_Receive (void *data, uint32_t num)
{
    usart_resources_t *usart = &usart1_res;
    int32_t ctr = 0;
    uint8_t *d = (uint8_t *)data;
    while (!(usart->reg->FR & UART_FR_RXFE_Msk) && ctr < num) {
            // Read data from RX FIFO into receive buffer
           d[ctr] = usart->reg->DR;
           ctr++;
    }
    return ctr;
    //return USARTx_Receive(data, num, &usart1_res);
}

static int32_t USART1_Transfer (const void      *data_out,
                                      void      *data_in,
                                      uint32_t   num) {
    return USARTx_Transfer(data_out, data_in, num, &usart1_res);
}

static uint32_t USART1_GetTxCount (void)
{
    return USARTx_GetTxCount(&usart1_res);
}

static uint32_t USART1_GetRxCount (void)
{
    return USARTx_GetRxCount(&usart1_res);
}

static int32_t USART1_Control (uint32_t control, uint32_t arg)
{
    return USARTx_Control(control, arg, &usart1_res);
}

static USART_STATUS USART1_GetStatus (void)
{
  return USARTx_GetStatus(&usart1_res);
}

static int32_t USART1_SetModemControl (USART_MODEM_CONTROL control)
{
  return USARTx_SetModemControl(control, &usart1_res);
}

static USART_MODEM_STATUS USART1_GetModemStatus(void)
{
  return USARTx_GetModemStatus(&usart1_res);
}

void UART1_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    UARTx_IRQHandler(&usart1_res);
}

DRIVER_USART driver_uart1 = {
	USARTx_GetVersion,
	USART1_GetCapabilities,
	USART1_Initialize,
	USART1_Uninitialize,
	USART1_PowerControl,
	USART1_Send,
	USART1_Receive,
	USART1_Transfer,
	USART1_GetTxCount,
	USART1_GetRxCount,
	USART1_Control,
	USART1_GetStatus,
	USART1_SetModemControl,
	USART1_GetModemStatus
};
#else
void UART1_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
}
#endif // RTE_Drivers_UART1

// UART2 Wrapper
#if RTE_Drivers_UART2
static USART_CAPABILITIES USART2_GetCapabilities (void)
{
    return USARTx_GetCapabilities(&usart2_res);
}

static int32_t USART2_Initialize (USART_SignalEvent_t cb_event)
{
    // misc_enable_uart0();
    return USARTx_Initialize(cb_event, &usart2_res);
}

static int32_t USART2_Uninitialize (void)
{
    int32_t ret;
    ret = USARTx_Uninitialize(&usart2_res);
    // misc_disable_uart0();
    return ret;
}

static int32_t USART2_PowerControl (POWER_STATE state)
{
    return USARTx_PowerControl(state, &usart2_res);
}

static int32_t USART2_Send (const void *data, uint32_t num)
{
    return USARTx_Send(data, num, &usart2_res);
}

static int32_t USART2_Receive (void *data, uint32_t num)
{
    return USARTx_Receive(data, num, &usart2_res);
}

static int32_t USART2_Transfer (const void      *data_out,
                                      void      *data_in,
                                      uint32_t   num) {
    return USARTx_Transfer(data_out, data_in, num, &usart2_res);
}

static uint32_t USART2_GetTxCount (void)
{
    return USARTx_GetTxCount(&usart2_res);
}

static uint32_t USART2_GetRxCount (void)
{
    return USARTx_GetRxCount(&usart2_res);
}

static int32_t USART2_Control (uint32_t control, uint32_t arg)
{
    return USARTx_Control(control, arg, &usart2_res);
}

static USART_STATUS USART2_GetStatus (void)
{
  return USARTx_GetStatus(&usart2_res);
}

static int32_t USART2_SetModemControl (USART_MODEM_CONTROL control)
{
  return USARTx_SetModemControl(control, &usart2_res);
}

static USART_MODEM_STATUS USART2_GetModemStatus (void) {
  return USARTx_GetModemStatus(&usart2_res);
}

void UART2_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
  UARTx_IRQHandler(&usart2_res);
}

DRIVER_USART driver_uart2 = {
	USARTx_GetVersion,
	USART2_GetCapabilities,
	USART2_Initialize,
	USART2_Uninitialize,
	USART2_PowerControl,
	USART2_Send,
	USART2_Receive,
	USART2_Transfer,
	USART2_GetTxCount,
	USART2_GetRxCount,
	USART2_Control,
	USART2_GetStatus,
	USART2_SetModemControl,
	USART2_GetModemStatus
};
#else
void UART2_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
}
#endif // RTE_Drivers_UART2

// UART3 Wrapper
#if RTE_Drivers_UART3
static USART_CAPABILITIES USART3_GetCapabilities (void)
{
    return USARTx_GetCapabilities(&usart3_res);
}

static int32_t USART3_Initialize (USART_SignalEvent_t cb_event)
{
    // misc_enable_uart0();
    return USARTx_Initialize(cb_event, &usart3_res);
}

static int32_t USART3_Uninitialize (void)
{
    int32_t ret;
    ret = USARTx_Uninitialize(&usart3_res);
    // misc_disable_uart3();
    return ret;
}

static int32_t USART3_PowerControl (POWER_STATE state)
{
    return USARTx_PowerControl(state, &usart3_res);
}

static int32_t USART3_Send (const void *data, uint32_t num)
{
    return USARTx_Send(data, num, &usart3_res);
}

static int32_t USART3_Receive (void *data, uint32_t num)
{
    return USARTx_Receive(data, num, &usart3_res);
}

static int32_t USART3_Transfer (const void      *data_out,
                                      void      *data_in,
                                      uint32_t   num) {
    return USARTx_Transfer(data_out, data_in, num, &usart3_res);
}

static uint32_t USART3_GetTxCount (void)
{
    return USARTx_GetTxCount(&usart3_res);
}

static uint32_t USART3_GetRxCount (void)
{
    return USARTx_GetRxCount(&usart3_res);
}

static int32_t USART3_Control (uint32_t control, uint32_t arg)
{
    return USARTx_Control(control, arg, &usart3_res);
}

static USART_STATUS USART3_GetStatus (void)
{
  return USARTx_GetStatus(&usart3_res);
}

static int32_t USART3_SetModemControl (USART_MODEM_CONTROL control)
{
  return USARTx_SetModemControl(control, &usart3_res);
}

static USART_MODEM_STATUS USART3_GetModemStatus (void) {
  return USARTx_GetModemStatus(&usart3_res);
}

void UART3_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
  UARTx_IRQHandler(&usart3_res);
}

DRIVER_USART driver_uart3 = {
	USARTx_GetVersion,
	USART3_GetCapabilities,
	USART3_Initialize,
	USART3_Uninitialize,
	USART3_PowerControl,
	USART3_Send,
	USART3_Receive,
	USART3_Transfer,
	USART3_GetTxCount,
	USART3_GetRxCount,
	USART3_Control,
	USART3_GetStatus,
	USART3_SetModemControl,
	USART3_GetModemStatus
};
#else
void UART3_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
}
#endif  // RTE_Drivers_UART3

// UART4 Wrapper
#if RTE_Drivers_UART4
static USART_CAPABILITIES USART4_GetCapabilities (void)
{
    return USARTx_GetCapabilities(&usart4_res);
}

static int32_t USART4_Initialize (USART_SignalEvent_t cb_event)
{
    // misc_enable_uart0();
    return USARTx_Initialize(cb_event, &usart4_res);
}

static int32_t USART4_Uninitialize (void)
{
    int32_t ret;
    ret = USARTx_Uninitialize(&usart4_res);
    // misc_disable_uart3();
    return ret;
}

static int32_t USART4_PowerControl (POWER_STATE state)
{
    return USARTx_PowerControl(state, &usart4_res);
}

static int32_t USART4_Send (const void *data, uint32_t num)
{
    return USARTx_Send(data, num, &usart4_res);
}

static int32_t USART4_Receive (void *data, uint32_t num)
{
    return USARTx_Receive(data, num, &usart4_res);
}

static int32_t USART4_Transfer (const void      *data_out,
                                      void      *data_in,
                                      uint32_t   num) {
    return USARTx_Transfer(data_out, data_in, num, &usart4_res);
}

static uint32_t USART4_GetTxCount (void)
{
    return USARTx_GetTxCount(&usart4_res);
}

static uint32_t USART4_GetRxCount (void)
{
    return USARTx_GetRxCount(&usart4_res);
}

static int32_t USART4_Control (uint32_t control, uint32_t arg)
{
    return USARTx_Control(control, arg, &usart4_res);
}

static USART_STATUS USART4_GetStatus (void)
{
    return USARTx_GetStatus(&usart4_res);
}

static int32_t USART4_SetModemControl (USART_MODEM_CONTROL control)
{
    return USARTx_SetModemControl(control, &usart4_res);
}

static USART_MODEM_STATUS USART4_GetModemStatus (void) {
    return USARTx_GetModemStatus(&usart4_res);
}

void UART4_IRQHandler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    UARTx_IRQHandler(&usart4_res);
}

DRIVER_USART driver_uart4 = {
	USARTx_GetVersion,
	USART4_GetCapabilities,
	USART4_Initialize,
	USART4_Uninitialize,
	USART4_PowerControl,
	USART4_Send,
	USART4_Receive,
	USART4_Transfer,
	USART4_GetTxCount,
	USART4_GetRxCount,
	USART4_Control,
	USART4_GetStatus,
	USART4_SetModemControl,
	USART4_GetModemStatus
};
#else
void UART4_IRQHandler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
}
#endif // RTE_Drivers_UART4

