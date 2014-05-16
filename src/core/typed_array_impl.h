// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_IMPL_H_
#define CORE_TYPED_ARRAY_IMPL_H_

#include "core/typed_array.h"

namespace itl {
namespace internal {

template <typename Type>
Type* TypedArray<Type>::data() { return data_.get(); }

template <typename Type>
const Type* TypedArray<Type>::data() const { return data_.get(); }

template <typename Type>
TypedArray<Type>::TypedArray(const size_t tuple_number)
    : AbstractArray(), tuple_number_(tuple_number),
      data_(new Type[tuple_number]) {}

}  // namespace internal
}  // namespace itl

#endif  // CORE_TYPED_ARRAY_IMPL_H_
