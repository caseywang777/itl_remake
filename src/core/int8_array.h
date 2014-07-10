// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_INT8_ARRAY_H_
#define CORE_INT8_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Int8Array : public internal::TypedArray<int8_t> {
 public:
  Int8Array();
  explicit Int8Array(size_t tuple_number);
  Int8Array(size_t tuple_number, int8_t* data);
  Int8Array(size_t tuple_number, size_t tuple_size);
  Int8Array(size_t tuple_number, size_t tuple_size, int8_t* data);

  virtual ~Int8Array();

  virtual int DataType() const { return kInt8; }

  int8_t DataTypeMin() const { return kInt8Min; }
  int8_t DataTypeMax() const { return kInt8Max; }

 private:
  Int8Array(const Int8Array& rhs) = delete;
  Int8Array& operator=(const Int8Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_INT8_ARRAY_H_
