#ifndef DRIVER_I2C_H_
#define DRIVER_I2C_H_

#include "driver_common.h"

#define I2C_API_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */


/****** I2C Control Codes *****/

#define I2C_OWN_ADDRESS             (0x01)      // Set Own Slave Address; arg = address 
#define I2C_BUS_SPEED               (0x02)      // Set Bus Speed; arg = speed
#define I2C_BUS_CLEAR               (0x03)      // Execute Bus clear: send nine clock pulses
#define I2C_ABORT_TRANSFER          (0x04)      // Abort Master/Slave Transmit/Receive

/*----- I2C Bus Speed -----*/
#define I2C_BUS_SPEED_STANDARD      (0x01)      // Standard Speed (100kHz)
#define I2C_BUS_SPEED_FAST          (0x02)      // Fast Speed     (400kHz)
#define I2C_BUS_SPEED_FAST_PLUS     (0x03)      // Fast+ Speed    (  1MHz)
#define I2C_BUS_SPEED_HIGH          (0x04)      // High Speed     (3.4MHz)


/****** I2C Address Flags *****/

#define I2C_ADDRESS_10BIT           (0x0400)    // 10-bit address flag
#define I2C_ADDRESS_GC              (0x8000)    // General Call flag


/* I2C Status */
typedef volatile struct _I2C_STATUS {
    uint32_t busy             : 1;  // Busy flag
    uint32_t mode             : 1;  // Mode: 0=Slave, 1=Master
    uint32_t direction        : 1;  // Direction: 0=Transmitter, 1=Receiver
    uint32_t general_call     : 1;  // General Call indication (cleared on start of next Slave operation)
    uint32_t arbitration_lost : 1;  // Master lost arbitration (cleared on start of next Master operation)
    uint32_t bus_error        : 1;  // Bus error detected (cleared on start of next Master/Slave operation)
    uint32_t reserved         : 26;
} I2C_STATUS;


/****** I2C Event *****/
#define I2C_EVENT_TRANSFER_DONE       (1UL << 0)  // Master/Slave Transmit/Receive finished
#define I2C_EVENT_TRANSFER_INCOMPLETE (1UL << 1)  // Master/Slave Transmit/Receive incomplete transfer
#define I2C_EVENT_SLAVE_TRANSMIT      (1UL << 2)  // Addressed as Slave Transmitter but transmit operation is not set.
#define I2C_EVENT_SLAVE_RECEIVE       (1UL << 3)  // Addressed as Slave Receiver but receive operation is not set.
#define I2C_EVENT_ADDRESS_NACK        (1UL << 4)  // Address not acknowledged from Slave
#define I2C_EVENT_GENERAL_CALL        (1UL << 5)  // Slave addressed with general call address
#define I2C_EVENT_ARBITRATION_LOST    (1UL << 6)  // Master lost arbitration
#define I2C_EVENT_BUS_ERROR           (1UL << 7)  // Bus error detected (START/STOP at illegal position)
#define I2C_EVENT_BUS_CLEAR           (1UL << 8)  // Bus clear finished


typedef void (*I2C_SignalEvent_t) (uint32_t event);  // Pointer to \ref I2C_SignalEvent : Signal I2C Event.


/* I2C Driver Capabilities.  */
typedef struct _I2C_CAPABILITIES {
  uint32_t address_10_bit : 1;          // supports 10-bit addressing
  uint32_t reserved       : 31;         // Reserved (must be zero)
} I2C_CAPABILITIES;


/* Access structure of the I2C Driver. */
typedef struct _DRIVER_I2C {
	DRIVER_VERSION	 (*GetVersion)     (void);
	I2C_CAPABILITIES (*GetCapabilities)(void);
	int32_t		 (*Initialize)     (I2C_SignalEvent_t cb_event);
	int32_t		 (*Uninitialize)   (void);
	int32_t		 (*PowerControl)   (POWER_STATE state);
	int32_t		 (*MasterTransmit) (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending);
	int32_t		 (*MasterReceive)  (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending);
	int32_t		 (*SlaveTransmit)  (const uint8_t *data, uint32_t num);
	int32_t		 (*SlaveReceive)   (uint8_t *data, uint32_t num);
	int32_t		 (*GetDataCount)   (void);
	int32_t		 (*Control)        (uint32_t control, uint32_t arg);
	I2C_STATUS	 (*GetStatus)      (void);
} const DRIVER_I2C;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_I2C_H_ */
