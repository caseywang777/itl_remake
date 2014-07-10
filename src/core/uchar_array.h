// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_UCHAR_ARRAY_H_
#define CORE_UCHAR_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT UcharArray : public internal::TypedArray<unsigned char> {
 public:
  UcharArray();
  explicit UcharArray(size_t tuple_number);
  UcharArray(size_t tuple_number, unsigned char* data);
  UcharArray(size_t tuple_number, size_t tuple_size);
  UcharArray(size_t tuple_number, size_t tuple_size, unsigned char* data);

  virtual ~UcharArray();

  virtual int DataType() const { return kUchar; }

  unsigned char DataTypeMin() const { return '0'; }
  unsigned char DataTypeMax() const { return kUcharMax; }

 private:
  UcharArray(const UcharArray& rhs) = delete;
  UcharArray& operator=(const UcharArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_UCHAR_ARRAY_H_
