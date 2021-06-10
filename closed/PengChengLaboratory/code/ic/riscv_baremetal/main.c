#include <stdio.h>
#include <riscv.h>
#include <debug.h>
#include <math.h>

//#include "tensorflow/lite/micro/examples/micro_speech/main_functions.h"

#include "rv_spi.h"
#include <rv_gpio.h>
#include <rv_uart.h>
#include <platform.h>


extern int core_main (void);
extern void whet(void);
extern int eflash_test(void);
extern void dma_test(void);
extern void gpio_test(void);
extern void gpio_freq_div(void);
extern void timer_test(void);
extern void wdt_test(void);
extern void regs_probe(void);
extern void dual_io_test(void);

#if 0
void send_value(uint8_t val)
{
	uint8_t buf[4];
	buf[0] = 0x5a;
	buf[1] = val;
	buf[2] = val;
	buf[3] = 0xa5;
	driver_uart2.Send(buf, 4);
}


#define SND_DATA_SAMPLES	2048
volatile static uint16_t gbuf[SND_DATA_SAMPLES];
#define TRANSFER_SPEED	100000000

void spi_event_rcv(uint32_t ev)
{
	if ((ev & 0x1)== 1)
	{
		int i;
		capture_samples(gbuf, SND_DATA_SAMPLES);
		/*
		printf("rcv:\n");
		for (i = 0; i < SND_DATA_SAMPLES; i++)
		{
			printf("%4x,", gbuf[i]);
			if ((i + 1) % 16 == 0)
				printf("\n");
		}
		*/
	}
}


void data_is_ready(void)
{
	int i;
    uint32_t status;
	DRIVER_GPIO *GPIO2 = &driver_gpio2;


	status = RV32_GPIO2->RIS;
    for (i = 0; i < 8; i++) {
        if ((status >> i) & 0x1)
            GPIO2->irq_clear(i);
    }

	GPIO2->pull_high(1<<2);
	for(i = 0; i < 2; i++)
		__asm__ __volatile__("nop");
	GPIO2->pull_low(1<<2);

	Driver_SPI2.Receive(gbuf, SND_DATA_SAMPLES * sizeof(uint16_t));
}
#endif

int main(void)
{
	DRIVER_GPIO *GPIO2 = &driver_gpio2;
	printf("Start to run!\n");

	//probe_csrs();
	//systick_test();

	//core_main();
	//whet();
    //dma_test();
    //gpio_test();
    //timer_test();
    //wdt_test();
    //regs_probe();
    //dual_io_test();

    //gpio_freq_div();

	printf("Completed!\n");
	#if 0
	Driver_SPI2.Initialize(spi_event_rcv);
	Driver_SPI2.PowerControl(POWER_FULL);
	Driver_SPI2.Control(SPI_MODE_MASTER |
                        SPI_CPOL0_CPHA0 |
                        SPI_MSB_LSB |
                        SPI_SS_MASTER_UNUSED |
                        SPI_DATA_BITS(8),
                        TRANSFER_SPEED);
	printf("spi speed: %d\n",Driver_SPI2.Control(SPI_GET_BUS_SPEED, 0));

	GPIO2->set_direction(2, GPIO_PIN_DIRECTION_OUTPUT);
	GPIO2->pull_low(1<<2);

	GPIO2->set_irq_handler(data_is_ready);
    GPIO2->irq_cfg(1, INT_TYPE_RISING_EDGE);
    GPIO2->irq_enable(1);
    eu_interrupt_enable(RV32_GPIO2_IRQn);
	#endif

	driver_uart2.Initialize(NULL);

	driver_uart2.PowerControl(POWER_FULL);

	driver_uart2.Control(USART_DATA_BITS_8	|
				       USART_PARITY_NONE	|
				       USART_STOP_BITS_1	|
				       USART_FLOW_CONTROL_NONE,
				       115200);
	
	//driver_uart2.Send("hello world!\r\n", 14);
	printf("----------->\n\r");
	printf("start test!!!\r\n");
	printf("----------->\r\n");

	//while (1);

	/* Infinite loop */
	setup();

    while (1) {
      loop();
    }
	
	return 0;
}
