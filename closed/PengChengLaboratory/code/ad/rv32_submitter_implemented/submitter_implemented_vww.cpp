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

#include "api/internally_implemented.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "util/quantization_helpers.h"
#include "util/tf_micro_model_runner.h"
#include "vww/vww_inputs.h"
#include "vww/vww_model_data.h"
#include "vww/vww_model_settings.h"

constexpr int kTensorArenaSize = 200 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

tflite::MicroModelRunner<int8_t, int8_t, 6> *runner;

// Implement this method to prepare for inference and preprocess inputs.
void th_load_tensor() {
  int8_t input[kVwwInputSize];

  size_t bytes = ee_get_buffer(reinterpret_cast<uint8_t *>(input),
                               kVwwInputSize * sizeof(int8_t));
  if (bytes / sizeof(int8_t) != kVwwInputSize) {
    th_printf("Input db has %d elemented, expected %d\n",
              bytes / sizeof(int8_t), kVwwInputSize);
    return;
  }

  for (int i = 0; i < bytes; i++) {
    input[i] -= 128;
  }

  runner->SetInput(input);
}

// Add to this method to return real inference results.
void th_results() {
  const int nresults = 3;
  /**
   * The results need to be printed back in exactly this format; if easier
   * to just modify this loop than copy to results[] above, do that.
   */
  th_printf("m-results-[");
  int kCategoryCount = 2;
  for (size_t i = 0; i < kCategoryCount; i++) {
    float converted =
        DequantizeInt8ToFloat(runner->GetOutput()[i], runner->output_scale(),
                              runner->output_zero_point());

    // Some platforms don't implement floating point formatting.
    th_printf("%0.3f", converted);
    if (i < (nresults - 1)) {
      th_printf(",");
    }
  }
  th_printf("]\r\n");
}

// Implement this method with the logic to perform one inference cycle.
void th_infer() { runner->Invoke(); }

/// \brief optional API.
void th_final_initialize(void) {
  static tflite::MicroMutableOpResolver<6> resolver;
  resolver.AddFullyConnected();
  resolver.AddConv2D();
  resolver.AddDepthwiseConv2D();
  resolver.AddReshape();
  resolver.AddSoftmax();
  resolver.AddAveragePool2D();

  static tflite::MicroModelRunner<int8_t, int8_t, 6> model_runner(
      g_person_detect_model_data, resolver, tensor_arena, kTensorArenaSize);
  runner = &model_runner;
}

void th_pre() {}
void th_post() {}

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

/* N.B.: Many embedded *printf SDKs do not support all format specifiers. */
int th_vprintf(const char *format, va_list ap) { return vprintf(format, ap); }
void th_printf(const char *p_fmt, ...) {
  va_list args;
  va_start(args, p_fmt);
  (void)th_vprintf(p_fmt, args); /* ignore return */
  va_end(args);
}

#include <rv_uart.h>

char th_getchar() 
{ 
  //return getchar(); 
  char buf[2];
  int32_t len = 0;
  extern DRIVER_USART *UART_Console;

  while (len < 1)
  {
    len = UART_Console->Receive(buf, 1); 
    __asm__ __volatile__("nop");
  }
 
  return buf[0];
}

//UnbufferedSerial pc(USBTX, USBRX);

void th_serialport_initialize(void)
{ 
  /*pc.baud(115200); */
}


#include <rv_timer.h>
#include <platform.h>

DRIVER_TIMER *TIMER0 = &driver_timer0;

volatile static uint32_t timer_cnt;
static int ticker_is_init = 0;

void output_cb (uint32_t event)
{
    uint32_t count, status;

    count = TIMER0->get_count();
    status = TIMER0->get_status();
    TIMER0->set_status(0);
    timer_cnt++;
}

unsigned long us_ticker_read()
{
  uint32_t dt ;
  if (!ticker_is_init)
  {
    ticker_is_init = 1;
    eu_interrupt_enable(RV32_TIMER0_IRQn);
    timer_cnt = 0;
    TIMER0->set_irq_cb(output_cb);
    TIMER0->set_count(0);
    TIMER0->configure(TIMx_CTRL_OVFIF_ENABLE_Msk|
                      (TIMER_MODE_FREERUN << TIMx_CTRL_MODE_Pos));
  }
  dt = (uint32_t)((timer_cnt * ((uint64_t)1 << 24)) / 48 + (uint64_t)TIMER0->get_count() / 48);
  return (dt);
}


void th_timestamp(void) {
  unsigned long microSeconds = 0ul;
  /* USER CODE 2 BEGIN */
  microSeconds = us_ticker_read();
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