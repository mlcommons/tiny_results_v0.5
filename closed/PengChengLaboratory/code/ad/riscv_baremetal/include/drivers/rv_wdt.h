#ifndef __rv_wdt_h__
#define __rv_wdt_h__
#include <wdt.h>

typedef void (*wdt_signalevent_t) (void);

void wdt_init(uint32_t);
void wdt_restart(void);
void wdt_enable_interrupt(void);
void wdt_disable_interrupt(void);
void wdt_clear_interrupt(void);
void wdt_enable_reset(void);
void wdt_disable_reset(void);
void wdt_lock(void);
void wdt_unlock(void);
uint32_t wdt_intstatus(void);
void wdt_set_irq_callback(wdt_signalevent_t);

#endif
