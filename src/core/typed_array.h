// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_H_
#define CORE_TYPED_ARRAY_H_

#include <cstddef>
#include <memory>

#include "core/abstract_array.h"

namespace itl {
namespace internal {

template <typename Type>
class CORE_EXPORT TypedArray : public AbstractArray {
 private:
  size_t tuple_number_ = 0, tuple_size_ = 1;
  std::unique_ptr<Type[]> data_;
};

}  // namespace internal
}  // namespace itl

#endif  // CORE_TYPED_ARRAY_H_
