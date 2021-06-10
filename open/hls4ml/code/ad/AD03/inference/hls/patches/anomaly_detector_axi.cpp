#include "anomaly_detector_axi.h"

#if 0
void anomaly_detector_axi(
        input_axi_t in[N_IN],
        output_axi_t out[N_OUT]
        ){

#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE m_axi depth=N_IN port=in offset=slave bundle=IN_BUS
#pragma HLS INTERFACE m_axi depth=N_OUT port=out offset=slave bundle=OUT_BUS

    unsigned short in_size = 0;
    unsigned short out_size = 0;

    input_t in_local[N_IN];
    result_t out_local[N_OUT];

    for(unsigned i = 0; i < N_IN; i++){
#pragma HLS UNROLL
        in_local[i] = in[i]; // Read input with cast
    }

    anomaly_detector(in_local, out_local, in_size, out_size);

    for(unsigned i = 0; i < N_OUT; i++){
#pragma HLS UNROLL
        out[i] = out_local[i]; // Write output with cast
    }
}
#else

void load_axi(input_axi_t axi_in_local[AXI_DEPTH_IN], input_axi_t in[AXI_DEPTH_IN * 197], unsigned b) {
#pragma HLS INLINE off
    LOAD:
            for (unsigned i = 0; i < AXI_DEPTH_IN; i++) {
#pragma HLS PIPELINE
                axi_in_local[i] = in[b * AXI_DEPTH_IN + i];
            }
}

void load_unpack(input_t model_in[N_IN], input_axi_t axi_in_local[AXI_DEPTH_IN], unsigned b) {
        {
#pragma HLS INLINE off

            LOAD_UNPACK_OUTER:
            for (unsigned i = 0; i < AXI_DEPTH_IN; i++) {
#pragma HLS UNROLL
                input_axi_t axi_data = axi_in_local[b * AXI_DEPTH_IN + i];
                LOAD_UNPACK_INNER:
                for (unsigned j = 0; j < W_COUNT_IN; j++) {
#pragma HLS UNROLL
                    input_t data;
                    data.range(W_IN-1, 0) = axi_data.range(((j+1)*W_IN)-1, j*W_IN);
                    model_in[i * W_COUNT_IN + j].range(W_IN- 1, 0) = data.range(W_IN-1, 0);
                }
            }
        }
}

void load(input_t model_in[N_IN], input_axi_t in[AXI_DEPTH_IN * 197], unsigned b) {
#pragma HLS INLINE off
    // Local copy of the packed data from the AXI ports
    input_axi_t axi_in_local[AXI_DEPTH_IN];
 //#pragma HLS STREAM variable=axi_in_local dim=1
#pragma HLS ARRAY_PARTITION variable=axi_in_local complete dim=1

    load_axi(axi_in_local, in, b);

    load_unpack(model_in, axi_in_local, b);
}


void store_pack(output_axi_t axi_out_local[AXI_DEPTH_OUT], result_t model_out[N_OUT], unsigned b) {
    #pragma HLS INLINE off

    STORE_PACK_OUTER:
                for (unsigned i = 0; i < AXI_DEPTH_OUT; i++) {
    #pragma HLS UNROLL
                    output_axi_t axi_data;
                    STORE_PACK_INNER:
                    for (unsigned j = 0; j < W_COUNT_OUT; j++) {
    #pragma HLS UNROLL
                        ap_fixed<8,8> data = model_out[i * W_COUNT_OUT + j]; // cast
                        axi_data.range(((j+1)*W_OUT)-1, j*W_OUT) = data.range(W_OUT-1, 0);
                    }
                    axi_out_local[i] = axi_data;
                }
}

void store_axi(output_axi_t out[AXI_DEPTH_OUT * 197], output_axi_t axi_out_local[AXI_DEPTH_OUT],  unsigned b) {
    #pragma HLS INLINE off
    STORE:
                for (unsigned i = 0; i < AXI_DEPTH_OUT; i++) {
    #pragma HLS PIPELINE
                    out[b * AXI_DEPTH_OUT + i] = axi_out_local[i];
                }
}

void store(output_axi_t out[AXI_DEPTH_OUT * 197], result_t model_out[N_OUT], unsigned b) {
#pragma HLS INLINE off


    output_axi_t axi_out_local[AXI_DEPTH_OUT];
#pragma HLS ARRAY_PARTITION variable=axi_out_local complete dim=1
//#pragma HLS STREAM variable=axi_out_local dim=1

    store_pack(axi_out_local,  model_out, b);

    store_axi(out, axi_out_local, b);
}

void anomaly_detector_axi(
        input_axi_t in[AXI_DEPTH_IN * 197],
        output_axi_t out[AXI_DEPTH_OUT * 197],
        unsigned batch
        ){
    const unsigned axi_in_size = AXI_DEPTH_IN * 197;
    const unsigned axi_out_size = AXI_DEPTH_OUT * 197;

#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE m_axi depth=axi_in_size port=in offset=slave bundle=IN_BUS
#pragma HLS INTERFACE m_axi depth=axi_out_size port=out offset=slave bundle=OUT_BUS
#pragma HLS INTERFACE s_axilite port=batch bundle=CTRL_BUS

    unsigned short in_size = 0;
    unsigned short out_size = 0;



    // Model input and output data
    input_t model_in[N_IN];
    result_t model_out[N_OUT];

BATCH:
    for (unsigned b = 0; b < MAX_BATCH_SIZE; b++) {
//#pragma HLS PIPELINE // issue: unroll everything in the hierarchy
//#pragma HLS DATAFLOW // issue: race conditions
        if (b >= batch) break;

#if 0
LOAD:
        {
#pragma HLS INLINE off
            for (unsigned i = 0; i < AXI_DEPTH_IN; i++) {
#pragma HLS UNROLL
                input_axi_t axi_data = in[b * N_IN + i];
                for (unsigned j = 0; j < W_COUNT_IN; j++) {
#pragma HLS UNROLL
                    input_t data;
                    data.range(W_IN-1, 0) = axi_data.range(((j+1)*W_IN)-1, j*W_IN);
                    model_in[i * W_COUNT_IN + j].range(W_IN- 1, 0) = data.range(W_IN-1, 0);
                }
            }
        }
#else

        load(model_in, in, b);

#endif

        anomaly_detector(model_in, model_out, in_size, out_size);

#if 0
STORE:
        {
#pragma HLS INLINE off
            for (unsigned i = 0; i < AXI_DEPTH_OUT; i++) {
#pragma HLS UNROLL
                output_axi_t axi_data;
                for (unsigned j = 0; j < W_COUNT_OUT; j++) {
#pragma HLS UNROLL
                    result_t data = model_out[i * W_COUNT_OUT + j];
                    axi_data.range(((j+1)*W_OUT)-1, j*W_OUT) = data.range(W_OUT-1, 0);
                }
                out[b * N_OUT + i] = axi_data;
            }
        }
#else

       store(out, model_out, b);

#endif
    }

}
#endif
