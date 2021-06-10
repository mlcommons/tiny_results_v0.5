#include <stddef.h>
#include <platform.h>
#include <rv_gpio.h>

#if RTE_Drivers_GPIO0
static gpio_res_t gpio0_res = {
    RV32_GPIO0,
    NULL
};
#endif
#if RTE_Drivers_GPIO1
static gpio_res_t gpio1_res = {
    RV32_GPIO1,
    NULL
};
#endif
#if RTE_Drivers_GPIO2
static gpio_res_t gpio2_res = {
    RV32_GPIO2,
    NULL
};
#endif
#if RTE_Drivers_GPIO3
static gpio_res_t gpio3_res = {
    RV32_GPIO3,
    NULL
};
#endif
#if RTE_Drivers_GPIO4
static gpio_res_t gpio4_res = {
    RV32_GPIO4,
    NULL
};
#endif

static void GPIO_PinSetDirection (uint8_t pin_num, uint8_t dir, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    if (dir) // output
        gpio->DIR |= (1UL << pin_num);
    else // 0
        gpio->DIR &= ~(1UL << pin_num);
}

static uint8_t GPIO_PinRead (uint8_t pin_num, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return 0;

    // TODO
    return *((uint8_t *)gpio + (1 << (pin_num + 2))) ? 1 : 0;
}

static void GPIO_PinWrite (uint8_t pin_num, uint8_t val, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    // TODO
    if (val)
        *((uint8_t *)gpio + (1 << (pin_num + 2))) = 0xff;
    else
        *((uint8_t *)gpio + (1 << (pin_num + 2))) = 0x0;
}

static void GPIO_PinPullHigh (uint8_t pinMask, rv32_gpio_t *gpio)
{
    *((uint8_t *)gpio + (pinMask << 2)) = 0xff;
}

static void GPIO_PinPullLow (uint8_t pinMask, rv32_gpio_t *gpio)
{
    *((uint8_t *)gpio + (pinMask << 2)) = 0x00;
}

static void GPIO_PinIntCfg (uint8_t pin_num, gpio_int_t intType, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    switch (intType) {
    case INT_TYPE_RISING_EDGE:
        gpio->IS  &= ~(1UL << pin_num);
        gpio->IBE &= ~(1UL << pin_num);
        gpio->IEV |=  (1UL << pin_num);
        break;
    case INT_TYPE_FALLING_EDGE:
        gpio->IS  &= ~(1UL << pin_num);
        gpio->IBE &= ~(1UL << pin_num);
        gpio->IEV &= ~(1UL << pin_num);
        break;
    case INT_TYPE_BOTH_EDGE:
        gpio->IS  &= ~(1UL << pin_num);
        gpio->IBE |=  (1UL << pin_num);
        break;
    case INT_TYPE_LOW_LEVEL:
        gpio->IS  |=  (1UL << pin_num);
        gpio->IBE &= ~(1UL << pin_num);
        gpio->IEV &= ~(1UL << pin_num);
        break;
    case INT_TYPE_HIGH_LEVEL:
        gpio->IS  |=  (1UL << pin_num);
        gpio->IBE &= ~(1UL << pin_num);
        gpio->IEV |=  (1UL << pin_num);
        break;
    default:
        break;
    }
}

static void GPIO_PinIntEnable (uint8_t pin_num, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    gpio->IE |= (1UL << pin_num);
}

static void GPIO_PinIntDisable (uint8_t pin_num, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    gpio->IE &= ~(1UL << pin_num);
}

static uint8_t GPIO_PinIntStatus (uint8_t pin_num, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return 0;

    return (gpio->RIS & (1UL << pin_num));
}

static void GPIO_PinIntClear (uint8_t pin_num, rv32_gpio_t *gpio)
{
    if (pin_num > 7)
        return;

    gpio->IC = (1UL << pin_num);
}

#if RTE_Drivers_GPIO0
static void gpio0_set_direction(uint8_t pin_num, uint8_t dir)
{
    GPIO_PinSetDirection(pin_num, dir, RV32_GPIO0); 
}

