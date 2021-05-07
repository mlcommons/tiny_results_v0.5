#ifndef __i2c_h__
#define __i2c_h__
#include <device.h>

typedef struct rv32_i2c {
	volatile uint32_t CON;
	volatile uint32_t TAR;
	volatile uint32_t SAR;
	volatile uint32_t HS_MADDR;
	volatile uint32_t DATA_CMD;
	volatile uint32_t SS_SCL_HCNT;
	volatile uint32_t SS_SCL_LCNT;
	volatile uint32_t FS_SCL_HCNT;
	volatile uint32_t FS_SCL_LCNT;
	volatile uint32_t HS_SCL_HCNT;
	volatile uint32_t HS_SCL_LCNT;
	volatile uint32_t INTR_STAT;
	volatile uint32_t INTR_MASK;
	volatile uint32_t RAW_INTR_STAT;
	volatile uint32_t RX_TL;
	volatile uint32_t TX_TL;
	volatile uint32_t CLR_INTR;
	volatile uint32_t CLR_RX_UNDER;
	volatile uint32_t CLR_RX_OVER;
	volatile uint32_t CLR_TX_OVER;
	volatile uint32_t CLR_RD_REQ;
	volatile uint32_t CLR_TX_ABRT;
	volatile uint32_t CLR_RX_DONE;
	volatile uint32_t CLR_ACTIVITY;
	volatile uint32_t CLR_STOP_DET;
	volatile uint32_t CLR_START_DET;
	volatile uint32_t CLR_GEN_CALL;
	volatile uint32_t ENABLE;
	volatile uint32_t STATUS;
	volatile uint32_t TXFLR;
	volatile uint32_t RXFLR;
	volatile uint32_t SDA_HOLD;
	volatile uint32_t TX_ABRT_SOURCE;
	volatile uint32_t SLV_DATA_NACK_ONLY;
	volatile uint32_t DMA_CR;
	volatile uint32_t DMA_TDLR;
	volatile uint32_t DMA_RDLR;
	volatile uint32_t SDA_SETUP;
	volatile uint32_t ACK_GENERAL_CALL;
	volatile uint32_t ENABLE_STATUS;
	volatile uint32_t FS_SPKLEN;
	volatile uint32_t HS_SPKLEN;
	volatile uint32_t RESERVED[20];
	volatile uint32_t COMP_VERSION;
	volatile uint32_t COMP_TYPE;
} rv32_i2c_t;

#define I2C_CON_MASTER_Pos         (0UL)
#define I2C_CON_MASTER_Msk         (0x1UL)
#define I2C_CON_SPEED_Pos          (1UL)
#define I2C_CON_SPEED_Msk          (0x6UL)
#define I2C_CON_10BIT_ADDR_SLAVE_Pos (3UL)
#define I2C_CON_10BIT_ADDR_SLAVE_Msk (0x8UL)
#define I2C_CON_10BIT_ADDR_MASTER_Pos (4UL)
#define I2C_CON_10BIT_ADDR_MASTER_Msk (0x10UL)
#define I2C_CON_RESTART_EN_Pos     (5UL)                     /* I2C CON: RESTART_EN (Bit 5) */
#define I2C_CON_RESTART_EN_Msk     (0x20UL)
#define I2C_CON_SLAVE_DISABLE_Pos  (6UL)
#define I2C_CON_SLAVE_DISABLE_Msk  (0x40UL)

#define I2C_TAR_TAR_Pos            (0UL)
#define I2C_TAR_TAR_Msk            (0x3ffUL)
#define I2C_TAR_GC_OR_START_Pos    (10UL)
#define I2C_TAR_GC_OR_START_Msk    (0x400UL)
#define I2C_TAR_SPECIAL_Pos        (11UL)
#define I2C_TAR_SPECIAL_Msk        (0x800UL)
#define I2C_TAR_10BIT_ADDR_MASTER_Pos (12UL)                 /* I2C TAR: 10BIT_ADDR_MASTER (Bit 12) */
#define I2C_TAR_10BIT_ADDR_MASTER_Msk (0x1000UL)             /* I2C TAR: 10BIT_ADDR_MASTER (Bitfield-Mask: 0x01) */

