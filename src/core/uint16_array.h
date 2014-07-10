// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_UINT16_ARRAY_H_
#define CORE_UINT16_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Uint16Array : public internal::TypedArray<uint16_t> {
 public:
  Uint16Array();
  explicit Uint16Array(size_t tuple_number);
  Uint16Array(size_t tuple_number, uint16_t* data);
  Uint16Array(size_t tuple_number, size_t tuple_size);
  Uint16Array(size_t tuple_number, size_t tuple_size, uint16_t* data);

  virtual ~Uint16Array();

  virtual int DataType() const { return kUint16; }

  uint16_t DataTypeMin() const { return 0; }
  uint16_t DataTypeMax() const { return kUint16Max; }

 private:
  Uint16Array(const Uint16Array& rhs) = delete;
  Uint16Array& operator=(const Uint16Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_UINT16_ARRAY_H_
