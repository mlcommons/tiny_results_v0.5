#ifndef __rv_gpio_h__
#define __rv_gpio_h__
#include <gpio.h>

// GPIO Direction
#define GPIO_PIN_DIRECTION_INPUT     (0)
#define GPIO_PIN_DIRECTION_OUTPUT    (1)

typedef enum _gpio_int {
    INT_TYPE_RISING_EDGE,
    INT_TYPE_FALLING_EDGE,
    INT_TYPE_BOTH_EDGE,
    INT_TYPE_LOW_LEVEL,
    INT_TYPE_HIGH_LEVEL
} gpio_int_t;

typedef void (*gpio_signalevent_t) (void);

typedef struct _gpio_res {
    rv32_gpio_t *reg;
    gpio_signalevent_t cb_event;
} gpio_res_t;

typedef struct _DRIVER_GPIO {
    void    (*set_direction)  (uint8_t pin_num, uint8_t dir);
    uint8_t (*read         )  (uint8_t pin_num);
    void    (*write        )  (uint8_t pin_num, uint8_t val);
    void    (*pull_high    )  (uint8_t mask);
    void    (*pull_low     )  (uint8_t mask);
    void    (*irq_cfg      )  (uint8_t pin_num, gpio_int_t type);
    void    (*irq_enable   )  (uint8_t pin_num);
    void    (*irq_disable  )  (uint8_t pin_num);
    uint8_t (*irq_status   )  (uint8_t pin_num);
    void    (*irq_clear    )  (uint8_t pin_num);
    void    (*set_irq_handler)(gpio_signalevent_t cb_event);
} const DRIVER_GPIO;

extern DRIVER_GPIO driver_gpio0;
extern DRIVER_GPIO driver_gpio1;
extern DRIVER_GPIO driver_gpio2;
extern DRIVER_GPIO driver_gpio3;
extern DRIVER_GPIO driver_gpio4;


#endif
