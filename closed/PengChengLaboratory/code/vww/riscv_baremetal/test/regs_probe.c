#include <stdio.h>
#include <platform.h>

static void uart_regs_probe (void)
{
    printf("uart_regs_probe start\n");
    printf("UART0->DR:        0x%lx\n", RV32_UART0->DR);
    printf("UART0->RSR (ECR): 0x%lx\n", RV32_UART0->RSR);
    printf("UART0->FR:        0x%lx\n", RV32_UART0->FR);
    printf("UART0->ILPR:      0x%lx\n", RV32_UART0->ILPR);
    printf("UART0->IBDR:      0x%lx\n", RV32_UART0->IBDR);
    printf("UART0->FBDR:      0x%lx\n", RV32_UART0->FBDR);
    printf("UART0->LCR_H:     0x%lx\n", RV32_UART0->LCR_H);
    printf("UART0->CR:        0x%lx\n", RV32_UART0->CR);
    printf("UART0->IFLS:      0x%lx\n", RV32_UART0->IFLS);
    printf("UART0->IMSC:      0x%lx\n", RV32_UART0->IMSC);
    printf("UART0->RIS:       0x%lx\n", RV32_UART0->RIS);
    printf("UART0->MIS:       0x%lx\n", RV32_UART0->RIS);
    printf("UART0->ICR:       0x%lx\n", RV32_UART0->ICR);
    printf("UART0->DMACR:     0x%lx\n", RV32_UART0->DMACR);
    printf("UART0->PIDR0:     0x%lx\n", RV32_UART0->PIDR0);
    printf("UART0->PIDR1:     0x%lx\n", RV32_UART0->PIDR1);
    printf("UART0->PIDR2:     0x%lx\n", RV32_UART0->PIDR2);
    printf("UART0->PIDR3:     0x%lx\n", RV32_UART0->PIDR3);
    printf("UART0->CIDR0:     0x%lx\n", RV32_UART0->CIDR0);
    printf("UART0->CIDR1:     0x%lx\n", RV32_UART0->CIDR1);
    printf("UART0->CIDR2:     0x%lx\n", RV32_UART0->CIDR2);
    printf("UART0->CIDR3:     0x%lx\n", RV32_UART0->CIDR3);
    printf("\n");
    printf("UART1->DR:        0x%lx\n", RV32_UART1->DR);
    printf("UART1->RSR (ECR): 0x%lx\n", RV32_UART1->RSR);
    printf("UART1->FR:        0x%lx\n", RV32_UART1->FR);
    printf("UART1->ILPR:      0x%lx\n", RV32_UART1->ILPR);
    printf("UART1->IBDR:      0x%lx\n", RV32_UART1->IBDR);
    printf("UART1->FBDR:      0x%lx\n", RV32_UART1->FBDR);
    printf("UART1->LCR_H:     0x%lx\n", RV32_UART1->LCR_H);
    printf("UART1->CR:        0x%lx\n", RV32_UART1->CR);
    printf("UART1->IFLS:      0x%lx\n", RV32_UART1->IFLS);
    printf("UART1->IMSC:      0x%lx\n", RV32_UART1->IMSC);
    printf("UART1->RIS:       0x%lx\n", RV32_UART1->RIS);
    printf("UART1->MIS:       0x%lx\n", RV32_UART1->RIS);
    printf("UART1->ICR:       0x%lx\n", RV32_UART1->ICR);
    printf("UART1->DMACR:     0x%lx\n", RV32_UART1->DMACR);
    printf("UART1->PIDR0:     0x%lx\n", RV32_UART1->PIDR0);
    printf("UART1->PIDR1:     0x%lx\n", RV32_UART1->PIDR1);
    printf("UART1->PIDR2:     0x%lx\n", RV32_UART1->PIDR2);
    printf("UART1->PIDR3:     0x%lx\n", RV32_UART1->PIDR3);
    printf("UART1->CIDR0:     0x%lx\n", RV32_UART1->CIDR0);
    printf("UART1->CIDR1:     0x%lx\n", RV32_UART1->CIDR1);
    printf("UART1->CIDR2:     0x%lx\n", RV32_UART1->CIDR2);
    printf("UART1->CIDR3:     0x%lx\n", RV32_UART1->CIDR3);
    printf("\n");
    printf("UART2->DR:        0x%lx\n", RV32_UART2->DR);
    printf("UART2->RSR (ECR): 0x%lx\n", RV32_UART2->RSR);
    printf("UART2->FR:        0x%lx\n", RV32_UART2->FR);
    printf("UART2->ILPR:      0x%lx\n", RV32_UART2->ILPR);
    printf("UART2->IBDR:      0x%lx\n", RV32_UART2->IBDR);
    printf("UART2->FBDR:      0x%lx\n", RV32_UART2->FBDR);
    printf("UART2->LCR_H:     0x%lx\n", RV32_UART2->LCR_H);
    printf("UART2->CR:        0x%lx\n", RV32_UART2->CR);
    printf("UART2->IFLS:      0x%lx\n", RV32_UART2->IFLS);
    printf("UART2->IMSC:      0x%lx\n", RV32_UART2->IMSC);
    printf("UART2->RIS:       0x%lx\n", RV32_UART2->RIS);
    printf("UART2->MIS:       0x%lx\n", RV32_UART2->RIS);
    printf("UART2->ICR:       0x%lx\n", RV32_UART2->ICR);
    printf("UART2->DMACR:     0x%lx\n", RV32_UART2->DMACR);
    printf("UART2->PIDR0:     0x%lx\n", RV32_UART2->PIDR0);
    printf("UART2->PIDR1:     0x%lx\n", RV32_UART2->PIDR1);
    printf("UART2->PIDR2:     0x%lx\n", RV32_UART2->PIDR2);
    printf("UART2->PIDR3:     0x%lx\n", RV32_UART2->PIDR3);
    printf("UART2->CIDR0:     0x%lx\n", RV32_UART2->CIDR0);
    printf("UART2->CIDR1:     0x%lx\n", RV32_UART2->CIDR1);
    printf("UART2->CIDR2:     0x%lx\n", RV32_UART2->CIDR2);
    printf("UART2->CIDR3:     0x%lx\n", RV32_UART2->CIDR3);
    printf("\n");
    printf("UART3->DR:        0x%lx\n", RV32_UART3->DR);
    printf("UART3->RSR (ECR): 0x%lx\n", RV32_UART3->RSR);
    printf("UART3->FR:        0x%lx\n", RV32_UART3->FR);
    printf("UART3->ILPR:      0x%lx\n", RV32_UART3->ILPR);
    printf("UART3->IBDR:      0x%lx\n", RV32_UART3->IBDR);
    printf("UART3->FBDR:      0x%lx\n", RV32_UART3->FBDR);
    printf("UART3->LCR_H:     0x%lx\n", RV32_UART3->LCR_H);
    printf("UART3->CR:        0x%lx\n", RV32_UART3->CR);
    printf("UART3->IFLS:      0x%lx\n", RV32_UART3->IFLS);
    printf("UART3->IMSC:      0x%lx\n", RV32_UART3->IMSC);
    printf("UART3->RIS:       0x%lx\n", RV32_UART3->RIS);
    printf("UART3->MIS:       0x%lx\n", RV32_UART3->RIS);
    printf("UART3->ICR:       0x%lx\n", RV32_UART3->ICR);
    printf("UART3->DMACR:     0x%lx\n", RV32_UART3->DMACR);
    printf("UART3->PIDR0:     0x%lx\n", RV32_UART3->PIDR0);
    printf("UART3->PIDR1:     0x%lx\n", RV32_UART3->PIDR1);
    printf("UART3->PIDR2:     0x%lx\n", RV32_UART3->PIDR2);
    printf("UART3->PIDR3:     0x%lx\n", RV32_UART3->PIDR3);
    printf("UART3->CIDR0:     0x%lx\n", RV32_UART3->CIDR0);
    printf("UART3->CIDR1:     0x%lx\n", RV32_UART3->CIDR1);
    printf("UART3->CIDR2:     0x%lx\n", RV32_UART3->CIDR2);
    printf("UART3->CIDR3:     0x%lx\n", RV32_UART3->CIDR3);
    printf("\n");
    printf("UART4->DR:        0x%lx\n", RV32_UART4->DR);
    printf("UART4->RSR (ECR): 0x%lx\n", RV32_UART4->RSR);
    printf("UART4->FR:        0x%lx\n", RV32_UART4->FR);
    printf("UART4->ILPR:      0x%lx\n", RV32_UART4->ILPR);
    printf("UART4->IBDR:      0x%lx\n", RV32_UART4->IBDR);
    printf("UART4->FBDR:      0x%lx\n", RV32_UART4->FBDR);
    printf("UART4->LCR_H:     0x%lx\n", RV32_UART4->LCR_H);
    printf("UART4->CR:        0x%lx\n", RV32_UART4->CR);
    printf("UART4->IFLS:      0x%lx\n", RV32_UART4->IFLS);
    printf("UART4->IMSC:      0x%lx\n", RV32_UART4->IMSC);
    printf("UART4->RIS:       0x%lx\n", RV32_UART4->RIS);
    printf("UART4->MIS:       0x%lx\n", RV32_UART4->RIS);
    printf("UART4->ICR:       0x%lx\n", RV32_UART4->ICR);
    printf("UART4->DMACR:     0x%lx\n", RV32_UART4->DMACR);
    printf("UART4->PIDR0:     0x%lx\n", RV32_UART4->PIDR0);
    printf("UART4->PIDR1:     0x%lx\n", RV32_UART4->PIDR1);
    printf("UART4->PIDR2:     0x%lx\n", RV32_UART4->PIDR2);
    printf("UART4->PIDR3:     0x%lx\n", RV32_UART4->PIDR3);
    printf("UART4->CIDR0:     0x%lx\n", RV32_UART4->CIDR0);
    printf("UART4->CIDR1:     0x%lx\n", RV32_UART4->CIDR1);
    printf("UART4->CIDR2:     0x%lx\n", RV32_UART4->CIDR2);
    printf("UART4->CIDR3:     0x%lx\n", RV32_UART4->CIDR3);
    printf("\n");
    printf("uart_regs_probe end\n");
}

