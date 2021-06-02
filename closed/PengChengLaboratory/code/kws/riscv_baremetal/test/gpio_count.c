#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_gpio.h>


volatile static uint32_t count = 0;

void gpio_freq_div(void)
{
    uint32_t i = 0;
    DRIVER_GPIO *GPIO0 = &driver_gpio0;

    printf("gpio_freq_div start\n");

    // Use GPIO0-PIN0 to determine whether the test should be stopped.
    // When GPIO0-PIN0 is pull-up, test starts. Or, end it.
    GPIO0->set_direction(0, GPIO_PIN_DIRECTION_INPUT);
    GPIO0->set_direction(1, GPIO_PIN_DIRECTION_OUTPUT);

    while (GPIO0->read(0)) {
        if (count % 10 == 0) {
            GPIO0->write(1, (uint8_t)(++i % 2));
        }
        count++;
    }

    printf("gpio_freq_div end\n");
}
