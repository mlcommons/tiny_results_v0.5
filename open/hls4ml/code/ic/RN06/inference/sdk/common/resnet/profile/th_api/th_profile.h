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


#ifndef __TH_PROFILE_H
#define __TH_PROFILE_H

#include "../ee_profile.h"
#include "th_util.h"

#include "xresnet_axi.h"  /* accelerator */
#include "xil_cache.h"   /* enable/disable caches etc */
//#include <math.h>
/* PORTME:
 * Select an EE_MODEL_VERSION_* from ee_profile.h, so that the Host UI
 * knows which model is inside this DUT!
 * */
#define TH_MODEL_VERSION EE_MODEL_VERSION_IC01

#define src_FEATURE_COUNT 3072
#define dst_FEATURE_COUNT 10


unsigned char *src_mem_pos;
unsigned char *dst_mem_pos;
uint8_t slices;
uint8_t bins;
unsigned int accel_cnt;
#endif