static void i2c_regs_probe (void)
{
    printf("i2c_regs_probe start\n");
	printf("I2C0->CON:                0x%lx\n", RV32_I2C0->CON);
    printf("I2C0->TAR:                0x%lx\n", RV32_I2C0->TAR);
    printf("I2C0->SAR:                0x%lx\n", RV32_I2C0->SAR);
    printf("I2C0->HS_MADDR:           0x%lx\n", RV32_I2C0->HS_MADDR);
    printf("I2C0->DATA_CMD:           0x%lx\n", RV32_I2C0->DATA_CMD);
    printf("I2C0->SS_SCL_HCNT:        0x%lx\n", RV32_I2C0->SS_SCL_HCNT);
    printf("I2C0->SS_SCL_LCNT:        0x%lx\n", RV32_I2C0->SS_SCL_LCNT);
    printf("I2C0->FS_SCL_HCNT:        0x%lx\n", RV32_I2C0->FS_SCL_HCNT);
    printf("I2C0->FS_SCL_LCNT:        0x%lx\n", RV32_I2C0->FS_SCL_LCNT);
    printf("I2C0->HS_SCL_HCNT:        0x%lx\n", RV32_I2C0->HS_SCL_HCNT);
    printf("I2C0->HS_SCL_LCNT:        0x%lx\n", RV32_I2C0->HS_SCL_LCNT);
    printf("I2C0->INTR_STAT:          0x%lx\n", RV32_I2C0->INTR_STAT);
    printf("I2C0->INTR_MASK:          0x%lx\n", RV32_I2C0->INTR_MASK);
    printf("I2C0->RAW_INTR_STAT:      0x%lx\n", RV32_I2C0->RAW_INTR_STAT);
    printf("I2C0->RX_TL:              0x%lx\n", RV32_I2C0->RX_TL);
    printf("I2C0->TX_TL:              0x%lx\n", RV32_I2C0->TX_TL);
    printf("I2C0->CLR_INTR:           0x%lx\n", RV32_I2C0->CLR_INTR);
    printf("I2C0->CLR_RX_UNDER:       0x%lx\n", RV32_I2C0->CLR_RX_UNDER);
    printf("I2C0->CLR_RX_OVER:        0x%lx\n", RV32_I2C0->CLR_RX_OVER);
    printf("I2C0->CLR_TX_OVER:        0x%lx\n", RV32_I2C0->CLR_TX_OVER);
    printf("I2C0->CLR_RD_REQ:         0x%lx\n", RV32_I2C0->CLR_RD_REQ);
    printf("I2C0->CLR_TX_ABRT:        0x%lx\n", RV32_I2C0->CLR_TX_ABRT);
    printf("I2C0->CLR_RX_DONE:        0x%lx\n", RV32_I2C0->CLR_RX_DONE);
    printf("I2C0->CLR_ACTIVITY:       0x%lx\n", RV32_I2C0->CLR_ACTIVITY);
    printf("I2C0->CLR_STOP_DET:       0x%lx\n", RV32_I2C0->CLR_STOP_DET);
    printf("I2C0->CLR_START_DET:      0x%lx\n", RV32_I2C0->CLR_START_DET);
    printf("I2C0->CLR_GEN_CALL:       0x%lx\n", RV32_I2C0->CLR_GEN_CALL);
    printf("I2C0->ENABLE:             0x%lx\n", RV32_I2C0->ENABLE);
    printf("I2C0->STATUS:             0x%lx\n", RV32_I2C0->STATUS);
    printf("I2C0->TXFLR:              0x%lx\n", RV32_I2C0->TXFLR);
    printf("I2C0->RXFLR:              0x%lx\n", RV32_I2C0->RXFLR);
    printf("I2C0->SDA_HOLD:           0x%lx\n", RV32_I2C0->SDA_HOLD);
    printf("I2C0->TX_ABRT_SOURCE:     0x%lx\n", RV32_I2C0->TX_ABRT_SOURCE);
    printf("I2C0->SLV_DATA_NACK_ONLY: 0x%lx\n", RV32_I2C0->SLV_DATA_NACK_ONLY);
    printf("I2C0->DMA_CR:             0x%lx\n", RV32_I2C0->DMA_CR);
    printf("I2C0->DMA_TDLR:           0x%lx\n", RV32_I2C0->DMA_TDLR);
    printf("I2C0->DMA_RDLR:           0x%lx\n", RV32_I2C0->DMA_RDLR);
    printf("I2C0->SDA_SETUP:          0x%lx\n", RV32_I2C0->SDA_SETUP);
    printf("I2C0->ACK_GENERAL_CALL:   0x%lx\n", RV32_I2C0->ACK_GENERAL_CALL);
    printf("I2C0->ENABLE_STATUS:      0x%lx\n", RV32_I2C0->ENABLE_STATUS);
    printf("I2C0->FS_SPKLEN:          0x%lx\n", RV32_I2C0->FS_SPKLEN);
    printf("I2C0->HS_SPKLEN:          0x%lx\n", RV32_I2C0->HS_SPKLEN);
    printf("I2C0->COMP_VERSION:       0x%lx\n", RV32_I2C0->COMP_VERSION);
    printf("I2C0->COMP_TYPE:          0x%lx\n", RV32_I2C0->COMP_TYPE);
    printf("\n");
	printf("I2C1->CON:                0x%lx\n", RV32_I2C1->CON);
    printf("I2C1->TAR:                0x%lx\n", RV32_I2C1->TAR);
    printf("I2C1->SAR:                0x%lx\n", RV32_I2C1->SAR);
    printf("I2C1->HS_MADDR:           0x%lx\n", RV32_I2C1->HS_MADDR);
    printf("I2C1->DATA_CMD:           0x%lx\n", RV32_I2C1->DATA_CMD);
    printf("I2C1->SS_SCL_HCNT:        0x%lx\n", RV32_I2C1->SS_SCL_HCNT);
    printf("I2C1->SS_SCL_LCNT:        0x%lx\n", RV32_I2C1->SS_SCL_LCNT);
    printf("I2C1->FS_SCL_HCNT:        0x%lx\n", RV32_I2C1->FS_SCL_HCNT);
    printf("I2C1->FS_SCL_LCNT:        0x%lx\n", RV32_I2C1->FS_SCL_LCNT);
    printf("I2C1->HS_SCL_HCNT:        0x%lx\n", RV32_I2C1->HS_SCL_HCNT);
    printf("I2C1->HS_SCL_LCNT:        0x%lx\n", RV32_I2C1->HS_SCL_LCNT);
    printf("I2C1->INTR_STAT:          0x%lx\n", RV32_I2C1->INTR_STAT);
    printf("I2C1->INTR_MASK:          0x%lx\n", RV32_I2C1->INTR_MASK);
    printf("I2C1->RAW_INTR_STAT:      0x%lx\n", RV32_I2C1->RAW_INTR_STAT);
    printf("I2C1->RX_TL:              0x%lx\n", RV32_I2C1->RX_TL);
    printf("I2C1->TX_TL:              0x%lx\n", RV32_I2C1->TX_TL);
    printf("I2C1->CLR_INTR:           0x%lx\n", RV32_I2C1->CLR_INTR);
    printf("I2C1->CLR_RX_UNDER:       0x%lx\n", RV32_I2C1->CLR_RX_UNDER);
    printf("I2C1->CLR_RX_OVER:        0x%lx\n", RV32_I2C1->CLR_RX_OVER);
    printf("I2C1->CLR_TX_OVER:        0x%lx\n", RV32_I2C1->CLR_TX_OVER);
    printf("I2C1->CLR_RD_REQ:         0x%lx\n", RV32_I2C1->CLR_RD_REQ);
    printf("I2C1->CLR_TX_ABRT:        0x%lx\n", RV32_I2C1->CLR_TX_ABRT);
    printf("I2C1->CLR_RX_DONE:        0x%lx\n", RV32_I2C1->CLR_RX_DONE);
    printf("I2C1->CLR_ACTIVITY:       0x%lx\n", RV32_I2C1->CLR_ACTIVITY);
    printf("I2C1->CLR_STOP_DET:       0x%lx\n", RV32_I2C1->CLR_STOP_DET);
    printf("I2C1->CLR_START_DET:      0x%lx\n", RV32_I2C1->CLR_START_DET);
    printf("I2C1->CLR_GEN_CALL:       0x%lx\n", RV32_I2C1->CLR_GEN_CALL);
    printf("I2C1->ENABLE:             0x%lx\n", RV32_I2C1->ENABLE);
    printf("I2C1->STATUS:             0x%lx\n", RV32_I2C1->STATUS);
    printf("I2C1->TXFLR:              0x%lx\n", RV32_I2C1->TXFLR);
    printf("I2C1->RXFLR:              0x%lx\n", RV32_I2C1->RXFLR);
    printf("I2C1->SDA_HOLD:           0x%lx\n", RV32_I2C1->SDA_HOLD);
    printf("I2C1->TX_ABRT_SOURCE      0x%lx\n", RV32_I2C1->TX_ABRT_SOURCE);
    printf("I2C1->SLV_DATA_NACK_ONLY: 0x%lx\n", RV32_I2C1->SLV_DATA_NACK_ONLY);
    printf("I2C1->DMA_CR:             0x%lx\n", RV32_I2C1->DMA_CR);
    printf("I2C1->DMA_TDLR:           0x%lx\n", RV32_I2C1->DMA_TDLR);
    printf("I2C1->DMA_RDLR:           0x%lx\n", RV32_I2C1->DMA_RDLR);
    printf("I2C1->SDA_SETUP:          0x%lx\n", RV32_I2C1->SDA_SETUP);
    printf("I2C1->ACK_GENERAL_CALL:   0x%lx\n", RV32_I2C1->ACK_GENERAL_CALL);
    printf("I2C1->ENABLE_STATUS:      0x%lx\n", RV32_I2C1->ENABLE_STATUS);
    printf("I2C1->FS_SPKLEN:          0x%lx\n", RV32_I2C1->FS_SPKLEN);
    printf("I2C1->HS_SPKLEN:          0x%lx\n", RV32_I2C1->HS_SPKLEN);
    printf("I2C1->COMP_VERSION:       0x%lx\n", RV32_I2C1->COMP_VERSION);
    printf("I2C1->COMP_TYPE:          0x%lx\n", RV32_I2C1->COMP_TYPE);
    printf("\n");
    printf("i2c_regs_probe end\n");
}

