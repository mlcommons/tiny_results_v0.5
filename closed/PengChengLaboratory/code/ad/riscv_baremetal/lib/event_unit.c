#include <platform.h>

void eu_interrupt_enable(uint32_t irq)
{
    if (irq < SECONDARY_BASE) {
        RV32_IC->IER |= (1U << irq);
    } else if (irq <= RV32_USB_SECIRQn) {
        RV32_IC->IER |= (1U << RV32_ICTL_IRQn);
        // TODO: Call secondary irq enable function
    }
}

void eu_interrupt_disable(uint32_t irq)
{
    if (irq < SECONDARY_BASE) {
        RV32_IC->IER &= ~(1U << irq);
    } else if (irq <= RV32_USB_SECIRQn) {
        RV32_IC->IER &= ~(1U << RV32_ICTL_IRQn);
        // TODO: Call secondary irq enable function
    }
}

uint32_t eu_interrupt_get_pending(uint32_t irq)
{
    if (irq < SECONDARY_BASE) {
        return (RV32_IC->IPR >> irq) & 0x1;
    } else if (irq <= RV32_USB_SECIRQn) {
        // TODO: Call secondary irq pending get function
        return 0;
    }
    return 0;
}

void eu_interrupt_set_pending(uint32_t irq)
{
    if (irq < SECONDARY_BASE) {
        RV32_IC->ISP |= (1U << irq);
    } else if (irq <= RV32_USB_SECIRQn) {
        // TODO: sec irq stuff
        RV32_IC->ISP |= (1U << RV32_ICTL_IRQn);
    }
}

void eu_interrupt_clear_pending(uint32_t irq)
{
    if (irq < SECONDARY_BASE) {
        RV32_IC->ICP |= (1U << irq);
    } else if (irq <= RV32_USB_SECIRQn) {
        // TODO: sec irq stuff
        RV32_IC->ICP |= (1U << RV32_ICTL_IRQn);
    }
}

void eu_event_enable(uint32_t evt)
{
    if (evt < 32)
        RV32_IC->EER |= (1U << evt);
}

void eu_event_disable(uint32_t evt)
{
    if (evt < 32)
        RV32_IC->EER &= ~(1U << evt);
}

uint32_t eu_event_get_pending(uint32_t evt)
{
    if (evt < 32)
        return (RV32_IC->EPR >> evt) & 0x1;
    return 0;
}

void eu_event_set_pending(uint32_t evt)
{
    if (evt < 32)
        RV32_IC->ESP |= (1U << evt);
}

void eu_event_clear_pending(uint32_t evt)
{
    if (evt < 32)
        RV32_IC->ECP |= (1U << evt);
}

