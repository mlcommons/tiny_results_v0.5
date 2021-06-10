#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_spi.h>
#include <rv_i2c.h>
#include <rv_gpio.h>

#define BUFFER_SIZE 8
#define SLAVE_ADDR  0x0f

#define TRANSFER_SPEED 1250000

// SPI0 ~ SPI5
static DRIVER_SPI *SPI0 = &Driver_SPI0;

// I2C0 ~ I2C1
static DRIVER_I2C *I2C0 = &Driver_I2C0;

static DRIVER_GPIO *GPIO0 = &driver_gpio0;

uint8_t txbuf[BUFFER_SIZE];
uint8_t rxbuf[BUFFER_SIZE];

volatile int event;
volatile int flag;

void buffer_init(void)
{
    int i;

    printf("Initialize buffers, set both tx/rx buffers to 0...\n");

    for (i = 0; i < BUFFER_SIZE; i++) {
        txbuf[i] = 0;
        rxbuf[i] = 0;
    }

    printf("Buffers have been initialized.\n");
}

void i2c_cb_event (uint32_t e)
{
    event |= e;
}

void test_i2c(DRIVER_I2C *I2Cdrv)
{
    uint8_t is_master;
    int i;

    printf("Enter test_i2c\n");

    buffer_init();

    // Determine which machine we are in: Master or Slave
    GPIO0->set_direction(0, GPIO_PIN_DIRECTION_INPUT);
    is_master = GPIO0->read(0);

    if (is_master) { // For Master
        printf("This is I2C master.\n");

        // master delay
        while ( i++ < 8192) {
        }
        printf("Master is delayed.\n");

        // Prepare data
        for (i = 0; i < BUFFER_SIZE; i++) {
            txbuf[i] = i;
        }

        // Initialize I2C driver
        I2Cdrv->Initialize(i2c_cb_event);

        // Power up I2C
        I2Cdrv->PowerControl(POWER_FULL);

        // Configure I2C
        I2Cdrv->Control(I2C_BUS_SPEED, I2C_BUS_SPEED_FAST);
        I2Cdrv->Control(I2C_BUS_CLEAR, 0);

        // Send
        I2Cdrv->MasterTransmit(SLAVE_ADDR, txbuf, BUFFER_SIZE, false);
        while ((event & I2C_EVENT_TRANSFER_DONE) == 0) {};
        event &= ~I2C_EVENT_TRANSFER_DONE;
        printf("Send done.\n");

        // Receive
        I2Cdrv->MasterReceive(SLAVE_ADDR, rxbuf, BUFFER_SIZE, false);
        while ((event & I2C_EVENT_TRANSFER_DONE) == 0) {};
        event &= ~I2C_EVENT_TRANSFER_DONE;
        printf("Receive done.\n");

        // Print received data
        for (i = 0; i < BUFFER_SIZE; i++) {
            printf("rxbuf[%d] = 0x%x\n", i, rxbuf[i]);
        }
    } else {
        printf("This is I2C slave.\n");

        // Prepare data
        for (i = 0; i < BUFFER_SIZE; i++) {
            txbuf[i] = BUFFER_SIZE - i - 1;
        }

        // Initialize I2C driver
        I2Cdrv->Initialize(i2c_cb_event);

        // Power up I2C
        I2Cdrv->PowerControl(POWER_FULL);

        // Configure I2C
        I2Cdrv->Control(I2C_OWN_ADDRESS, SLAVE_ADDR);

        // Receive
        I2Cdrv->SlaveReceive(rxbuf, BUFFER_SIZE);
        while ((event & I2C_EVENT_TRANSFER_DONE) == 0) {};
        event &= ~I2C_EVENT_TRANSFER_DONE;

        // Send
        I2Cdrv->SlaveTransmit(txbuf, BUFFER_SIZE);
        while ((event & I2C_EVENT_TRANSFER_DONE) == 0) {};
        event &= ~I2C_EVENT_TRANSFER_DONE;
        printf("Transfer done.\n");

        // Print received data
        for (i = 0; i < BUFFER_SIZE; i++) {
            printf("rxbuf[%d] = 0x%x\n", i, rxbuf[i]);
        }
    }

    I2Cdrv->Uninitialize();
}

