// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_UINT32_ARRAY_H_
#define CORE_UINT32_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Uint32Array : public internal::TypedArray<uint32_t> {
 public:
  Uint32Array();
  explicit Uint32Array(size_t tuple_number);
  Uint32Array(size_t tuple_number, uint32_t* data);
  Uint32Array(size_t tuple_number, size_t tuple_size);
  Uint32Array(size_t tuple_number, size_t tuple_size, uint32_t* data);

  virtual ~Uint32Array();

  virtual int DataType() const { return kUint32; }

  uint32_t DataTypeMin() const { return 0; }
  uint32_t DataTypeMax() const { return kUint32Max; }

 private:
  Uint32Array(const Uint32Array& rhs) = delete;
  Uint32Array& operator=(const Uint32Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_UINT32_ARRAY_H_
