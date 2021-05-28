/*
Copyright (C) EEMBC(R). All Rights Reserved

All EEMBC Benchmark Software are products of EEMBC and are provided under the
terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
are proprietary intellectual properties of EEMBC and its Members and is
protected under all applicable laws, including all applicable copyright laws.

If you received this EEMBC Benchmark Software without having a currently
effective EEMBC Benchmark License Agreement, you must discontinue use.

Copyright 2020 The MLPerf Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This file reflects a modified version of th_lib from EEMBC. The reporting logic
in th_results is copied from the original in EEMBC.
==============================================================================*/
/// \file
/// \brief C++ implementations of submitter_implemented.h

#include "api/submitter_implemented.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "runtime/runtime.h"
#include "api/internally_implemented.h"
#include "ad/ad_helper.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> // exit()
#include <stdio.h> // for perror()
#include <fstream>
#include <chrono>


using namespace std;

string model_path = "bin/ad_int8.so";
rt::ModelRunner model(model_path);

char output_buffer[30000];
int initialized = 0;
int serial_fd = 0;
char * PATH_TO_SERIAL = "/dev/ttyAMA0";
float input_pixels[kAdInputSize];
int8_t input_asint[kAdInputSize];

// Implement this method to prepare for inference and preprocess inputs.
void th_load_tensor() {


  size_t bytes = ee_get_buffer(reinterpret_cast<uint8_t *>(input_pixels),
                               kAdInputSize * sizeof(float));
  if (bytes / sizeof(float) != kAdInputSize) {
    th_printf("Input db has %d elemented, expected %d\n", bytes / sizeof(float),
              kAdInputSize);
    return;
  }

  float input_scale = 0.3910152316093445;
  int input_zero_point = 89;
  for (int i = 0; i < kAdInputSize; i++) {
    input_asint[i] = QuantizeFloatToInt8(
        input_pixels[i], input_scale, input_zero_point);
  }
  int arrSize = sizeof(input_asint)/sizeof(input_asint[0]);
  cout << "The size of the array is: " << arrSize;
  cout << "creating array size: " << sizeof(input_asint) << endl;
  model.createNDArray(input_asint);
  model.setInput();
  cout << "input is now set" << endl;
}

// Add to this method to return real inference results.
void th_results() {
  const int nresults = 640;
  float diffsum = 0;
  float result;
  
  int8_t* output = model.getOutput();

   for (size_t i = 0; i < nresults; i++) {
    float converted = DequantizeInt8ToFloat(output[i], 0.36449846625328064, 96);
    float diff = converted - input_pixels[i];
    diffsum += diff * diff;
  }
  diffsum /= nresults;
  result = diffsum;
  th_printf("m-results-[%0.3f]\r\n", result);
}

// Implement this method with the logic to perform one inference cycle.
void th_infer() { 
  model.invoke();
}

/// \brief optional API.
void th_final_initialize(void) {}

void th_pre() {}
void th_post() {model.cleanUp();}

void th_command_ready(char volatile *p_command) {
  p_command = p_command;
  ee_serial_command_parser_callback((char *)p_command);
}

// th_libc implementations.
int th_strncmp(const char *str1, const char *str2, size_t n) {
  return strncmp(str1, str2, n);
}

char *th_strncpy(char *dest, const char *src, size_t n) {
  return strncpy(dest, src, n);
}

size_t th_strnlen(const char *str, size_t maxlen) {
  return strnlen(str, maxlen);
}

char *th_strcat(char *dest, const char *src) { return strcat(dest, src); }

char *th_strtok(char *str1, const char *sep) { return strtok(str1, sep); }

int th_atoi(const char *str) { return atoi(str); }

void *th_memset(void *b, int c, size_t len) { return memset(b, c, len); }

void *th_memcpy(void *dst, const void *src, size_t n) {
  return memcpy(dst, src, n);
}


void die(int fd, char *msg) {
  perror(msg);
  close(fd);
  exit(1);
}


void leip_initialize() {
  serial_fd = open(PATH_TO_SERIAL, O_RDWR);
  if(serial_fd == -1) { die(serial_fd, "open()"); }
  initialized = 1;
}

int th_vprintf(const char *format, va_list ap) {
  int result;
  int out_len;
  int L_WRITE = 1;
  if (!initialized) {
    leip_initialize();
  }
  result = vsprintf(output_buffer, format, ap);
  out_len = strlen(output_buffer);
  for (int i = 0; i < out_len; i++) {
    if(write(serial_fd, output_buffer+i, L_WRITE) != L_WRITE) {
      die(serial_fd, "write()");
    }
  }
  return result;
}

void th_printf(const char *p_fmt, ...) {
  va_list args;
  va_start(args, p_fmt);
  (void)th_vprintf(p_fmt, args); /* ignore return */
  va_end(args);
}

char th_getchar() {
  int bytesread;
  char buffer[1];
  bytesread = read(serial_fd, buffer, 1);
  if(bytesread != 1) { die(serial_fd, "read()"); }
  // return getchar();
  return buffer[0];
}

void th_serialport_initialize(void) {}

void th_timestamp(void) {
  unsigned long microSeconds = 0ul;
  /* USER CODE 2 BEGIN */
  microSeconds = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
  /* USER CODE 2 END */
  /* This message must NOT be changed. */
  th_printf(EE_MSG_TIMESTAMP, microSeconds);
}

void th_timestamp_initialize(void) {
  /* USER CODE 1 BEGIN */
  // Setting up BOTH perf and energy here
  /* USER CODE 1 END */
  /* This message must NOT be changed. */
  th_printf(EE_MSG_TIMESTAMP_MODE);
  /* Always call the timestamp on initialize so that the open-drain output
     is set to "1" (so that we catch a falling edge) */
  th_timestamp();
}
