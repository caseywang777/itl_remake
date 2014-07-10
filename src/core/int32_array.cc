// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/int32_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<int32_t>;

Int32Array::Int32Array() = default;

Int32Array::Int32Array(size_t tuple_number)
    : internal::TypedArray<int32_t>(tuple_number) {}

Int32Array::Int32Array(size_t tuple_number, int32_t* data)
    : internal::TypedArray<int32_t>(tuple_number, data) {}

Int32Array::Int32Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<int32_t>(tuple_number, tuple_size) {}

Int32Array::Int32Array(size_t tuple_number, size_t tuple_size, int32_t* data)
    : internal::TypedArray<int32_t>(tuple_number, tuple_size, data) {}

Int32Array::~Int32Array() = default;

}  // namespace itl
