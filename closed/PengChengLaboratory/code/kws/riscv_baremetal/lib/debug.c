#include <string.h>
#include <stdio.h>
#include <debug.h>
#include <riscv.h>
#include <system.h>
#include <platform.h>

void probe_csrs(void)
{
	printf("MSTATUS: 0x%lx\n", csr_read(RV_CSR_MSTATUS));
	printf("MTVEC: 0x%lx\n", csr_read(RV_CSR_MTVEC));
	printf("MEPC: 0x%lx\n", csr_read(RV_CSR_MEPC));
	printf("MCAUSE: 0x%lx\n", csr_read(RV_CSR_MCAUSE));
}

void event_unit_test(void)
{
	RV32_IC->ISP = 1U << 7;
	RV32_IC->ESP = 1U << 7;
}

void systick_test(void)
{
	int i;
	printf("system_ticks: %ld\n", get_systicks());
	for (i = 0; i < 48000; i++) {};
	printf("system_ticks: %ld\n", get_systicks());
}

