/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AUDIO_DSP_OPEN_SOURCE_PORTING_H_
#define AUDIO_DSP_OPEN_SOURCE_PORTING_H_

#include <iostream>
#include <cmath>
#include <string>

#define TYPED_TEST_SUITE TYPED_TEST_CASE
#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P

using std::string;

typedef uint8_t uint8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  TypeName& operator=(const TypeName&) = delete


template<typename T> struct MathLimits {
  // Not a number, i.e. result of 0/0.
  static const T kNaN;
  // Positive infinity, i.e. result of 1/0.
  static const T kPosInf;
  // Negative infinity, i.e. result of -1/0.
  static const T kNegInf;
};


template <> struct MathLimits<float> {
  static constexpr float kNaN = HUGE_VALF - HUGE_VALF;
  static constexpr float kPosInf = HUGE_VALF;
  static constexpr float kNegInf = -HUGE_VALF;
};

class MathUtil {
 public:
  enum QuadraticRootType {kNoRealRoots = 0, kAmbiguous = 1, kTwoRealRoots = 2};

  static QuadraticRootType RealRootsForQuadratic(long double a,
                                                 long double b,
                                                 long double c,
                                                 long double *r1,
                                                 long double *r2);
};


// TODO: glog actually includes a demangler function, but it isn't obvious how
//       to access it with our BUILD setup.
namespace util {
// Note that these don't do any demangling in the open source code.
bool Demangle(const char *mangled, char *out, int out_size);
string Demangle(const char* mangled);
}  // namespace util

#endif  // AUDIO_DSP_OPEN_SOURCE_PORTING_H_
