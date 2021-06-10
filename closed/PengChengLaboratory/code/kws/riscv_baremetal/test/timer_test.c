#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_timer.h>

DRIVER_TIMER *TIMER0 = &driver_timer0;

volatile uint32_t flag;
volatile uint32_t cflag;

void freerun_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    printf("Free-running mode interrupt! ");
    printf("( CNT: 0x%lx, STAT: 0x%lx )\n", count, status);
    flag = 1;
}

void modulo_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    printf("Modulo mode interrupt! ");
    printf("( CNT: 0x%lx, STAT: 0x%lx )\n", count, status);
    flag++;
}

void updown_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    printf("Up-and-down mode interrupt! ");
    printf("( CNT: 0x%lx, STAT: 0x%lx )\n", count, status);
    flag++;
}

void output_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    printf("CNT: 0x%lx, STAT: 0x%lx\n", count, status);
    if (status & TIMx_STAT_OVFIF_Msk)
        printf(" Timer interrupt.\n");
    if (status & 0x7) {
        printf(" Channel output compare interrupt.\n");
        cflag++;
    }
}

void input_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    printf("CNT: 0x%lx, STAT: 0x%lx\n", count, status);
    if (status & TIMx_STAT_OVFIF_Msk)
        printf(" Timer interrupt.\n");
    if (status & 0x7) {
        printf(" Channel input capture interrupt, CCR0: 0x%lx.\n", TIMER0->get_ccrx(CCR0));
        cflag++;
    }
}

void timer_test(void)
{
    eu_interrupt_enable(RV32_TIMER0_IRQn);
    TIMER0->chn_config(0, 0);
    TIMER0->configure(0);
    // Channel input capture
    printf("Channel input capture test.\n");
    cflag = 0;
    TIMER0->set_irq_cb(input_cb);
    TIMER0->set_count(0);
    TIMER0->set_ccrx(65536, CCR);
    TIMER0->configure(TIMER_MODE_MODULO << TIMx_CTRL_MODE_Pos);
    TIMER0->chn_config((0x3 << TIMx_CCTLx_CAP_Pos) |
                       (CHANNEL_MODE_CAPTURE << TIMx_CCTLx_MODE_Pos) |
                       (TIMx_CCTLx_IE_Msk), 0);
    while (cflag < 1) {};
    TIMER0->chn_config(0, 0);
    TIMER0->configure(0);
    printf("Channel input capture test END.\n");
    flag = 0;

    // Channel outnput compare
    printf("Channel output compare test.\n");
    cflag = 0;
    TIMER0->set_irq_cb(output_cb);
    TIMER0->set_count(0);
    TIMER0->set_ccrx(0x20000, CCR0);
    TIMER0->chn_config((CHANNEL_MODE_COMPARE << TIMx_CCTLx_MODE_Pos) |
                       (TIMx_CCTLx_IE_Msk) |
                       (0x2 << TIMx_CCTLx_CMP_Pos), 0);
    TIMER0->configure(TIMER_MODE_FREERUN << TIMx_CTRL_MODE_Pos);
    while (cflag < 1) {};
    TIMER0->chn_config(0, 0);
    TIMER0->configure(0);
    printf("Channel output compare test END.\n");

#if 0
    // Modulo mode
    printf("Modulo mode test.\n");
    flag = 0;
    TIMER0->set_irq_cb(modulo_cb);
    TIMER0->set_count(0);
    TIMER0->set_ccrx(0xffffff, CCR);
    TIMER0->configure(TIMx_CTRL_OVFIF_ENABLE_Msk|
                      (TIMER_MODE_MODULO << TIMx_CTRL_MODE_Pos));
    while (flag < 1) {};
    TIMER0->configure(0);
    printf("Modulo mode test END.\n");

    // Up-and-down mode
    printf("Up-and-down mode test.\n");
    flag = 0;
    TIMER0->set_irq_cb(modulo_cb);
    TIMER0->set_count(0);
    //TIMER0->set_ccrx(65536, CCR);
    TIMER0->set_ccrx(0xffffff, CCR);
    TIMER0->configure(TIMx_CTRL_OVFIF_ENABLE_Msk|
                      (TIMER_MODE_UPDOWN << TIMx_CTRL_MODE_Pos));
    while (flag < 1) {};
    TIMER0->configure(0);
    printf("Up-and-down mode test END.\n");

    // Free-running mode
    printf("Free-running mode test.\n");
    flag = 0;
    TIMER0->set_irq_cb(freerun_cb);
    TIMER0->set_count(0);
    TIMER0->configure(TIMx_CTRL_OVFIF_ENABLE_Msk|
                      (TIMER_MODE_FREERUN << TIMx_CTRL_MODE_Pos));
    while (flag < 1) {};
    TIMER0->configure(0);
    printf("Free-running mode test END.\n");
#endif
    eu_interrupt_disable(RV32_TIMER0_IRQn);

}
