#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include "driver_common.h"

#define USART_API_VERSION DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

/* USART Control Codes */

#define USART_CONTROL_Pos                0
#define USART_CONTROL_Msk               (0xFFUL << USART_CONTROL_Pos)

/* USART Control Codes: Mode */
#define USART_MODE_ASYNCHRONOUS         (0x01UL << USART_CONTROL_Pos)
#define USART_MODE_SYNCHRONOUS_MASTER   (0x02UL << USART_CONTROL_Pos)
#define USART_MODE_SYNCHRONOUS_SLAVE    (0x03UL << USART_CONTROL_Pos)
#define USART_MODE_SINGLE_WIRE          (0x04UL << USART_CONTROL_Pos)
#define USART_MODE_IRDA                 (0x05UL << USART_CONTROL_Pos)
#define USART_MODE_SMART_CARD           (0x06UL << USART_CONTROL_Pos)

/* USART Control Codes: Mode Parameters: Data Bits */
#define USART_DATA_BITS_Pos              8
#define USART_DATA_BITS_Msk             (7UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_5               (5UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_6               (6UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_7               (7UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_8               (0UL << USART_DATA_BITS_Pos)
#define USART_DATA_BITS_9               (1UL << USART_DATA_BITS_Pos)

/* USART Control Codes: Mode Parameters: Parity */
#define USART_PARITY_Pos                 12
#define USART_PARITY_Msk                (3UL << USART_PARITY_Pos)
#define USART_PARITY_NONE               (0UL << USART_PARITY_Pos)
#define USART_PARITY_EVEN               (1UL << USART_PARITY_Pos)
#define USART_PARITY_ODD                (2UL << USART_PARITY_Pos)

/* USART Control Codes: Mode Parameters: Stop Bits */
#define USART_STOP_BITS_Pos              14
#define USART_STOP_BITS_Msk             (3UL << USART_STOP_BITS_Pos)
#define USART_STOP_BITS_1               (0UL << USART_STOP_BITS_Pos)
#define USART_STOP_BITS_2               (1UL << USART_STOP_BITS_Pos)
#define USART_STOP_BITS_1_5             (2UL << USART_STOP_BITS_Pos)
#define USART_STOP_BITS_0_5             (3UL << USART_STOP_BITS_Pos)

/* USART Control Codes: Mode Parameters: Flow Control */
#define USART_FLOW_CONTROL_Pos           16
#define USART_FLOW_CONTROL_Msk          (3UL << USART_FLOW_CONTROL_Pos)
#define USART_FLOW_CONTROL_NONE         (0UL << USART_FLOW_CONTROL_Pos)
#define USART_FLOW_CONTROL_RTS          (1UL << USART_FLOW_CONTROL_Pos)
#define USART_FLOW_CONTROL_CTS          (2UL << USART_FLOW_CONTROL_Pos)
#define USART_FLOW_CONTROL_RTS_CTS      (3UL << USART_FLOW_CONTROL_Pos)

/* USART Control Codes: Mode Parameters: Clock Polarity (Synchronous mode) */
#define USART_CPOL_Pos                   18
#define USART_CPOL_Msk                  (1UL << USART_CPOL_Pos)
#define USART_CPOL0                     (0UL << USART_CPOL_Pos)
#define USART_CPOL1                     (1UL << USART_CPOL_Pos)

/* USART Control Codes: Mode Parameters: Clock Phase (Synchronous mode) */
#define USART_CPHA_Pos                   19
#define USART_CPHA_Msk                  (1UL << USART_CPHA_Pos)
#define USART_CPHA0                     (0UL << USART_CPHA_Pos)
#define USART_CPHA1                     (1UL << USART_CPHA_Pos)


/* USART Control Codes: Miscellaneous Controls */
#define USART_SET_DEFAULT_TX_VALUE      (0x10UL << USART_CONTROL_Pos)  
#define USART_SET_IRDA_PULSE            (0x11UL << USART_CONTROL_Pos)
#define USART_SET_SMART_CARD_GUARD_TIME (0x12UL << USART_CONTROL_Pos)
#define USART_SET_SMART_CARD_CLOCK      (0x13UL << USART_CONTROL_Pos)
#define USART_CONTROL_SMART_CARD_NACK   (0x14UL << USART_CONTROL_Pos)
#define USART_CONTROL_TX                (0x15UL << USART_CONTROL_Pos)
#define USART_CONTROL_RX                (0x16UL << USART_CONTROL_Pos)
#define USART_CONTROL_BREAK             (0x17UL << USART_CONTROL_Pos)
#define USART_ABORT_SEND                (0x18UL << USART_CONTROL_Pos)
#define USART_ABORT_RECEIVE             (0x19UL << USART_CONTROL_Pos)
#define USART_ABORT_TRANSFER            (0x1AUL << USART_CONTROL_Pos)

