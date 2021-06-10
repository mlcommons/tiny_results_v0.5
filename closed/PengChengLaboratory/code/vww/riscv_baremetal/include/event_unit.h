#ifndef __event_unit_h__
#define __event_unit_h__
#include <stdint.h>

typedef struct rv32_ic {
	volatile uint32_t IER;
	volatile uint32_t IPR;
	volatile uint32_t ISP;
	volatile uint32_t ICP;
	volatile uint32_t EER;
	volatile uint32_t EPR;
	volatile uint32_t ESP;
	volatile uint32_t ECP;
	volatile uint32_t SCR;
	volatile uint32_t SSR;
} rv32_ic_t;

#ifdef __cplusplus
extern "C" {
#endif

void eu_interrupt_enable(uint32_t irq);
void eu_interrupt_disable(uint32_t irq);
uint32_t eu_interrupt_get_pending(uint32_t irq);
void eu_interrupt_set_pending(uint32_t irq);
void eu_interrupt_clear_pending(uint32_t irq);

void eu_event_enable(uint32_t irq);
void eu_event_disable(uint32_t irq);
uint32_t eu_event_get_pending(uint32_t irq);
void eu_event_set_pending(uint32_t irq);
void eu_event_clear_pending(uint32_t irq);
#ifdef __cplusplus
}
#endif

#endif
