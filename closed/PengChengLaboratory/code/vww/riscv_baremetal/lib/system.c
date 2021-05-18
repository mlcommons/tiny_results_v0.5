#include <string.h>
#include <stdio.h>
#include <system.h>
#include <riscv.h>
#include <platform.h>
#include <rv_uart.h>

#define STDIO_BAUDRATE 115200
#define HZ 1000

DRIVER_USART *UART_Console = &driver_uart1;

volatile uint32_t system_ticks = 0x0UL;

static uint32_t stdio_initialized = 0U;

int stdio_init(void)
{
	int32_t status;

	if (UART_Console == NULL)
		return 0;

	status = UART_Console->Initialize(NULL);
	if (status != DRIVER_OK)
		return -1;

	status = UART_Console->PowerControl(POWER_FULL);
	if (status != DRIVER_OK)
		return -1;

	status = UART_Console->Control(USART_DATA_BITS_8	|
				       USART_PARITY_NONE	|
				       USART_STOP_BITS_1	|
				       USART_FLOW_CONTROL_NONE,
				       STDIO_BAUDRATE);
	if (status != DRIVER_OK)
		return -1;

    stdio_initialized = 1U;

	return 0;
}

int stdio_getchar(void)
{
    return (0);
}

int stdio_putchar(int ch)
{
    uint8_t buf[2], count;

    if (UART_Console == NULL)
        return (ch & 0xff);

    if (!stdio_initialized) {
        stdio_init();
    }

    if (ch == '\n') {
        buf[0] = '\r';
        buf[1] = '\n';
        count = 2U;
    } else {
        buf[0] = ch;
        count = 1U;
    }

	while (UART_Console->Send(buf, count) != DRIVER_OK);

	return (ch & 0xff);
}

void trap_init(void)
{
	uint32_t mstatus;

	mstatus = RV_MSTATUS_MIE;
	csr_write(RV_CSR_MSTATUS, mstatus);
}

uint32_t get_system_clocks(void)
{
	return (180000000UL);
}

/*
 * System Tick Configuration.
 * Initializes the System Timer and its interrupt, and starts the System Tick Timer.
 *
 *   - IN: ticks Number of ticks between two interrupts.
 */
static uint32_t systick_config(uint32_t ticks)
{
	RV32_SYSTICK_TIMER->RELOAD = (uint32_t)(ticks - 1UL);
	RV32_SYSTICK_TIMER->VAL = 0UL;
	RV32_SYSTICK_TIMER->CTRL = 0x9;
    eu_interrupt_enable(RV32_SYSTICK_IRQn);

	return (0UL);
}

static void pad_config(void)
{
    // REG_PAD_CTL_*
    // SPI0
    // RV32_CRU->PAD_CTL_0 = 0
    // SPI1
    // RV32_CRU->PAD_CTL_1 = 0
    // SPI2
    // RV32_CRU->PAD_CTL_2 = 0
    // SPI3
    // RV32_CRU->PAD_CTL_3 = 0
    // SPI4
    // RV32_CRU->PAD_CTL_4 = 0
    // SPI5
    // RV32_CRU->PAD_CTL_5 = 0
}

static void pll_config(void)
{
    int M, N, OD;
    int nClk_in, nClk_out;

    // Set REG_PLL_CONF. After soft reset, REG_PLL_CONF will be
    // writen into REG_PLL_CONF_REAL by hardware.
    //
    // REG_PLL_CONF = M + (N << 8) + (OD << 16)
    //   M = M7*128 + M6*64 + M5*32 + M4*16 + M3*8 + M2*4 + M1*2 + M0*1
    //   N = N3*8 + N2*4 + N1*2 + N0*1
    //   XIN = reference clock (50MHz)
    //   NO = 2 ^ (OD0 + 2*OD1)
    //   CLK_OUT = XIN * (M / N) * (1 / NO)
    M = 14;
    N = 1;
    OD = 1;

    RV32_CRU->PLL_CONF = ((M << CRU_PLL_CONF_M_Pos) & CRU_PLL_CONF_M_Msk) |
                         ((N << CRU_PLL_CONF_N_Pos) & CRU_PLL_CONF_N_Msk) |
                         ((OD << CRU_PLL_CONF_OD_Pos) & CRU_PLL_CONF_OD_Msk);

    printf("PLL CONF REG set done, M=%d, N=%d, OD=%d\n", M, N, OD);

    nClk_in = 48;
    nClk_out = (nClk_in * M / N) >> OD;

    printf("CPU current is running at %d MHz!\n", nClk_out);
}

void cru_init(void)
{
    uint32_t rst_src = RV32_CRU->RESET_SOURCE & CRU_RESET_SOURCE_Msk;

    switch (rst_src) {
    case CRU_RESET_SOURCE_COLD:
        printf("Boot from cold reset.\n");
        pad_config();
        pll_config();
        __asm__ __volatile__ ("fence");
        RV32_CRU->SOFT_RESET = 0x1;
        // unreachable
        goto unreach;
    case CRU_RESET_SOURCE_SOFT:
        printf("Boot from soft reset.\n");
        break;
    case CRU_RESET_SOURCE_LOCAL:
        printf("Boot from local reset.\n");
        break;
    case CRU_RESET_SOURCE_WDT:
        printf("Boot from watchdog reset.\n");
        break;
    default:
        // unreachable
        goto unreach;
    }

    return;
unreach:
    while (1) {};
}

void system_init(void)
{
	stdio_init();
    cru_init();
	trap_init();
	systick_config(get_system_clocks() / HZ); // interrupt per ms
}

void systick_handler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_SYSTICK_IRQn);
    eu_interrupt_clear_pending(RV32_SYSTICK_IRQn);
	RV32_SYSTICK_TIMER->IC = 0x1;
	system_ticks++;
    eu_interrupt_enable(RV32_SYSTICK_IRQn);
}

uint32_t get_systicks(void)
{
	return system_ticks;
}
