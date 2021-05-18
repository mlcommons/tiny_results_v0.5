#ifndef DRIVER_SPI_H_
#define DRIVER_SPI_H_

#include "driver_common.h"

#define SPI_API_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

/****** SPI Control Codes *****/

#define SPI_CONTROL_Pos              0
#define SPI_CONTROL_Msk             (0xFFUL << SPI_CONTROL_Pos)

/*----- SPI Control Codes: Mode -----*/
#define SPI_MODE_INACTIVE           (0x00UL << SPI_CONTROL_Pos)     ///< SPI Inactive
#define SPI_MODE_MASTER             (0x01UL << SPI_CONTROL_Pos)     ///< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
#define SPI_MODE_SLAVE              (0x02UL << SPI_CONTROL_Pos)     ///< SPI Slave  (Output on MISO, Input on MOSI)
#define SPI_MODE_MASTER_SIMPLEX     (0x03UL << SPI_CONTROL_Pos)     ///< SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
#define SPI_MODE_SLAVE_SIMPLEX      (0x04UL << SPI_CONTROL_Pos)     ///< SPI Slave  (Output/Input on MISO)

/*----- SPI Control Codes: Mode Parameters: Frame Format -----*/
#define SPI_FRAME_FORMAT_Pos         8
#define SPI_FRAME_FORMAT_Msk        (7UL << SPI_FRAME_FORMAT_Pos)
#define SPI_CPOL0_CPHA0             (0UL << SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 0 (default)
#define SPI_CPOL0_CPHA1             (1UL << SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 1
#define SPI_CPOL1_CPHA0             (2UL << SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 0
#define SPI_CPOL1_CPHA1             (3UL << SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 1
#define SPI_TI_SSI                  (4UL << SPI_FRAME_FORMAT_Pos)   ///< Texas Instruments Frame Format
#define SPI_MICROWIRE               (5UL << SPI_FRAME_FORMAT_Pos)   ///< National Microwire Frame Format

/*----- SPI Control Codes: Mode Parameters: Data Bits -----*/
#define SPI_DATA_BITS_Pos            12
#define SPI_DATA_BITS_Msk           (0x3FUL << SPI_DATA_BITS_Pos)
#define SPI_DATA_BITS(n)            (((n) & 0x3F) << SPI_DATA_BITS_Pos) ///< Number of Data bits

/*----- SPI Control Codes: Mode Parameters: Bit Order -----*/
#define SPI_BIT_ORDER_Pos            18
#define SPI_BIT_ORDER_Msk           (1UL << SPI_BIT_ORDER_Pos)
#define SPI_MSB_LSB                 (0UL << SPI_BIT_ORDER_Pos)      ///< SPI Bit order from MSB to LSB (default)
#define SPI_LSB_MSB                 (1UL << SPI_BIT_ORDER_Pos)      ///< SPI Bit order from LSB to MSB

/*----- SPI Control Codes: Mode Parameters: Slave Select Mode -----*/
#define SPI_SS_MASTER_MODE_Pos       19
#define SPI_SS_MASTER_MODE_Msk      (3UL << SPI_SS_MASTER_MODE_Pos)
#define SPI_SS_MASTER_UNUSED        (0UL << SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Not used (default)
#define SPI_SS_MASTER_SW            (1UL << SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Software controlled
#define SPI_SS_MASTER_HW_OUTPUT     (2UL << SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware controlled Output
#define SPI_SS_MASTER_HW_INPUT      (3UL << SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware monitored Input
#define SPI_SS_SLAVE_MODE_Pos        21
#define SPI_SS_SLAVE_MODE_Msk       (1UL << SPI_SS_SLAVE_MODE_Pos)
#define SPI_SS_SLAVE_HW             (0UL << SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Hardware monitored (default)
#define SPI_SS_SLAVE_SW             (1UL << SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Software controlled


/*----- SPI Control Codes: Miscellaneous Controls  -----*/
#define SPI_SET_BUS_SPEED           (0x10UL << SPI_CONTROL_Pos)     ///< Set Bus Speed in bps; arg = value
#define SPI_GET_BUS_SPEED           (0x11UL << SPI_CONTROL_Pos)     ///< Get Bus Speed in bps
#define SPI_SET_DEFAULT_TX_VALUE    (0x12UL << SPI_CONTROL_Pos)     ///< Set default Transmit value; arg = value
#define SPI_CONTROL_SS              (0x13UL << SPI_CONTROL_Pos)     ///< Control Slave Select; arg: 0=inactive, 1=active 
#define SPI_ABORT_TRANSFER          (0x14UL << SPI_CONTROL_Pos)     ///< Abort current data transfer


