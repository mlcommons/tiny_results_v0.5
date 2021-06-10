#ifndef __rv_uart_h__
#define __rv_uart_h__
#include <uart.h>
#include <driver_usart.h>

// USART flags
#define USART_FLAG_INITIALIZED       (1U << 0)
#define USART_FLAG_POWERED           (1U << 1)
#define USART_FLAG_CONFIGURED        (1U << 2)
#define USART_FLAG_TX_ENABLED        (1U << 3)
#define USART_FLAG_RX_ENABLED        (1U << 4)
#define USART_FLAG_SEND_ACTIVE       (1U << 5)

// USART TX FIFO trigger level
#define USART_TRIG_LVL_18            (0x00U)
#define USART_TRIG_LVL_14            (0x01U)
#define USART_TRIG_LVL_12            (0x02U)
#define USART_TRIG_LVL_34            (0x03U)
#define USART_TRIG_LVL_78            (0x04U)

// UART Transfer Information (Run-Time)
typedef struct _usart_transfer_info {
  uint32_t                rx_num;        // Total number of data to be received
  uint32_t                tx_num;        // Total number of data to be send
  uint8_t                *rx_buf;        // Pointer to in data buffer
  uint8_t                *tx_buf;        // Pointer to out data buffer
  uint32_t                rx_cnt;        // Number of data received
  uint32_t                tx_cnt;        // Number of data sent
  uint8_t                 tx_def_val;    // Transmit default value (used in USART_SYNC_MASTER_MODE_RX)
  uint8_t                 rx_dump_val;   // Receive dump value (used in USART_SYNC_MASTER_MODE_TX)
  uint8_t                 send_active;   // Send active flag
  uint8_t                 sync_mode;     // Synchronous mode
} usart_transfer_info_t;

typedef struct _usart_rx_status {
  uint8_t rx_busy;                       // Receiver busy flag
  uint8_t rx_overflow;                   // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                      // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;              // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;               // Parity error detected on receive (cleared on start of next receive operation)
} usart_rx_status_t;

// UART Information (Run-Time)
typedef struct _usart_info {
  USART_SignalEvent_t cb_event;      // Event callback
  usart_rx_status_t         rx_status;     // Receive status flags
  usart_transfer_info_t    xfer;          // Transfer information
  uint8_t                 flags;         // USART driver flags
  uint32_t                baudrate;      // Baudrate
} usart_info_t;

// UART DMA
typedef const struct _usart_dma {
    uint8_t             channel;
    uint8_t             peripheral;
} usart_dma_t;

// UART Resources definitions
typedef struct _usart_resources {
  USART_CAPABILITIES      capabilities;  // Capabilities
  rv32_uart_t          *reg;           // Pointer to UART peripheral
  uint32_t                base_clk;      // USART clocks frequency
  uint32_t                irq_num;       // USART IRQ Number
  uint32_t                tx_trig_lvl;   // Transmit FIFO Trigger level
  uint32_t                rx_trig_lvl;   // Receive FIFO Trigger level
  usart_dma_t            *dma_tx;
  usart_dma_t            *dma_rx;
  usart_info_t           *info;          // Run-Time Information
} usart_resources_t;

extern DRIVER_USART driver_uart0;
extern DRIVER_USART driver_uart1;
extern DRIVER_USART driver_uart2;
extern DRIVER_USART driver_uart3;
extern DRIVER_USART driver_uart4;

#endif