static void gpio_regs_probe (void)
{
    printf("gpio_regs_probe start\n");
	printf("GPIO0->DIR:   0x%lx\n", RV32_GPIO0->DIR);
	printf("GPIO0->IS:    0x%lx\n", RV32_GPIO0->IS);
	printf("GPIO0->IBE:   0x%lx\n", RV32_GPIO0->IBE);
	printf("GPIO0->IEV:   0x%lx\n", RV32_GPIO0->IEV);
	printf("GPIO0->IE:    0x%lx\n", RV32_GPIO0->IE);
	printf("GPIO0->RIS:   0x%lx\n", RV32_GPIO0->RIS);
	printf("GPIO0->MIS:   0x%lx\n", RV32_GPIO0->MIS);
	printf("GPIO0->IC:    0x%lx\n", RV32_GPIO0->IC);
	printf("GPIO0->AFSEL: 0x%lx\n", RV32_GPIO0->AFSEL);
	printf("GPIO0->PIDR0: 0x%lx\n", RV32_GPIO0->PIDR0);
	printf("GPIO0->PIDR1: 0x%lx\n", RV32_GPIO0->PIDR1);
	printf("GPIO0->PIDR2: 0x%lx\n", RV32_GPIO0->PIDR2);
	printf("GPIO0->PIDR3: 0x%lx\n", RV32_GPIO0->PIDR3);
	printf("GPIO0->CIDR0: 0x%lx\n", RV32_GPIO0->CIDR0);
	printf("GPIO0->CIDR1: 0x%lx\n", RV32_GPIO0->CIDR1);
	printf("GPIO0->CIDR2: 0x%lx\n", RV32_GPIO0->CIDR2);
	printf("GPIO0->CIDR3: 0x%lx\n", RV32_GPIO0->CIDR3);
    printf("\n");
	printf("GPIO1->DIR:   0x%lx\n", RV32_GPIO1->DIR);
	printf("GPIO1->IS:    0x%lx\n", RV32_GPIO1->IS);
	printf("GPIO1->IBE:   0x%lx\n", RV32_GPIO1->IBE);
	printf("GPIO1->IEV:   0x%lx\n", RV32_GPIO1->IEV);
	printf("GPIO1->IE:    0x%lx\n", RV32_GPIO1->IE);
	printf("GPIO1->RIS:   0x%lx\n", RV32_GPIO1->RIS);
	printf("GPIO1->MIS:   0x%lx\n", RV32_GPIO1->MIS);
	printf("GPIO1->IC:    0x%lx\n", RV32_GPIO1->IC);
	printf("GPIO1->AFSEL: 0x%lx\n", RV32_GPIO1->AFSEL);
	printf("GPIO1->PIDR0: 0x%lx\n", RV32_GPIO1->PIDR0);
	printf("GPIO1->PIDR1: 0x%lx\n", RV32_GPIO1->PIDR1);
	printf("GPIO1->PIDR2: 0x%lx\n", RV32_GPIO1->PIDR2);
	printf("GPIO1->PIDR3: 0x%lx\n", RV32_GPIO1->PIDR3);
	printf("GPIO1->CIDR0: 0x%lx\n", RV32_GPIO1->CIDR0);
	printf("GPIO1->CIDR1: 0x%lx\n", RV32_GPIO1->CIDR1);
	printf("GPIO1->CIDR2: 0x%lx\n", RV32_GPIO1->CIDR2);
	printf("GPIO1->CIDR3: 0x%lx\n", RV32_GPIO1->CIDR3);
    printf("\n");
	printf("GPIO2->DIR:   0x%lx\n", RV32_GPIO2->DIR);
	printf("GPIO2->IS:    0x%lx\n", RV32_GPIO2->IS);
	printf("GPIO2->IBE:   0x%lx\n", RV32_GPIO2->IBE);
	printf("GPIO2->IEV:   0x%lx\n", RV32_GPIO2->IEV);
	printf("GPIO2->IE:    0x%lx\n", RV32_GPIO2->IE);
	printf("GPIO2->RIS:   0x%lx\n", RV32_GPIO2->RIS);
	printf("GPIO2->MIS:   0x%lx\n", RV32_GPIO2->MIS);
	printf("GPIO2->IC:    0x%lx\n", RV32_GPIO2->IC);
	printf("GPIO2->AFSEL: 0x%lx\n", RV32_GPIO2->AFSEL);
	printf("GPIO2->PIDR0: 0x%lx\n", RV32_GPIO2->PIDR0);
	printf("GPIO2->PIDR1: 0x%lx\n", RV32_GPIO2->PIDR1);
	printf("GPIO2->PIDR2: 0x%lx\n", RV32_GPIO2->PIDR2);
	printf("GPIO2->PIDR3: 0x%lx\n", RV32_GPIO2->PIDR3);
	printf("GPIO2->CIDR0: 0x%lx\n", RV32_GPIO2->CIDR0);
	printf("GPIO2->CIDR1: 0x%lx\n", RV32_GPIO2->CIDR1);
	printf("GPIO2->CIDR2: 0x%lx\n", RV32_GPIO2->CIDR2);
	printf("GPIO2->CIDR3: 0x%lx\n", RV32_GPIO2->CIDR3);
    printf("\n");
	printf("GPIO3->DIR:   0x%lx\n", RV32_GPIO3->DIR);
	printf("GPIO3->IS:    0x%lx\n", RV32_GPIO3->IS);
	printf("GPIO3->IBE:   0x%lx\n", RV32_GPIO3->IBE);
	printf("GPIO3->IEV:   0x%lx\n", RV32_GPIO3->IEV);
	printf("GPIO3->IE:    0x%lx\n", RV32_GPIO3->IE);
	printf("GPIO3->RIS:   0x%lx\n", RV32_GPIO3->RIS);
	printf("GPIO3->MIS:   0x%lx\n", RV32_GPIO3->MIS);
	printf("GPIO3->IC:    0x%lx\n", RV32_GPIO3->IC);
	printf("GPIO3->AFSEL: 0x%lx\n", RV32_GPIO3->AFSEL);
	printf("GPIO3->PIDR0: 0x%lx\n", RV32_GPIO3->PIDR0);
	printf("GPIO3->PIDR1: 0x%lx\n", RV32_GPIO3->PIDR1);
	printf("GPIO3->PIDR2: 0x%lx\n", RV32_GPIO3->PIDR2);
	printf("GPIO3->PIDR3: 0x%lx\n", RV32_GPIO3->PIDR3);
	printf("GPIO3->CIDR0: 0x%lx\n", RV32_GPIO3->CIDR0);
	printf("GPIO3->CIDR1: 0x%lx\n", RV32_GPIO3->CIDR1);
	printf("GPIO3->CIDR2: 0x%lx\n", RV32_GPIO3->CIDR2);
	printf("GPIO3->CIDR3: 0x%lx\n", RV32_GPIO3->CIDR3);
    printf("\n");
	printf("GPIO4->DIR:   0x%lx\n", RV32_GPIO4->DIR);
	printf("GPIO4->IS:    0x%lx\n", RV32_GPIO4->IS);
	printf("GPIO4->IBE:   0x%lx\n", RV32_GPIO4->IBE);
	printf("GPIO4->IEV:   0x%lx\n", RV32_GPIO4->IEV);
	printf("GPIO4->IE:    0x%lx\n", RV32_GPIO4->IE);
	printf("GPIO4->RIS:   0x%lx\n", RV32_GPIO4->RIS);
	printf("GPIO4->MIS:   0x%lx\n", RV32_GPIO4->MIS);
	printf("GPIO4->IC:    0x%lx\n", RV32_GPIO4->IC);
	printf("GPIO4->AFSEL: 0x%lx\n", RV32_GPIO4->AFSEL);
	printf("GPIO4->PIDR0: 0x%lx\n", RV32_GPIO4->PIDR0);
	printf("GPIO4->PIDR1: 0x%lx\n", RV32_GPIO4->PIDR1);
	printf("GPIO4->PIDR2: 0x%lx\n", RV32_GPIO4->PIDR2);
	printf("GPIO4->PIDR3: 0x%lx\n", RV32_GPIO4->PIDR3);
	printf("GPIO4->CIDR0: 0x%lx\n", RV32_GPIO4->CIDR0);
	printf("GPIO4->CIDR1: 0x%lx\n", RV32_GPIO4->CIDR1);
	printf("GPIO4->CIDR2: 0x%lx\n", RV32_GPIO4->CIDR2);
	printf("GPIO4->CIDR3: 0x%lx\n", RV32_GPIO4->CIDR3);
    printf("\n");
    printf("gpio_regs_probe end\n");
}

