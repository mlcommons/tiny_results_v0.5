#ifndef __ictl_h__
#define __ictl_h__
#include <stdint.h>

typedef struct rv32_ictl {
    volatile uint32_t irq_inten_l;          // 0x00
    volatile uint32_t irq_inten_h;          // 0x04
    volatile uint32_t irq_intmask_l;        // 0x08
    volatile uint32_t irq_intmask_h;        // 0x0c
    volatile uint32_t irq_intforce_l;       // 0x10
    volatile uint32_t irq_intforce_h;       // 0x14
    volatile uint32_t irq_rawstatus_l;      // 0x18
    volatile uint32_t irq_rawstatus_h;      // 0x1c
    volatile uint32_t irq_status_l;         // 0x20
    volatile uint32_t irq_status_h;         // 0x24
    volatile uint32_t irq_maskstatus_l;     // 0x28
    volatile uint32_t irq_maskstatus_h;     // 0x2c
    volatile uint32_t irq_finalstatus_l;    // 0x30
    volatile uint32_t irq_finalstatus_h;    // 0x34
    volatile uint32_t irq_vector;           // 0x38
    volatile uint32_t res0;                 // 0x3c
    volatile uint32_t irq_vector_0;         // 0x40
    volatile uint32_t res1;                 // 0x44
    volatile uint32_t irq_vector_1;         // 0x48
    volatile uint32_t res2;                 // 0x4c
    volatile uint32_t irq_vector_2;         // 0x50
    volatile uint32_t res3;                 // 0x54
    volatile uint32_t irq_vector_3;         // 0x58
    volatile uint32_t res4;                 // 0x5c
    volatile uint32_t irq_vector_4;         // 0x60
    volatile uint32_t res5;                 // 0x64
    volatile uint32_t irq_vector_5;         // 0x68
    volatile uint32_t res6;                 // 0x6c
    volatile uint32_t irq_vector_6;         // 0x70
    volatile uint32_t res7;                 // 0x74
    volatile uint32_t irq_vector_7;         // 0x78
    volatile uint32_t res8;                 // 0x7c
    volatile uint32_t irq_vector_8;         // 0x80
    volatile uint32_t res9;                 // 0x84
    volatile uint32_t irq_vector_9;         // 0x88
    volatile uint32_t res10;                // 0x8c
    volatile uint32_t irq_vector_10;        // 0x90
    volatile uint32_t res11;                // 0x94
    volatile uint32_t irq_vector_11;        // 0x98
    volatile uint32_t res12;                // 0x9c
    volatile uint32_t irq_vector_12;        // 0xa0
    volatile uint32_t res13;                // 0xa4
    volatile uint32_t irq_vector_13;        // 0xa8
    volatile uint32_t res14;                // 0xac
    volatile uint32_t irq_vector_14;        // 0xb0
    volatile uint32_t res15;                // 0xb4
    volatile uint32_t irq_vector_15;        // 0xb8
    volatile uint32_t res16;                // 0xbc
    volatile uint32_t fiq_inten;            // 0xc0
    volatile uint32_t fiq_intmask;          // 0xc4
    volatile uint32_t fiq_intforce;         // 0xc8
    volatile uint32_t fiq_rawstatus;        // 0xcc
    volatile uint32_t fiq_status;           // 0xd0
    volatile uint32_t fiq_finalstatus;      // 0xd4
    volatile uint32_t irq_plevel;           // 0xd8
    volatile uint32_t res17;                // 0xdc
    volatile uint32_t comp_version;         // 0xe0
    volatile uint32_t res18;                // 0xe4
    volatile uint32_t irq_pr[64];           // 0xe8+N*4
    volatile uint32_t irq_vector_default;   // 0x1e8
    volatile uint32_t res19;                // 0x1ec
} rv32_ictl_t;

#endif
