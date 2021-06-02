#ifndef __cru_h__
#define __cru_h__
#include <stdint.h>

typedef struct rv32_cru {
    volatile uint32_t RESET_SOURCE;     // 0x000
    volatile uint32_t SOFT_RESET;       // 0x004
    volatile uint32_t LOCAL_RST_0;      // 0x008
    volatile uint32_t LOCAL_RST_1;      // 0x00c
    volatile uint32_t RST_MASK;         // 0x010
    volatile uint32_t RES0[3];
    volatile uint32_t WAIT01;           // 0x020
    volatile uint32_t WAIT23;           // 0x024
    volatile uint32_t WAITLP;           // 0x028
    volatile uint32_t RES1;
    volatile uint32_t PLL_CONF;         // 0x030
    volatile uint32_t PLL_CONF_REAL;    // 0x034
    volatile uint32_t PLL_LOCK;         // 0x038
    volatile uint32_t RES2[9];
    volatile uint32_t CLK_STOP_0;       // 0x060
    volatile uint32_t CLK_STOP_1;       // 0x064
    volatile uint32_t RES3[38];
    volatile uint32_t PAD_CTL_0;        // 0x100
    volatile uint32_t PAD_CTL_1;        // 0x104
    volatile uint32_t PAD_CTL_2;        // 0x108
    volatile uint32_t PAD_CTL_3;        // 0x10c
    volatile uint32_t PAD_CTL_4;        // 0x110
    volatile uint32_t PAD_CTL_5;        // 0x114
    volatile uint32_t RES4[46];
    volatile uint32_t DMA0_SEL_0;       // 0x1d0
    volatile uint32_t DMA0_SEL_1;       // 0x1d4
    volatile uint32_t DMA1_SEL_0;       // 0x1d8
    volatile uint32_t DMA1_SEL_1;       // 0x1dc
    volatile uint32_t RES5[8];
    volatile uint32_t GMU_CTL;          // 0x200
    volatile uint32_t DM_STATUS;        // 0x204
} rv32_cru_t;

#define CRU_RESET_SOURCE_Msk                0xf
#define CRU_RESET_SOURCE_COLD               0x1
#define CRU_RESET_SOURCE_SOFT               0x2
#define CRU_RESET_SOURCE_LOCAL              0x4
#define CRU_RESET_SOURCE_WDT                0x8


#define CRU_SOFT_RESET_Msk                  0x1

#define CRU_LOCAL_RST_0_GPIO0_Msk           (1U << 31)
#define CRU_LOCAL_RST_0_GPIO1_Msk           (1U << 30)
#define CRU_LOCAL_RST_0_GPIO2_Msk           (1U << 29)
#define CRU_LOCAL_RST_0_GPIO3_Msk           (1U << 28)
#define CRU_LOCAL_RST_0_GPIO4_Msk           (1U << 27)
#define CRU_LOCAL_RST_0_I2C8_Msk            (1U << 26)
#define CRU_LOCAL_RST_0_I2C9_Msk            (1U << 25)
#define CRU_LOCAL_RST_0_I2S10_Msk           (1U << 24)
#define CRU_LOCAL_RST_0_I2S11_Msk           (1U << 23)
#define CRU_LOCAL_RST_0_I2S_SLAVE_Msk       (1U << 22)
#define CRU_LOCAL_RST_0_SPI_FLASH_Msk       (1U << 21)
#define CRU_LOCAL_RST_0_SSP10_Msk           (1U << 20)
#define CRU_LOCAL_RST_0_SSP11_Msk           (1U << 19)
#define CRU_LOCAL_RST_0_SSP12_Msk           (1U << 18)
#define CRU_LOCAL_RST_0_SSP13_Msk           (1U << 17)
#define CRU_LOCAL_RST_0_SSP14_Msk           (1U << 16)
#define CRU_LOCAL_RST_0_SSP15_Msk           (1U << 15)
#define CRU_LOCAL_RST_0_SYSTIMER_Msk        (1U << 14)
#define CRU_LOCAL_RST_0_TIMER0_Msk          (1U << 13)
#define CRU_LOCAL_RST_0_TIMER1_Msk          (1U << 12)
#define CRU_LOCAL_RST_0_TIMER2_Msk          (1U << 11)
#define CRU_LOCAL_RST_0_TIMER3_Msk          (1U << 10)
#define CRU_LOCAL_RST_0_TIMER4_Msk          (1U << 9)
#define CRU_LOCAL_RST_0_TIMER5_Msk          (1U << 8)
#define CRU_LOCAL_RST_0_TRNG_Msk            (1U << 7)
#define CRU_LOCAL_RST_0_UART5_Msk           (1U << 6)
#define CRU_LOCAL_RST_0_UART6_Msk           (1U << 5)
#define CRU_LOCAL_RST_0_UART7_Msk           (1U << 4)
#define CRU_LOCAL_RST_0_UART8_Msk           (1U << 3)
#define CRU_LOCAL_RST_0_UART9_Msk           (1U << 2)
#define CRU_LOCAL_RST_0_WDT_Msk             (1U << 1)
#define CRU_LOCAL_RST_0_NVIC_Msk            (1U << 0)

