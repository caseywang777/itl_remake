// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/float_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<float>;

FloatArray::FloatArray(size_t tuple_number)
    : internal::TypedArray<float>(tuple_number) {}

}  // namespace itl