#define I2C_SAR_SAR_Pos            (0UL)
#define I2C_SAR_SAR_Msk            (0x3ffUL)

#define I2C_HS_MADDR_HS_MAR_Pos    (0UL)
#define I2C_HS_MADDR_HS_MAR_Msk    (0x7UL)

#define I2C_DATA_CMD_DAT_Pos       (0UL)
#define I2C_DATA_CMD_DAT_Msk       (0xffUL)
#define I2C_DATA_CMD_CMD_Pos       (8UL)
#define I2C_DATA_CMD_CMD_Msk       (0x100UL)
#define I2C_DATA_CMD_STOP_Pos      (9UL)
#define I2C_DATA_CMD_STOP_Msk      (0x200UL)
#define I2C_DATA_CMD_RESTART_Pos   (10UL)
#define I2C_DATA_CMD_RESTART_Msk   (0x400UL)

#define I2C_SS_SCL_HCNT_SS_SCL_HCNT_Pos (0UL)
#define I2C_SS_SCL_HCNT_SS_SCL_HCNT_Msk (0xffffUL)

#define I2C_SS_SCL_LCNT_SS_SCL_LCNT_Pos (0UL)
#define I2C_SS_SCL_LCNT_SS_SCL_LCNT_Msk (0xffffUL)

#define I2C_FS_SCL_HCNT_FS_SCL_HCNT_Pos (0UL)
#define I2C_FS_SCL_HCNT_FS_SCL_HCNT_Msk (0xffffUL)

#define I2C_FS_SCL_LCNT_FS_SCL_LCNT_Pos (0UL)
#define I2C_FS_SCL_LCNT_FS_SCL_LCNT_Msk (0xffffUL)

#define I2C_HS_SCL_HCNT_HS_SCL_HCNT_Pos (0UL)
#define I2C_HS_SCL_HCNT_HS_SCL_HCNT_Msk (0xffffUL)

#define I2C_HS_SCL_LCNT_HS_SCL_LCNT_Pos (0UL)
#define I2C_HS_SCL_LCNT_HS_SCL_LCNT_Msk (0xffffUL)

#define I2C_INTR_STAT_R_RX_UNDER_Pos (0UL)
#define I2C_INTR_STAT_R_RX_UNDER_Msk (0x1UL)
#define I2C_INTR_STAT_R_RX_OVER_Pos (1UL)
#define I2C_INTR_STAT_R_RX_OVER_Msk (0x2UL)
#define I2C_INTR_STAT_R_RX_FULL_Pos (2UL)
#define I2C_INTR_STAT_R_RX_FULL_Msk (0x4UL)
#define I2C_INTR_STAT_R_TX_OVER_Pos (3UL)
#define I2C_INTR_STAT_R_TX_OVER_Msk (0x8UL)
#define I2C_INTR_STAT_R_TX_EMPTY_Pos (4UL)
#define I2C_INTR_STAT_R_TX_EMPTY_Msk (0x10UL)
#define I2C_INTR_STAT_R_RD_REQ_Pos (5UL)
#define I2C_INTR_STAT_R_RD_REQ_Msk (0x20UL)
#define I2C_INTR_STAT_R_TX_ABRT_Pos (6UL)
#define I2C_INTR_STAT_R_TX_ABRT_Msk (0x40UL)
#define I2C_INTR_STAT_R_RX_DONE_Pos (7UL)
#define I2C_INTR_STAT_R_RX_DONE_Msk (0x80UL)
#define I2C_INTR_STAT_R_ACTIVITY_Pos (8UL)
#define I2C_INTR_STAT_R_ACTIVITY_Msk (0x100UL)
#define I2C_INTR_STAT_R_STOP_DET_Pos (9UL)
#define I2C_INTR_STAT_R_STOP_DET_Msk (0x200UL)
#define I2C_INTR_STAT_R_START_DET_Pos (10UL)
#define I2C_INTR_STAT_R_START_DET_Msk (0x400UL)
#define I2C_INTR_STAT_R_GEN_CALL_Pos (11UL)
#define I2C_INTR_STAT_R_GEN_CALL_Msk (0x800UL)

