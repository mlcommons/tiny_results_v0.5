#ifndef __rv_spi_h__
#define __rv_spi_h__
#include <spi.h>
#include <driver_spi.h>

/* Current driver status flag definition */
#define SSP_INITIALIZED                   (1    << 0)       // SSP initialized
#define SSP_POWERED                       (1    << 1)       // SSP powered on
#define SSP_CONFIGURED                    (1    << 2)       // SSP configured
#define SSP_DATA_LOST                     (1    << 3)       // SSP data lost occurred
#define SSP_MODE_FAULT                    (1    << 4)       // SSP mode fault occurred

/* DMA Configuration */
typedef const struct _ssp_dma {
  uint8_t               tx_en;          // Transmit channel enabled
  uint8_t               tx_ch;          // Transmit channel number
  uint8_t               tx_peri;        // Transmit peripheral
  void                (*tx_callback)(uint32_t event); // Transmit callback
  uint8_t               rx_en;          // Receive channel enabled
  uint8_t               rx_ch;          // Receive channel number
  uint8_t               rx_peri;        // Receive peripheral
  void                (*rx_callback)(uint32_t event); // Receive callback
} ssp_dma_t;

/* SSP status */
typedef struct _ssp_status {
  uint8_t busy;                         // Transmitter/Receiver busy flag
  uint8_t data_lost;                    // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint8_t mode_fault;                   // Mode fault detected; optional (cleared on start of transfer operation)
} ssp_status_t;

/* SSP Information (Run-time) */
typedef struct _ssp_info {
  SPI_SignalEvent_t     cb_event;       // Event Callback
  ssp_status_t          status;         // Status flags
  uint8_t               state;          // Current SSP state
  uint32_t              mode;           // Current SSP mode
} ssp_info_t;

/* SSP Transfer Information (Run-Time) */
typedef struct _ssp_transfer_info {
  uint32_t              num;            // Total number of transfers
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              rx_cnt_total;   // Number of total data received
  uint32_t              tx_cnt;         // Number of data sent
  uint32_t              tx_cnt_total;   // Number of total data sent
  uint32_t              dump_val;       // Variable for dumping DMA data
  uint16_t              def_val;        // Default transfer value
} ssp_transfer_info_t;

/* SSP Resources */
typedef struct _ssp_resources {
    rv32_spi_t          *reg;          // SSP peripheral register interface
    ssp_dma_t               dma;            // SSP DMA configuration
    uint32_t              irq_num;        // SSP IRQ number
    ssp_info_t             *info;           // SSP Run-time information
    ssp_transfer_info_t    *xfer;           // SSP transfer information
} ssp_resources_t;

extern DRIVER_SPI Driver_SPI0;
extern DRIVER_SPI Driver_SPI1;
extern DRIVER_SPI Driver_SPI2;
extern DRIVER_SPI Driver_SPI3;

#endif