#define CRU_LOCAL_RST_1_CORE_Msk            (1U << 11)
#define CRU_LOCAL_RST_1_EFLASH_Msk          (1U << 10)
#define CRU_LOCAL_RST_1_FLASH_CACHE_Msk     (1U << 9)
#define CRU_LOCAL_RST_1_GMU_Msk             (1U << 8)
#define CRU_LOCAL_RST_1_OCN_Msk             (1U << 7)
#define CRU_LOCAL_RST_1_ROM_Msk             (1U << 6)
#define CRU_LOCAL_RST_1_SRAM_Msk            (1U << 5)
#define CRU_LOCAL_RST_1_USB_Msk             (1U << 4)
#define CRU_LOCAL_RST_1_DMAC0_Msk           (1U << 3)
#define CRU_LOCAL_RST_1_DMAC1_Msk           (1U << 2)
#define CRU_LOCAL_RST_1_CAN12_Msk           (1U << 1)
#define CRU_LOCAL_RST_1_CAN13_Msk           (1U << 0)

#define CRU_RST_MASK_Msk                    0x1

#define CRU_WAIT_01_WAIT0_Pos               (0)
#define CRU_WAIT_01_WAIT0_Msk               (0xff << CRU_WAIT_01_WAIT0_Pos)
#define CRU_WAIT_01_WAIT1_Pos               (16)
#define CRU_WAIT_01_WAIT1_Msk               (0xff << CRU_WAIT_01_WAIT1_Pos)

#define CRU_WAIT_23_WAIT2_Pos               (0)
#define CRU_WAIT_23_WAIT2_Msk               (0xff << CRU_WAIT_23_WAIT2_Pos)
#define CRU_WAIT_23_WAIT3_Pos               (16)
#define CRU_WAIT_23_WAIT3_Msk               (0xff << CRU_WAIT_23_WAIT3_Pos)

#define CRU_WAIT_LP_WAIT_LOCAL_Pos          (0)
#define CRU_WAIT_LP_WAIT_LOCAL_Msk          (0xff << CRU_WAIT_LP_WAIT_LOCAL_Pos)
#define CRU_WAIT_LP_WAIT_PLL_Pos            (16)
#define CRU_WAIT_LP_WAIT_PLL_Msk            (0xff << CRU_WAIT_LP_WAIT_PLL_Pos)

#define CRU_PLL_CONF_M_Pos                  (0)
#define CRU_PLL_CONF_M_Msk                  (0xff << CRU_PLL_CONF_M_Pos)
#define CRU_PLL_CONF_N_Pos                  (8)
#define CRU_PLL_CONF_N_Msk                  (0xf << CRU_PLL_CONF_N_Pos)
#define CRU_PLL_CONF_OD_Pos                 (16)
#define CRU_PLL_CONF_OD_Msk                 (0x3 << CRU_PLL_CONF_OD_Pos)