#define I2C_INTR_MASK_M_RX_UNDER_Pos (0UL)
#define I2C_INTR_MASK_M_RX_UNDER_Msk (0x1UL)
#define I2C_INTR_MASK_M_RX_OVER_Pos (1UL)
#define I2C_INTR_MASK_M_RX_OVER_Msk (0x2UL)
#define I2C_INTR_MASK_M_RX_FULL_Pos (2UL)
#define I2C_INTR_MASK_M_RX_FULL_Msk (0x4UL)                  /* I2C INTR_MASK: M_RX_FULL (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_TX_OVER_Pos (3UL)                    /* I2C INTR_MASK: M_TX_OVER (Bit 3) */
#define I2C_INTR_MASK_M_TX_OVER_Msk (0x8UL)                  /* I2C INTR_MASK: M_TX_OVER (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_TX_EMPTY_Pos (4UL)                   /* I2C INTR_MASK: M_TX_EMPTY (Bit 4) */
#define I2C_INTR_MASK_M_TX_EMPTY_Msk (0x10UL)                /* I2C INTR_MASK: M_TX_EMPTY (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_RD_REQ_Pos (5UL)                     /* I2C INTR_MASK: M_RD_REQ (Bit 5) */
#define I2C_INTR_MASK_M_RD_REQ_Msk (0x20UL)                  /* I2C INTR_MASK: M_RD_REQ (Bitfield-Mask: 0x01)  */
#define I2C_INTR_MASK_M_TX_ABRT_Pos (6UL)                    /* I2C INTR_MASK: M_TX_ABRT (Bit 6) */
#define I2C_INTR_MASK_M_TX_ABRT_Msk (0x40UL)                 /* I2C INTR_MASK: M_TX_ABRT (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_RX_DONE_Pos (7UL)                    /* I2C INTR_MASK: M_RX_DONE (Bit 7) */
#define I2C_INTR_MASK_M_RX_DONE_Msk (0x80UL)                 /* I2C INTR_MASK: M_RX_DONE (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_ACTIVITY_Pos (8UL)                   /* I2C INTR_MASK: M_ACTIVITY (Bit 8) */
#define I2C_INTR_MASK_M_ACTIVITY_Msk (0x100UL)               /* I2C INTR_MASK: M_ACTIVITY (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_STOP_DET_Pos (9UL)                   /* I2C INTR_MASK: M_STOP_DET (Bit 9) */
#define I2C_INTR_MASK_M_STOP_DET_Msk (0x200UL)               /* I2C INTR_MASK: M_STOP_DET (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_START_DET_Pos (10UL)                 /* I2C INTR_MASK: M_START_DET (Bit 10) */
#define I2C_INTR_MASK_M_START_DET_Msk (0x400UL)              /* I2C INTR_MASK: M_START_DET (Bitfield-Mask: 0x01) */
#define I2C_INTR_MASK_M_GEN_CALL_Pos (11UL)                  /* I2C INTR_MASK: M_GEN_CALL (Bit 11) */
#define I2C_INTR_MASK_M_GEN_CALL_Msk (0x800UL)               /* I2C INTR_MASK: M_GEN_CALL (Bitfield-Mask: 0x01) */

