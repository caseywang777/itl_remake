// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/uint8_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<uint8_t>;

Uint8Array::Uint8Array() = default;

Uint8Array::Uint8Array(size_t tuple_number)
    : internal::TypedArray<uint8_t>(tuple_number) {}

Uint8Array::Uint8Array(size_t tuple_number, uint8_t* data)
    : internal::TypedArray<uint8_t>(tuple_number, data) {}

Uint8Array::Uint8Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<uint8_t>(tuple_number, tuple_size) {}

Uint8Array::Uint8Array(size_t tuple_number, size_t tuple_size, uint8_t* data)
    : internal::TypedArray<uint8_t>(tuple_number, tuple_size, data) {}

Uint8Array::~Uint8Array() = default;

}  // namespace itl