static void dma_regs_probe (void)
{
    printf("dma_regs_probe start\n");
    printf("DMA0->MC0:  0x%lx\n", RV32_DMA0->MC0);
    printf("DMA0->SAR0: 0x%lx\n", RV32_DMA0->SAR0);
    printf("DMA0->DAR0: 0x%lx\n", RV32_DMA0->DAR0);
    printf("DMA0->BC0:  0x%lx\n", RV32_DMA0->BC0);
    printf("DMA0->MC1:  0x%lx\n", RV32_DMA0->MC1);
    printf("DMA0->SAR1: 0x%lx\n", RV32_DMA0->SAR0);
    printf("DMA0->DAR1: 0x%lx\n", RV32_DMA0->DAR0);
    printf("DMA0->BC1:  0x%lx\n", RV32_DMA0->BC1);
    printf("DMA0->MC2:  0x%lx\n", RV32_DMA0->MC2);
    printf("DMA0->SAR2: 0x%lx\n", RV32_DMA0->SAR2);
    printf("DMA0->DAR2: 0x%lx\n", RV32_DMA0->DAR2);
    printf("DMA0->BC2:  0x%lx\n", RV32_DMA0->BC2);
    printf("DMA0->MC3:  0x%lx\n", RV32_DMA0->MC3);
    printf("DMA0->SAR3: 0x%lx\n", RV32_DMA0->SAR3);
    printf("DMA0->DAR3: 0x%lx\n", RV32_DMA0->DAR3);
    printf("DMA0->BC3:  0x%lx\n", RV32_DMA0->BC3);
    printf("DMA0->MC4:  0x%lx\n", RV32_DMA0->MC4);
    printf("DMA0->SAR4: 0x%lx\n", RV32_DMA0->SAR4);
    printf("DMA0->DAR4: 0x%lx\n", RV32_DMA0->DAR4);
    printf("DMA0->BC4:  0x%lx\n", RV32_DMA0->BC4);
    printf("DMA0->MC5:  0x%lx\n", RV32_DMA0->MC5);
    printf("DMA0->SAR5: 0x%lx\n", RV32_DMA0->SAR5);
    printf("DMA0->DAR5: 0x%lx\n", RV32_DMA0->DAR5);
    printf("DMA0->BC5:  0x%lx\n", RV32_DMA0->BC5);
    printf("DMA0->CSR:  0x%lx\n", RV32_DMA0->CSR);
    printf("\n");
    printf("DMA1->MC0:  0x%lx\n", RV32_DMA1->MC0);
    printf("DMA1->SAR0: 0x%lx\n", RV32_DMA1->SAR0);
    printf("DMA1->DAR0: 0x%lx\n", RV32_DMA1->DAR0);
    printf("DMA1->BC0:  0x%lx\n", RV32_DMA1->BC0);
    printf("DMA1->MC1:  0x%lx\n", RV32_DMA1->MC1);
    printf("DMA1->SAR1: 0x%lx\n", RV32_DMA1->SAR0);
    printf("DMA1->DAR1: 0x%lx\n", RV32_DMA1->DAR0);
    printf("DMA1->BC1:  0x%lx\n", RV32_DMA1->BC1);
    printf("DMA1->MC2:  0x%lx\n", RV32_DMA1->MC2);
    printf("DMA1->SAR2: 0x%lx\n", RV32_DMA1->SAR2);
    printf("DMA1->DAR2: 0x%lx\n", RV32_DMA1->DAR2);
    printf("DMA1->BC2:  0x%lx\n", RV32_DMA1->BC2);
    printf("DMA1->MC3:  0x%lx\n", RV32_DMA1->MC3);
    printf("DMA1->SAR3: 0x%lx\n", RV32_DMA1->SAR3);
    printf("DMA1->DAR3: 0x%lx\n", RV32_DMA1->DAR3);
    printf("DMA1->BC3:  0x%lx\n", RV32_DMA1->BC3);
    printf("DMA1->MC4:  0x%lx\n", RV32_DMA1->MC4);
    printf("DMA1->SAR4: 0x%lx\n", RV32_DMA1->SAR4);
    printf("DMA1->DAR4: 0x%lx\n", RV32_DMA1->DAR4);
    printf("DMA1->BC4:  0x%lx\n", RV32_DMA1->BC4);
    printf("DMA1->MC5:  0x%lx\n", RV32_DMA1->MC5);
    printf("DMA1->SAR5: 0x%lx\n", RV32_DMA1->SAR5);
    printf("DMA1->DAR5: 0x%lx\n", RV32_DMA1->DAR5);
    printf("DMA1->BC5:  0x%lx\n", RV32_DMA1->BC5);
    printf("DMA1->CSR:  0x%lx\n", RV32_DMA1->CSR);
    printf("\n");
    printf("dma_regs_probe end\n");
}

