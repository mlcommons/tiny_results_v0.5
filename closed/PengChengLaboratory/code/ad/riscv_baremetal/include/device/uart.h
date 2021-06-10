#ifndef __uart_h__
#define __uart_h__
#include <device.h>

typedef struct rv32_uart {
	volatile uint32_t  DR;
	union {
		volatile uint32_t RSR;
		volatile uint32_t ECR;
	};
	volatile uint32_t  RES[4];
	volatile uint32_t  FR;
	volatile uint32_t  RES1;
	volatile uint32_t  ILPR;
	volatile uint32_t  IBDR;
	volatile uint32_t  FBDR;
	volatile uint32_t  LCR_H;
	volatile uint32_t  CR;
	volatile uint32_t  IFLS;
	volatile uint32_t  IMSC;
	volatile uint32_t  RIS;
	volatile uint32_t  MIS;
	volatile uint32_t  ICR;
	volatile uint32_t  DMACR;
	volatile uint32_t  RES2[997];
	volatile uint32_t  PIDR0;
	volatile uint32_t  PIDR1;
	volatile uint32_t  PIDR2;
	volatile uint32_t  PIDR3;
	volatile uint32_t  CIDR0;
	volatile uint32_t  CIDR1;
	volatile uint32_t  CIDR2;
	volatile uint32_t  CIDR3;
} rv32_uart_t;

#define UART_DR_DATA_Pos           (0UL)
#define UART_DR_DATA_Msk           (0xffUL)
#define UART_DR_FE_Pos             (8UL)
#define UART_DR_FE_Msk             (0x100UL)
#define UART_DR_PE_Pos             (9UL)
#define UART_DR_PE_Msk             (0x200UL)
#define UART_DR_BE_Pos             (10UL)
#define UART_DR_BE_Msk             (0x400UL)
#define UART_DR_OE_Pos             (11UL)
#define UART_DR_OE_Msk             (0x800UL)

#define UART_RSR_FE_Pos            (0UL)
#define UART_RSR_FE_Msk            (0x1UL)
#define UART_RSR_PE_Pos            (1UL)
#define UART_RSR_PE_Msk            (0x2UL)
#define UART_RSR_BE_Pos            (2UL)
#define UART_RSR_BE_Msk            (0x4UL)
#define UART_RSR_OE_Pos            (3UL)
#define UART_RSR_OE_Msk            (0x8UL)

#define UART_ECR_FE_Pos            (0UL)
#define UART_ECR_FE_Msk            (0x1UL)
#define UART_ECR_PE_Pos            (1UL)
#define UART_ECR_PE_Msk            (0x2UL)
#define UART_ECR_BE_Pos            (2UL)
#define UART_ECR_BE_Msk            (0x4UL)
#define UART_ECR_OE_Pos            (3UL)
#define UART_ECR_OE_Msk            (0x8UL)

#define UART_FR_CTS_Pos            (0UL)
#define UART_FR_CTS_Msk            (0x1UL)
#define UART_FR_DSR_Pos            (1UL)
#define UART_FR_DSR_Msk            (0x2UL)
#define UART_FR_DCD_Pos            (2UL)
#define UART_FR_DCD_Msk            (0x4UL)
#define UART_FR_BUSY_Pos           (3UL)
#define UART_FR_BUSY_Msk           (0x8UL)
#define UART_FR_RXFE_Pos           (4UL)
#define UART_FR_RXFE_Msk           (0x10UL)
#define UART_FR_TXFF_Pos           (5UL)
#define UART_FR_TXFF_Msk           (0x20UL)
#define UART_FR_RXFF_Pos           (6UL)
#define UART_FR_RXFF_Msk           (0x40UL)
#define UART_FR_TXFE_Pos           (7UL)
#define UART_FR_TXFE_Msk           (0x80UL)
#define UART_FR_RI_Pos             (8UL)
#define UART_FR_RI_Msk             (0x100UL)

#define UART_ILPR_ILPDVSR_Pos      (0UL)
#define UART_ILPR_ILPDVSR_Msk      (0xffUL)

#define UART_IBDR_BAUDDIVINT_Pos   (0UL)
#define UART_IBDR_BAUDDIVINT_Msk   (0xffffUL)

#define UART_FBDR_BAUDDIVFRAC_Pos  (0UL)
#define UART_FBDR_BAUDDIVFRAC_Msk  (0x3fUL)

