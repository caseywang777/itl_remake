// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_SCHAR_ARRAY_H_
#define CORE_SCHAR_ARRAY_H_

#include "core/basic_types.h"
#include "core/typed_array.h"

namespace itl {

class CORE_EXPORT ScharArray : public internal::TypedArray<signed char> {
 public:
  ScharArray();
  explicit ScharArray(size_t tuple_number);
  ScharArray(size_t tuple_number, signed char* data);
  ScharArray(size_t tuple_number, size_t tuple_size);
  ScharArray(size_t tuple_number, size_t tuple_size, signed char* data);

  virtual ~ScharArray();

  virtual int DataType() const { return kSchar; }

  signed char DataTypeMin() const { return kScharMin; }
  signed char DataTypeMax() const { return kScharMax; }

 private:
  ScharArray(const ScharArray& rhs) = delete;
  ScharArray& operator=(const ScharArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_SCHAR_ARRAY_H_
