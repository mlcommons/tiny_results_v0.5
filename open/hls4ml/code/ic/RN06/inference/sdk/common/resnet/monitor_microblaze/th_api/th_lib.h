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

#ifndef __TH_LIB_H
#define __TH_LIB_H

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "th_libc.h"
#include "../ee_main.h"

//#include "../../src.h"
//#include "../../dst.h"
#include "xresnet_axi.h"  /* accelerator */

#include "xtmrctr.h"     /* timer */

XTmrCtr TimerCounterInst;
#define TMRCTR_DEVICE_ID	XPAR_TMRCTR_0_DEVICE_ID
#define TIMER_CNTR_0		0
#define TIMER_CNTR_1		1

#define src_FEATURE_COUNT 3072
#define dst_FEATURE_COUNT 10

#if 0
/* base address for the accelerator */
#define MEM_BASE_ADDR XPAR_PS7_DDR_0_S_AXI_BASEADDR

/* data offsets and pointers */
#define SRC_BUFFER_BASE (MEM_BASE_ADDR + 0x00000000)
//unsigned char *src_mem = (unsigned char*)SRC_BUFFER_BASE;

#define DST_BUFFER_BASE (MEM_BASE_ADDR + 0x00020000)
//unsigned char *dst_mem = (unsigned char*)DST_BUFFER_BASE;
#else
unsigned char src_mem[src_FEATURE_COUNT];
unsigned char dst_mem[dst_FEATURE_COUNT];
#endif

// It is crucial to follow EEMBC message syntax for key messages
#define EE_MSG_TIMESTAMP "m-lap-us-%lu\r\n"

#ifndef EE_CFG_ENERGY_MODE
#define EE_CFG_ENERGY_MODE 1
#endif

#if EE_CFG_ENERGY_MODE == 1
#define EE_MSG_TIMESTAMP_MODE "m-timestamp-mode-energy\r\n"
#else
#define EE_MSG_TIMESTAMP_MODE "m-timestamp-mode-performance\r\n"
#endif

/**
 * This string is used in the "name%" command. When the host UI starts a test,
 * it calles the "name%" command, and the result is captured in the log file.
 * It can be quite useful to have the device's name in the log file for future
 * reference or debug.
 */
#define TH_VENDOR_NAME_STRING "Xilinx_ArtyA7_100T"


long long unsigned th_calibration_time;
long long unsigned th_timestamp_counts;
long long unsigned th_timer_timestamp;
long long unsigned th_timer_start;

uint8_t  floatsize;
uint32_t src_mem_size;
uint32_t dst_mem_size;

XResnet_axi do_resnet;
XResnet_axi_Config *do_resnet_cfg;

void th_final_initialize(void);
void th_timestamp_initialize(void);
void th_timestamp(void);
void th_serialport_initialize(void);
void th_printf(const char *fmt, ...);
void th_command_ready(char volatile *);
/* accelerator initialization routine */
void init_accelerators();
double get_elapsed_time(u64 clk_start, u64 clk_stop);

#endif // __TH_LIB_H
