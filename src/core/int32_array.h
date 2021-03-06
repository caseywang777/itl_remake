// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_INT32_ARRAY_H_
#define CORE_INT32_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Int32Array : public internal::TypedArray<int32_t> {
 public:
  Int32Array();
  explicit Int32Array(size_t tuple_number);
  Int32Array(size_t tuple_number, int32_t* data);
  Int32Array(size_t tuple_number, size_t tuple_size);
  Int32Array(size_t tuple_number, size_t tuple_size, int32_t* data);

  virtual ~Int32Array();

  virtual int DataType() const { return kInt32; }

  int32_t DataTypeMin() const { return kInt32Min; }
  int32_t DataTypeMax() const { return kInt32Max; }

 private:
  Int32Array(const Int32Array& rhs) = delete;
  Int32Array& operator=(const Int32Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_INT32_ARRAY_H_
