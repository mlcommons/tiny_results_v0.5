#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_gpio.h>

DRIVER_GPIO *GPIO0 = &driver_gpio0;
DRIVER_GPIO *GPIO1 = &driver_gpio1;

volatile static uint32_t gpio_irq_count = 0;

void gpio_regs_test(void)
{
    printf("Start gpio_regs_test\n");
	printf("GPIO0 DIR:   0x%lx\n", RV32_GPIO0->DIR);
	printf("GPIO0 IS:    0x%lx\n", RV32_GPIO0->IS);
	printf("GPIO0 IBE:   0x%lx\n", RV32_GPIO0->IBE);
	printf("GPIO0 IEV:   0x%lx\n", RV32_GPIO0->IEV);
	printf("GPIO0 IE:    0x%lx\n", RV32_GPIO0->IE);
	printf("GPIO0 RIS:   0x%lx\n", RV32_GPIO0->RIS);
	printf("GPIO0 MIS:   0x%lx\n", RV32_GPIO0->MIS);
	printf("GPIO0 IC:    0x%lx\n", RV32_GPIO0->IC);
	printf("GPIO0 AFSEL: 0x%lx\n", RV32_GPIO0->AFSEL);
	printf("GPIO0 PIDR0: 0x%lx\n", RV32_GPIO0->PIDR0);
	printf("GPIO0 PIDR1: 0x%lx\n", RV32_GPIO0->PIDR1);
	printf("GPIO0 PIDR2: 0x%lx\n", RV32_GPIO0->PIDR2);
	printf("GPIO0 PIDR3: 0x%lx\n", RV32_GPIO0->PIDR3);
	printf("GPIO0 CIDR0: 0x%lx\n", RV32_GPIO0->CIDR0);
	printf("GPIO0 CIDR1: 0x%lx\n", RV32_GPIO0->CIDR1);
	printf("GPIO0 CIDR2: 0x%lx\n", RV32_GPIO0->CIDR2);
	printf("GPIO0 CIDR3: 0x%lx\n", RV32_GPIO0->CIDR3);
    printf("End gpio_regs_test\n");
}

void gpio_output_test(void)
{
    printf("Start gpio_output_test\n");

    GPIO1->set_direction(0, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(1, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(2, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(3, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(4, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(5, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(6, GPIO_PIN_DIRECTION_OUTPUT);
    GPIO1->set_direction(7, GPIO_PIN_DIRECTION_OUTPUT);

    GPIO1->pull_high(0xff);

    printf("End gpio_output_test\n");
}

void gpio_input_test(void)
{
    uint8_t gpio_input;

    printf("start gpio_input_test\n");

    GPIO0->set_direction(0, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(1, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(2, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(3, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(4, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(5, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(6, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(7, GPIO_PIN_DIRECTION_INPUT);

    gpio_input  = GPIO0->read(0);       // PIN0 0x4
    gpio_input |= GPIO0->read(1) << 1;  // PIN1 0x8
    gpio_input |= GPIO0->read(2) << 2;  // PIN2 0x10
    gpio_input |= GPIO0->read(3) << 3;  // PIN3 0x20
    gpio_input |= GPIO0->read(4) << 4;  // PIN4 0x40
    gpio_input |= GPIO0->read(5) << 5;  // PIN5 0x80
    gpio_input |= GPIO0->read(6) << 6;  // PIN6 0x100
    gpio_input |= GPIO0->read(7) << 7;  // PIN7 0x200

    printf("Input value is 0x%x\n", gpio_input);

    printf("End gpio_input_test\n");
}

void gpio_irq_print(void)
{
    int i;
    uint32_t status;

    status = RV32_GPIO0->RIS;
    for (i = 0; i < 8; i++) {
        if ((status >> i) & 0x1)
            GPIO0->irq_clear(i);
    }
    printf("GPIO interrupt! Raw interrupt status = 0x%lx\n",
           status);
    gpio_irq_count++;
}

void gpio_irq_test(void)
{
    printf("Start gpio_irq_test\n");

    GPIO0->set_irq_handler(gpio_irq_print);

    GPIO0->irq_cfg(0, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(1, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(2, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(3, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(4, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(5, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(6, INT_TYPE_RISING_EDGE);
    GPIO0->irq_cfg(7, INT_TYPE_RISING_EDGE);

    GPIO0->irq_enable(0);
    GPIO0->irq_enable(1);
    GPIO0->irq_enable(2);
    GPIO0->irq_enable(3);
    GPIO0->irq_enable(4);
    GPIO0->irq_enable(5);
    GPIO0->irq_enable(6);
    GPIO0->irq_enable(7);

    eu_interrupt_enable(RV32_GPIO0_IRQn);
    printf("Wait for irq...\n");
    while (gpio_irq_count < 1) {};
    eu_interrupt_disable(RV32_GPIO0_IRQn);

    printf("End gpio_irq_test\n");
}

void gpio_test(void)
{
    gpio_regs_test();
    gpio_output_test();
    gpio_input_test();
    gpio_irq_test();
}
