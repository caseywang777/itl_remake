// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_ABSTRACT_ARRAY_H_
#define CORE_ABSTRACT_ARRAY_H_

#include "core/core_export.h"

namespace itl {

class CORE_EXPORT AbstractArray {
 public:
  virtual ~AbstractArray() = default;

 protected:
  AbstractArray() = default;
  AbstractArray(const AbstractArray& rhs) = delete;
  AbstractArray& operator=(const AbstractArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_ABSTRACT_ARRAY_H_