static void spi_regs_probe (void)
{
    printf("spi_regs_probe start\n");
    printf("SPI0->CR0:      0x%lx\n", RV32_SPI0->CR0);
    printf("SPI0->CR1:      0x%lx\n", RV32_SPI0->CR1);
    printf("SPI0->DR:       0x%lx\n", RV32_SPI0->DR);
    printf("SPI0->SR:       0x%lx\n", RV32_SPI0->SR);
    printf("SPI0->CPSR:     0x%lx\n", RV32_SPI0->CPSR);
    printf("SPI0->IMSC:     0x%lx\n", RV32_SPI0->IMSC);
    printf("SPI0->RIS:      0x%lx\n", RV32_SPI0->RIS);
    printf("SPI0->MIS:      0x%lx\n", RV32_SPI0->MIS);
    printf("SPI0->ICR:      0x%lx\n", RV32_SPI0->ICR);
    printf("SPI0->DMACR:    0x%lx\n", RV32_SPI0->DMACR);
    printf("SPI0->PIDR0:    0x%lx\n", RV32_SPI0->PIDR0);
    printf("SPI0->PIDR1:    0x%lx\n", RV32_SPI0->PIDR1);
    printf("SPI0->PIDR2:    0x%lx\n", RV32_SPI0->PIDR2);
    printf("SPI0->PIDR3:    0x%lx\n", RV32_SPI0->PIDR3);
    printf("SPI0->CIDR0:    0x%lx\n", RV32_SPI0->CIDR0);
    printf("SPI0->CIDR1:    0x%lx\n", RV32_SPI0->CIDR1);
    printf("SPI0->CIDR2:    0x%lx\n", RV32_SPI0->CIDR2);
    printf("SPI0->CIDR3:    0x%lx\n", RV32_SPI0->CIDR3);
    printf("\n");
#if 1
    printf("SPI1->CR0:      0x%lx\n", RV32_SPI1->CR0);
    printf("SPI1->CR1:      0x%lx\n", RV32_SPI1->CR1);
    printf("SPI1->DR:       0x%lx\n", RV32_SPI1->DR);
    printf("SPI1->SR:       0x%lx\n", RV32_SPI1->SR);
    printf("SPI1->CPSR:     0x%lx\n", RV32_SPI1->CPSR);
    printf("SPI1->IMSC:     0x%lx\n", RV32_SPI1->IMSC);
    printf("SPI1->RIS:      0x%lx\n", RV32_SPI1->RIS);
    printf("SPI1->MIS:      0x%lx\n", RV32_SPI1->MIS);
    printf("SPI1->ICR:      0x%lx\n", RV32_SPI1->ICR);
    printf("SPI1->DMACR:    0x%lx\n", RV32_SPI1->DMACR);
    printf("SPI1->PIDR0:    0x%lx\n", RV32_SPI1->PIDR0);
    printf("SPI1->PIDR1:    0x%lx\n", RV32_SPI1->PIDR1);
    printf("SPI1->PIDR2:    0x%lx\n", RV32_SPI1->PIDR2);
    printf("SPI1->PIDR3:    0x%lx\n", RV32_SPI1->PIDR3);
    printf("SPI1->CIDR0:    0x%lx\n", RV32_SPI1->CIDR0);
    printf("SPI1->CIDR1:    0x%lx\n", RV32_SPI1->CIDR1);
    printf("SPI1->CIDR2:    0x%lx\n", RV32_SPI1->CIDR2);
    printf("SPI1->CIDR3:    0x%lx\n", RV32_SPI1->CIDR3);
    printf("\n");
    printf("SPI2->CR0:      0x%lx\n", RV32_SPI2->CR0);
    printf("SPI2->CR1:      0x%lx\n", RV32_SPI2->CR1);
    printf("SPI2->DR:       0x%lx\n", RV32_SPI2->DR);
    printf("SPI2->SR:       0x%lx\n", RV32_SPI2->SR);
    printf("SPI2->CPSR:     0x%lx\n", RV32_SPI2->CPSR);
    printf("SPI2->IMSC:     0x%lx\n", RV32_SPI2->IMSC);
    printf("SPI2->RIS:      0x%lx\n", RV32_SPI2->RIS);
    printf("SPI2->MIS:      0x%lx\n", RV32_SPI2->MIS);
    printf("SPI2->ICR:      0x%lx\n", RV32_SPI2->ICR);
    printf("SPI2->DMACR:    0x%lx\n", RV32_SPI2->DMACR);
    printf("SPI2->PIDR0:    0x%lx\n", RV32_SPI2->PIDR0);
    printf("SPI2->PIDR1:    0x%lx\n", RV32_SPI2->PIDR1);
    printf("SPI2->PIDR2:    0x%lx\n", RV32_SPI2->PIDR2);
    printf("SPI2->PIDR3:    0x%lx\n", RV32_SPI2->PIDR3);
    printf("SPI2->CIDR0:    0x%lx\n", RV32_SPI2->CIDR0);
    printf("SPI2->CIDR1:    0x%lx\n", RV32_SPI2->CIDR1);
    printf("SPI2->CIDR2:    0x%lx\n", RV32_SPI2->CIDR2);
    printf("SPI2->CIDR3:    0x%lx\n", RV32_SPI2->CIDR3);
    printf("\n");
    printf("SPI3->CR0:      0x%lx\n", RV32_SPI3->CR0);
    printf("SPI3->CR1:      0x%lx\n", RV32_SPI3->CR1);
    printf("SPI3->DR:       0x%lx\n", RV32_SPI3->DR);
    printf("SPI3->SR:       0x%lx\n", RV32_SPI3->SR);
    printf("SPI3->CPSR:     0x%lx\n", RV32_SPI3->CPSR);
    printf("SPI3->IMSC:     0x%lx\n", RV32_SPI3->IMSC);
    printf("SPI3->RIS:      0x%lx\n", RV32_SPI3->RIS);
    printf("SPI3->MIS:      0x%lx\n", RV32_SPI3->MIS);
    printf("SPI3->ICR:      0x%lx\n", RV32_SPI3->ICR);
    printf("SPI3->DMACR:    0x%lx\n", RV32_SPI3->DMACR);
    printf("SPI3->PIDR0:    0x%lx\n", RV32_SPI3->PIDR0);
    printf("SPI3->PIDR1:    0x%lx\n", RV32_SPI3->PIDR1);
    printf("SPI3->PIDR2:    0x%lx\n", RV32_SPI3->PIDR2);
    printf("SPI3->PIDR3:    0x%lx\n", RV32_SPI3->PIDR3);
    printf("SPI3->CIDR0:    0x%lx\n", RV32_SPI3->CIDR0);
    printf("SPI3->CIDR1:    0x%lx\n", RV32_SPI3->CIDR1);
    printf("SPI3->CIDR2:    0x%lx\n", RV32_SPI3->CIDR2);
    printf("SPI3->CIDR3:    0x%lx\n", RV32_SPI3->CIDR3);
    printf("\n");
    printf("SPI4->CR0:      0x%lx\n", RV32_SPI4->CR0);
    printf("SPI4->CR1:      0x%lx\n", RV32_SPI4->CR1);
    printf("SPI4->DR:       0x%lx\n", RV32_SPI4->DR);
    printf("SPI4->SR:       0x%lx\n", RV32_SPI4->SR);
    printf("SPI4->CPSR:     0x%lx\n", RV32_SPI4->CPSR);
    printf("SPI4->IMSC:     0x%lx\n", RV32_SPI4->IMSC);
    printf("SPI4->RIS:      0x%lx\n", RV32_SPI4->RIS);
    printf("SPI4->MIS:      0x%lx\n", RV32_SPI4->MIS);
    printf("SPI4->ICR:      0x%lx\n", RV32_SPI4->ICR);
    printf("SPI4->DMACR:    0x%lx\n", RV32_SPI4->DMACR);
    printf("SPI4->PIDR0:    0x%lx\n", RV32_SPI4->PIDR0);
    printf("SPI4->PIDR1:    0x%lx\n", RV32_SPI4->PIDR1);
    printf("SPI4->PIDR2:    0x%lx\n", RV32_SPI4->PIDR2);
    printf("SPI4->PIDR3:    0x%lx\n", RV32_SPI4->PIDR3);
    printf("SPI4->CIDR0:    0x%lx\n", RV32_SPI4->CIDR0);
    printf("SPI4->CIDR1:    0x%lx\n", RV32_SPI4->CIDR1);
    printf("SPI4->CIDR2:    0x%lx\n", RV32_SPI4->CIDR2);
    printf("SPI4->CIDR3:    0x%lx\n", RV32_SPI4->CIDR3);
    printf("\n");
    printf("SPI5->CR0:      0x%lx\n", RV32_SPI5->CR0);
    printf("SPI5->CR1:      0x%lx\n", RV32_SPI5->CR1);
    printf("SPI5->DR:       0x%lx\n", RV32_SPI5->DR);
    printf("SPI5->SR:       0x%lx\n", RV32_SPI5->SR);
    printf("SPI5->CPSR:     0x%lx\n", RV32_SPI5->CPSR);
    printf("SPI5->IMSC:     0x%lx\n", RV32_SPI5->IMSC);
    printf("SPI5->RIS:      0x%lx\n", RV32_SPI5->RIS);
    printf("SPI5->MIS:      0x%lx\n", RV32_SPI5->MIS);
    printf("SPI5->ICR:      0x%lx\n", RV32_SPI5->ICR);
    printf("SPI5->DMACR:    0x%lx\n", RV32_SPI5->DMACR);
    printf("SPI5->PIDR0:    0x%lx\n", RV32_SPI5->PIDR0);
    printf("SPI5->PIDR1:    0x%lx\n", RV32_SPI5->PIDR1);
    printf("SPI5->PIDR2:    0x%lx\n", RV32_SPI5->PIDR2);
    printf("SPI5->PIDR3:    0x%lx\n", RV32_SPI5->PIDR3);
    printf("SPI5->CIDR0:    0x%lx\n", RV32_SPI5->CIDR0);
    printf("SPI5->CIDR1:    0x%lx\n", RV32_SPI5->CIDR1);
    printf("SPI5->CIDR2:    0x%lx\n", RV32_SPI5->CIDR2);
    printf("SPI5->CIDR3:    0x%lx\n", RV32_SPI5->CIDR3);
    printf("\n");
#endif
    printf("spi_regs_probe end\n");
}

