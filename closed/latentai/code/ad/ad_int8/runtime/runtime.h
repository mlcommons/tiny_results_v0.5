/// \file
/// \brief Model runner for TVM

#ifndef RUNTIME_H
#define RUNTIME_H

#include <dlpack/dlpack.h>
#include <dmlc/io.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <tvm/runtime/module.h>
#include <tvm/runtime/packed_func.h>
#include <tvm/runtime/registry.h>
#include <tvm/runtime/container.h>
#include <cstdio>
#include <sys/time.h>

using namespace std;


namespace rt {

    class ModelRunner {
    private:
        int dtype_code;
        int dtype_bits;
        int dtype_lanes;
        int device_type;
        int device_id;
        int in_ndim;
        const int64_t in_shape[2] = {1, 640};
        const int64_t out_shape[2] = {1, 640};
        int in_size;
        int out_size;
        std::string input_name;
        DLTensor* tvm_input;
        tvm::runtime::Module mod_factory;
        tvm::runtime::Module gmod;
        tvm::runtime::PackedFunc set_input;
        tvm::runtime::PackedFunc get_output;
        tvm::runtime::PackedFunc run;

    public:
        // DLTensor* tvm_input;
        ModelRunner(std::string model_path);
        void invoke();
        void setInput();
        void createNDArray(int8_t *data);
        int8_t* getOutput();
        int input_size();

        int output_size();

        void cleanUp();
    };
}

#endif