#define CRU_PLL_CONF_REAL_M_Pos             (0)
#define CRU_PLL_CONF_REAL_M_Msk             (0xff << CRU_PLL_CONF_M_Pos)
#define CRU_PLL_CONF_REAL_N_Pos             (8)
#define CRU_PLL_CONF_REAL_N_Msk             (0xf << CRU_PLL_CONF_N_Pos)
#define CRU_PLL_CONF_REAL_OD_Pos            (16)
#define CRU_PLL_CONF_REAL_OD_Msk            (0x3 << CRU_PLL_CONF_OD_Pos)

#define CRU_PLL_LOCK_Msk                    0x1

#define CRU_CLK_STOP_0_I2S_SLAVE_O_Msk      (1U << 0)
#define CRU_CLK_STOP_0_I2S11_O_Msk          (1U << 1)
#define CRU_CLK_STOP_0_I2S10_O_Msk          (1U << 2)
#define CRU_CLK_STOP_0_50_Msk               (1U << 3)
#define CRU_CLK_STOP_0_FREERUN_TIMER_Msk    (1U << 4)
#define CRU_CLK_STOP_0_USB_48M_Msk          (1U << 5)
#define CRU_CLK_STOP_0_NVIC_Msk             (1U << 6)
#define CRU_CLK_STOP_0_WDT_Msk              (1U << 7)
#define CRU_CLK_STOP_0_UART9_Msk            (1U << 8)
#define CRU_CLK_STOP_0_UART8_Msk            (1U << 9)
#define CRU_CLK_STOP_0_UART7_Msk            (1U << 10)
#define CRU_CLK_STOP_0_UART6_Msk            (1U << 11)
#define CRU_CLK_STOP_0_UART5_Msk            (1U << 12)
#define CRU_CLK_STOP_0_TRNG_Msk             (1U << 13)
#define CRU_CLK_STOP_0_TIMER5_Msk           (1U << 14)
#define CRU_CLK_STOP_0_TIMER4_Msk           (1U << 15)
#define CRU_CLK_STOP_0_TIMER3_Msk           (1U << 16)
#define CRU_CLK_STOP_0_TIMER2_Msk           (1U << 17)
#define CRU_CLK_STOP_0_TIMER1_Msk           (1U << 18)
#define CRU_CLK_STOP_0_TIMER0_Msk           (1U << 19)
#define CRU_CLK_STOP_0_SYSTIMER_Msk         (1U << 20)
#define CRU_CLK_STOP_0_SSP15_Msk            (1U << 21)
#define CRU_CLK_STOP_0_SSP14_Msk            (1U << 22)
#define CRU_CLK_STOP_0_SSP13_Msk            (1U << 23)
#define CRU_CLK_STOP_0_SSP12_Msk            (1U << 24)
#define CRU_CLK_STOP_0_SSP11_Msk            (1U << 25)
#define CRU_CLK_STOP_0_SSP10_Msk            (1U << 26)
#define CRU_CLK_STOP_0_SPI_FLASH_Msk        (1U << 27)
#define CRU_CLK_STOP_0_I2S_SLAVE_Msk        (1U << 28)
#define CRU_CLK_STOP_0_I2S11_Msk            (1U << 29)
#define CRU_CLK_STOP_0_I2S10_Msk            (1U << 30)
#define CRU_CLK_STOP_0_I2S9_Msk             (1U << 31)