static uint8_t gpio0_read(uint8_t pin_num)
{
    return GPIO_PinRead(pin_num, RV32_GPIO0);
}

static void gpio0_write(uint8_t pin_num, uint8_t val)
{
    GPIO_PinWrite(pin_num, val, RV32_GPIO0);
}

static void gpio0_pull_high(uint8_t mask)
{
    GPIO_PinPullHigh(mask, RV32_GPIO0);
}

static void gpio0_pull_low(uint8_t mask)
{
    GPIO_PinPullLow(mask, RV32_GPIO0);
}

static void gpio0_irq_cfg(uint8_t pin_num, gpio_int_t type)
{
    GPIO_PinIntCfg(pin_num, type, RV32_GPIO0);
}

static void gpio0_irq_enable(uint8_t pin_num)
{
    GPIO_PinIntEnable(pin_num, RV32_GPIO0);
}

static void gpio0_irq_disable(uint8_t pin_num)
{
    GPIO_PinIntDisable(pin_num, RV32_GPIO0);
}

static uint8_t gpio0_irq_status(uint8_t pin_num)
{
    return GPIO_PinIntStatus(pin_num, RV32_GPIO0);
}

static void gpio0_irq_clear (uint8_t pin_num)
{
    GPIO_PinIntClear(pin_num, RV32_GPIO0);
}

static void gpio0_set_irq_handler (gpio_signalevent_t cb_event)
{
    gpio0_res.cb_event = cb_event;
}

void gpio0_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_GPIO0_IRQn);
    eu_interrupt_clear_pending(RV32_GPIO0_IRQn);
    if (gpio0_res.cb_event)
        gpio0_res.cb_event();
    eu_interrupt_enable(RV32_GPIO0_IRQn);
}

DRIVER_GPIO driver_gpio0 = {
    gpio0_set_direction,
    gpio0_read,
    gpio0_write,
    gpio0_pull_high,
    gpio0_pull_low,
    gpio0_irq_cfg,
    gpio0_irq_enable,
    gpio0_irq_disable,
    gpio0_irq_status,
    gpio0_irq_clear,
    gpio0_set_irq_handler
};
#endif

#if RTE_Drivers_GPIO1
static void gpio1_set_direction(uint8_t pin_num, uint8_t dir)
{
    GPIO_PinSetDirection(pin_num, dir, RV32_GPIO1); 
}

static uint8_t gpio1_read(uint8_t pin_num)
{
    return GPIO_PinRead(pin_num, RV32_GPIO1);
}

static void gpio1_write(uint8_t pin_num, uint8_t val)
{
    GPIO_PinWrite(pin_num, val, RV32_GPIO1);
}

static void gpio1_pull_high(uint8_t mask)
{
    GPIO_PinPullHigh(mask, RV32_GPIO1);
}

static void gpio1_pull_low(uint8_t mask)
{
    GPIO_PinPullLow(mask, RV32_GPIO1);
}

static void gpio1_irq_cfg(uint8_t pin_num, gpio_int_t type)
{
    GPIO_PinIntCfg(pin_num, type, RV32_GPIO1);
}

static void gpio1_irq_enable(uint8_t pin_num)
{
    GPIO_PinIntEnable(pin_num, RV32_GPIO1);
}

static void gpio1_irq_disable(uint8_t pin_num)
{
    GPIO_PinIntDisable(pin_num, RV32_GPIO1);
}

static uint8_t gpio1_irq_status(uint8_t pin_num)
{
    return GPIO_PinIntStatus(pin_num, RV32_GPIO1);
}

static void gpio1_irq_clear (uint8_t pin_num)
{
    GPIO_PinIntClear(pin_num, RV32_GPIO1);
}

static void gpio1_set_irq_handler (gpio_signalevent_t cb_event)
{
    gpio1_res.cb_event = cb_event;
}

