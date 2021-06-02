#ifndef __platform_h__
#define __platform_h__

#include <config.h>
#include <stdint.h>

#include <cru.h>
#include <event_unit.h>
#include <ictl.h>
#include <can.h>
#include <dma.h>
#include <emac.h>
#include <flash_cache.h>
#include <gpio.h>
#include <i2c.h>
#include <i2s_master.h>
#include <i2s_slave.h>
#include <spi_flash.h>
#include <spi.h>
#include <systick.h>
#include <timer.h>
#include <trng.h>
#include <uart.h>
#include <usb.h>
#include <wdt.h>

/* Device Type Definitions */
typedef struct memblock {
	uint32_t start;
	uint32_t size;
} memblock_t;

/* Address Map */
#define RV32_ROM_BASE             0x00000000UL
#define RV32_EFLASH_BASE		    0x00400000UL
#define RV32_SRAM_BASE		    0x00800000UL
#define RV32_EXT_FLASH_BASE		0x20000000UL
#define RV32_USB_BASE			    0x40000000UL
#define RV32_DEBUG_SLAVE_BASE		0x40010000UL
#define RV32_DMAC_REG0_BASE		0x40020000UL
#define RV32_DMAC_REG1_BASE		0x40021000UL
#define RV32_CRU_BASE			    0x40022000UL
#define RV32_EFLASH_CTRL_BASE		0x40023000UL
#define RV32_FLASHCACHE_CTRL_BASE	0x40024000UL
#define RV32_IC_BASE			    0x40025000UL
#define RV32_ICTL_BASE            0x40026000UL
#define RV32_EMAC_BASE		    0x40028000UL
#define RV32_GPIO0_BASE		    0x40030000UL
#define RV32_GPIO1_BASE		    0x40031000UL
#define RV32_GPIO2_BASE		    0x40032000UL
#define RV32_GPIO3_BASE		    0x40033000UL
#define RV32_GPIO4_BASE		    0x40034000UL
#define RV32_UART0_BASE		    0x40035000UL
#define RV32_UART1_BASE		    0x40036000UL
#define RV32_UART2_BASE		    0x40037000UL
#define RV32_UART3_BASE		    0x40038000UL
#define RV32_UART4_BASE		    0x40039000UL
#define RV32_SPI0_BASE		    0x4003a000UL
#define RV32_SPI1_BASE		    0x4003b000UL
#define RV32_SPI2_BASE		    0x4003c000UL
#define RV32_SPI3_BASE		    0x4003d000UL
#define RV32_SPI4_BASE		    0x4003e000UL
#define RV32_SPI5_BASE		    0x4003f000UL
#define RV32_TIMER0_BASE		    0x40040000UL
#define RV32_TIMER1_BASE		    0x40041000UL
#define RV32_TIMER2_BASE		    0x40042000UL
#define RV32_TIMER3_BASE		    0x40043000UL
#define RV32_TIMER4_BASE		    0x40044000UL
#define RV32_TIMER5_BASE		    0x40045000UL
#define RV32_SYSTICK_TIMER_BASE	0x40046000UL
#define RV32_WDT_BASE			    0x40047000UL
#define RV32_I2C0_BASE		    0x40048000UL
#define RV32_I2C1_BASE		    0x40049000UL
#define RV32_I2S0_BASE		    0x4004a000UL
#define RV32_I2S1_BASE		    0x4004b000UL
#define RV32_CAN0_BASE		    0x4004c000UL
#define RV32_CAN1_BASE		    0x4004d000UL
#define RV32_TRNG_BASE		    0x4004e000UL
#define RV32_I2S_SLAVE_BASE		0x4004f000UL

/* Irq Number */
#define RV32_ERROR_IRQn           0
#define RV32_DMAC0_IRQn           1
#define RV32_I2S1_IRQn            2
#define RV32_I2S0_IRQn            3
#define RV32_I2C1_IRQn            4
#define RV32_I2C0_IRQn            5
#define RV32_WDT_IRQn             6
#define RV32_SYSTICK_IRQn         7
#define RV32_SPI0_IRQn            8
#define RV32_TIMER4_IRQn          9
#define RV32_TIMER3_IRQn          10
#define RV32_TIMER2_IRQn          11
#define RV32_TIMER1_IRQn          12
#define RV32_TIMER0_IRQn          13
#define RV32_SPI1_IRQn            14
#define RV32_UART3_IRQn           15
#define RV32_UART2_IRQn           16
#define RV32_UART1_IRQn           17
#define RV32_UART0_IRQn           18
#define RV32_TRNG_IRQn            19
#define RV32_ICTL_IRQn            20
#define RV32_EMAC_IRQn            21
#define RV32_I2SSLAVE_IRQn        22
#define RV32_SPI2_IRQn            23
#define RV32_GPIO3_IRQn           24
#define RV32_GPIO2_IRQn           25
#define RV32_GPIO1_IRQn           26
#define RV32_GPIO0_IRQn           27
#define RV32_DMAC1_IRQn           28
#define RV32_FCU_IRQn             29
#define RV32_CAN1_IRQn            30
#define RV32_CAN0_IRQn            31