#define CRU_CLK_STOP_1_I2C8_Msk             (1U << 0)
#define CRU_CLK_STOP_1_GPIO4_Msk            (1U << 1)
#define CRU_CLK_STOP_1_GPIO3_Msk            (1U << 2)
#define CRU_CLK_STOP_1_GPIO2_Msk            (1U << 3)
#define CRU_CLK_STOP_1_GPIO1_Msk            (1U << 4)
#define CRU_CLK_STOP_1_GPIO0_Msk            (1U << 5)
#define CRU_CLK_STOP_1_CAN13_Msk            (1U << 6)
#define CRU_CLK_STOP_1_CAN12_Msk            (1U << 7)
#define CRU_CLK_STOP_1_48M_Msk              (1U << 8)
#define CRU_CLK_STOP_1_DMAC1_Msk            (1U << 9)
#define CRU_CLK_STOP_1_DMAC0_Msk            (1U << 10)
#define CRU_CLK_STOP_1_USB_Msk              (1U << 11)
#define CRU_CLK_STOP_1_SRAM_Msk             (1U << 12)
#define CRU_CLK_STOP_1_ROM_Msk              (1U << 13)
#define CRU_CLK_STOP_1_OCN_Msk              (1U << 14)
#define CRU_CLK_STOP_1_GMU_Msk              (1U << 15)
#define CRU_CLK_STOP_1_FLASH_CACHE_Msk      (1U << 16)
#define CRU_CLK_STOP_1_EFLASH_Msk           (1U << 17)
#define CRU_CLK_STOP_1_CORE_Msk             (1U << 18)

#define CRU_PAD_CTRL_x_SPIx_MOSO_Pos        (0U)
#define CRU_PAD_CTRL_x_SPIx_MOSO_Msk        (0x7 << CRU_PAD_CTRL_x_SPIx_MOSO_Pos)
#define CRU_PAD_CTRL_x_SPIx_MISI_Pos        (8U)
#define CRU_PAD_CTRL_x_SPIx_MISI_Msk        (0x7 << CRU_PAD_CTRL_x_SPIx_MISI_Pos)
#define CRU_PAD_CTRL_x_SPIx_CS_Pos          (16U)
#define CRU_PAD_CTRL_x_SPIx_CS_Msk          (0x7 << CRU_PAD_CTRL_x_SPIx_CS_Pos)
#define CRU_PAD_CTRL_x_SPIx_CLK_Pos         (24U)
#define CRU_PAD_CTRL_x_SPIx_CLK_Msk         (0x7 << CRU_PAD_CTRL_x_SPIx_CLK_Pos)

#define CRU_DMAx_SEL_0_CHANNEL0_SEL_Pos     (0U)
#define CRU_DMAx_SEL_0_CHANNEL0_SEL_Msk     (0x3f << CRU_DMAx_SEL_0_CHANNEL0_SEL_Pos)
#define CRU_DMAx_SEL_0_CHANNEL1_SEL_Pos     (8U)
#define CRU_DMAx_SEL_0_CHANNEL1_SEL_Msk     (0x3f << CRU_DMAx_SEL_0_CHNNNEL1_SEL_Pos)
#define CRU_DMAx_SEL_0_CHANNEL2_SEL_Pos     (16U)
#define CRU_DMAx_SEL_0_CHANNEL2_SEL_Msk     (0x3f << CRU_DMAx_SEL_0_CHNNNEL2_SEL_Pos)
#define CRU_DMAx_SEL_0_CHANNEL3_SEL_Pos     (24U)
#define CRU_DMAx_SEL_0_CHANNEL3_SEL_Msk     (0x3f << CRU_DMAx_SEL_0_CHNNNEL3_SEL_Pos)

#define CRU_DMAx_SEL_1_CHANNEL4_SEL_Pos     (0U)
#define CRU_DMAx_SEL_1_CHANNEL4_SEL_Msk     (0x3f << CRU_DMAx_SEL_1_CHANNEL4_SEL_Pos)
#define CRU_DMAx_SEL_1_CHANNEL5_SEL_Pos     (0U)
#define CRU_DMAx_SEL_1_CHANNEL5_SEL_Msk     (0x3f << CRU_DMAx_SEL_1_CHANNEL5_SEL_Pos)

#define CRU_GMU_PHY_SEL_Msk                 0x1

#define CRU_DM_STATUS_Msk                   0x1
#endif
