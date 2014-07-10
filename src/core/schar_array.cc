// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/schar_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<signed char>;

ScharArray::ScharArray() = default;

ScharArray::ScharArray(size_t tuple_number)
    : internal::TypedArray<signed char>(tuple_number) {}

ScharArray::ScharArray(size_t tuple_number, signed char* data)
    : internal::TypedArray<signed char>(tuple_number, data) {}

ScharArray::ScharArray(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<signed char>(tuple_number, tuple_size) {}

ScharArray::ScharArray(size_t tuple_number, size_t tuple_size,
                       signed char* data)
    : internal::TypedArray<signed char>(tuple_number, tuple_size, data) {}

ScharArray::~ScharArray() = default;

}  // namespace itl
