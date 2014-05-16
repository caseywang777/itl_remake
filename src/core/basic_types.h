// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_BASIC_TYPES_H_
#define CORE_BASIC_TYPES_H_

#include <cfloat>
#include <climits>
#include <cstdint>

namespace itl {

enum {kBit, kSchar, kUchar,
      kInt8, kInt16, kInt32, kInt64,
      kUint8, kUint16, kUint32, kUint64,
      kFloat, kDouble};

const signed char kScharMin = SCHAR_MIN;
const signed char kScharMax = SCHAR_MAX;
const unsigned char kUcharMax = UCHAR_MAX;
const int8_t kInt8Min = INT8_MIN;
const int8_t kInt8Max = INT8_MAX;
const int16_t kInt16Min = INT16_MIN;
const int16_t kInt16Max = INT16_MAX;
const int32_t kInt32Min = INT32_MIN;
const int32_t kInt32Max = INT32_MAX;
const int64_t kInt64Min = INT64_MIN;
const int64_t kInt64Max = INT64_MAX;
const uint8_t kUint8Max = UINT8_MAX;
const uint16_t kUint16Max = UINT16_MAX;
const uint32_t kUint32Max = UINT32_MAX;
const uint64_t kUint64Max = UINT64_MAX;
const float kFloatMin = FLT_MIN;
const float kFloatMax = FLT_MAX;
const double kDoubleMin = DBL_MIN;
const double kDoubleMax = DBL_MAX;

}  // namespace itl

#endif  // CORE_BASIC_TYPES_H_
