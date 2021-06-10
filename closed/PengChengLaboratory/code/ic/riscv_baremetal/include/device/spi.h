#ifndef __spi_h__
#define __spi_h__
#include <device.h>

typedef struct rv32_spi {
	volatile uint32_t CR0;
	volatile uint32_t CR1;
	volatile uint32_t DR;
	volatile uint32_t SR;
	volatile uint32_t CPSR;
	volatile uint32_t IMSC;
	volatile uint32_t RIS;
	volatile uint32_t MIS;
	volatile uint32_t ICR;
	volatile uint32_t DMACR;
	volatile uint32_t RES[1006];
	volatile uint32_t PIDR0;
	volatile uint32_t PIDR1;
	volatile uint32_t PIDR2;
	volatile uint32_t PIDR3;
	volatile uint32_t CIDR0;
	volatile uint32_t CIDR1;
	volatile uint32_t CIDR2;
	volatile uint32_t CIDR3;
} rv32_spi_t;

#define SPI_CR0_DSS_Pos            (0UL)                     /* SPI CR0: DSS (Bit 0) */
#define SPI_CR0_DSS_Msk            (0xfUL)                   /* SPI CR0: DSS (Bitfield-Mask: 0x0f) */
#define SPI_CR0_FRF_Pos            (4UL)                     /* SPI CR0: FRF (Bit 4) */
#define SPI_CR0_FRF_Msk            (0x30UL)                  /* SPI CR0: FRF (Bitfield-Mask: 0x03) */
#define SPI_CR0_CPOL_Pos           (6UL)                     /* SPI CR0: CPOL (Bit 6) */
#define SPI_CR0_CPOL_Msk           (0x40UL)                  /* SPI CR0: CPOL (Bitfield-Mask: 0x01) */
#define SPI_CR0_CPHA_Pos           (7UL)                     /* SPI CR0: CPHA (Bit 7) */
#define SPI_CR0_CPHA_Msk           (0x80UL)                  /* SPI CR0: CPHA (Bitfield-Mask: 0x01) */
#define SPI_CR0_SCR_Pos            (8UL)                     /* SPI CR0: SCR (Bit 8) */
#define SPI_CR0_SCR_Msk            (0xff00UL)                /* SPI CR0: SCR (Bitfield-Mask: 0xff) */

#define SPI_CR1_LBM_Pos            (0UL)                     /* SPI CR1: LBM (Bit 0) */
#define SPI_CR1_LBM_Msk            (0x1UL)                   /* SPI CR1: LBM (Bitfield-Mask: 0x01) */
#define SPI_CR1_SSE_Pos            (1UL)                     /* SPI CR1: SSE (Bit 1) */
#define SPI_CR1_SSE_Msk            (0x2UL)                   /* SPI CR1: SSE (Bitfield-Mask: 0x01) */
#define SPI_CR1_MS_Pos             (2UL)                     /* SPI CR1: MS (Bit 2) */
#define SPI_CR1_MS_Msk             (0x4UL)                   /* SPI CR1: MS (Bitfield-Mask: 0x01) */
#define SPI_CR1_SOD_Pos            (3UL)                     /* SPI CR1: SOD (Bit 3) */
#define SPI_CR1_SOD_Msk            (0x8UL)                   /* SPI CR1: SOD (Bitfield-Mask: 0x01) */

#define SPI_DR_DATA_Pos            (0UL)                     /* SPI DR: DATA (Bit 0) */
#define SPI_DR_DATA_Msk            (0xffffUL)                /* SPI DR: DATA (Bitfield-Mask: 0xffff) */

#define SPI_SR_TFE_Pos             (0UL)                     /* SPI SR: TFE (Bit 0) */
#define SPI_SR_TFE_Msk             (0x1UL)                   /* SPI SR: TFE (Bitfield-Mask: 0x01) */
#define SPI_SR_TNF_Pos             (1UL)                     /* SPI SR: TNF (Bit 1) */
#define SPI_SR_TNF_Msk             (0x2UL)                   /* SPI SR: TNF (Bitfield-Mask: 0x01) */
#define SPI_SR_RNE_Pos             (2UL)                     /* SPI SR: RNE (Bit 2) */
#define SPI_SR_RNE_Msk             (0x4UL)                   /* SPI SR: RNE (Bitfield-Mask: 0x01) */
#define SPI_SR_RFF_Pos             (3UL)                     /* SPI SR: RFF (Bit 3) */
#define SPI_SR_RFF_Msk             (0x8UL)                   /* SPI SR: RFF (Bitfield-Mask: 0x01) */
#define SPI_SR_BSY_Pos             (4UL)                     /* SPI SR: BSY (Bit 4) */
#define SPI_SR_BSY_Msk             (0x10UL)                  /* SPI SR: BSY (Bitfield-Mask: 0x01) */

