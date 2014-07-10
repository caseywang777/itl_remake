// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_UINT64_ARRAY_H_
#define CORE_UINT64_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Uint64Array : public internal::TypedArray<uint64_t> {
 public:
  Uint64Array();
  explicit Uint64Array(size_t tuple_number);
  Uint64Array(size_t tuple_number, uint64_t* data);
  Uint64Array(size_t tuple_number, size_t tuple_size);
  Uint64Array(size_t tuple_number, size_t tuple_size, uint64_t* data);

  virtual ~Uint64Array();

  virtual int DataType() const { return kUint64; }

  uint64_t DataTypeMin() const { return 0; }
  uint64_t DataTypeMax() const { return kUint64Max; }

 private:
  Uint64Array(const Uint64Array& rhs) = delete;
  Uint64Array& operator=(const Uint64Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_UINT64_ARRAY_H_
