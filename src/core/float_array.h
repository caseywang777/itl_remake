// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_FLOAT_ARRAY_H_
#define CORE_FLOAT_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT FloatArray : public internal::TypedArray<float> {
 public:
  FloatArray();
  explicit FloatArray(size_t tuple_number);
  FloatArray(size_t tuple_number, float* data);
  FloatArray(size_t tuple_number, size_t tuple_size);
  FloatArray(size_t tuple_number, size_t tuple_size, float* data);

  virtual ~FloatArray();

  virtual int DataType() const { return kFloat; }

  float DataTypeMin() const { return kFloatMin; }
  float DataTypeMax() const { return kFloatMax; }

 private:
  FloatArray(const FloatArray& rhs) = delete;
  FloatArray& operator=(const FloatArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_FLOAT_ARRAY_H_