#define I2C_RAW_INTR_STAT_RX_UNDER_Pos (0UL)                 /* I2C RAW_INTR_STAT: RX_UNDER (Bit 0) */
#define I2C_RAW_INTR_STAT_RX_UNDER_Msk (0x1UL)               /* I2C RAW_INTR_STAT: RX_UNDER (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_RX_OVER_Pos (1UL)                  /* I2C RAW_INTR_STAT: RX_OVER (Bit 1) */
#define I2C_RAW_INTR_STAT_RX_OVER_Msk (0x2UL)                /* I2C RAW_INTR_STAT: RX_OVER (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_RX_FULL_Pos (2UL)                  /* I2C RAW_INTR_STAT: RX_FULL (Bit 2) */
#define I2C_RAW_INTR_STAT_RX_FULL_Msk (0x4UL)                /* I2C RAW_INTR_STAT: RX_FULL (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_TX_OVER_Pos (3UL)                  /* I2C RAW_INTR_STAT: TX_OVER (Bit 3) */
#define I2C_RAW_INTR_STAT_TX_OVER_Msk (0x8UL)                /* I2C RAW_INTR_STAT: TX_OVER (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_TX_EMPTY_Pos (4UL)                 /* I2C RAW_INTR_STAT: TX_EMPTY (Bit 4) */
#define I2C_RAW_INTR_STAT_TX_EMPTY_Msk (0x10UL)              /* I2C RAW_INTR_STAT: TX_EMPTY (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_RD_REQ_Pos (5UL)                   /* I2C RAW_INTR_STAT: RD_REQ (Bit 5) */
#define I2C_RAW_INTR_STAT_RD_REQ_Msk (0x20UL)                /* I2C RAW_INTR_STAT: RD_REQ (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_TX_ABRT_Pos (6UL)                  /* I2C RAW_INTR_STAT: TX_ABRT (Bit 6) */
#define I2C_RAW_INTR_STAT_TX_ABRT_Msk (0x40UL)               /* I2C RAW_INTR_STAT: TX_ABRT (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_RX_DONE_Pos (7UL)                  /* I2C RAW_INTR_STAT: RX_DONE (Bit 7) */
#define I2C_RAW_INTR_STAT_RX_DONE_Msk (0x80UL)               /* I2C RAW_INTR_STAT: RX_DONE (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_ACTIVITY_Pos (8UL)                 /* I2C RAW_INTR_STAT: ACTIVITY (Bit 8) */
#define I2C_RAW_INTR_STAT_ACTIVITY_Msk (0x100UL)             /* I2C RAW_INTR_STAT: ACTIVITY (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_STOP_DET_Pos (9UL)                 /* I2C RAW_INTR_STAT: STOP_DET (Bit 9) */
#define I2C_RAW_INTR_STAT_STOP_DET_Msk (0x200UL)             /* I2C RAW_INTR_STAT: STOP_DET (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_START_DET_Pos (10UL)               /* I2C RAW_INTR_STAT: START_DET (Bit 10) */
#define I2C_RAW_INTR_STAT_START_DET_Msk (0x400UL)            /* I2C RAW_INTR_STAT: START_DET (Bitfield-Mask: 0x01) */
#define I2C_RAW_INTR_STAT_GEN_CALL_Pos (11UL)                /* I2C RAW_INTR_STAT: GEN_CALL (Bit 11) */
#define I2C_RAW_INTR_STAT_GEN_CALL_Msk (0x800UL)             /* I2C RAW_INTR_STAT: GEN_CALL (Bitfield-Mask: 0x01) */

#define I2C_RX_TL_RX_TL_Pos        (0UL)                     /* I2C RX_TL: RX_TL (Bit 0) */
#define I2C_RX_TL_RX_TL_Msk        (0xffUL)                  /* I2C RX_TL: RX_TL (Bitfield-Mask: 0xff) */

#define I2C_TX_TL_TX_TL_Pos        (0UL)                     /* I2C TX_TL: TX_TL (Bit 0) */
#define I2C_TX_TL_TX_TL_Msk        (0xffUL)                  /* I2C TX_TL: TX_TL (Bitfield-Mask: 0xff) */