#define UART_LCR_H_BRK_Pos         (0UL)
#define UART_LCR_H_BRK_Msk         (0x1UL)
#define UART_LCR_H_PEN_Pos         (1UL)
#define UART_LCR_H_PEN_Msk         (0x2UL)
#define UART_LCR_H_EPS_Pos         (2UL)
#define UART_LCR_H_EPS_Msk         (0x4UL)
#define UART_LCR_H_STP2_Pos        (3UL)
#define UART_LCR_H_STP2_Msk        (0x8UL)
#define UART_LCR_H_FEN_Pos         (4UL)
#define UART_LCR_H_FEN_Msk         (0x10UL)
#define UART_LCR_H_WLEN_Pos        (5UL)
#define UART_LCR_H_WLEN_Msk        (0x60UL)
#define UART_LCR_H_SPS_Pos         (7UL)
#define UART_LCR_H_SPS_Msk         (0x80UL)

#define UART_CR_UARTEN_Pos         (0UL)
#define UART_CR_UARTEN_Msk         (0x1UL)
#define UART_CR_SIREN_Pos          (1UL)
#define UART_CR_SIREN_Msk          (0x2UL)
#define UART_CR_SIRLP_Pos          (2UL)
#define UART_CR_SIRLP_Msk          (0x4UL)
#define UART_CR_TXE_Pos            (8UL)
#define UART_CR_TXE_Msk            (0x100UL)
#define UART_CR_RXE_Pos            (9UL)
#define UART_CR_RXE_Msk            (0x200UL)
#define UART_CR_DTR_Pos            (10UL)
#define UART_CR_DTR_Msk            (0x400UL)
#define UART_CR_RTS_Pos            (11UL)
#define UART_CR_RTS_Msk            (0x800UL)
#define UART_CR_RTSEN_Pos          (14UL) 
#define UART_CR_RTSEN_Msk          (0x4000UL)
#define UART_CR_CTSEN_Pos          (15UL)
#define UART_CR_CTSEN_Msk          (0x8000UL)

#define UART_IFLS_TXIFLSEL_Pos     (0UL)
#define UART_IFLS_TXIFLSEL_Msk     (0x7UL)
#define UART_IFLS_RXIFLSEL_Pos     (3UL)
#define UART_IFLS_RXIFLSEL_Msk     (0x38UL)

#define UART_IMSC_RIMIM_Pos        (0UL)
#define UART_IMSC_RIMIM_Msk        (0x1UL)
#define UART_IMSC_CTSMIM_Pos       (1UL)
#define UART_IMSC_CTSMIM_Msk       (0x2UL)
#define UART_IMSC_DCDMIM_Pos       (2UL)
#define UART_IMSC_DCDMIM_Msk       (0x4UL)
#define UART_IMSC_DSRMIM_Pos       (3UL)
#define UART_IMSC_DSRMIM_Msk       (0x8UL)
#define UART_IMSC_RXIM_Pos         (4UL)
#define UART_IMSC_RXIM_Msk         (0x10UL)
#define UART_IMSC_TXIM_Pos         (5UL)
#define UART_IMSC_TXIM_Msk         (0x20UL)
#define UART_IMSC_RTIM_Pos         (6UL)
#define UART_IMSC_RTIM_Msk         (0x40UL)
#define UART_IMSC_FEIM_Pos         (7UL)
#define UART_IMSC_FEIM_Msk         (0x80UL)
#define UART_IMSC_PEIM_Pos         (8UL)
#define UART_IMSC_PEIM_Msk         (0x100UL)
#define UART_IMSC_BEIM_Pos         (9UL)
#define UART_IMSC_BEIM_Msk         (0x200UL)
#define UART_IMSC_OEIM_Pos         (10UL)
#define UART_IMSC_OEIM_Msk         (0x400UL)

