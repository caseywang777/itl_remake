// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/int8_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<int8_t>;

Int8Array::Int8Array() = default;

Int8Array::Int8Array(size_t tuple_number)
    : internal::TypedArray<int8_t>(tuple_number) {}

Int8Array::Int8Array(size_t tuple_number, int8_t* data)
    : internal::TypedArray<int8_t>(tuple_number, data) {}

Int8Array::Int8Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<int8_t>(tuple_number, tuple_size) {}

Int8Array::Int8Array(size_t tuple_number, size_t tuple_size, int8_t* data)
    : internal::TypedArray<int8_t>(tuple_number, tuple_size, data) {}

Int8Array::~Int8Array() = default;

}  // namespace itl
