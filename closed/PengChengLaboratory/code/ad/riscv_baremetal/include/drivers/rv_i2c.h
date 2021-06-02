#ifndef __rv_i2c_h__
#define __rv_i2c_h__
#include <i2c.h>
#include <driver_i2c.h>

#define IC_CLK  208
#define NANO_TO_MICRO           1000

/* High and low times in different speed modes (in ns) */
#define MIN_SS_SCL_HIGHTIME     4000
#define MIN_SS_SCL_LOWTIME      4700
#define MIN_FS_SCL_HIGHTIME     600
#define MIN_FS_SCL_LOWTIME      1300
#define MIN_HS_SCL_HIGHTIME     60
#define MIN_HS_SCL_LOWTIME      160

/* i2c control register definitions */
#define IC_CON_SPD_SS           0x0002
#define IC_CON_SPD_FS           0x0004
#define IC_CON_SPD_HS           0x0006
#define IC_CON_MM               0x0001

/* I2C Driver state flags */
#define I2C_FLAG_INIT       (1 << 0)        // Driver initialized
#define I2C_FLAG_POWER      (1 << 1)        // Driver power on
#define I2C_FLAG_SETUP      (1 << 2)        // Master configured, clock set
#define I2C_FLAG_SLAVE_RX   (1 << 3)        // Slave receive registered

/* I2C Stalled Status flags */
#define I2C_MASTER          (1 << 0)        // Master stalled
#define I2C_SLAVE_TX        (1 << 1)        // Slave stalled on transmit
#define I2C_SLAVE_RX        (1 << 2)        // Slave stalled on receive
#define I2C_SLAVE           (I2C_SLAVE_TX | I2C_SLAVE_RX)


/* I2C Control Information */
typedef struct {
  I2C_SignalEvent_t         cb_event;      // Event callback
  I2C_STATUS                status;        // Status flags
  uint8_t                   flags;         // Control and state flags
  uint8_t                   sla_rw;        // Slave address and RW bit
  bool                      pending;       // Transfer pending (no STOP)
  uint8_t                   stalled;       // Stall mode status flags
  uint8_t                   con_aa;        // I2C slave CON flag
  int32_t                   cnt;           // Master transfer count
  uint8_t                  *data;          // Master data to transfer
  uint32_t                  num;           // Number of bytes to transfer
  uint8_t                  *sdata;         // Slave data to transfer
  uint32_t                  snum;          // Number of bytes to transfer
} I2C_CTRL;

/* I2C Resource Configuration */
typedef struct {
  rv32_i2c_t             *reg;           // I2C register interface
  uint32_t                  i2c_irq;       // I2C Event IRQ Number
  I2C_CTRL                 *ctrl;          // Run-Time control information
} const I2C_RESOURCES;

extern DRIVER_I2C Driver_I2C0;
extern DRIVER_I2C Driver_I2C1;

#endif /* __rv_i2c_h__ */
