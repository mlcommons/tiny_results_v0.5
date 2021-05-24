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
//"profile/th_api/th_profile.h"
#include "th_profile.h"

/* From profile/ee_buffer.c */
extern uint8_t *gp_buff;
extern size_t   g_buff_size;
extern size_t   g_buff_pos;

char max = -128;
short i_max = -1;
void getMax(char input, short index)
{
	// get sign bit
	unsigned char sign = (input & 0b10000000) >> 7;
	unsigned char max_sign = (max & 0b10000000) >> 7;
	if (sign == max_sign) { // if same sign, just compare values
		if (input > max) {
		i_max = index;
		max = input;
		}
	}
	else if (sign == 0) { // if different sign, input is bigger if it's positive
       i_max = index;
       max = input;
   }
}

/**
 * Copy the octet buffer `gp_buff` into your input tensor in the proper
 * format.
 */
void
th_load_tensor(void)
{
    Xil_DCacheFlushRange((UINTPTR)src_mem, src_FEATURE_COUNT * sizeof(unsigned char));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, dst_FEATURE_COUNT * sizeof(unsigned char));

    //printf("src_mem_size: %li", src_mem_size);
    for (int i = 0; i < src_mem_size; i++) {//Init SRC mem with input data (32x32x3, 3072 uint8)
        src_mem[i] = (gp_buff[i]);
    }

    for (int i = 0; i < dst_mem_size; i++) {//Init DST mem with 0's
        dst_mem[i] = 0x00;
    }
    //malloc_stats();
}

/**
 * Perform a single inference.
 */
void
th_infer(void)
{
    Xil_DCacheFlushRange((UINTPTR)src_mem, src_FEATURE_COUNT * sizeof(unsigned char));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, dst_FEATURE_COUNT * sizeof(unsigned char));
    unsigned char *src_mem_i = src_mem;
    unsigned char *dst_mem_i = dst_mem;
    XResnet_axi_Set_in_V(&do_resnet, (unsigned)src_mem_i);
    XResnet_axi_Set_out_V(&do_resnet, (unsigned)dst_mem_i);
    //XResnet_axi_Set_batch(&do_resnet, 1);
    XResnet_axi_Start(&do_resnet);
    /* polling */
    while (!XResnet_axi_IsDone(&do_resnet));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, dst_FEATURE_COUNT * sizeof(unsigned char));
}

void
th_results(void)
{
    float *results  = NULL;
    size_t nresults = 0;
    /* USER CODE 1 BEGIN */
    // reset max, i_max
    max = -128;
    i_max = -1;
    float res_arr[10] = {0,0,0,0,0,0,0,0,0,0};
    results = res_arr;
    printf("SRC mem: ");
    for (int i =0; i < src_FEATURE_COUNT; i++){
    	printf("%i, ",(unsigned char) src_mem[i]);
    }
    printf("\r\nDST mem: ");
    for (int i =0; i < dst_FEATURE_COUNT; i++){
    	printf("%i, ",(unsigned char) dst_mem[i]);
    }
    printf("\r\n");
    printf("\r\nRaw Values: [");
    for (nresults = 0; nresults < dst_FEATURE_COUNT; ++nresults)
    {
      printf("%c", (unsigned char)dst_mem[nresults]);
    }
    printf("]\r\n");
    for(short i = 0; i < dst_FEATURE_COUNT; i++){
           getMax(dst_mem[i], i);
    	   printf("check %i",i);
    }
    printf("The max index is: %i\r\n", i_max);
    res_arr[i_max] = 1.0;

    /* USER CODE 1 END */
    /**
     * The results need to be printed back in exactly this forth_printf("m-results-[%0.3f]\r\n", result);mat; if easier
     * to just modify this loop than copy to results[] above, do that.
     */
    th_printf("m-results-[");
        for (size_t i = 0; i < nresults; i++)
        {
            /* N.B. Be sure %f is enabled in SDK */
            th_printf("%.3f", (float)results[i]);
            if (i < (nresults - 1))
            {
                th_printf(",");
            }
        }
        th_printf("]\r\n");
}
