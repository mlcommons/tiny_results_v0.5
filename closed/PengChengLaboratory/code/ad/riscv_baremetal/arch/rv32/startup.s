        .section .text.init,"ax",@progbits
        .globl _head
        .type _head,@function

_head:
        .cfi_startproc
        .cfi_undefined ra
        /* Setup global pointer */
.option push
.option norelax
        la gp, __global_pointer$
.option pop

        /* Load text section */
        la a0, _sitext
        la a1, _stext
        la a2, _etext
        bgeu a1, a2, copy_text_done /* branch if a1 >= a2 */
copy_text:
        lw t0, (a0)
        sw t0, (a1)
        addi a0, a0, 4
        addi a1, a1, 4
        bltu a1, a2, copy_text      /* branch if a1 < a2 */
copy_text_done:

        call _start
        .cfi_endproc

        .section .text,"ax",@progbits
        .globl _start
        .type _start,@function

_start:
        .cfi_startproc
        .cfi_undefined ra

		/*enable fp
		*/
		csrr   t0, mstatus
		li     t1, 0x00003000
		or     t0, t0, t1
		csrw   mstatus, t0

        /* Load rodata section */
        la a0, _sirodata
        la a1, _srodata
        la a2, _erodata
        /* We will load an extra 4B data following the .rodata,
         * which is .sdata2._global_impure_ptr inserted by the
         * toolchain.
         */
        bgtu a1, a2, copy_rodata_done   /* branch if a1 > a2 */
copy_rodata:
        lw t0, (a0)
        sw t0, (a1)
        addi a0, a0, 4
        addi a1, a1, 4
        bleu a1, a2, copy_rodata        /* branch if a1 <= a2 */
copy_rodata_done:

        /* Load data section */
        la a0, _sidata
        la a1, _sdata
        la a2, _edata
        bgeu a1, a2, copy_data_done /* branch if a1 >= a2 */
copy_data:
        lw t0, (a0)
        sw t0, (a1)
        addi a0, a0, 4
        addi a1, a1, 4
        bltu a1, a2, copy_data      /* branch if a1 < a2 */
copy_data_done:

        /* Clear bss section */
        la a0, _sbss
        la a1, _ebss
        bgeu a0, a1, clear_bss_done
clear_bss:
        sw zero, (a0)
        addi a0, a0, 4
        bltu a0, a1, clear_bss
clear_bss_done:



        /* Setup stack pointer */
        la sp, _estack

        /* Setup default trap vector */
        la t0, trap_vector
        csrw mtvec, t0

        /* Call the system initialization function */
        call system_init
		/*bacon add*/
		call __libc_init_array
        /* Enter main() */
        call main
        tail exit

        /* Infinite Loop */
park:
        wfi
        j park

        .cfi_endproc

	.macro SAVE_ALL
        addi sp, sp, -64
        sw ra, (0*4)(sp)
        sw a0, (1*4)(sp)
        sw a1, (2*4)(sp)
        sw a2, (3*4)(sp)
        sw a3, (4*4)(sp)
        sw a4, (5*4)(sp)
        sw a5, (6*4)(sp)
        sw a6, (7*4)(sp)
        sw a7, (8*4)(sp)
        sw t0, (9*4)(sp)
        sw t1, (10*4)(sp)
        sw t2, (11*4)(sp)
        sw t3, (12*4)(sp)
        sw t4, (13*4)(sp)
        sw t5, (14*4)(sp)
        sw t6, (15*4)(sp)
	.endm

	.macro RESTORE_ALL
        lw ra, (0*4)(sp)
        lw a0, (1*4)(sp)
        lw a1, (2*4)(sp)
        lw a2, (3*4)(sp)
        lw a3, (4*4)(sp)
        lw a4, (5*4)(sp)
        lw a5, (6*4)(sp)
        lw a6, (7*4)(sp)
        lw a7, (8*4)(sp)
        lw t0, (9*4)(sp)
        lw t1, (10*4)(sp)
        lw t2, (11*4)(sp)
        lw t3, (12*4)(sp)
        lw t4, (13*4)(sp)
        lw t5, (14*4)(sp)
        lw t6, (15*4)(sp)
        addi sp, sp, 64
	.endm

	.macro irq_wrapper name irq_handler
	.globl \name