#define I2C_CLR_INTR_TX_TL_Pos     (0UL)                     /* I2C CLR_INTR: TX_TL (Bit 0) */
#define I2C_CLR_INTR_TX_TL_Msk     (0x1UL)                   /* I2C CLR_INTR: TX_TL (Bitfield-Mask: 0x01) */

#define I2C_CLR_RX_UNDER_CLR_RX_UNDER_Pos (0UL)              /* I2C CLR_RX_UNDER: CLR_RX_UNDER (Bit 0) */
#define I2C_CLR_RX_UNDER_CLR_RX_UNDER_Msk (0x1UL)            /* I2C CLR_RX_UNDER: CLR_RX_UNDER (Bitfield-Mask: 0x01) */

#define I2C_CLR_RX_OVER_CLR_RX_OVER_Pos (0UL)                /* I2C CLR_RX_OVER: CLR_RX_OVER (Bit 0) */
#define I2C_CLR_RX_OVER_CLR_RX_OVER_Msk (0x1UL)              /* I2C CLR_RX_OVER: CLR_RX_OVER (Bitfield-Mask: 0x01) */

#define I2C_CLR_TX_OVER_CLR_TX_OVER_Pos (0UL)                /* I2C CLR_TX_OVER: CLR_TX_OVER (Bit 0) */
#define I2C_CLR_TX_OVER_CLR_TX_OVER_Msk (0x1UL)              /* I2C CLR_TX_OVER: CLR_TX_OVER (Bitfield-Mask: 0x01) */

#define I2C_CLR_RD_REQ_CLR_RD_REQ_Pos (0UL)                  /* I2C CLR_RD_REQ: CLR_RD_REQ (Bit 0) */
#define I2C_CLR_RD_REQ_CLR_RD_REQ_Msk (0x1UL)                /* I2C CLR_RD_REQ: CLR_RD_REQ (Bitfield-Mask: 0x01) */

#define I2C_CLR_TX_ABRT_CLR_TX_ABRT_Pos (0UL)                /* I2C CLR_TX_ABRT: CLR_TX_ABRT (Bit 0) */
#define I2C_CLR_TX_ABRT_CLR_TX_ABRT_Msk (0x1UL)              /* I2C CLR_TX_ABRT: CLR_TX_ABRT (Bitfield-Mask: 0x01) */

#define I2C_CLR_RX_DONE_CLR_RX_DONE_Pos (0UL)                /* I2C CLR_RX_DONE: CLR_RX_DONE (Bit 0) */
#define I2C_CLR_RX_DONE_CLR_RX_DONE_Msk (0x1UL)              /* I2C CLR_RX_DONE: CLR_RX_DONE (Bitfield-Mask: 0x01) */

#define I2C_CLR_ACTIVITY_CLR_ACTIVITY_Pos (0UL)              /* I2C CLR_ACTIVITY: CLR_ACTIVITY (Bit 0) */
#define I2C_CLR_ACTIVITY_CLR_ACTIVITY_Msk (0x1UL)            /* I2C CLR_ACTIVITY: CLR_ACTIVITY (Bitfield-Mask: 0x01) */

#define I2C_CLR_STOP_DET_CLR_STOP_DET_Pos (0UL)              /* I2C CLR_STOP_DET: CLR_STOP_DET (Bit 0) */
#define I2C_CLR_STOP_DET_CLR_STOP_DET_Msk (0x1UL)            /* I2C CLR_STOP_DET: CLR_STOP_DET (Bitfield-Mask: 0x01) */

#define I2C_CLR_START_DET_CLR_START_DET_Pos (0UL)            /* I2C CLR_START_DET: CLR_START_DET (Bit 0) */
#define I2C_CLR_START_DET_CLR_START_DET_Msk (0x1UL)          /* I2C CLR_START_DET: CLR_START_DET (Bitfield-Mask: 0x01) */

