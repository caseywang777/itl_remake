// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/uint32_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<uint32_t>;

Uint32Array::Uint32Array() = default;

Uint32Array::Uint32Array(size_t tuple_number)
    : internal::TypedArray<uint32_t>(tuple_number) {}

Uint32Array::Uint32Array(size_t tuple_number, uint32_t* data)
    : internal::TypedArray<uint32_t>(tuple_number, data) {}

Uint32Array::Uint32Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<uint32_t>(tuple_number, tuple_size) {}

Uint32Array::Uint32Array(size_t tuple_number, size_t tuple_size, uint32_t* data)
    : internal::TypedArray<uint32_t>(tuple_number, tuple_size, data) {}

Uint32Array::~Uint32Array() = default;

}  // namespace itl