\name:
        # Save registers
	SAVE_ALL

        # Invoke the handler
        mv a0, sp
        csrr a1, mcause
        csrr a2, mepc
        jal \irq_handler

        # Restore registers
	RESTORE_ALL
	mret
	.endm


irq_wrapper exception_handler   trap_handler
irq_wrapper dmac0_irq_handler   dma0_handler
irq_wrapper iis11_irq_handler   trap_handler
irq_wrapper iis10_irq_handler   trap_handler
irq_wrapper ic9_irq_handler     I2C1_IRQHandler
irq_wrapper ic8_irq_handler     I2C0_IRQHandler
irq_wrapper wdog_irq_handler    wdt_handler 
irq_wrapper systick_irq_handler systick_handler
irq_wrapper ssp0_irq_handler    SSP0_IRQHandler
irq_wrapper timer4_irq_handler  timer4_handler
irq_wrapper timer3_irq_handler  timer3_handler
irq_wrapper timer2_irq_handler  timer2_handler
irq_wrapper timer1_irq_handler  timer1_handler
irq_wrapper timer0_irq_handler  timer0_handler
irq_wrapper ssp1_irq_handler    SSP1_IRQHandler
irq_wrapper uart8_irq_handler   UART3_IRQHandler
irq_wrapper uart7_irq_handler   UART2_IRQHandler
irq_wrapper uart6_irq_handler   UART1_IRQHandler
irq_wrapper uart5_irq_handler   UART0_IRQHandler 
irq_wrapper trng_irq_handler    trap_handler
irq_wrapper ictl_irq_handler    trap_handler
irq_wrapper mac_irq_handler     trap_handler
irq_wrapper i2s_irq_handler     trap_handler
irq_wrapper ssp12_irq_handler   SSP2_IRQHandler
irq_wrapper gpio3_irq_handler   gpio3_handler
irq_wrapper gpio2_irq_handler   gpio2_handler
irq_wrapper gpio1_irq_handler   gpio1_handler
irq_wrapper gpio0_irq_handler   gpio0_handler
irq_wrapper dmac1_irq_handler   dma1_handler
irq_wrapper fcu_irq_handler     trap_handler
irq_wrapper can13_irq_handler   trap_handler
irq_wrapper can12_irq_handler   trap_handler

        .align 8
trap_vector:
	.option norvc
	/* Interrupts */
	j exception_handler	/* IRQ 0 & Exception */
	j dmac0_irq_handler	/* IRQ 1 */
	j iis11_irq_handler	/* IRQ 2 */
	j iis10_irq_handler	/* IRQ 3 */
	j ic9_irq_handler	/* IRQ 4 */
	j ic8_irq_handler	/* IRQ 5 */
	j wdog_irq_handler	/* IRQ 6 */
	j systick_irq_handler	/* IRQ 7 */
    j ssp0_irq_handler      /* IRQ 8 */
	j timer4_irq_handler	/* IRQ 9 */
	j timer3_irq_handler	/* IRQ 10 */
	j timer2_irq_handler	/* IRQ 11 */
	j timer1_irq_handler	/* IRQ 12 */
	j timer0_irq_handler	/* IRQ 13 */
    j ssp1_irq_handler  /* IRQ 14 */
	j uart8_irq_handler	/* IRQ 15 */
	j uart7_irq_handler	/* IRQ 16 */
	j uart6_irq_handler	/* IRQ 17 */
	j uart5_irq_handler	/* IRQ 18 */
	j trng_irq_handler	/* IRQ 19 */
    j ictl_irq_handler  /* IRQ 20 */
	j mac_irq_handler	/* IRQ 21 */
	j i2s_irq_handler	/* IRQ 22 */
    j ssp12_irq_handler /* IRQ 23 */
	j gpio3_irq_handler	/* IRQ 24 */
	j gpio2_irq_handler	/* IRQ 25 */
	j gpio1_irq_handler	/* IRQ 26 */
	j gpio0_irq_handler	/* IRQ 27 */
	j dmac1_irq_handler	/* IRQ 28 */
	j fcu_irq_handler	/* IRQ 29 */
	j can13_irq_handler	/* IRQ 30 */
	j can12_irq_handler	/* IRQ 31 */