#define I2C_CLR_GEN_CALL_CLR_GEN_CALL_Pos (0UL)              /* I2C CLR_GEN_CALL: CLR_GEN_CALL (Bit 0) */
#define I2C_CLR_GEN_CALL_CLR_GEN_CALL_Msk (0x1UL)            /* I2C CLR_GEN_CALL: CLR_GEN_CALL (Bitfield-Mask: 0x01) */

#define I2C_ENABLE_ENABLE_Pos      (0UL)                     /* I2C ENABLE: ENABLE (Bit 0)                     */
#define I2C_ENABLE_ENABLE_Msk      (0x1UL)                   /* I2C ENABLE: ENABLE (Bitfield-Mask: 0x01)       */

#define I2C_STATUS_ACTIVITY_Pos    (0UL)
#define I2C_STATUS_ACTIVITY_Msk    (0x1UL)
#define I2C_STATUS_TFNF_Pos        (1UL)
#define I2C_STATUS_TFNF_Msk        (0x2UL)
#define I2C_STATUS_TFE_Pos         (2UL)
#define I2C_STATUS_TFE_Msk         (0x4UL)
#define I2C_STATUS_RFNE_Pos        (3UL)                     /* I2C STATUS: RFNE (Bit 3)                       */
#define I2C_STATUS_RFNE_Msk        (0x8UL)                   /* I2C STATUS: RFNE (Bitfield-Mask: 0x01)         */
#define I2C_STATUS_RFF_Pos         (4UL)                     /* I2C STATUS: RFF (Bit 4)                        */
#define I2C_STATUS_RFF_Msk         (0x10UL)                  /* I2C STATUS: RFF (Bitfield-Mask: 0x01)          */
#define I2C_STATUS_MST_ACTIVITY_Pos (5UL)                    /* I2C STATUS: MST_ACTIVITY (Bit 5)               */
#define I2C_STATUS_MST_ACTIVITY_Msk (0x20UL)                 /* I2C STATUS: MST_ACTIVITY (Bitfield-Mask: 0x01) */
#define I2C_STATUS_SLV_ACTIVITY_Pos (6UL)                    /* I2C STATUS: SLV_ACTIVITY (Bit 6)               */
#define I2C_STATUS_SLV_ACTIVITY_Msk (0x40UL)                 /* I2C STATUS: SLV_ACTIVITY (Bitfield-Mask: 0x01) */

#define I2C_TXFLR_TXFLR_Pos        (0UL)                     /* I2C TXFLR: TXFLR (Bit 0)                       */
#define I2C_TXFLR_TXFLR_Msk        (0xffffffffUL)            /* I2C TXFLR: TXFLR (Bitfield-Mask: 0xffffffff)   */

#define I2C_RXFLR_RXFLR_Pos        (0UL)                     /* I2C RXFLR: RXFLR (Bit 0)                       */
#define I2C_RXFLR_RXFLR_Msk        (0xffffffffUL)            /* I2C RXFLR: RXFLR (Bitfield-Mask: 0xffffffff)   */

#define I2C_SDA_HOLD_SDA_HOLD_Pos  (0UL)                     /* I2C SDA_HOLD: SDA_HOLD (Bit 0)                 */
#define I2C_SDA_HOLD_SDA_HOLD_Msk  (0xffffUL)                /* I2C SDA_HOLD: SDA_HOLD (Bitfield-Mask: 0xffff) */

