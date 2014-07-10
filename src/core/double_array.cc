// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/double_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<double>;

DoubleArray::DoubleArray() = default;

DoubleArray::DoubleArray(size_t tuple_number)
    : internal::TypedArray<double>(tuple_number) {}

DoubleArray::DoubleArray(size_t tuple_number, double* data)
    : internal::TypedArray<double>(tuple_number, data) {}

DoubleArray::DoubleArray(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<double>(tuple_number, tuple_size) {}

DoubleArray::DoubleArray(size_t tuple_number, size_t tuple_size, double* data)
    : internal::TypedArray<double>(tuple_number, tuple_size, data) {}

DoubleArray::~DoubleArray() = default;

}  // namespace itl
