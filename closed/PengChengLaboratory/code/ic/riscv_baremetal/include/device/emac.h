#ifndef __emac_h__
#define __emac_h__
#include <device.h>

typedef struct rv32_emac {
    volatile uint32_t MACCR;
    volatile uint32_t MACFFR;
    volatile uint32_t MACHTHR;
    volatile uint32_t MACHTLR;
    volatile uint32_t MACMIIAR;
    volatile uint32_t MACMIIDR;
    volatile uint32_t MACFCR;
    volatile uint32_t MACVLANTR;
    volatile uint32_t RESERVED0[2];
    volatile uint32_t MACRWUFFR;
    volatile uint32_t MACPMTCSR;
    volatile uint32_t RESERVED1;
    volatile uint32_t MACDBGR;
    volatile uint32_t MACSR;
    volatile uint32_t MACIMR;
    volatile uint32_t MACA0HR;
    volatile uint32_t MACA0LR;
    volatile uint32_t MACA1HR;
    volatile uint32_t MACA1LR;
    volatile uint32_t RESERVED2[44];
    volatile uint32_t MMCCR;
    volatile uint32_t MMCRIR;
    volatile uint32_t MMCTIR;
    volatile uint32_t MMCRIMR;
    volatile uint32_t MMCTIMR;
    volatile uint32_t RESERVED3[14];
    volatile uint32_t MMCTGFSCCR;
    volatile uint32_t MMCTGFMSCCR;
    volatile uint32_t RESERVED4[5];
    volatile uint32_t MMCTGFCR;
    volatile uint32_t RESERVED5[10];
    volatile uint32_t MMCRFCECR;
    volatile uint32_t MMCRFAECR;
    volatile uint32_t RESERVED6[10];
    volatile uint32_t MMCRGUFCR;
    volatile uint32_t RESERVED7[334];
    volatile uint32_t PTPTSCR;
    volatile uint32_t PTPSSIR;
    volatile uint32_t PTPTSHR;
    volatile uint32_t PTPTSLR;
    volatile uint32_t PTPTSHUR;
    volatile uint32_t PTPTSLUR;
    volatile uint32_t PTPTSAR;
    volatile uint32_t PTPTTHR;
    volatile uint32_t PTPTTLR;
    volatile uint32_t RESERVED8;
    volatile uint32_t PTPTSSR;
    volatile uint32_t RESERVED9[565];
    volatile uint32_t DMABMR;
    volatile uint32_t DMATPDR;
    volatile uint32_t DMARPDR;
    volatile uint32_t DMARDLAR;
    volatile uint32_t DMATDLAR;
    volatile uint32_t DMASR;
    volatile uint32_t DMAOMR;
    volatile uint32_t DMAIER;
    volatile uint32_t DMAMFBOCR;
    volatile uint32_t DMARSWTR;
    volatile uint32_t RESERVED10[8];
    volatile uint32_t DMACHTDR;
    volatile uint32_t DMACHRDR;
    volatile uint32_t DMACHTBAR;
    volatile uint32_t DMACHRBAR;
} rv32_emac_t;

#endif