/* USART specific error codes */
#define USART_ERROR_MODE                (DRIVER_ERROR_SPECIFIC - 1)
#define USART_ERROR_BAUDRATE            (DRIVER_ERROR_SPECIFIC - 2)
#define USART_ERROR_DATA_BITS           (DRIVER_ERROR_SPECIFIC - 3)
#define USART_ERROR_PARITY              (DRIVER_ERROR_SPECIFIC - 4)
#define USART_ERROR_STOP_BITS           (DRIVER_ERROR_SPECIFIC - 5)
#define USART_ERROR_FLOW_CONTROL        (DRIVER_ERROR_SPECIFIC - 6)
#define USART_ERROR_CPOL                (DRIVER_ERROR_SPECIFIC - 7)
#define USART_ERROR_CPHA                (DRIVER_ERROR_SPECIFIC - 8)

/* USART Status */
typedef volatile struct _USART_STATUS {
	uint32_t tx_busy          : 1;
	uint32_t rx_busy          : 1;
	uint32_t tx_underflow     : 1;
	uint32_t rx_overflow      : 1;
	uint32_t rx_break         : 1;
	uint32_t rx_framing_error : 1;
	uint32_t rx_parity_error  : 1;
	uint32_t reserved         : 25;
} USART_STATUS;

/* USART Modem Control */
typedef enum _USART_MODEM_CONTROL {
	USART_RTS_CLEAR,
	USART_RTS_SET,
	USART_DTR_CLEAR,
	USART_DTR_SET
} USART_MODEM_CONTROL;

/* USART Modem Status */
typedef volatile struct _USART_MODEM_STATUS {
	uint32_t cts      : 1;
	uint32_t dsr      : 1;
	uint32_t dcd      : 1;
	uint32_t ri       : 1;
	uint32_t reserved : 28;
} USART_MODEM_STATUS;


/****** USART Event *****/
#define USART_EVENT_SEND_COMPLETE       (1UL << 0)
#define USART_EVENT_RECEIVE_COMPLETE    (1UL << 1)
#define USART_EVENT_TRANSFER_COMPLETE   (1UL << 2)
#define USART_EVENT_TX_COMPLETE         (1UL << 3)
#define USART_EVENT_TX_UNDERFLOW        (1UL << 4)
#define USART_EVENT_RX_OVERFLOW         (1UL << 5)
#define USART_EVENT_RX_TIMEOUT          (1UL << 6)
#define USART_EVENT_RX_BREAK            (1UL << 7)
#define USART_EVENT_RX_FRAMING_ERROR    (1UL << 8)
#define USART_EVENT_RX_PARITY_ERROR     (1UL << 9)
#define USART_EVENT_CTS                 (1UL << 10)
#define USART_EVENT_DSR                 (1UL << 11)
#define USART_EVENT_DCD                 (1UL << 12)
#define USART_EVENT_RI                  (1UL << 13)

typedef void (*USART_SignalEvent_t) (uint32_t event);

/* USART Device Driver Capabilities. */
typedef struct _USART_CAPABILITIES {
	uint32_t asynchronous       : 1;
	uint32_t synchronous_master : 1;
	uint32_t synchronous_slave  : 1;
	uint32_t single_wire        : 1;
	uint32_t irda               : 1;
	uint32_t smart_card         : 1;
	uint32_t smart_card_clock   : 1;
	uint32_t flow_control_rts   : 1;
	uint32_t flow_control_cts   : 1;
	uint32_t event_tx_complete  : 1;
	uint32_t event_rx_timeout   : 1;
	uint32_t rts                : 1;
	uint32_t cts                : 1;
	uint32_t dtr                : 1;
	uint32_t dsr                : 1;
	uint32_t dcd                : 1;
	uint32_t ri                 : 1;
	uint32_t event_cts          : 1;
	uint32_t event_dsr          : 1;
	uint32_t event_dcd          : 1;
	uint32_t event_ri           : 1;
	uint32_t reserved           : 11;
} USART_CAPABILITIES;

/* Access structure of the USART Driver. */
typedef struct _DRIVER_USART {
	DRIVER_VERSION		(*GetVersion)      (void);
	USART_CAPABILITIES	(*GetCapabilities) (void);
	int32_t			(*Initialize)      (USART_SignalEvent_t cb_event);
	int32_t			(*Uninitialize)    (void);
	int32_t			(*PowerControl)    (POWER_STATE state);
	int32_t			(*Send)            (const void *data, uint32_t num);
	int32_t			(*Receive)         (void *data, uint32_t num);
	int32_t			(*Transfer)        (const void *data_out,
						    void *data_in,
						    uint32_t    num);
	uint32_t		(*GetTxCount)      (void);
	uint32_t		(*GetRxCount)      (void);
	int32_t			(*Control)         (uint32_t control, uint32_t arg);
	USART_STATUS		(*GetStatus)       (void);
	int32_t			(*SetModemControl) (USART_MODEM_CONTROL control);
	USART_MODEM_STATUS	(*GetModemStatus)  (void);
} const DRIVER_USART;


#endif /* __DRIVER_USART_H__ */
