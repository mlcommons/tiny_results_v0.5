#ifndef ANOMALY_DETECTOR_AXI_H_
#define ANOMALY_DETECTOR_AXI_H_

#include "anomaly_detector.h"

typedef layer14_t result_t;

#define CEILING_DIV(x, y) (((x) + (y) - 1) / (y) )

// Model dimensions
static const unsigned N_IN = 128;
static const unsigned N_OUT = 128;

// Max batch size
static const unsigned MAX_BATCH_SIZE = 197;

// Model word size
static const unsigned W_IN = 8;
static const unsigned W_OUT = 8;

// Width of the AXI busses. It is usually 32 or 64 on Zynq.
static const unsigned AXI_WIDTH = 64;

// Word count in a single AXI-width word.
static const unsigned W_COUNT_IN = (AXI_WIDTH / W_IN);
static const unsigned W_COUNT_OUT = (AXI_WIDTH / W_OUT);

// Depth of AXI busses given the model inputs and outputs.
static const unsigned AXI_DEPTH_IN = CEILING_DIV((W_IN * N_IN), AXI_WIDTH);
static const unsigned AXI_DEPTH_OUT = CEILING_DIV((W_OUT * N_OUT), AXI_WIDTH);

typedef ap_uint<AXI_WIDTH> input_axi_t;
typedef ap_uint<AXI_WIDTH> output_axi_t;

void anomaly_detector_axi(
        input_axi_t in[AXI_DEPTH_IN * MAX_BATCH_SIZE],
        output_axi_t out[AXI_DEPTH_OUT * MAX_BATCH_SIZE],
        unsigned batch
);

#endif
