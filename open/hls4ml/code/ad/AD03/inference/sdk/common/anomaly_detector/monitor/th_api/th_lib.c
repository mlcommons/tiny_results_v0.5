/**
 * Copyright (C) EEMBC(R). All Rights Reserved
 *
 * All EEMBC Benchmark Software are products of EEMBC and are provided under the
 * terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
 * are proprietary intellectual properties of EEMBC and its Members and is
 * protected under all applicable laws, including all applicable copyright laws.
 *
 * If you received this EEMBC Benchmark Software without having a currently
 * effective EEMBC Benchmark License Agreement, you must discontinue use.
 */

#include "th_lib.h"

#if EE_CFG_SELFHOSTED != 1


double get_elapsed_time(XTime start, XTime stop)
{
    return 1.0 * (stop - start) / (COUNTS_PER_SECOND);
}

/* accelerator initialization routine */
void init_accelerators()
{
    //printf("INFO: Initializing accelerator\n\r");
    do_anomaly_detector_cfg = XAnomaly_detector_axi_LookupConfig(XPAR_ANOMALY_DETECTOR_AXI_DEVICE_ID);
    if (do_anomaly_detector_cfg)
    {
        int status  = XAnomaly_detector_axi_CfgInitialize(&do_anomaly_detector, do_anomaly_detector_cfg);
        if (status != XST_SUCCESS)
        {
            //printf("ERROR: Initializing accelerator\n\r");
        }
    }
}


/**
 * PORTME: If there's anything else that needs to be done on init, do it here,
 * othewise OK to leave it alone.
 */
void
th_final_initialize(void)
{
	init_platform();

	init_accelerators();

	floatsize = sizeof(float);
	src_mem_size = (src_FEATURE_COUNT* sizeof(unsigned char));
	dst_mem_size = (dst_FEATURE_COUNT* sizeof(unsigned char));

	//malloc_stats();
	src_mem = malloc(2*src_mem_size);
	dst_mem = malloc(2*dst_mem_size);
	//printf("src: %p, dst %p \n",src_mem,dst_mem);
	th_printf("INFO: Init Finished!\r\n");
}

/**
 * PORTME: If using energy mode, set up an open-drain GPIO (if it hasn't been
 * done already by the IDE boilerplate). If using performance mode, prepare a
 * timer if necessary.
 */
void
th_timestamp_initialize(void)
{
    /* USER CODE 1 BEGIN */
	XTime th_timer_stop;
	XTime_GetTime(&th_timer_start);
	usleep(1000); //sleep for 1000us to calibrate timer
	XTime_GetTime(&th_timer_stop);
	th_calibration_time = get_elapsed_time(th_timer_start, th_timer_stop)/1000;
    /* USER CODE 1 END */
    /* This message must NOT be changed. */
    th_printf(EE_MSG_TIMESTAMP_MODE);
    /* Always call the timestamp on initialize so that the open-drain output
       is set to "1" (so that we catch a falling edge) */
    th_timestamp();
}

/**
 * PORTME: In "energy mode",generate a falling edge. Since GPIO pin is
 * OPEN-DRAIN it is OK to float and let the pullup resistor drive. In
 * "performance mode", a timer is needed. Depending on the benchmark, the
 * resolution may be as large as 1ms (1000us). In this case, it is OK for the
 * DUT to supply a 1ms timer, just multiply by 1000. Either way, the user must
 * set the microSeconds value in "performance mode".
 *
 * NOTE: The hold time for the GPIO is 1us
 */
void
th_timestamp(void)
{
//#warning "th_timestamp() not implemented"
#if EE_CFG_ENERGY_MODE == 1
/* USER CODE 1 BEGIN */
/* Step 1. Pull pin low */
/* Step 2. Hold low for at least 1us */
	continue; //Not worrying about for performance mode, #TODO
/* Step 3. Release driver */
/* USER CODE 1 END */
#else
    unsigned long microSeconds = 0ul;
    /* USER CODE 2 BEGIN */
	XTime_GetTime(&th_timer_timestamp);
	th_timestamp_counts = get_elapsed_time(th_timer_start, th_timer_timestamp);
	microSeconds = th_timestamp_counts/th_calibration_time;
    /* USER CODE 2 END */
    /* This message must NOT be changed. */
    th_printf(EE_MSG_TIMESTAMP, microSeconds);
#endif
}

/**
 * PORTME: Set up a serialport at 9600 baud to use for communication to the
 * host system if it hasn't already been done, otherwise it is OK to leave this
 * blank.
 *
 * Repeat: for connections through the IO Manager, baud rate is 9600!
 * For connections directly to the Host UI, baud must be 115200.
 */
void
th_serialport_initialize(void)
{
#if EE_CFG_ENERGY_MODE == 1
/* In energy mode, we talk to the DUT through the IO Manager at 9600 baud */
	//FW Needs to be recompiled for lower speed? #TODO
#else
/* In performance mode, we talk directly to the DUT at 115200 baud */
	init_uart();
#endif
}

/**
 * PORTME: Modify this function to call the proper printf and send to the
 * serial port.
 *
 * It may only be necessary to comment out this function and define
 * th_printf as printf and just rerout fputc();
 */
void
th_printf(const char *p_fmt, ...)
{
    va_list args;
    va_start(args, p_fmt);
    (void)th_vprintf(p_fmt, args); /* ignore return */
    va_end(args);
}

/**
 * PORTME: This function is called with a pointer to the command built from the
 * ee_serial_callback() function during the ISR. It is up to the developer
 * to call ee_serial_command_parser_callback() at the next available non-ISR
 * clock with this command string.
 */
void
th_command_ready(char volatile *p_command)
{
    p_command = p_command;

    ee_serial_command_parser_callback(p_command);
/**
 * Example of how this might be implemented if there's no need to store
 * the command string locally:
 *
 * ee_serial_command_parser_callback(command);
 *
 * Or, depending on the baremetal/RTOS, it might be necessary to create a
 * static char array in this file, store the command, and then call
 * ee_serial_command_parser_callback() when the system is ready to do
 * work.
 */
//#warning "th_command_ready() not implemented"
}

#endif /* EE_CFG_SELFHOSTED */

