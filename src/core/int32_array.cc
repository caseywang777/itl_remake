// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/int32_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class TypedArray<int32_t>;

Int32Array::Int32Array() = default;

Int32Array::Int32Array(const size_t tuple_number)
    : TypedArray<int32_t>(tuple_number) {
}

Int32Array::Int32Array(const size_t tuple_number, const size_t tuple_size)
    : TypedArray<int32_t>(tuple_number, tuple_size) {
}

Int32Array::Int32Array(const size_t tuple_number, const size_t tuple_size,
                       int32_t* data)
    : TypedArray<int32_t>(tuple_number, tuple_size, data) {
}

Int32Array::~Int32Array() = default;

}  // namespace itl
