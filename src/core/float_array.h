// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_FLOAT_ARRAY_H_
#define CORE_FLOAT_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT FloatArray : public TypedArray<float> {
 public:
  FloatArray();
  explicit FloatArray(const size_t tuple_number);
  FloatArray(const size_t tuple_number, const size_t tuple_size);
  FloatArray(const size_t tuple_number, const size_t tuple_size,
             float* data);
  virtual ~FloatArray();

  virtual int DataType() const { return kFloat; }

  float DataTypeMin() const { return kFloatMin; }
  float DataTypeMax() const { return kFloatMax; }

 private:
  FloatArray(const FloatArray&) = delete;
  FloatArray& operator=(const FloatArray&) = delete;
};

}  // namespace itl

#endif  // CORE_FLOAT_ARRAY_H_