static void wdt_regs_probe (void)
{
    printf("wdt_regs_probe start.\n");
    printf("WDT->LOAD:  0x%lx\n", RV32_WDT->LOAD);
    printf("WDT->VAL:   0x%lx\n", RV32_WDT->VAL);
    printf("WDT->CTRL:  0x%lx\n", RV32_WDT->CTRL);
    printf("WDT->IC:    0x%lx\n", RV32_WDT->IC);
    printf("WDT->RIS:   0x%lx\n", RV32_WDT->RIS);
    printf("WDT->IS:    0x%lx\n", RV32_WDT->IS);
    printf("WDT->LOCK:  0x%lx\n", RV32_WDT->LOCK);
    printf("WDT->PIDR4: 0x%lx\n", RV32_WDT->PIDR4);
    printf("WDT->PIDR5: 0x%lx\n", RV32_WDT->PIDR5);
    printf("WDT->PIDR6: 0x%lx\n", RV32_WDT->PIDR6);
    printf("WDT->PIDR7: 0x%lx\n", RV32_WDT->PIDR7);
    printf("WDT->PIDR0: 0x%lx\n", RV32_WDT->PIDR0);
    printf("WDT->PIDR1: 0x%lx\n", RV32_WDT->PIDR1);
    printf("WDT->PIDR2: 0x%lx\n", RV32_WDT->PIDR2);
    printf("WDT->PIDR3: 0x%lx\n", RV32_WDT->PIDR3);
    printf("WDT->CIDR0: 0x%lx\n", RV32_WDT->CIDR0);
    printf("WDT->CIDR1: 0x%lx\n", RV32_WDT->CIDR1);
    printf("WDT->CIDR2: 0x%lx\n", RV32_WDT->CIDR2);
    printf("WDT->CIDR3: 0x%lx\n", RV32_WDT->CIDR3);
    printf("wdt_regs_probe end.\n");
}

static void timer_regs_probe (void)
{
    printf("timer_regs_probe start.\n");
    printf("TIMER0->CNT:    0x%lx\n", RV32_TIMER0->CNT);
    printf("TIMER0->CTRL:   0x%lx\n", RV32_TIMER0->CTRL);
    printf("TIMER0->STAT:   0x%lx\n", RV32_TIMER0->STAT);
    printf("TIMER0->CCR:    0x%lx\n", RV32_TIMER0->CCR);
    printf("TIMER0->CCTL0:  0x%lx\n", RV32_TIMER0->CCTL0);
    printf("TIMER0->CCR0:   0x%lx\n", RV32_TIMER0->CCR0);
    printf("TIMER0->CCTL1:  0x%lx\n", RV32_TIMER0->CCTL1);
    printf("TIMER0->CCR1:   0x%lx\n", RV32_TIMER0->CCR1);
    printf("TIMER0->CCTL2:  0x%lx\n", RV32_TIMER0->CCTL2);
    printf("TIMER0->CCR2:   0x%lx\n", RV32_TIMER0->CCR2);
    printf("\n");
    printf("TIMER1->CNT:    0x%lx\n", RV32_TIMER1->CNT);
    printf("TIMER1->CTRL:   0x%lx\n", RV32_TIMER1->CTRL);
    printf("TIMER1->STAT:   0x%lx\n", RV32_TIMER1->STAT);
    printf("TIMER1->CCR:    0x%lx\n", RV32_TIMER1->CCR);
    printf("TIMER1->CCTL0:  0x%lx\n", RV32_TIMER1->CCTL0);
    printf("TIMER1->CCR0:   0x%lx\n", RV32_TIMER1->CCR0);
    printf("TIMER1->CCTL1:  0x%lx\n", RV32_TIMER1->CCTL1);
    printf("TIMER1->CCR1:   0x%lx\n", RV32_TIMER1->CCR1);
    printf("TIMER1->CCTL2:  0x%lx\n", RV32_TIMER1->CCTL2);
    printf("TIMER1->CCR2:   0x%lx\n", RV32_TIMER1->CCR2);
    printf("\n");
    printf("TIMER2->CNT:    0x%lx\n", RV32_TIMER2->CNT);
    printf("TIMER2->CTRL:   0x%lx\n", RV32_TIMER2->CTRL);
    printf("TIMER2->STAT:   0x%lx\n", RV32_TIMER2->STAT);
    printf("TIMER2->CCR:    0x%lx\n", RV32_TIMER2->CCR);
    printf("TIMER2->CCTL0:  0x%lx\n", RV32_TIMER2->CCTL0);
    printf("TIMER2->CCR0:   0x%lx\n", RV32_TIMER2->CCR0);
    printf("TIMER2->CCTL1:  0x%lx\n", RV32_TIMER2->CCTL1);
    printf("TIMER2->CCR1:   0x%lx\n", RV32_TIMER2->CCR1);
    printf("TIMER2->CCTL2:  0x%lx\n", RV32_TIMER2->CCTL2);
    printf("TIMER2->CCR2:   0x%lx\n", RV32_TIMER2->CCR2);
    printf("\n");
    printf("TIMER3->CNT:    0x%lx\n", RV32_TIMER3->CNT);
    printf("TIMER3->CTRL:   0x%lx\n", RV32_TIMER3->CTRL);
    printf("TIMER3->STAT:   0x%lx\n", RV32_TIMER3->STAT);
    printf("TIMER3->CCR:    0x%lx\n", RV32_TIMER3->CCR);
    printf("TIMER3->CCTL0:  0x%lx\n", RV32_TIMER3->CCTL0);
    printf("TIMER3->CCR0:   0x%lx\n", RV32_TIMER3->CCR0);
    printf("TIMER3->CCTL1:  0x%lx\n", RV32_TIMER3->CCTL1);
    printf("TIMER3->CCR1:   0x%lx\n", RV32_TIMER3->CCR1);
    printf("TIMER3->CCTL2:  0x%lx\n", RV32_TIMER3->CCTL2);
    printf("TIMER3->CCR2:   0x%lx\n", RV32_TIMER3->CCR2);
    printf("\n");
    printf("TIMER4->CNT:    0x%lx\n", RV32_TIMER4->CNT);
    printf("TIMER4->CTRL:   0x%lx\n", RV32_TIMER4->CTRL);
    printf("TIMER4->STAT:   0x%lx\n", RV32_TIMER4->STAT);
    printf("TIMER4->CCR:    0x%lx\n", RV32_TIMER4->CCR);
    printf("TIMER4->CCTL0:  0x%lx\n", RV32_TIMER4->CCTL0);
    printf("TIMER4->CCR0:   0x%lx\n", RV32_TIMER4->CCR0);
    printf("TIMER4->CCTL1:  0x%lx\n", RV32_TIMER4->CCTL1);
    printf("TIMER4->CCR1:   0x%lx\n", RV32_TIMER4->CCR1);
    printf("TIMER4->CCTL2:  0x%lx\n", RV32_TIMER4->CCTL2);
    printf("TIMER4->CCR2:   0x%lx\n", RV32_TIMER4->CCR2);
    printf("\n");
    printf("TIMER5->CNT:    0x%lx\n", RV32_TIMER5->CNT);
    printf("TIMER5->CTRL:   0x%lx\n", RV32_TIMER5->CTRL);
    printf("TIMER5->STAT:   0x%lx\n", RV32_TIMER5->STAT);
    printf("TIMER5->CCR:    0x%lx\n", RV32_TIMER5->CCR);
    printf("TIMER5->CCTL0:  0x%lx\n", RV32_TIMER5->CCTL0);
    printf("TIMER5->CCR0:   0x%lx\n", RV32_TIMER5->CCR0);
    printf("TIMER5->CCTL1:  0x%lx\n", RV32_TIMER5->CCTL1);
    printf("TIMER5->CCR1:   0x%lx\n", RV32_TIMER5->CCR1);
    printf("TIMER5->CCTL2:  0x%lx\n", RV32_TIMER5->CCTL2);
    printf("TIMER5->CCR2:   0x%lx\n", RV32_TIMER5->CCR2);
    printf("\n");
    printf("timer_regs_probe end.\n");
}

