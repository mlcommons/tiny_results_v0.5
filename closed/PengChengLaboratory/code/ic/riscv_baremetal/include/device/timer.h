#ifndef __timer_h__
#define __timer_h__
#include <device.h>

#define RV32_TIMER_CHN_NUM    3

typedef struct rv32_timer {
    volatile uint32_t CNT;
    volatile uint32_t CTRL;
    volatile uint32_t STAT;
    volatile uint32_t CCR;
    volatile uint32_t CCTL0;
    volatile uint32_t CCR0;
    volatile uint32_t CCTL1;
    volatile uint32_t CCR1;
    volatile uint32_t CCTL2;
    volatile uint32_t CCR2;
} rv32_timer_t;

#define TIMx_CNT_Pos                    (8U)
#define TIMx_CNT_Msk                    (0xffff << TIMx_CNT_Pos)

#define TIMx_CTRL_MODE_Pos              (0U)
#define TIMx_CTRL_MODE_Msk              (0x3 << TIMx_CTRL_MODE_Pos)
#define TIMx_CTRL_DIV_Pos               (2U)
#define TIMx_CTRL_DIV_Msk               (0xff << TIMx_CTRL_DIV_Pos)
#define TIMx_CTRL_OVFIF_ENABLE_Pos      (10U)
#define TIMx_CTRL_OVFIF_ENABLE_Msk      (0x1 << TIMx_CTRL_OVFIF_ENABLE_Pos)

#define TIMx_STAT_CH0IF_Pos             (0U)
#define TIMx_STAT_CH0IF_Msk             (0x1 << TIMx_STAT_CH0IF_Pos)
#define TIMx_STAT_CH1IF_Pos             (1U)
#define TIMx_STAT_CH1IF_Msk             (0x1 << TIMx_STAT_CH1IF_Pos)
#define TIMx_STAT_CH2IF_Pos             (2U)
#define TIMx_STAT_CH2IF_Msk             (0x1 << TIMx_STAT_CH2IF_Pos)
#define TIMx_STAT_OVFIF_Pos             (2U)
#define TIMx_STAT_OVFIF_Msk             (0x1 << TIMx_STAT_OVFIF_Pos)

#define TIMx_CCR_Msk                    (0xffffff)

#define TIMx_CCTLx_CAP_Pos              (0U)
#define TIMx_CCTLx_CAP_Msk              (0x3 << TIMx_CCTLx_CAP_Pos)
#define TIMx_CCTLx_MODE_Pos             (2U)
#define TIMx_CCTLx_MODE_Msk             (0x1 << TIMx_CCTLx_MODE_Pos)
#define TIMx_CCTLx_IE_Pos               (3U)
#define TIMx_CCTLx_IE_Msk               (0x1 << TIMx_CCTLx_IE_Pos)
#define TIMx_CCTLx_CMP_Pos              (4U)
#define TIMx_CCTLx_CMP_Msk              (0x7 << TIMx_CCTLx_CMP_Pos)
#define TIMx_CCTLx_PIN_VAL_Pos          (7U)
#define TIMx_CCTLx_PIN_VAL_Msk          (0x1 << TIMx_CCTLx_PIN_VAL_Pos)
#define TIMx_CCTLx_DMA_EN_Pos           (8U)
#define TIMx_CCTLx_DMA_EN_Msk           (0x1 << TIMx_CCTLx_DMA_EN_Pos)
#endif
