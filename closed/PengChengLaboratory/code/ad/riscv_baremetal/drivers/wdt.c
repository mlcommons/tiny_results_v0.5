#include <platform.h>
#include <rv_wdt.h>
#include <stddef.h>
#include <stdio.h>

static wdt_signalevent_t wdt_cb_event;

void wdt_init(uint32_t val)
{
    //TODO
    //MISC_Enable_WDT();
    RV32_WDT->LOAD = val;
    wdt_cb_event = NULL;
}

void wdt_restart(void)
{
    RV32_WDT->LOAD = RV32_WDT->LOAD;
}

void wdt_enable_interrupt(void)
{
    eu_interrupt_enable(RV32_WDT_IRQn);
    RV32_WDT->CTRL |= RV32_WDT_CTRL_INTEN_Msk;
}

void wdt_disable_interrupt(void)
{
    eu_interrupt_disable(RV32_WDT_IRQn);
    RV32_WDT->CTRL &= ~RV32_WDT_CTRL_INTEN_Msk;
}

inline void wdt_clear_interrupt(void)
{
    RV32_WDT->IC = 0x1;
}

void wdt_enable_reset(void)
{
    RV32_WDT->CTRL |= (RV32_WDT_CTRL_INTEN_Msk |
                         RV32_WDT_CTRL_RESEN_Msk);
    RV32_CRU->RST_MASK = CRU_RST_MASK_Msk;
}

void wdt_disable_reset(void)
{
    RV32_WDT->CTRL &= ~(RV32_WDT_CTRL_INTEN_Msk |
                          RV32_WDT_CTRL_RESEN_Msk);
    RV32_CRU->RST_MASK = 0;
}

void wdt_lock(void)
{
    RV32_WDT->LOCK = 0x1;
}

void wdt_unlock(void)
{
    RV32_WDT->LOCK = 0x0;
}

uint32_t wdt_intstatus(void)
{
    return RV32_WDT->RIS;
}

void wdt_set_irq_callback(wdt_signalevent_t cb_event)
{
    wdt_cb_event = cb_event;
}

//extern volatile uint32_t wdt_irq_count;

void wdt_handler(uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_WDT_IRQn);
    wdt_clear_interrupt();
    eu_interrupt_clear_pending(RV32_WDT_IRQn);
    //wdt_irq_count++;
    //printf("WDT interrupts! count: %ld\n", wdt_irq_count);
    eu_interrupt_enable(RV32_WDT_IRQn);
}