static void mac_regs_probe (void)
{
    printf("mac_regs_probe start.\n");
    printf("RV32_EMAC0->MACCR:        0x%lx\n", RV32_EMAC0->MACCR);
    printf("RV32_EMAC0->MACFFR:       0x%lx\n", RV32_EMAC0->MACFFR);
    printf("RV32_EMAC0->MACHTHR:      0x%lx\n", RV32_EMAC0->MACHTHR);
    printf("RV32_EMAC0->MACHTLR:      0x%lx\n", RV32_EMAC0->MACHTLR);
    printf("RV32_EMAC0->MACMIIAR:     0x%lx\n", RV32_EMAC0->MACMIIAR);
    printf("RV32_EMAC0->MACMIIDR:     0x%lx\n", RV32_EMAC0->MACMIIDR);
    printf("RV32_EMAC0->MACFCR:       0x%lx\n", RV32_EMAC0->MACFCR);
    printf("RV32_EMAC0->MACVLANTR:    0x%lx\n", RV32_EMAC0->MACVLANTR);
    printf("RV32_EMAC0->MACRWUFFR:    0x%lx\n", RV32_EMAC0->MACRWUFFR);
    printf("RV32_EMAC0->MACPMTCSR:    0x%lx\n", RV32_EMAC0->MACPMTCSR);
    printf("RV32_EMAC0->MACDBGR:      0x%lx\n", RV32_EMAC0->MACDBGR);
    printf("RV32_EMAC0->MACSR:        0x%lx\n", RV32_EMAC0->MACSR);
    printf("RV32_EMAC0->MACIMR:       0x%lx\n", RV32_EMAC0->MACIMR);
    printf("RV32_EMAC0->MACA0HR:      0x%lx\n", RV32_EMAC0->MACA0HR);
    printf("RV32_EMAC0->MACA0LR:      0x%lx\n", RV32_EMAC0->MACA0LR);
    printf("RV32_EMAC0->MACA1HR:      0x%lx\n", RV32_EMAC0->MACA1HR);
    printf("RV32_EMAC0->MACA1LR:      0x%lx\n", RV32_EMAC0->MACA1LR);
    printf("RV32_EMAC0->MMCCR:        0x%lx\n", RV32_EMAC0->MMCCR);
    printf("RV32_EMAC0->MMCRIR:       0x%lx\n", RV32_EMAC0->MMCRIR);
    printf("RV32_EMAC0->MMCTIR:       0x%lx\n", RV32_EMAC0->MMCTIR);
    printf("RV32_EMAC0->MMCRIMR:      0x%lx\n", RV32_EMAC0->MMCRIMR);
    printf("RV32_EMAC0->MMCTIMR:      0x%lx\n", RV32_EMAC0->MMCTIMR);
    printf("RV32_EMAC0->MMCTGFSCCR:   0x%lx\n", RV32_EMAC0->MMCTGFSCCR);
    printf("RV32_EMAC0->MMCTGFMSCCR:  0x%lx\n", RV32_EMAC0->MMCTGFMSCCR);
    printf("RV32_EMAC0->MMCTGFCR:     0x%lx\n", RV32_EMAC0->MMCTGFCR);
    printf("RV32_EMAC0->MMCRFCECR:    0x%lx\n", RV32_EMAC0->MMCRFCECR);
    printf("RV32_EMAC0->MMCRFAECR:    0x%lx\n", RV32_EMAC0->MMCRFAECR);
    printf("RV32_EMAC0->MMCRGUFCR:    0x%lx\n", RV32_EMAC0->MMCRGUFCR);
    printf("RV32_EMAC0->PTPTSCR:      0x%lx\n", RV32_EMAC0->PTPTSCR);
    printf("RV32_EMAC0->PTPSSIR:      0x%lx\n", RV32_EMAC0->PTPSSIR);
    printf("RV32_EMAC0->PTPTSHR:      0x%lx\n", RV32_EMAC0->PTPTSHR);
    printf("RV32_EMAC0->PTPTSLR:      0x%lx\n", RV32_EMAC0->PTPTSLR);
    printf("RV32_EMAC0->PTPTSHUR:     0x%lx\n", RV32_EMAC0->PTPTSHUR);
    printf("RV32_EMAC0->PTPTSLUR:     0x%lx\n", RV32_EMAC0->PTPTSLUR);
    printf("RV32_EMAC0->PTPTSAR:      0x%lx\n", RV32_EMAC0->PTPTSAR);
    printf("RV32_EMAC0->PTPTTHR:      0x%lx\n", RV32_EMAC0->PTPTTHR);
    printf("RV32_EMAC0->PTPTTLR:      0x%lx\n", RV32_EMAC0->PTPTTLR);
    printf("RV32_EMAC0->PTPTSSR:      0x%lx\n", RV32_EMAC0->PTPTSSR);
    printf("RV32_EMAC0->DMABMR:       0x%lx\n", RV32_EMAC0->DMABMR);
    printf("RV32_EMAC0->DMATPDR:      0x%lx\n", RV32_EMAC0->DMATPDR);
    printf("RV32_EMAC0->DMARPDR:      0x%lx\n", RV32_EMAC0->DMARPDR);
    printf("RV32_EMAC0->DMARDLAR:     0x%lx\n", RV32_EMAC0->DMARDLAR);
    printf("RV32_EMAC0->DMATDLAR:     0x%lx\n", RV32_EMAC0->DMATDLAR);
    printf("RV32_EMAC0->DMASR:        0x%lx\n", RV32_EMAC0->DMASR);
    printf("RV32_EMAC0->DMAOMR:       0x%lx\n", RV32_EMAC0->DMAOMR);
    printf("RV32_EMAC0->DMAIER:       0x%lx\n", RV32_EMAC0->DMAIER);
    printf("RV32_EMAC0->DMAMFBOCR:    0x%lx\n", RV32_EMAC0->DMAMFBOCR);
    printf("RV32_EMAC0->DMARSWTR:     0x%lx\n", RV32_EMAC0->DMARSWTR);
    printf("RV32_EMAC0->DMACHTDR:     0x%lx\n", RV32_EMAC0->DMACHTDR);
    printf("RV32_EMAC0->DMACHRDR:     0x%lx\n", RV32_EMAC0->DMACHRDR);
    printf("RV32_EMAC0->DMACHTBAR:    0x%lx\n", RV32_EMAC0->DMACHTBAR);
    printf("RV32_EMAC0->DMACHRBAR:    0x%lx\n", RV32_EMAC0->DMACHRBAR);
    printf("mac_regs_probe end.\n");
}