void spi_cb_event (uint32_t event)
{
    switch (event) {
    case SPI_EVENT_TRANSFER_COMPLETE:
        // Success
        flag = 1;
        break;
    case SPI_EVENT_DATA_LOST:
        break;
    case SPI_EVENT_MODE_FAULT:
        break;
    }
}

void test_spi(DRIVER_SPI *SPIdrv_master, DRIVER_SPI *SPIdrv_slave)
{
    uint8_t is_master;
    int i;

    printf("Enter test_spi\n");

    buffer_init();

    // Determine which machine we are in: Master or Slave
    GPIO0->set_direction(0, GPIO_PIN_DIRECTION_INPUT);
    is_master = GPIO0->read(0);

    if (is_master) { // For Master
        printf("This is Master.\n");

        while (i++ < 8192) {}
        printf("master is delayed.\n");

        // Prepare data
        for (i = 0; i < BUFFER_SIZE; i++) {
            txbuf[i] = i;
        }

        // Initialization SPI driver
        SPIdrv_master->Initialize(spi_cb_event);

        // Power up the SPI peripheral
        SPIdrv_master->PowerControl(POWER_FULL);

        SPIdrv_master->Control(SPI_SET_DEFAULT_TX_VALUE, 0xab);

        // Configure the SPI to Master, 8-bit mode @1.25 mBits/Sec
        SPIdrv_master->Control(SPI_MODE_MASTER |
                               SPI_CPOL1_CPHA1 |
                               SPI_MSB_LSB |
                               SPI_SS_MASTER_UNUSED |
                               SPI_DATA_BITS(8),
                               TRANSFER_SPEED);

        // Send
        flag = 0;
        SPIdrv_master->Transfer(txbuf, rxbuf, BUFFER_SIZE);

        // Wait for completion
        while (flag == 0) {};
        printf("Transfered %ld bytes.\n", SPIdrv_master->GetDataCount());

        SPIdrv_master->Control(SPI_MODE_INACTIVE, 0);

        // Print received data
        for (i = 0; i < BUFFER_SIZE; i++) {
            printf("rxbuf[%d] = 0x%x\n", i, rxbuf[i]);
        }

        SPIdrv_master->Uninitialize();
    } else { // For Slave
        printf("This is Slave.\n");

        RV32_CRU->PAD_CTL_0 = 0x1010000;

        // Prepare data
        for (i = 0; i < BUFFER_SIZE; i++) {
            txbuf[i] = BUFFER_SIZE - i - 1;
        }

        // Driver initialization
        SPIdrv_slave->Initialize(spi_cb_event);

        // Power up the SPI peripheral
        SPIdrv_slave->PowerControl(POWER_FULL);

        SPIdrv_slave->Control(SPI_SET_DEFAULT_TX_VALUE, 0xab);

        SPIdrv_slave->Control(SPI_MODE_SLAVE |
                              SPI_CPOL1_CPHA1 |
                              SPI_MSB_LSB |
                              SPI_SS_SLAVE_HW |
                              SPI_DATA_BITS(8),
                              TRANSFER_SPEED);

        // Receive
        flag = 0;
        SPIdrv_slave->Transfer(txbuf, rxbuf, BUFFER_SIZE);

        // Wait for completion
        while (flag == 0) {};
        printf("Transfered %ld bytes.\n", SPIdrv_slave->GetDataCount());

        SPIdrv_slave->Control(SPI_MODE_INACTIVE, 0);

        // Print received data
        for (i = 0; i < BUFFER_SIZE; i++) {
            printf("rxbuf[%d] = 0x%x\n", i , rxbuf[i]);
        }

        SPIdrv_slave->Uninitialize();
    }

}

void dual_io_test(void)
{
    test_i2c(I2C0);
    test_spi(SPI0, SPI0);
}
