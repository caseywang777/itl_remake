// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/uchar_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<unsigned char>;

UcharArray::UcharArray() = default;

UcharArray::UcharArray(size_t tuple_number)
    : internal::TypedArray<unsigned char>(tuple_number) {}

UcharArray::UcharArray(size_t tuple_number, unsigned char* data)
    : internal::TypedArray<unsigned char>(tuple_number, data) {}

UcharArray::UcharArray(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<unsigned char>(tuple_number, tuple_size) {}

UcharArray::UcharArray(size_t tuple_number, size_t tuple_size,
                       unsigned char* data)
    : internal::TypedArray<unsigned char>(tuple_number, tuple_size, data) {}

UcharArray::~UcharArray() = default;

}  // namespace itl
