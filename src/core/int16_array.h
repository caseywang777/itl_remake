// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_INT16_ARRAY_H_
#define CORE_INT16_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Int16Array : public internal::TypedArray<int16_t> {
 public:
  Int16Array();
  explicit Int16Array(size_t tuple_number);
  Int16Array(size_t tuple_number, int16_t* data);
  Int16Array(size_t tuple_number, size_t tuple_size);
  Int16Array(size_t tuple_number, size_t tuple_size, int16_t* data);

  virtual ~Int16Array();

  virtual int DataType() const { return kInt16; }

  int16_t DataTypeMin() const { return kInt16Min; }
  int16_t DataTypeMax() const { return kInt16Max; }

 private:
  Int16Array(const Int16Array& rhs) = delete;
  Int16Array& operator=(const Int16Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_INT16_ARRAY_H_