#define SPI_CPSR_CPSDVSR_Pos       (0UL)                     /* SPI CPSR: CPSDVSR (Bit 0) */
#define SPI_CPSR_CPSDVSR_Msk       (0xffUL)                  /* SPI CPSR: CPSDVSR (Bitfield-Mask: 0xff) */

#define SPI_IMSC_RORIM_Pos         (0UL)                     /* SPI IMSC: RORIM (Bit 0) */
#define SPI_IMSC_RORIM_Msk         (0x1UL)                   /* SPI IMSC: RORIM (Bitfield-Mask: 0x01) */
#define SPI_IMSC_RTIM_Pos          (1UL)                     /* SPI IMSC: RTIM (Bit 1) */
#define SPI_IMSC_RTIM_Msk          (0x2UL)                   /* SPI IMSC: RTIM (Bitfield-Mask: 0x01) */
#define SPI_IMSC_RXIM_Pos          (2UL)                     /* SPI IMSC: RXIM (Bit 2) */
#define SPI_IMSC_RXIM_Msk          (0x4UL)                   /* SPI IMSC: RXIM (Bitfield-Mask: 0x01) */
#define SPI_IMSC_TXIM_Pos          (3UL)                     /* SPI IMSC: TXIM (Bit 3) */
#define SPI_IMSC_TXIM_Msk          (0x8UL)                   /* SPI IMSC: TXIM (Bitfield-Mask: 0x01) */

#define SPI_RIS_RORRIS_Pos         (0UL)                     /* SPI RIS: RORRIS (Bit 0) */
#define SPI_RIS_RORRIS_Msk         (0x1UL)                   /* SPI RIS: RORRIS (Bitfield-Mask: 0x01) */
#define SPI_RIS_RTRIS_Pos          (1UL)                     /* SPI RIS: RTRIS (Bit 1) */
#define SPI_RIS_RTRIS_Msk          (0x2UL)                   /* SPI RIS: RTRIS (Bitfield-Mask: 0x01) */
#define SPI_RIS_RXRIS_Pos          (2UL)                     /* SPI RIS: RXRIS (Bit 2) */
#define SPI_RIS_RXRIS_Msk          (0x4UL)                   /* SPI RIS: RXRIS (Bitfield-Mask: 0x01) */
#define SPI_RIS_TXRIS_Pos          (3UL)                     /* SPI RIS: TXRIS (Bit 3) */
#define SPI_RIS_TXRIS_Msk          (0x8UL)                   /* SPI RIS: TXRIS (Bitfield-Mask: 0x01) */

#define SPI_MIS_RORMIS_Pos         (0UL)                     /* SPI MIS: RORMIS (Bit 0) */
#define SPI_MIS_RORMIS_Msk         (0x1UL)                   /* SPI MIS: RORMIS (Bitfield-Mask: 0x01) */
#define SPI_MIS_RTMIS_Pos          (1UL)                     /* SPI MIS: RTMIS (Bit 1) */
#define SPI_MIS_RTMIS_Msk          (0x2UL)                   /* SPI MIS: RTMIS (Bitfield-Mask: 0x01) */
#define SPI_MIS_RXMIS_Pos          (2UL)                     /* SPI MIS: RXMIS (Bit 2) */
#define SPI_MIS_RXMIS_Msk          (0x4UL)                   /* SPI MIS: RXMIS (Bitfield-Mask: 0x01) */
#define SPI_MIS_TXMIS_Pos          (3UL)                     /* SPI MIS: TXMIS (Bit 3) */
#define SPI_MIS_TXMIS_Msk          (0x8UL)                   /* SPI MIS: TXMIS (Bitfield-Mask: 0x01) */

#define SPI_ICR_RORIC_Pos          (0UL)                     /* SPI ICR: RORIC (Bit 0) */
#define SPI_ICR_RORIC_Msk          (0x1UL)                   /* SPI ICR: RORIC (Bitfield-Mask: 0x01) */
#define SPI_ICR_RTIC_Pos           (1UL)                     /* SPI ICR: RTIC (Bit 1) */
#define SPI_ICR_RTIC_Msk           (0x2UL)                   /* SPI ICR: RTIC (Bitfield-Mask: 0x01) */

#define SPI_DMACR_RXDMAE_Pos       (0UL)                     /* SPI DMACR: RXDMAE (Bit 0) */
#define SPI_DMACR_RXDMAE_Msk       (0x1UL)                   /* SPI DMACR: RXDMAE (Bitfield-Mask: 0x01) */
#define SPI_DMACR_TXDMAE_Pos       (1UL)                     /* SPI DMACR: TXDMAE (Bit 1) */
#define SPI_DMACR_TXDMAE_Msk       (0x2UL)                   /* SPI DMACR: TXDMAE (Bitfield-Mask: 0x01) */

#endif
