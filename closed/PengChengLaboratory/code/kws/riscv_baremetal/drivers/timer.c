#include <stddef.h>
#include <platform.h>
#include <rv_timer.h>

#ifdef RTE_Drivers_TIMER0
static timer_res_t timer0_res = {
    RV32_TIMER0,
    RV32_TIMER0_IRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIME0 */

#ifdef RTE_Drivers_TIMER1
static timer_res_t timer1_res = {
    RV32_TIMER1,
    RV32_TIMER1_IRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIMER1 */

#ifdef RTE_Drivers_TIMER2
static timer_res_t timer2_res = {
    RV32_TIMER2,
    RV32_TIMER2_IRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIMER2 */

#ifdef RTE_Drivers_TIMER3
static timer_res_t timer3_res = {
    RV32_TIMER3,
    RV32_TIMER3_IRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIMER3 */

#ifdef RTE_Drivers_TIMER4
static timer_res_t timer4_res = {
    RV32_TIMER4,
    RV32_TIMER4_IRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIMER4 */

#ifdef RTE_Drivers_TIMER5
static timer_res_t timer5_res = {
    RV32_TIMER5,
    RV32_TIMER5_SECIRQn,
    TIMER_MODE_STOP,
    {
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET,
        CHANNEL_MODE_UNSET
    },
    NULL
};
#endif /* RTE_Drivers_TIMER5 */

static void timer_set_count (uint32_t val, timer_res_t *t)
{
    t->reg->CNT = val & TIMx_CNT_Msk;
}

static uint32_t timer_get_count (timer_res_t *t)
{
    return t->reg->CNT;
}

static void timer_configure(uint32_t val, timer_res_t *t)
{
    switch (val & TIMx_CTRL_MODE_Msk) {
    case 0x0:
        t->tmode = TIMER_MODE_STOP;
        break;
    case 0x1:
        t->tmode = TIMER_MODE_FREERUN;
        break;
    case 0x2:
        t->tmode = TIMER_MODE_MODULO;
        break;
    case 0x3:
        t->tmode = TIMER_MODE_UPDOWN;
        break;
    default:
        break;
    }

    t->reg->CTRL = val;
}

static void timer_set_status(uint32_t val, timer_res_t *t)
{
    t->reg->STAT = val & 0xf;
}

static uint32_t timer_get_status(timer_res_t *t)
{
    return t->reg->STAT;
}

static int timer_chn_config(uint32_t val, uint32_t n, timer_res_t *t)
{
    if (n >= RV32_TIMER_CHN_NUM)
        return -1;

    if (val & TIMx_CCTLx_MODE_Msk)
        t->cmode[n] = CHANNEL_MODE_COMPARE;
    else
        t->cmode[n] = CHANNEL_MODE_CAPTURE;

    switch (n) {
    case 0:
        t->reg->CCTL0 = val;
        break;
    case 1:
        t->reg->CCTL1 = val;
        break;
    case 2:
        t->reg->CCTL2 = val;
        break;
    default:
        return -1;
    }

    return 0;
}

static uint32_t timer_get_ccrx(rv32_timer_ccr ccr, timer_res_t *t)
{
    uint32_t ret = 0x1000000;

    switch(ccr) {
    case CCR:
        ret = t->reg->CCR;
        break;
    case CCR0:
        ret = t->reg->CCR0;
        break;
    case CCR1:
        ret = t->reg->CCR1;
        break;
    case CCR2:
        ret = t->reg->CCR2;
        break;
    }
    return ret;
}

static void timer_set_ccrx(uint32_t val, rv32_timer_ccr ccr, timer_res_t *t)
{
    switch(ccr) {
    case CCR:
        t->reg->CCR = val & TIMx_CCR_Msk;
        break;
    case CCR0:
        t->reg->CCR0 = val & TIMx_CCR_Msk;
        break;
    case CCR1:
        t->reg->CCR1 = val & TIMx_CCR_Msk;
        break;
    case CCR2:
        t->reg->CCR2 = val & TIMx_CCR_Msk;
        break;
    default:
        break;
    }
}

static void timer_set_irq_cb (timer_signalevent_t cb_event, timer_res_t *t)
{
    if (t != NULL)
        t->cb_event = cb_event;
}

static void generic_timer_irq_handler(timer_res_t *t)
{
    uint32_t event;

    // TODO: event assignments
    event = 0;

    if (t->cb_event)
        t->cb_event(event);
}


#ifdef RTE_Drivers_TIMER0
static void timer0_set_count (uint32_t val)
{
    timer_set_count(val, &timer0_res);
}

static uint32_t timer0_get_count (void)
{
    return timer_get_count(&timer0_res);
}

static void timer0_configure (uint32_t val)
{
    timer_configure(val, &timer0_res);
}

static void timer0_set_status (uint32_t val)
{
    timer_set_status(val, &timer0_res);
}

static uint32_t timer0_get_status (void)
{
    return timer_get_status(&timer0_res);
}

static int timer0_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer0_res);
}

static uint32_t timer0_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer0_res);
}

static void timer0_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer0_res);
}

static void timer0_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer0_res);
}

void timer0_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer0_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer0 = {
    timer0_set_count,
    timer0_get_count,
    timer0_configure,
    timer0_set_status,
    timer0_get_status,
    timer0_chn_config,
    timer0_set_ccrx,
    timer0_get_ccrx,
    timer0_set_irq_cb
};
#endif /* RTE_Drivers_TIME0 */

#ifdef RTE_Drivers_TIMER1
static void timer1_set_count (uint32_t val)
{
    timer_set_count(val, &timer1_res);
}

static uint32_t timer1_get_count (void)
{
    return timer_get_count(&timer1_res);
}

