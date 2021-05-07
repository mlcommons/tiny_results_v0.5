/**
 * !!!!!! Don't Forget !!!!!!
 *  Set Heap Size in ldscript.ld to 0x1000000 (16MB)
 * !!!!!! Don't Forget !!!!!!
 */

#include "xresnet_axi.h"  /* accelerator */
#include "stdio.h"       /* printf */
#include "unistd.h"      /* sleep */
#include "stdlib.h"
#include "malloc.h"
#include "xil_io.h"      /* peripheral read/write wrappers */
//#include "xtime_l.h"     /* to measure performance of the system */
#include "platform.h"    /* platform init/cleanup functions */
#include "xil_cache.h"   /* enable/disable caches etc */
#include "xil_printf.h"  /* UART debug print functions */
#include "xparameters.h" /* peripherals base addresses */

#include "monitor/ee_main.h"

//#include "src.h"
//#include "dst.h"

#define __DEBUG__

//#define src_FEATURE_COUNT 3072
//#define dst_FEATURE_COUNT 10
#define src_SAMPLE_COUNT 10
#define dst_SAMPLE_COUNT 10



#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define SHORT_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define SHORT_TO_BINARY(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x800 ? '1' : '0'), \
  (byte & 0x400 ? '1' : '0'), \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


#define MAX_PRINT_ELEMENTS (4)

#define ITERATION_FACTOR (1)

const unsigned INPUT_N_ELEMENTS = src_SAMPLE_COUNT*src_FEATURE_COUNT;
const unsigned OUTPUT_N_ELEMENTS = dst_SAMPLE_COUNT*dst_FEATURE_COUNT;

/* the top of the hill :-) */
int main(int argc, char** argv)
{

    /* ****** TEST HARNESS ******* */
    xil_printf("INFO: Initalizing EEMBC Test Harness\r\n");
    //Initalize the test harness
    ee_benchmark_initialize();

    //Pass UART input to the test harness command parser
    xil_printf("INFO: Handing off to EEMBC Test Harness Command Parser!\r\n");
    while (true) { //Optimize me! TODO Is there a more power efficient way to do this? does it matter?
    	ee_serial_callback(inbyte());
    }

    cleanup_platform();

    return 0;
}
