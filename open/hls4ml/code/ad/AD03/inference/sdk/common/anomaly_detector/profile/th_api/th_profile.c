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
//#include <ap_fixed.h>
#include <math.h>
/* From profile/ee_buffer.c */
extern uint8_t *gp_buff;
extern size_t   g_buff_size;
extern size_t   g_buff_pos;

#include "../../src.h"
#include "../../dst.h"
float mse(signed char a[], signed char b[], int size) {
	float error = 0;
	for (int i = 0; i < size; i++) {
		error += pow((b[i] - a[i]), 2);
	}
	return error / size;
}
float used_floats[128];
/**
 * Copy the octet buffer `gp_buff` into your input tensor in the proper
 * format.
 */
void
th_load_tensor(void)
{

    init_platform();
    init_accelerators();
    Xil_DCacheFlushRange((UINTPTR)src_mem, 128 * sizeof(unsigned char));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));

	//XAnomaly_detector_axi_Set_in_V(&do_anomaly_detector, (unsigned)src_mem);
	//XAnomaly_detector_axi_Set_out_V(&do_anomaly_detector, (unsigned)dst_mem);
	//XAnomaly_detector_axi_Set_batch(&do_anomaly_detector, 1);

	float data_flt = 0.0;
	int skip = 4; // take only every nth frame, where n = skip-1
	slices = 4;
	bins = 128;
	float flt_buffer[slices*bins];
	for (int i = 0; i < 512*floatsize; i+=floatsize){
		memcpy(&data_flt,&gp_buff[i],(int)floatsize);
		flt_buffer[i/(int)floatsize] = (signed char) round(data_flt); //data_flt;
		//printf("Loaded %.3f into float buffer at pos %i\r\n",data_flt,(i/(int)floatsize));
	}
	//printf("g_buff_size: %i ",g_buff_size);
	//printf("src_mem_size: %i\r\n",src_mem_size);




	for (int i=0; i < slices; i++){
	  for (int j=0; j < bins; j+=skip){
	  //printf("Destination pos %i, src pos %i\r\n",((i*(bins/skip)+(j/skip))),(i*bins+j));
	  src_mem[((i*(bins/skip)+(j/skip)))] = (signed char)flt_buffer[(i*bins+j)];
	  used_floats[((i*(bins/skip)+(j/skip)))]=flt_buffer[(i*bins+j)];
	  }
	}

	/*
	   for (int i = 0; i < dst_mem_size; i++) {//Init DST mem with 0's
	       src_mem[i] = src_data[i];
	    }
	*/
    //for (int i = 0; i <= slices; i+=skip) { //Load input data, number of features = slices/bins (4x128 in our case), only loading every nth
    	//printf("%i :[",i);
    	//for (int j=0; j < bins; j++){
        	//printf(" %i,",j); //TODO FIXME
        	//src_mem[i*slices+j] = (signed char)flt_buffer[i*j]; //src_mem = 0-127, flt_buffer = 0-511, skip all but every 4th mel bin
        	//printf("Loaded data %i, orig float %.3f at input %i\r\n",(int8_t)src_mem[i*(j/skip)],flt_buffer[i*j], i*(j/skip));
    	//}
    	//printf("]\r\n");
   // }
   /*
	for (int i = 0; i < dst_mem_size; i++) {//Init DST mem with 0's
       src_mem[i] = 0x00;
    }
    */
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
	/*
	//start accelerator

    //unsigned char *src_mem_i = src_mem;
    //unsigned char *dst_mem_i = dst_mem;
	//printf("INFO: SRC @%p\r\n", src_mem_i);
	//printf("INFO: DST @%p\r\n", dst_mem_i);
    Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));

    XAnomaly_detector_axi_Set_in_V(&do_anomaly_detector, (unsigned)src_mem);
    XAnomaly_detector_axi_Set_out_V(&do_anomaly_detector, (unsigned)dst_mem);
    XAnomaly_detector_axi_Set_batch(&do_anomaly_detector, 1);

    XAnomaly_detector_axi_Start(&do_anomaly_detector);
    /* polling */
    //printf("Running Accelerator");
    /*
	while (!XAnomaly_detector_axi_IsDone(&do_anomaly_detector));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));
    */
	//printf("INFO: %s\n\r", __func__);
	//start accelerator
    //init_platform();
    //init_accelerators();


    Xil_DCacheFlushRange((UINTPTR)src_mem, 128 * sizeof(unsigned char));
    Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));
    unsigned char *src_mem_i = src_mem;
    unsigned char *dst_mem_i = dst_mem;
	//printf("INFO: SRC @%p\r\n", src_mem_i);
	//printf("INFO: DST @%p\r\n", dst_mem_i);
    XAnomaly_detector_axi_Set_in_V(&do_anomaly_detector, (unsigned)src_mem_i);
    XAnomaly_detector_axi_Set_out_V(&do_anomaly_detector, (unsigned)dst_mem_i);
    XAnomaly_detector_axi_Set_batch(&do_anomaly_detector, 1);
    XAnomaly_detector_axi_Start(&do_anomaly_detector);
    /* polling */
    while (!XAnomaly_detector_axi_IsDone(&do_anomaly_detector));
    //Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));
    //for(size_t i = 0; i < src_FEATURE_COUNT; i++) {
    //	printf("INFO: DST @%p:  %d\r\n", dst_mem + i, (signed char) dst_mem[i]);
    //}
}

void
th_results(void)
{
    float *results  = NULL;
    size_t nresults = 0;
    /* USER CODE 1 BEGIN */

    float result = 0;
    float sum = 0.0;
    float error = 0.0;
    Xil_DCacheFlushRange((UINTPTR)dst_mem, 128 * sizeof(unsigned char));
    /* Populate results[] and n from the fp32 prediction tensor. */
    //for(size_t i = 0; i < src_FEATURE_COUNT; i++){ //find the error score of each feature, then average over all features
    	//printf("INFO: Iteration %i\r\n",(i/floatsize));
    	//printf("INFO: FLT  %.3f ",(used_floats[i]));
    	//printf("INFO: SRC Mem:  %i",((signed char)src_mem[i]));
    	//printf(" DST Mem:  %i\r\n",((signed char)dst_mem[i]));
    	//printf(" DST Data:  %i\r\n",((signed char)dst_data[i]));
    	//error += ((signed char)src_mem[i]-(signed char)dst_mem[i])*((signed char)src_mem[i]-(signed char)dst_mem[i]);
    	//int diff = (signed char)src_mem[i]-(signed char)dst_mem[i];
    	//error += powf((float)diff,2);
    //}
    /*
    printf("[");
    for(size_t i = 0; i < src_FEATURE_COUNT; i++){
    	printf("%i, ",((signed char)src_mem[i]));
    }
    printf("]/r/n");
    */
    float mse_val = mse(dst_mem,src_mem,128);//error/128.0;

    //printf("INFO: Anomaly Score (MSE): %.3f\r\n",mse_val);
    result = mse_val;

    /* USER CODE 1 END */
    /**
     * The results need to be printed back in exactly this forth_printf("m-results-[%0.3f]\r\n", result);mat; if easier
     * to just modify this loop than copy to results[] above, do that.
     */
    th_printf("m-results-[%0.3f]\r\n", result);
}