static void timer1_configure (uint32_t val)
{
    timer_configure(val, &timer1_res);
}

static void timer1_set_status (uint32_t val)
{
    timer_set_status(val, &timer1_res);
}

static uint32_t timer1_get_status (void)
{
    return timer_get_status(&timer1_res);
}

static int timer1_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer1_res);
}

static uint32_t timer1_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer1_res);
}

static void timer1_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer1_res);
}

static void timer1_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer1_res);
}

void timer1_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer1_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer1 = {
    timer1_set_count,
    timer1_get_count,
    timer1_configure,
    timer1_set_status,
    timer1_get_status,
    timer1_chn_config,
    timer1_set_ccrx,
    timer1_get_ccrx,
    timer1_set_irq_cb
};
#endif /* RTE_Drivers_TIMER1 */

#ifdef RTE_Drivers_TIMER2
static void timer2_set_count (uint32_t val)
{
    timer_set_count(val, &timer2_res);
}

static uint32_t timer2_get_count (void)
{
    return timer_get_count(&timer2_res);
}

static void timer2_configure (uint32_t val)
{
    timer_configure(val, &timer2_res);
}

static void timer2_set_status (uint32_t val)
{
    timer_set_status(val, &timer2_res);
}

static uint32_t timer2_get_status (void)
{
    return timer_get_status(&timer2_res);
}

static int timer2_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer2_res);
}

static uint32_t timer2_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer2_res);
}

static void timer2_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer2_res);
}

static void timer2_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer2_res);
}

void timer2_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer2_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer2 = {
    timer2_set_count,
    timer2_get_count,
    timer2_configure,
    timer2_set_status,
    timer2_get_status,
    timer2_chn_config,
    timer2_set_ccrx,
    timer2_get_ccrx,
    timer2_set_irq_cb
};
#endif /* RTE_Drivers_TIMER2 */

#ifdef RTE_Drivers_TIMER3
static void timer3_set_count (uint32_t val)
{
    timer_set_count(val, &timer3_res);
}

static uint32_t timer3_get_count (void)
{
    return timer_get_count(&timer3_res);
}

static void timer3_configure (uint32_t val)
{
    timer_configure(val, &timer3_res);
}

static void timer3_set_status (uint32_t val)
{
    timer_set_status(val, &timer3_res);
}

static uint32_t timer3_get_status (void)
{
    return timer_get_status(&timer3_res);
}

static int timer3_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer3_res);
}

static uint32_t timer3_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer3_res);
}

static void timer3_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer3_res);
}

static void timer3_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer3_res);
}

void timer3_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer3_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer3 = {
    timer3_set_count,
    timer3_get_count,
    timer3_configure,
    timer3_set_status,
    timer3_get_status,
    timer3_chn_config,
    timer3_set_ccrx,
    timer3_get_ccrx,
    timer3_set_irq_cb
};
#endif /* RTE_Drivers_TIMER3 */

#ifdef RTE_Drivers_TIMER4
static void timer4_set_count (uint32_t val)
{
    timer_set_count(val, &timer4_res);
}

static uint32_t timer4_get_count (void)
{
    return timer_get_count(&timer4_res);
}

static void timer4_configure (uint32_t val)
{
    timer_configure(val, &timer4_res);
}

static void timer4_set_status (uint32_t val)
{
    timer_set_status(val, &timer4_res);
}

static uint32_t timer4_get_status (void)
{
    return timer_get_status(&timer4_res);
}

static int timer4_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer4_res);
}

static uint32_t timer4_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer4_res);
}

static void timer4_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer4_res);
}

static void timer4_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer4_res);
}

void timer4_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer4_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer4 = {
    timer4_set_count,
    timer4_get_count,
    timer4_configure,
    timer4_set_status,
    timer4_get_status,
    timer4_chn_config,
    timer4_set_ccrx,
    timer4_get_ccrx,
    timer4_set_irq_cb
};
#endif /* RTE_Drivers_TIMER4 */

#ifdef RTE_Drivers_TIMER5
static void timer5_set_count (uint32_t val)
{
    timer_set_count(val, &timer5_res);
}

static uint32_t timer5_get_count (void)
{
    return timer_get_count(&timer5_res);
}

static void timer5_configure (uint32_t val)
{
    timer_configure(val, &timer5_res);
}

static void timer5_set_status (uint32_t val)
{
    timer_set_status(val, &timer5_res);
}

static uint32_t timer5_get_status (void)
{
    return timer_get_status(&timer5_res);
}

static int timer5_chn_config (uint32_t val, uint8_t chn)
{
    return timer_chn_config(val, chn, &timer5_res);
}

static uint32_t timer5_get_ccrx (rv32_timer_ccr n)
{
    return timer_get_ccrx(n, &timer5_res);
}

static void timer5_set_ccrx (uint32_t val, rv32_timer_ccr n)
{
    timer_set_ccrx(val, n, &timer5_res);
}

static void timer5_set_irq_cb (timer_signalevent_t cb_event)
{
    timer_set_irq_cb(cb_event, &timer5_res);
}

void timer5_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_TIMER0_IRQn);
    eu_interrupt_clear_pending(RV32_TIMER0_IRQn);
    generic_timer_irq_handler(&timer5_res);
    eu_interrupt_enable(RV32_TIMER0_IRQn);
}

DRIVER_TIMER driver_timer5 = {
    timer5_set_count,
    timer5_get_count,
    timer5_configure,
    timer5_set_status,
    timer5_get_status,
    timer5_chn_config,
    timer5_set_ccrx,
    timer5_get_ccrx,
    timer5_set_irq_cb
};
#endif /* RTE_Drivers_TIMER5 */
