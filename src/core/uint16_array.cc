// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/uint16_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<uint16_t>;

Uint16Array::Uint16Array() = default;

Uint16Array::Uint16Array(size_t tuple_number)
    : internal::TypedArray<uint16_t>(tuple_number) {}

Uint16Array::Uint16Array(size_t tuple_number, uint16_t* data)
    : internal::TypedArray<uint16_t>(tuple_number, data) {}

Uint16Array::Uint16Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<uint16_t>(tuple_number, tuple_size) {}

Uint16Array::Uint16Array(size_t tuple_number, size_t tuple_size, uint16_t* data)
    : internal::TypedArray<uint16_t>(tuple_number, tuple_size, data) {}

Uint16Array::~Uint16Array() = default;

}  // namespace itl