#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_Pos (0UL)      /* I2C TX_ABRT_SOURCE: ABRT_7B_ADDR_NOACK (Bit 0) */
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_Msk (0x1UL)    /* I2C TX_ABRT_SOURCE: ABRT_7B_ADDR_NOACK (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_Pos (1UL)      /* I2C TX_ABRT_SOURCE: ABRT_10ADDR1_NOACK (Bit 1) */
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_Msk (0x2UL)    /* I2C TX_ABRT_SOURCE: ABRT_10ADDR1_NOACK (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_Pos (2UL)      /* I2C TX_ABRT_SOURCE: ABRT_10ADDR2_NOACK (Bit 2) */
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_Msk (0x4UL)    /* I2C TX_ABRT_SOURCE: ABRT_10ADDR2_NOACK (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_Pos (3UL)       /* I2C TX_ABRT_SOURCE: ABRT_TXDATA_NOACK (Bit 3)  */
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_Msk (0x8UL)     /* I2C TX_ABRT_SOURCE: ABRT_TXDATA_NOACK (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_Pos (4UL)        /* I2C TX_ABRT_SOURCE: ABRT_GCALL_NOACK (Bit 4)   */
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_Msk (0x10UL)     /* I2C TX_ABRT_SOURCE: ABRT_GCALL_NOACK (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_Pos (5UL)         /* I2C TX_ABRT_SOURCE: ABRT_GCALL_READ (Bit 5)    */
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_Msk (0x20UL)      /* I2C TX_ABRT_SOURCE: ABRT_GCALL_READ (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_Pos (6UL)          /* I2C TX_ABRT_SOURCE: ABRT_HS_ACKDET (Bit 6)     */
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_Msk (0x40UL)       /* I2C TX_ABRT_SOURCE: ABRT_HS_ACKDET (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_Pos (7UL)       /* I2C TX_ABRT_SOURCE: ABRT_SBYTE_ACKDET (Bit 7)  */
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_Msk (0x80UL)    /* I2C TX_ABRT_SOURCE: ABRT_SBYTE_ACKDET (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTR_Pos (8UL)          /* I2C TX_ABRT_SOURCE: ABRT_HS_NORSTR (Bit 8)     */
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTR_Msk (0x100UL)      /* I2C TX_ABRT_SOURCE: ABRT_HS_NORSTR (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_Pos (9UL)      /* I2C TX_ABRT_SOURCE: ABRT_SBYTE_NORSTRT (Bit 9) */
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_Msk (0x200UL)  /* I2C TX_ABRT_SOURCE: ABRT_SBYTE_NORSTRT (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_Pos (10UL)    /* I2C TX_ABRT_SOURCE: ABRT_10B_RD_NORSTRT (Bit 10) */
#define I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_Msk (0x400UL) /* I2C TX_ABRT_SOURCE: ABRT_10B_RD_NORSTRT (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_Pos (11UL)        /* I2C TX_ABRT_SOURCE: ABRT_MASTER_DIS (Bit 11)   */
#define I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_Msk (0x800UL)     /* I2C TX_ABRT_SOURCE: ABRT_MASTER_DIS (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ARB_LOST_Pos (12UL)               /* I2C TX_ABRT_SOURCE: ARB_LOST (Bit 12)          */
#define I2C_TX_ABRT_SOURCE_ARB_LOST_Msk (0x1000UL)           /* I2C TX_ABRT_SOURCE: ARB_LOST (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_Pos (13UL)   /* I2C TX_ABRT_SOURCE: ABRT_SLVFLUSH_TXFIFO (Bit 13) */
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_Msk (0x2000UL) /* I2C TX_ABRT_SOURCE: ABRT_SLVFLUSH_TXFIFO (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_Pos (14UL)       /* I2C TX_ABRT_SOURCE: ABRT_SLV_ARBLOST (Bit 14)  */
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_Msk (0x4000UL)   /* I2C TX_ABRT_SOURCE: ABRT_SLV_ARBLOST (Bitfield-Mask: 0x01) */
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_Pos (15UL)        /* I2C TX_ABRT_SOURCE: ABRT_SLVRD_INTX (Bit 15)   */
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_Msk (0x8000UL)    /* I2C TX_ABRT_SOURCE: ABRT_SLVRD_INTX (Bitfield-Mask: 0x01) */

#define I2C_SLV_DATA_NACK_ONLY_NACK_Pos (0UL)
#define I2C_SLV_DATA_NACK_ONLY_NACK_Msk (0x1UL)

