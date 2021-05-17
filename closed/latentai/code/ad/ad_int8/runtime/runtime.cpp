/// \file
/// \brief Model runner for TVM

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
#include <runtime/runtime.h>
#pragma once

using namespace std;

rt::ModelRunner::ModelRunner(std::string model_path) {
    dtype_code = kDLInt;
    dtype_bits = 8;
    dtype_lanes = 1;
    device_type = kDLCPU;
    device_id = 0;
    in_ndim = 2;
    in_size = 640;
    out_size = 640;
    input_name = "input_1";

    DLContext ctx{kDLCPU, 0};
    mod_factory = tvm::runtime::Module::LoadFromFile(model_path);
    gmod = mod_factory.GetFunction("default")(ctx);
    set_input = gmod.GetFunction("set_input");
    get_output = gmod.GetFunction("get_output");
    run = gmod.GetFunction("run");
}

void rt::ModelRunner::invoke() {
    run();
}

void rt::ModelRunner::setInput() {
    cout << "setting input" << endl;
    set_input(input_name, tvm_input);
}

void rt::ModelRunner::createNDArray(int8_t *data) {
   cout << "entering in createndarray" << endl;
   cout << "our data is size: " << sizeof(data) << endl;
    TVMArrayAlloc(in_shape, in_ndim, dtype_code, dtype_bits, dtype_lanes,
                    device_type, device_id, &tvm_input);
    cout << "allocated array with size: " << sizeof(tvm_input) << endl;
    TVMArrayCopyFromBytes(tvm_input, data, in_shape[1]*in_shape[2]*sizeof(int8_t));
    cout << "bytes copied" << endl;
}

int8_t* rt::ModelRunner::getOutput() {
    cout << "attempting to get output" << endl;
    tvm::runtime::NDArray out = get_output(0);
    int8_t* y_iter = static_cast<int8_t*>(out->data);
    return y_iter;
}

int rt::ModelRunner::input_size() { return in_size; }

int rt::ModelRunner::output_size() { return out_size; }

void rt::ModelRunner::cleanUp() { TVMArrayFree(tvm_input); }