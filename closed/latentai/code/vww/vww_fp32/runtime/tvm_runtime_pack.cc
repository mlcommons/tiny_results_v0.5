/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "/home/pi/tvm/src/runtime/c_runtime_api.cc"
#include "/home/pi/tvm/src/runtime/cpu_device_api.cc"
#include "/home/pi/tvm/src/runtime/file_utils.cc"
#include "/home/pi/tvm/src/runtime/library_module.cc"
#include "/home/pi/tvm/src/runtime/logging.cc"
#include "/home/pi/tvm/src/runtime/module.cc"
#include "/home/pi/tvm/src/runtime/ndarray.cc"
#include "/home/pi/tvm/src/runtime/object.cc"
#include "/home/pi/tvm/src/runtime/registry.cc"
#include "/home/pi/tvm/src/runtime/thread_pool.cc"
#include "/home/pi/tvm/src/runtime/threading_backend.cc"
#include "/home/pi/tvm/src/runtime/workspace_pool.cc"

#include "/home/pi/tvm/src/runtime/container.cc"
#include "/home/pi/tvm/src/runtime/contrib/sort/sort.cc"
#include "/home/pi/tvm/src/runtime/dso_library.cc"

// Graph runtime
#include "/home/pi/tvm/src/runtime/graph_executor/graph_executor.cc"
#include "/home/pi/tvm/src/runtime/graph_executor/graph_executor_factory.cc"