static void cru_regs_probe (void)
{
    printf("cru_regs_probe start.\n");
    printf("CRU->RESET_SOURCE:  0x%lx\n", RV32_CRU->RESET_SOURCE);
    printf("CRU->SOFT_RESET:    0x%lx\n", RV32_CRU->SOFT_RESET);
    printf("CRU->LOCAL_RST_0:   0x%lx\n", RV32_CRU->LOCAL_RST_0);
    printf("CRU->LOCAL_RST_1:   0x%lx\n", RV32_CRU->LOCAL_RST_1);
    printf("CRU->RST_MASK:      0x%lx\n", RV32_CRU->RST_MASK);
    printf("CRU->WAIT01:        0x%lx\n", RV32_CRU->WAIT01);
    printf("CRU->WAIT23:        0x%lx\n", RV32_CRU->WAIT23);
    printf("CRU->WAITLP:        0x%lx\n", RV32_CRU->WAITLP);
    printf("CRU->PLL_CONF:      0x%lx\n", RV32_CRU->PLL_CONF);
    printf("CRU->PLL_CONF_REAL: 0x%lx\n", RV32_CRU->PLL_CONF_REAL);
    printf("CRU->PLL_LOCK:      0x%lx\n", RV32_CRU->PLL_LOCK);
    printf("CRU->CLK_STOP_0:    0x%lx\n", RV32_CRU->CLK_STOP_0);
    printf("CRU->CLK_STOP_1:    0x%lx\n", RV32_CRU->CLK_STOP_1);
    printf("CRU->PAD_CTL_0:     0x%lx\n", RV32_CRU->PAD_CTL_0);
    printf("CRU->PAD_CTL_1:     0x%lx\n", RV32_CRU->PAD_CTL_1);
    printf("CRU->PAD_CTL_2:     0x%lx\n", RV32_CRU->PAD_CTL_2);
    printf("CRU->PAD_CTL_3:     0x%lx\n", RV32_CRU->PAD_CTL_3);
    printf("CRU->PAD_CTL_4:     0x%lx\n", RV32_CRU->PAD_CTL_4);
    printf("CRU->PAD_CTL_5:     0x%lx\n", RV32_CRU->PAD_CTL_5);
    printf("CRU->DMA0_SEL_0:    0x%lx\n", RV32_CRU->DMA0_SEL_0);
    printf("CRU->DMA0_SEL_1:    0x%lx\n", RV32_CRU->DMA0_SEL_1);
    printf("CRU->DMA1_SEL_0:    0x%lx\n", RV32_CRU->DMA1_SEL_0);
    printf("CRU->DMA1_SEL_1:    0x%lx\n", RV32_CRU->DMA1_SEL_1);
    printf("CRU->GMU_CTL:       0x%lx\n", RV32_CRU->GMU_CTL);
    printf("CRU->DM_STATUS:     0x%lx\n", RV32_CRU->DM_STATUS);
    printf("cru_regs_probe end.\n");
}

static void can_regs_probe(void)
{
    printf("can_regs_probe start.\n");
    // CAN0

    // CAN1

    printf("can_regs_probe end.\n");
}

static void flashcache_regs_probe(void)
{
    printf("flashcache_regs_probe start.\n");
    printf("FLASHCACHE_CTRL->CCR:       0x%lx\n", RV32_FLASHCACHE_CTRL->CCR);
    printf("FLASHCACHE_CTRL->SR:        0x%lx\n", RV32_FLASHCACHE_CTRL->SR);
    printf("FLASHCACHE_CTRL->IRQMASK:   0x%lx\n", RV32_FLASHCACHE_CTRL->IRQMASK);
    printf("FLASHCACHE_CTRL->IRQSTAT:   0x%lx\n", RV32_FLASHCACHE_CTRL->IRQSTAT);
    printf("FLASHCACHE_CTRL->HWPARAMS:  0x%lx\n", RV32_FLASHCACHE_CTRL->HWPARAMS);
    printf("FLASHCACHE_CTRL->CSHR:      0x%lx\n", RV32_FLASHCACHE_CTRL->CSHR);
    printf("FLASHCACHE_CTRL->CSMR:      0x%lx\n", RV32_FLASHCACHE_CTRL->CSMR);
    printf("FLASHCACHE_CTRL->PIDR4:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR4);
    printf("FLASHCACHE_CTRL->PIDR5:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR5);
    printf("FLASHCACHE_CTRL->PIDR6:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR6);
    printf("FLASHCACHE_CTRL->PIDR7:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR7);
    printf("FLASHCACHE_CTRL->PIDR0:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR0);
    printf("FLASHCACHE_CTRL->PIDR1:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR1);
    printf("FLASHCACHE_CTRL->PIDR2:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR2);
    printf("FLASHCACHE_CTRL->PIDR3:     0x%lx\n", RV32_FLASHCACHE_CTRL->PIDR3);
    printf("FLASHCACHE_CTRL->CIDR0:     0x%lx\n", RV32_FLASHCACHE_CTRL->CIDR0);
    printf("FLASHCACHE_CTRL->CIDR1:     0x%lx\n", RV32_FLASHCACHE_CTRL->CIDR1);
    printf("FLASHCACHE_CTRL->CIDR2:     0x%lx\n", RV32_FLASHCACHE_CTRL->CIDR2);
    printf("FLASHCACHE_CTRL->CIDR3:     0x%lx\n", RV32_FLASHCACHE_CTRL->CIDR3);
    printf("flashcache_regs_probe end.\n");
}

static void i2smaster_regs_probe(void)
{
    printf("i2smaster_regs_probe start.\n");
    // I2S0

    // I2S1

    printf("i2smaster_regs_probe end.\n");
}

static void i2sslave_regs_probe(void)
{
    printf("i2sslave_regs_probe start.\n");
    printf("i2sslave_regs_probe end.\n");
}

static void spiflash_regs_probe(void)
{
    printf("spiflash_regs_probe start.\n");
    printf("spiflash_regs_probe end.\n");
}

static void trng_regs_probe(void)
{
    printf("trng_regs_probe start.\n");
    printf("TRNG->IMR:                  0x%lx\n", RV32_TRNG0->IMR);
    printf("TRNG->ISR:                  0x%lx\n", RV32_TRNG0->ISR);
    printf("TRNG->ICR:                  0x%lx\n", RV32_TRNG0->ICR);
    printf("TRNG->CONFIG:               0x%lx\n", RV32_TRNG0->CONFIG);
    printf("TRNG->VALID:                0x%lx\n", RV32_TRNG0->VALID);
    printf("TRNG->EHR_DATA[0]:          0x%lx\n", RV32_TRNG0->EHR_DATA[0]);
    printf("TRNG->EHR_DATA[1]:          0x%lx\n", RV32_TRNG0->EHR_DATA[1]);
    printf("TRNG->EHR_DATA[2]:          0x%lx\n", RV32_TRNG0->EHR_DATA[2]);
    printf("TRNG->EHR_DATA[3]:          0x%lx\n", RV32_TRNG0->EHR_DATA[3]);
    printf("TRNG->EHR_DATA[4]:          0x%lx\n", RV32_TRNG0->EHR_DATA[4]);
    printf("TRNG->EHR_DATA[5]:          0x%lx\n", RV32_TRNG0->EHR_DATA[5]);
    printf("TRNG->RND_SOURCE_ENABLE:    0x%lx\n", RV32_TRNG0->RND_SOURCE_ENABLE);
    printf("TRNG->SAMPLE_CNT1:          0x%lx\n", RV32_TRNG0->SAMPLE_CNT1);
    printf("TRNG->AUTOCORR_STATISTIC:   0x%lx\n", RV32_TRNG0->AUTOCORR_STATISTIC);
    printf("TRNG->DEBUG_CONTROL:        0x%lx\n", RV32_TRNG0->DEBUG_CONTROL);
    printf("TRNG->SW_RESET:             0x%lx\n", RV32_TRNG0->SW_RESET);
    printf("TRNG->BUSY:                 0x%lx\n", RV32_TRNG0->BUSY);
    printf("TRNG->RST_BITS_COUNTER:     0x%lx\n", RV32_TRNG0->RST_BITS_COUNTER);
    printf("TRNG->RST_BIST_COUNTER[0]:  0x%lx\n", RV32_TRNG0->RST_BIST_COUNTER[0]);
    printf("TRNG->RST_BIST_COUNTER[1]:  0x%lx\n", RV32_TRNG0->RST_BIST_COUNTER[1]);
    printf("TRNG->RST_BIST_COUNTER[2]:  0x%lx\n", RV32_TRNG0->RST_BIST_COUNTER[2]);
    printf("trng_regs_probe end.\n");
}

static void usb_regs_probe(void)
{
    printf("usb_regs_probe start.\n");
    printf("usb_regs_probe end.\n");
}

void regs_probe (void)
{
    //uart_regs_probe();
    //i2c_regs_probe();
    //gpio_regs_probe();
    //dma_regs_probe();
    spi_regs_probe();
    //wdt_regs_probe();
    //timer_regs_probe();
    //cru_regs_probe();
    //mac_regs_probe();
    //can_regs_probe();
    //flashcache_regs_probe();
    //i2smaster_regs_probe();
    //i2sslave_regs_probe();
    spiflash_regs_probe();
    //trng_regs_probe();
    //usb_regs_probe();
}
