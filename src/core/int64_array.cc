// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/int64_array.h"

#include "core/typed_array_impl.h"

namespace itl {

template class internal::TypedArray<int64_t>;

Int64Array::Int64Array() = default;

Int64Array::Int64Array(size_t tuple_number)
    : internal::TypedArray<int64_t>(tuple_number) {}

Int64Array::Int64Array(size_t tuple_number, int64_t* data)
    : internal::TypedArray<int64_t>(tuple_number, data) {}

Int64Array::Int64Array(size_t tuple_number, size_t tuple_size)
    : internal::TypedArray<int64_t>(tuple_number, tuple_size) {}

Int64Array::Int64Array(size_t tuple_number, size_t tuple_size, int64_t* data)
    : internal::TypedArray<int64_t>(tuple_number, tuple_size, data) {}

Int64Array::~Int64Array() = default;

}  // namespace itl
