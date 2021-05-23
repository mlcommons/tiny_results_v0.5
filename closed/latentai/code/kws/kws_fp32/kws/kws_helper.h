/* Copyright 2020 The MLPerf Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
/// \file
/// \brief Keyword Spotting model settings.

#ifndef V0_1_KWS_HELPER_H_
#define V0_1_KWS_HELPER_H_

// All of these values are derived from the values used during model training,
// if you change your model you'll need to update these constants.
// constexpr int kNumCols = 1;
// constexpr int kNumRows = 640;

// constexpr int kAdInputSize = kNumCols * kNumRows;
constexpr int kKwsInputSize = 49 * 10;

// constexpr int kCategoryCount = 2;
// extern const char* kCategoryLabels[kCategoryCount];

#endif  // V0_1_KWS_HELPER_H_
