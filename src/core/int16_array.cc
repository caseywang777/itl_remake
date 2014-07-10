// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/int16_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<int16_t>;

Int16Array::Int16Array() = default;

Int16Array::Int16Array(size_t tuple_number)
    : internal::TypedArray<int16_t>(tuple_number) {}

Int16Array::Int16Array(size_t tuple_number, int16_t* data)
    : internal::TypedArray<int16_t>(tuple_number, data) {}

Int16Array::Int16Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<int16_t>(tuple_number, tuple_size) {}

Int16Array::Int16Array(size_t tuple_number, size_t tuple_size, int16_t* data)
    : internal::TypedArray<int16_t>(tuple_number, tuple_size, data) {}

Int16Array::~Int16Array() = default;

}  // namespace itl
