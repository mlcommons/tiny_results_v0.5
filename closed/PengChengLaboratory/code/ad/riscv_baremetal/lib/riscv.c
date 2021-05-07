#include <stdio.h>
#include <riscv.h>

#include <platform.h>

void trap_handler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
	if (mcause & 0x80000000) {	// Interrupt
		printf("Currently unsupport interrupt: 0x%lx\n", (mcause & 0x80000000));
	} else {		// Exception
		switch (mcause) {
		case  0: // Instruction address misaligned
			printf("Exception - Instruction address misaligned: mepc=0x%lx\n", mepc);
			break;
		case  1: // Instruction access fault
			printf("Exception - Instruction access fault: mepc=0x%lx\n", mepc);
			break;
		case  2: // Illegal instruction
			printf("Exception - Illegal instruction: mepc=0x%lx\n", mepc);
			break;
		case  3: // Breakpoint
			printf("Exception - Breakpoint: mepc=0x%lx\n", mepc);
			break;
		case  4: // Load address misaligned
			printf("Exception - Load address misaligned: mepc=0x%lx\n", mepc);
			break;
		case  5: // Load address fault
			printf("Exception - Load address fault: mepc=0x%lx\n", mepc);
			break;
		case  6: // Store/AMO address misaligned
			printf("Exception - Store/AMO address misaligned: mepc=0x%lx\n", mepc);
			break;
		case  7: // Store/AMO access fault
			printf("Exception - Store/AMO access fault: mepc=0x%lx\n", mepc);
			break;
		case  8: // Environment call from U-mode
			printf("Exception - Environment call from U-mode: mepc=0x%lx\n", mepc);
			break;
		case  9: // Environment call from S-mode
			printf("Exception - Environment call from S-mode: mepc=0x%lx\n", mepc);
			break;
		case 11: // Environment call from M-mode
			printf("Exception - Environment call from M-mode: mepc=0x%lx\n", mepc);
			break;
		case 12: // Instruction page fault
			printf("Exception - Instruction page fault: mepc=0x%lx\n", mepc);
			break;
		case 13: // Load page fault
			printf("Exception - Load page fault: mepc=0x%lx\n", mepc);
			break;
		case 15: // Store/AMO page fault
			printf("Exception - Store/AMO page fault: mepc=0x%lx\n", mepc);
			break;
		default:
			printf("Unknown exception: mcause=0x%lx, mepc=0x%lx\n", mcause, mepc);
			break;
		}
	}
}

