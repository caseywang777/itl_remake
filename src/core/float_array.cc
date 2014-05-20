// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/float_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class TypedArray<float>;

FloatArray::FloatArray() = default;

FloatArray::FloatArray(const size_t tuple_number)
    : TypedArray<float>(tuple_number) {
}

FloatArray::FloatArray(const size_t tuple_number, const size_t tuple_size)
    : TypedArray<float>(tuple_number, tuple_size) {
}

FloatArray::FloatArray(const size_t tuple_number, const size_t tuple_size,
                       float* data)
    : TypedArray<float>(tuple_number, tuple_size, data) {
}

FloatArray::~FloatArray() = default;

}  // namespace itl