void gpio1_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_GPIO1_IRQn);
    eu_interrupt_clear_pending(RV32_GPIO1_IRQn);
    if (gpio1_res.cb_event)
        gpio1_res.cb_event();
    eu_interrupt_enable(RV32_GPIO1_IRQn);
}

DRIVER_GPIO driver_gpio1 = {
    gpio1_set_direction,
    gpio1_read,
    gpio1_write,
    gpio1_pull_high,
    gpio1_pull_low,
    gpio1_irq_cfg,
    gpio1_irq_enable,
    gpio1_irq_disable,
    gpio1_irq_status,
    gpio1_irq_clear,
    gpio1_set_irq_handler
};
#endif

#if RTE_Drivers_GPIO2
static void gpio2_set_direction(uint8_t pin_num, uint8_t dir)
{
    GPIO_PinSetDirection(pin_num, dir, RV32_GPIO2); 
}

static uint8_t gpio2_read(uint8_t pin_num)
{
    return GPIO_PinRead(pin_num, RV32_GPIO2);
}

static void gpio2_write(uint8_t pin_num, uint8_t val)
{
    GPIO_PinWrite(pin_num, val, RV32_GPIO2);
}

static void gpio2_pull_high(uint8_t mask)
{
    GPIO_PinPullHigh(mask, RV32_GPIO2);
}

static void gpio2_pull_low(uint8_t mask)
{
    GPIO_PinPullLow(mask, RV32_GPIO2);
}

static void gpio2_irq_cfg(uint8_t pin_num, gpio_int_t type)
{
    GPIO_PinIntCfg(pin_num, type, RV32_GPIO2);
}

static void gpio2_irq_enable(uint8_t pin_num)
{
    GPIO_PinIntEnable(pin_num, RV32_GPIO2);
}

static void gpio2_irq_disable(uint8_t pin_num)
{
    GPIO_PinIntDisable(pin_num, RV32_GPIO2);
}

static uint8_t gpio2_irq_status(uint8_t pin_num)
{
    return GPIO_PinIntStatus(pin_num, RV32_GPIO2);
}

static void gpio2_irq_clear (uint8_t pin_num)
{
    GPIO_PinIntClear(pin_num, RV32_GPIO2);
}

static void gpio2_set_irq_handler (gpio_signalevent_t cb_event)
{
    gpio2_res.cb_event = cb_event;
}

void gpio2_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_GPIO2_IRQn);
    eu_interrupt_clear_pending(RV32_GPIO2_IRQn);
    if (gpio2_res.cb_event)
        gpio2_res.cb_event();
    eu_interrupt_enable(RV32_GPIO2_IRQn);
}

DRIVER_GPIO driver_gpio2 = {
    gpio2_set_direction,
    gpio2_read,
    gpio2_write,
    gpio2_pull_high,
    gpio2_pull_low,
    gpio2_irq_cfg,
    gpio2_irq_enable,
    gpio2_irq_disable,
    gpio2_irq_status,
    gpio2_irq_clear,
    gpio2_set_irq_handler
};
#endif

#if RTE_Drivers_GPIO3
static void gpio3_set_direction(uint8_t pin_num, uint8_t dir)
{
    GPIO_PinSetDirection(pin_num, dir, RV32_GPIO3); 
}

static uint8_t gpio3_read(uint8_t pin_num)
{
    return GPIO_PinRead(pin_num, RV32_GPIO3);
}

static void gpio3_write(uint8_t pin_num, uint8_t val)
{
    GPIO_PinWrite(pin_num, val, RV32_GPIO3);
}

static void gpio3_pull_high(uint8_t mask)
{
    GPIO_PinPullHigh(mask, RV32_GPIO3);
}

static void gpio3_pull_low(uint8_t mask)
{
    GPIO_PinPullLow(mask, RV32_GPIO3);
}

static void gpio3_irq_cfg(uint8_t pin_num, gpio_int_t type)
{
    GPIO_PinIntCfg(pin_num, type, RV32_GPIO3);
}

