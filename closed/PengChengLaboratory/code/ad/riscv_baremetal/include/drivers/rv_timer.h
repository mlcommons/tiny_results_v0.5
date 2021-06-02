#ifndef __rv_timer_h__
#define __rv_timer_h__
#include <timer.h>

typedef void (*timer_signalevent_t) (uint32_t event);

typedef enum _rv32_timer_mode {
    TIMER_MODE_STOP,
    TIMER_MODE_FREERUN,
    TIMER_MODE_MODULO,
    TIMER_MODE_UPDOWN
} rv32_timer_mode;

typedef enum _rv32_timer_channel_mode {
    CHANNEL_MODE_CAPTURE,
    CHANNEL_MODE_COMPARE,
    CHANNEL_MODE_UNSET
} rv32_timer_channel_mode;

typedef enum _rv32_timer_ccr {
    CCR,
    CCR0,
    CCR1,
    CCR2
} rv32_timer_ccr;

typedef struct _timer_res {
    rv32_timer_t *reg;
    uint32_t irq_num;
    rv32_timer_mode tmode;
    rv32_timer_channel_mode cmode[RV32_TIMER_CHN_NUM];
    timer_signalevent_t cb_event;
} timer_res_t;

#define TIMER_CTRL_CMP_SET          0x0
#define TIMER_CTRL_CMP_CLR          0x1
#define TIMER_CTRL_CMP_REV          0x2
#define TIMER_CTRL_CMP_UPS          0x3
#define TIMER_CTRL_CMP_UPC          0x4
#define TIMER_CTRL_CMP_CLR_CCR0SET  0x5
#define TIMER_CTRL_CMP_SET_CCR0CLR  0x6
#define TIMER_CTRL_CMP_PIN_INIT     0x7

#define TIMER_CTRL_CAP_NOCAP        0x0
#define TIMER_CTRL_CAP_UP           0x1
#define TIMER_CTRL_CAP_DWN          0x2
#define TIMER_CTRL_CAP_UPDWN        0x3

typedef struct _DRIVER_TIMER {
    void        (*set_count) (uint32_t val);
    uint32_t    (*get_count) (void);
    void        (*configure) (uint32_t val);
    void        (*set_status) (uint32_t val);
    uint32_t    (*get_status) (void);
    int         (*chn_config) (uint32_t val, uint8_t chn);
    void        (*set_ccrx) (uint32_t val, rv32_timer_ccr n);
    uint32_t    (*get_ccrx) (rv32_timer_ccr n);
    void        (*set_irq_cb) (timer_signalevent_t cb_event);
} const DRIVER_TIMER;

extern DRIVER_TIMER driver_timer0;
extern DRIVER_TIMER driver_timer1;
extern DRIVER_TIMER driver_timer2;
extern DRIVER_TIMER driver_timer3;
extern DRIVER_TIMER driver_timer4;

#endif /* __rv_timer_h__ */
