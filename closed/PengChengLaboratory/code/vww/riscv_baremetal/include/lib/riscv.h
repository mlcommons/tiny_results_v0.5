#ifndef __RISCV_H__
#define __RISCV_H__

#include <stdint.h>

/* Machine Information Registers */
#define RV_CSR_MVENDORID	0xf11	// Vendor ID
#define RV_CSR_MARCHID		0xf12	// Architecture ID
#define RV_CSR_MIMPID		0xf13	// Implementation ID
#define RV_CSR_MHARTID		0xf14	// Hardware Thread ID

/* Machine Trap Seteup */
#define RV_CSR_MSTATUS		0x300	// Machine Status
#define RV_CSR_MISA		0x301	// ISA and extensions
#define RV_CSR_MEDELEG		0x302	// Machine exception delegation register
#define RV_CSR_MIDELEG		0x303	// Machine interrupt delegation register
#define RV_CSR_MIE		0x304	// Machine interrupt-enable register
#define RV_CSR_MTVEC		0x305	// Machine Trap-Vector Base Address
#define RV_CSR_MCOUNTEREN	0x306	// Machine counter enable

/* Machine Trap Handling */
#define RV_CSR_MSCRATCH		0x340	// Scratch register for machine trap handlers
#define RV_CSR_MEPC		0x341	// Machine Exception Program Counter
#define RV_CSR_MCAUSE		0x342	// Machine Trap Cause
#define RV_CSR_MTVAL		0x343	// Machine bad address or instruction
#define RV_CSR_MIP		0x344	// Machine interrupt pending

/* Machine Counter/Timers */
#define RV_CSR_MCYCLE		0xb00
#define RV_CSR_MCYCLEH		0xb80

/* Debug Mode Registers */
#define RV_CSR_DCSR		0x7b0	// Debug Control and Status
#define RV_CSR_DPC		0x7b1	// Debug PC
#define RV_CSR_DSCRATCH		0x7b2	// Debug Scratch Register


/* Machine Status Register Bits*/
#define RV_MSTATUS_UIE		(1U << 0)
#define RV_MSTATUS_SIE		(1U << 1)
#define RV_MSTATUS_MIE		(1U << 3)
#define RV_MSTATUS_UPIE		(1U << 4)
#define RV_MSTATUS_SPIE		(1U << 5)
#define RV_MSTATUS_MPIE		(1U << 7)
#define RV_MSTATUS_SPP		(1U << 8)
#define RV_MSTATUS_MPP		(3U << 11)
#define RV_MSTATUS_FS		(3U << 13)
#define RV_MSTATUS_XS		(3U << 15)
#define RV_MSTATUS_MPRV		(1U << 17)
#define RV_MSTATUS_SUM		(1U << 18)
#define RV_MSTATUS_MXR		(1U << 19)
#define RV_MSTATUS_TVM		(1U << 20)
#define RV_MSTATUS_TW		(1U << 21)
#define RV_MSTATUS_TSR		(1U << 22)

/* Machine Interrupt Register Bits */
#define RV_MIx_USIP		(1U << 0)
#define RV_MIx_SSIP		(1U << 1)
#define RV_MIx_MSIP		(1U << 3)
#define RV_MIx_UTIP		(1U << 4)
#define RV_MIx_STIP		(1U << 5)
#define RV_MIx_MTIP		(1U << 7)
#define RV_MIx_UEIP		(1U << 8)
#define RV_MIx_SEIP		(1U << 9)
#define RV_MIx_MEIP		(1U << 11)

#define __ASM_STR(x) #x

#define csr_swap(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrw %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
})

#define csr_read(csr)						\
({								\
	register unsigned long __v;				\
	__asm__ __volatile__ ("csrr %0, " __ASM_STR(csr)	\
			      : "=r" (__v) :			\
			      : "memory");			\
	__v;							\
})

#define csr_write(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrw " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
})

#define csr_read_set(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrs %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
})

#define csr_set(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrs " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
})

#define csr_read_clear(csr, val)				\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrrc %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
})

#define csr_clear(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrc " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
})


/* Generic IO read/write.  These perform native-endian accesses. */
static inline void raw_writeb(uint8_t val, volatile void *addr)
{
	asm volatile("sb %0, 0(%1)" : : "r" (val), "r" (addr));
}

static inline void raw_writew(uint16_t val, volatile void *addr)
{
	asm volatile("sh %0, 0(%1)" : : "r" (val), "r" (addr));
}

static inline void raw_writel(uint32_t val, volatile void *addr)
{
	asm volatile("sw %0, 0(%1)" : : "r" (val), "r" (addr));
}

#endif /* __RISCV_H__ */
