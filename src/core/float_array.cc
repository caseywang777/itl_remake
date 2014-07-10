// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/float_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<float>;

FloatArray::FloatArray() = default;

FloatArray::FloatArray(size_t tuple_number)
    : internal::TypedArray<float>(tuple_number) {}

FloatArray::FloatArray(size_t tuple_number, float* data)
    : internal::TypedArray<float>(tuple_number, data) {}

FloatArray::FloatArray(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<float>(tuple_number, tuple_size) {}

FloatArray::FloatArray(size_t tuple_number, size_t tuple_size, float* data)
    : internal::TypedArray<float>(tuple_number, tuple_size, data) {}

FloatArray::~FloatArray() = default;

}  // namespace itl