#define UART_RIS_RIRMIS_Pos        (0UL)
#define UART_RIS_RIRMIS_Msk        (0x1UL)
#define UART_RIS_CTSRMIS_Pos       (1UL)
#define UART_RIS_CTSRMIS_Msk       (0x2UL)
#define UART_RIS_DCDRMIS_Pos       (2UL)
#define UART_RIS_DCDRMIS_Msk       (0x4UL)
#define UART_RIS_DSRRMIS_Pos       (3UL)
#define UART_RIS_DSRRMIS_Msk       (0x8UL)
#define UART_RIS_RXRIS_Pos         (4UL)
#define UART_RIS_RXRIS_Msk         (0x10UL)
#define UART_RIS_TXRIS_Pos         (5UL)
#define UART_RIS_TXRIS_Msk         (0x20UL)
#define UART_RIS_RTRIS_Pos         (6UL)
#define UART_RIS_RTRIS_Msk         (0x40UL)
#define UART_RIS_FERIS_Pos         (7UL)
#define UART_RIS_FERIS_Msk         (0x80UL)
#define UART_RIS_PERIS_Pos         (8UL)
#define UART_RIS_PERIS_Msk         (0x100UL)
#define UART_RIS_BERIS_Pos         (9UL)
#define UART_RIS_BERIS_Msk         (0x200UL)
#define UART_RIS_OERIS_Pos         (10UL)
#define UART_RIS_OERIS_Msk         (0x400UL)

#define UART_MIS_RIMMIS_Pos        (0UL)
#define UART_MIS_RIMMIS_Msk        (0x1UL)
#define UART_MIS_CTSMMIS_Pos       (1UL)
#define UART_MIS_CTSMMIS_Msk       (0x2UL)
#define UART_MIS_DCDMMIS_Pos       (2UL)
#define UART_MIS_DCDMMIS_Msk       (0x4UL)
#define UART_MIS_DSRMMIS_Pos       (3UL)
#define UART_MIS_DSRMMIS_Msk       (0x8UL)
#define UART_MIS_RXMIS_Pos         (4UL)
#define UART_MIS_RXMIS_Msk         (0x10UL)
#define UART_MIS_TXMIS_Pos         (5UL)
#define UART_MIS_TXMIS_Msk         (0x20UL)
#define UART_MIS_RTMIS_Pos         (6UL)
#define UART_MIS_RTMIS_Msk         (0x40UL)
#define UART_MIS_FEMIS_Pos         (7UL)
#define UART_MIS_FEMIS_Msk         (0x80UL)
#define UART_MIS_PEMIS_Pos         (8UL)
#define UART_MIS_PEMIS_Msk         (0x100UL)
#define UART_MIS_BEMIS_Pos         (9UL)
#define UART_MIS_BEMIS_Msk         (0x200UL)
#define UART_MIS_OEMIS_Pos         (10UL)
#define UART_MIS_OEMIS_Msk         (0x400UL)

#define UART_ICR_RIMIC_Pos         (0UL)
#define UART_ICR_RIMIC_Msk         (0x1UL)
#define UART_ICR_CTSMIC_Pos        (1UL)
#define UART_ICR_CTSMIC_Msk        (0x2UL)
#define UART_ICR_DCDMIC_Pos        (2UL)
#define UART_ICR_DCDMIC_Msk        (0x4UL)
#define UART_ICR_DSRMIC_Pos        (3UL)
#define UART_ICR_DSRMIC_Msk        (0x8UL)
#define UART_ICR_RXIC_Pos          (4UL)
#define UART_ICR_RXIC_Msk          (0x10UL)
#define UART_ICR_TXIC_Pos          (5UL)
#define UART_ICR_TXIC_Msk          (0x20UL)
#define UART_ICR_RTIC_Pos          (6UL)
#define UART_ICR_RTIC_Msk          (0x40UL)
#define UART_ICR_FEIC_Pos          (7UL)
#define UART_ICR_FEIC_Msk          (0x80UL)
#define UART_ICR_PEIC_Pos          (8UL)
#define UART_ICR_PEIC_Msk          (0x100UL)
#define UART_ICR_BEIC_Pos          (9UL)
#define UART_ICR_BEIC_Msk          (0x200UL)
#define UART_ICR_OEIC_Pos          (10UL) 
#define UART_ICR_OEIC_Msk          (0x400UL)

#define UART_DMACR_RXDMAE_Pos      (0UL)
#define UART_DMACR_RXDMAE_Msk      (0x1UL)
#define UART_DMACR_TXDMAE_Pos      (1UL)
#define UART_DMACR_TXDMAE_Msk      (0x2UL)
#define UART_DMACR_DMAONERR_Pos    (2UL)
#define UART_DMACR_DMAONERR_Msk    (0x4UL)

#endif
