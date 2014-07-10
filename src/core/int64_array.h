// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_INT64_ARRAY_H_
#define CORE_INT64_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Int64Array : public internal::TypedArray<int64_t> {
 public:
  Int64Array();
  explicit Int64Array(size_t tuple_number);
  Int64Array(size_t tuple_number, int64_t* data);
  Int64Array(size_t tuple_number, size_t tuple_size);
  Int64Array(size_t tuple_number, size_t tuple_size, int64_t* data);

  virtual ~Int64Array();

  virtual int DataType() const { return kInt64; }

  int64_t DataTypeMin() const { return kInt64Min; }
  int64_t DataTypeMax() const { return kInt64Max; }

 private:
  Int64Array(const Int64Array& rhs) = delete;
  Int64Array& operator=(const Int64Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_INT64_ARRAY_H_
