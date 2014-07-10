// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_UINT8_ARRAY_H_
#define CORE_UINT8_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT Uint8Array : public internal::TypedArray<uint8_t> {
 public:
  Uint8Array();
  explicit Uint8Array(size_t tuple_number);
  Uint8Array(size_t tuple_number, uint8_t* data);
  Uint8Array(size_t tuple_number, size_t tuple_size);
  Uint8Array(size_t tuple_number, size_t tuple_size, uint8_t* data);

  virtual ~Uint8Array();

  virtual int DataType() const { return kUint8; }

  uint8_t DataTypeMin() const { return 0; }
  uint8_t DataTypeMax() const { return kUint8Max; }

 private:
  Uint8Array(const Uint8Array& rhs) = delete;
  Uint8Array& operator=(const Uint8Array& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_UINT8_ARRAY_H_