/****** SPI Slave Select Signal definitions *****/
#define SPI_SS_INACTIVE              0                                  ///< SPI Slave Select Signal Inactive
#define SPI_SS_ACTIVE                1                                  ///< SPI Slave Select Signal Active


/****** SPI specific error codes *****/
#define SPI_ERROR_MODE              (DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Mode not supported
#define SPI_ERROR_FRAME_FORMAT      (DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Frame Format not supported
#define SPI_ERROR_DATA_BITS         (DRIVER_ERROR_SPECIFIC - 3)     ///< Specified number of Data bits not supported
#define SPI_ERROR_BIT_ORDER         (DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Bit order not supported
#define SPI_ERROR_SS_MODE           (DRIVER_ERROR_SPECIFIC - 5)     ///< Specified Slave Select Mode not supported


/**
\brief SPI Status
*/
typedef volatile struct _SPI_STATUS {
  uint32_t busy       : 1;              ///< Transmitter/Receiver busy flag
  uint32_t data_lost  : 1;              ///< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint32_t mode_fault : 1;              ///< Mode fault detected; optional (cleared on start of transfer operation)
  uint32_t reserved   : 29;
} SPI_STATUS;


/****** SPI Event *****/
#define SPI_EVENT_TRANSFER_COMPLETE (1UL << 0)  ///< Data Transfer completed
#define SPI_EVENT_DATA_LOST         (1UL << 1)  ///< Data lost: Receive overflow / Transmit underflow
#define SPI_EVENT_MODE_FAULT        (1UL << 2)  ///< Master Mode Fault (SS deactivated when Master)


// Function documentation
typedef void (*SPI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_SPI_SignalEvent : Signal SPI Event.


/**
\brief SPI Driver Capabilities.
*/
typedef struct _SPI_CAPABILITIES {
  uint32_t simplex          : 1;        ///< supports Simplex Mode (Master and Slave)
  uint32_t ti_ssi           : 1;        ///< supports TI Synchronous Serial Interface
  uint32_t microwire        : 1;        ///< supports Microwire Interface
  uint32_t event_mode_fault : 1;        ///< Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT
  uint32_t reserved         : 28;       ///< Reserved (must be zero)
} SPI_CAPABILITIES;


/**
\brief Access structure of the SPI Driver.
*/
typedef struct _DRIVER_SPI {
  DRIVER_VERSION       (*GetVersion)      (void);                             ///< Pointer to \ref ARM_SPI_GetVersion : Get driver version.
  SPI_CAPABILITIES     (*GetCapabilities) (void);                             ///< Pointer to \ref ARM_SPI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (SPI_SignalEvent_t cb_event);   ///< Pointer to \ref ARM_SPI_Initialize : Initialize SPI Interface.
  int32_t              (*Uninitialize)    (void);                             ///< Pointer to \ref ARM_SPI_Uninitialize : De-initialize SPI Interface.
  int32_t              (*PowerControl)    (POWER_STATE state);            ///< Pointer to \ref ARM_SPI_PowerControl : Control SPI Interface Power.
  int32_t              (*Send)            (const void *data, uint32_t num);   ///< Pointer to \ref ARM_SPI_Send : Start sending data to SPI Interface.
  int32_t              (*Receive)         (      void *data, uint32_t num);   ///< Pointer to \ref ARM_SPI_Receive : Start receiving data from SPI Interface.
  int32_t              (*Transfer)        (const void *data_out,
                                                 void *data_in,
                                           uint32_t    num);                  ///< Pointer to \ref ARM_SPI_Transfer : Start sending/receiving data to/from SPI.
  uint32_t             (*GetDataCount)    (void);                             ///< Pointer to \ref ARM_SPI_GetDataCount : Get transferred data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);   ///< Pointer to \ref ARM_SPI_Control : Control SPI Interface.
  SPI_STATUS           (*GetStatus)       (void);                             ///< Pointer to \ref ARM_SPI_GetStatus : Get SPI status.
} const DRIVER_SPI;

#endif /* DRIVER_SPI_H_ */
