// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_DOUBLE_ARRAY_H_
#define CORE_DOUBLE_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT DoubleArray : public internal::TypedArray<double> {
 public:
  DoubleArray();
  explicit DoubleArray(size_t tuple_number);
  DoubleArray(size_t tuple_number, double* data);
  DoubleArray(size_t tuple_number, size_t tuple_size);
  DoubleArray(size_t tuple_number, size_t tuple_size, double* data);

  virtual ~DoubleArray();

  virtual int DataType() const { return kDouble; }

  double DataTypeMin() const { return kDoubleMin; }
  double DataTypeMax() const { return kDoubleMax; }

 private:
  DoubleArray(const DoubleArray& rhs) = delete;
  DoubleArray& operator=(const DoubleArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_DOUBLE_ARRAY_H_