#define I2C_DMA_CR_RDMAE_Pos       (0UL)
#define I2C_DMA_CR_RDMAE_Msk       (0x1UL)
#define I2C_DMA_CR_TDMAE_Pos       (1UL)
#define I2C_DMA_CR_TDMAE_Msk       (0x2UL)

#define I2C_DMA_TDLR_DMATDL_Pos    (0UL)
#define I2C_DMA_TDLR_DMATDL_Msk    (0xffffffffUL)

#define I2C_DMA_RDLR_DMARDL_Pos    (0UL)                     /* I2C0 DMA_RDLR: DMARDL (Bit 0) */
#define I2C_DMA_RDLR_DMARDL_Msk    (0xffffffffUL)            /* I2C0 DMA_RDLR: DMARDL (Bitfield-Mask: 0xffffffff) */

#define I2C_SDA_SETUP_SDA_SETUP_Pos (0UL)                    /* I2C0 SDA_SETUP: SDA_SETUP (Bit 0) */
#define I2C_SDA_SETUP_SDA_SETUP_Msk (0xffUL)                 /* I2C0 SDA_SETUP: SDA_SETUP (Bitfield-Mask: 0xff) */

#define I2C_ACK_GENERAL_CALL_ACK_GEN_CALL_Pos (0UL)          /*!< MIZAR_I2C0 ACK_GENERAL_CALL: ACK_GEN_CALL (Bit 0)     */
#define I2C_ACK_GENERAL_CALL_ACK_GEN_CALL_Msk (0x1UL)        /*!< MIZAR_I2C0 ACK_GENERAL_CALL: ACK_GEN_CALL (Bitfield-Mask: 0x01) */

#define I2C_ENABLE_STATUS_EN_Pos   (0UL)                     /* I2C ENABLE_STATUS: EN (Bit 0) */
#define I2C_ENABLE_STATUS_EN_Msk   (0x1UL)                   /* I2C ENABLE_STATUS: EN (Bitfield-Mask: 0x01) */
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_Pos (1UL)  /* I2C ENABLE_STATUS: SLV_DISABLED_WHILE_BUSY (Bit 1) */
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_Msk (0x2UL) /* I2C ENABLE_STATUS: SLV_DISABLED_WHILE_BUSY (Bitfield-Mask: 0x01) */
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_Pos (2UL)         /* I2C ENABLE_STATUS: SLV_RX_DATA_LOST (Bit 2)    */
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_Msk (0x4UL)       /* I2C ENABLE_STATUS: SLV_RX_DATA_LOST (Bitfield-Mask: 0x01) */

#define I2C_FS_SPKLEN_FS_SPKLEN_Pos (0UL)                    /* I2C FS_SPKLEN: FS_SPKLEN (Bit 0)               */
#define I2C_FS_SPKLEN_FS_SPKLEN_Msk (0xffUL)                 /* I2C FS_SPKLEN: FS_SPKLEN (Bitfield-Mask: 0xff) */

#define I2C_HS_SPKLEN_HS_SPKLEN_Pos (0UL)                    /* I2C HS_SPKLEN: HS_SPKLEN (Bit 0)               */
#define I2C_HS_SPKLEN_HS_SPKLEN_Msk (0xffUL)                 /* I2C HS_SPKLEN: HS_SPKLEN (Bitfield-Mask: 0xff) */

#define I2C_COMP_VERSION_COMP_VERSION_Pos (0UL)              /* I2C COMP_VERSION: COMP_VERSION (Bit 0)         */
#define I2C_COMP_VERSION_COMP_VERSION_Msk (0xffffffffUL)     /* I2C COMP_VERSION: COMP_VERSION (Bitfield-Mask: 0xffffffff) */

#define I2C_COMP_TYPE_COMP_TYPE_Pos (0UL)                    /* I2C COMP_TYPE: COMP_TYPE (Bit 0) */
#define I2C_COMP_TYPE_COMP_TYPE_Msk (0xffffffffUL)           /* I2C COMP_TYPE: COMP_TYPE (Bitfield-Mask: 0xffffffff) */
#endif