#define SECONDARY_BASE              32

// Secondary IRQn
#define RV32_FLASHCACHE_SECIRQn   (0+SECONDARY_BASE)
#define RV32_TIMER5_SECIRQn       (1+SECONDARY_BASE)
#define RV32_UART4_SECIRQn        (2+SECONDARY_BASE)
#define RV32_GPIO4_SECIRQn        (3+SECONDARY_BASE)
#define RV32_SPI3_SECIRQn         (4+SECONDARY_BASE)
#define RV32_SPI4_SECIRQn         (5+SECONDARY_BASE)
#define RV32_SPI5_SECIRQn         (6+SECONDARY_BASE)
#define RV32_USB_SECIRQn          (7+SECONDARY_BASE)

/* Device Definitions */
#define RV32_USB0             ((rv32_usb_t *)          RV32_USB_BASE)
#define RV32_DMA0             ((rv32_dma_t *)          RV32_DMAC_REG0_BASE)
#define RV32_DMA1             ((rv32_dma_t *)          RV32_DMAC_REG1_BASE)
#define RV32_CRU              ((rv32_cru_t *)          RV32_CRU_BASE)
#define RV32_EFLASH_CTRL      ((rv32_eflash_t *)       RV32_EFLASH_CTRL_BASE)
#define RV32_FLASHCACHE_CTRL  ((rv32_flashcache_t *)   RV32_FLASHCACHE_CTRL_BASE)
#define RV32_IC               ((rv32_ic_t *)           RV32_IC_BASE)
#define RV32_ICTL             ((rv32_ictl_t *)         RV32_ICTL_BASE)
#define RV32_EMAC0            ((rv32_emac_t *)         RV32_EMAC_BASE)
#define RV32_GPIO0            ((rv32_gpio_t *)         RV32_GPIO0_BASE)
#define RV32_GPIO1            ((rv32_gpio_t *)         RV32_GPIO1_BASE)
#define RV32_GPIO2            ((rv32_gpio_t *)         RV32_GPIO2_BASE)
#define RV32_GPIO3            ((rv32_gpio_t *)         RV32_GPIO3_BASE)
#define RV32_GPIO4            ((rv32_gpio_t *)         RV32_GPIO4_BASE)
#define RV32_UART0            ((rv32_uart_t *)         RV32_UART0_BASE)
#define RV32_UART1            ((rv32_uart_t *)         RV32_UART1_BASE)
#define RV32_UART2            ((rv32_uart_t *)         RV32_UART2_BASE)
#define RV32_UART3            ((rv32_uart_t *)         RV32_UART3_BASE)
#define RV32_UART4            ((rv32_uart_t *)         RV32_UART4_BASE)
#define RV32_SPI0             ((rv32_spi_t *)          RV32_SPI0_BASE)
#define RV32_SPI1             ((rv32_spi_t *)          RV32_SPI1_BASE)
#define RV32_SPI2             ((rv32_spi_t *)          RV32_SPI2_BASE)
#define RV32_SPI3             ((rv32_spi_t *)          RV32_SPI3_BASE)
#define RV32_SPI4             ((rv32_spi_t *)          RV32_SPI4_BASE)
#define RV32_SPI5             ((rv32_spi_t *)          RV32_SPI5_BASE)
#define RV32_TIMER0           ((rv32_timer_t *)        RV32_TIMER0_BASE)
#define RV32_TIMER1           ((rv32_timer_t *)        RV32_TIMER1_BASE)
#define RV32_TIMER2           ((rv32_timer_t *)        RV32_TIMER2_BASE)
#define RV32_TIMER3           ((rv32_timer_t *)        RV32_TIMER3_BASE)
#define RV32_TIMER4           ((rv32_timer_t *)        RV32_TIMER4_BASE)
#define RV32_TIMER5           ((rv32_timer_t *)        RV32_TIMER5_BASE)
#define RV32_SYSTICK_TIMER	((rv32_system_tick_t *)	RV32_SYSTICK_TIMER_BASE)
#define RV32_WDT              ((rv32_wdt_t *)          RV32_WDT_BASE)
#define RV32_I2C0             ((rv32_i2c_t *)          RV32_I2C0_BASE)
#define RV32_I2C1             ((rv32_i2c_t *)          RV32_I2C1_BASE)
#define RV32_I2S0             ((rv32_i2s_t *)          RV32_I2S0_BASE)
#define RV32_I2S1             ((rv32_i2s_t *)          RV32_I2S1_BASE)
#define RV32_CAN0             ((rv32_can_t *)          RV32_CAN0_BASE)
#define RV32_CAN1             ((rv32_can_t *)          RV32_CAN1_BASE)
#define RV32_TRNG0            ((rv32_trng_t *)         RV32_TRNG_BASE)
#define RV32_I2S_SLAVE        ((rv32_i2s_t *)          RV32_I2S_SLAVE_BASE)

extern uint32_t get_system_clocks(void);

#endif
