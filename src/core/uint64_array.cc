// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/uint64_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<uint64_t>;

Uint64Array::Uint64Array() = default;

Uint64Array::Uint64Array(size_t tuple_number)
    : internal::TypedArray<uint64_t>(tuple_number) {}

Uint64Array::Uint64Array(size_t tuple_number, uint64_t* data)
    : internal::TypedArray<uint64_t>(tuple_number, data) {}

Uint64Array::Uint64Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<uint64_t>(tuple_number, tuple_size) {}

Uint64Array::Uint64Array(size_t tuple_number, size_t tuple_size, uint64_t* data)
    : internal::TypedArray<uint64_t>(tuple_number, tuple_size, data) {}

Uint64Array::~Uint64Array() = default;

}  // namespace itl