static void gpio3_irq_enable(uint8_t pin_num)
{
    GPIO_PinIntEnable(pin_num, RV32_GPIO3);
}

static void gpio3_irq_disable(uint8_t pin_num)
{
    GPIO_PinIntDisable(pin_num, RV32_GPIO3);
}

static uint8_t gpio3_irq_status(uint8_t pin_num)
{
    return GPIO_PinIntStatus(pin_num, RV32_GPIO3);
}

static void gpio3_irq_clear (uint8_t pin_num)
{
    GPIO_PinIntClear(pin_num, RV32_GPIO3);
}

static void gpio3_set_irq_handler (gpio_signalevent_t cb_event)
{
    gpio3_res.cb_event = cb_event;
}

void gpio3_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_GPIO3_IRQn);
    eu_interrupt_clear_pending(RV32_GPIO3_IRQn);
    if (gpio3_res.cb_event)
        gpio3_res.cb_event();
    eu_interrupt_disable(RV32_GPIO3_IRQn);
}

DRIVER_GPIO driver_gpio3 = {
    gpio3_set_direction,
    gpio3_read,
    gpio3_write,
    gpio3_pull_high,
    gpio3_pull_low,
    gpio3_irq_cfg,
    gpio3_irq_enable,
    gpio3_irq_disable,
    gpio3_irq_status,
    gpio3_irq_clear,
    gpio3_set_irq_handler
};
#endif

#if RTE_Drivers_GPIO4
static void gpio4_set_direction(uint8_t pin_num, uint8_t dir)
{
    GPIO_PinSetDirection(pin_num, dir, RV32_GPIO4); 
}

static uint8_t gpio4_read(uint8_t pin_num)
{
    return GPIO_PinRead(pin_num, RV32_GPIO4);
}

static void gpio4_write(uint8_t pin_num, uint8_t val)
{
    GPIO_PinWrite(pin_num, val, RV32_GPIO4);
}

static void gpio4_pull_high(uint8_t mask)
{
    GPIO_PinPullHigh(mask, RV32_GPIO4);
}

static void gpio4_pull_low(uint8_t mask)
{
    GPIO_PinPullLow(mask, RV32_GPIO4);
}

static void gpio4_irq_cfg(uint8_t pin_num, gpio_int_t type)
{
    GPIO_PinIntCfg(pin_num, type, RV32_GPIO4);
}

static void gpio4_irq_enable(uint8_t pin_num)
{
    GPIO_PinIntEnable(pin_num, RV32_GPIO4);
}

static void gpio4_irq_disable(uint8_t pin_num)
{
    GPIO_PinIntDisable(pin_num, RV32_GPIO4);
}

static uint8_t gpio4_irq_status(uint8_t pin_num)
{
    return GPIO_PinIntStatus(pin_num, RV32_GPIO4);
}

static void gpio4_irq_clear (uint8_t pin_num)
{
    GPIO_PinIntClear(pin_num, RV32_GPIO4);
}

static void gpio4_set_irq_handler (gpio_signalevent_t cb_event)
{
    gpio4_res.cb_event = cb_event;
}

void gpio4_handler (uint32_t *regs, uint32_t mcause, uint32_t mepc)
{
    eu_interrupt_disable(RV32_GPIO4_SECIRQn);
    eu_interrupt_clear_pending(RV32_GPIO4_SECIRQn);
    if (gpio4_res.cb_event)
        gpio4_res.cb_event();
    eu_interrupt_enable(RV32_GPIO4_SECIRQn);
}

DRIVER_GPIO driver_gpio4 = {
    gpio4_set_direction,
    gpio4_read,
    gpio4_write,
    gpio4_pull_high,
    gpio4_pull_low,
    gpio4_irq_cfg,
    gpio4_irq_enable,
    gpio4_irq_disable,
    gpio4_irq_status,
    gpio4_irq_clear,
    gpio4_set_irq_handler
};
#endif

