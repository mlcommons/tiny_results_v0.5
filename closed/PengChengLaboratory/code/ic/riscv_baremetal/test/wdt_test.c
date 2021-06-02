#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_wdt.h>

#define RELOAD_VALUE    0x300000

void wdt_regs_test(void)
{
    printf("Start wdt_regs_test\n");
	printf("WDT LOAD:   0x%lx\n", RV32_WDT->LOAD);
	printf("WDT VAL:    0x%lx\n", RV32_WDT->VAL);
	printf("WDT CTRL:   0x%lx\n", RV32_WDT->CTRL);
	printf("WDT IC:     0x%lx\n", RV32_WDT->IC);
	printf("WDT RIS:    0x%lx\n", RV32_WDT->RIS);
	printf("WDT IS:     0x%lx\n", RV32_WDT->IS);
	printf("WDT LOCK:   0x%lx\n", RV32_WDT->LOCK);
	printf("WDT PIDR0:  0x%lx\n", RV32_WDT->PIDR0);
	printf("WDT PIDR1:  0x%lx\n", RV32_WDT->PIDR1);
	printf("WDT PIDR2:  0x%lx\n", RV32_WDT->PIDR2);
	printf("WDT PIDR3:  0x%lx\n", RV32_WDT->PIDR3);
	printf("WDT PIDR4:  0x%lx\n", RV32_WDT->PIDR4);
	printf("WDT PIDR5:  0x%lx\n", RV32_WDT->PIDR5);
	printf("WDT PIDR6:  0x%lx\n", RV32_WDT->PIDR6);
	printf("WDT PIDR7:  0x%lx\n", RV32_WDT->PIDR7);
	printf("WDT CIDR0:  0x%lx\n", RV32_WDT->CIDR0);
	printf("WDT CIDR1:  0x%lx\n", RV32_WDT->CIDR1);
	printf("WDT CIDR2:  0x%lx\n", RV32_WDT->CIDR2);
	printf("WDT CIDR3:  0x%lx\n", RV32_WDT->CIDR3);
    printf("End wdt_regs_test\n");
}

void wdt_lock_test(void)
{

    printf("Start wdt_lock_test.\n");
    if (RV32_WDT->LOCK & 0x1)
        printf("\tRegister write is locked!\n");
    else
        printf("\tRegister write is not locked!\n");

    RV32_WDT->LOAD = 0x55555555;
    printf("\tWDT LOAD:   0x%lx\n", RV32_WDT->LOAD);

    RV32_WDT->LOCK = 0x1111;
    if (RV32_WDT->LOCK & 0x1)
        printf("\tRegister write is locked! Test Suceed!\n");
    else
        printf("\tRegister write is not locked! Test Failed!\n");

    RV32_WDT->LOAD = 0xaaaaaaaa;
    if (RV32_WDT->LOAD != 0x55555555)
        printf("\tLoad register can be written! Test Failed!\n");
    else
        printf("\tLoad register can not be written! Test Succeed!\n");

    RV32_WDT->LOCK = 0x1ACCE551;
    if (RV32_WDT->LOCK & 0x1)
        printf("\tRegister write is locked! Failed!\n");
    else
        printf("\tRegister write is not locked! Suceed!\n");

    RV32_WDT->LOAD = 0xaaaaaaaa;
    if (RV32_WDT->LOAD != 0xaaaaaaaa)
        printf("\tLoad register can not be written! Test Failed!\n");
    else
        printf("\tLoad register can be written! Test Succeed!\n");

    printf("End wdt_lock_test.\nn");
}

volatile uint32_t wdt_irq_count = 0;

#if 0
void wdt_cb_event_test(void)
{
    //wdt_clear_interrupt();
    wdt_irq_count++;
    printf("WDT interrupts! count: %ld\n", wdt_irq_count);
}
#endif

void wdt_irq_test(void)
{
    printf("Start wdt_irq_test\n");

//    wdt_set_irq_callback(wdt_cb_event_test);
    wdt_init(RELOAD_VALUE);
    wdt_enable_interrupt();

    printf("Reload value = 0x%x\n", RELOAD_VALUE);

    while (wdt_irq_count < 2) {
        asm("wfi");
    }

    wdt_disable_interrupt();
    printf("End wdt_irq_test\n");
}

void wdt_reset_test(void)
{
    printf("Start wdt_reset_test\n");

    wdt_init(RELOAD_VALUE);
    wdt_enable_reset();

    printf("End wdt_reset_test\n");
}

void wdt_test(void)
{
    printf("WDT test begins.\n");

    wdt_regs_test();
    wdt_lock_test();
    wdt_irq_test();
    wdt_reset_test();

    printf("WDT test ends.\n");
}
