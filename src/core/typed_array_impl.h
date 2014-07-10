// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_IMPL_H_
#define CORE_TYPED_ARRAY_IMPL_H_

#include "core/typed_array.h"

#include <cassert>
#include <algorithm>

namespace itl {
namespace internal {

template <typename Type>
TypedArray<Type>::~TypedArray() = default;

template <typename Type>
const AbstractArray* TypedArray<Type>::tuple(size_t tuple_id,
                                             double* begin, double* end) const {
  assert((end - begin) == tuple_size_);

  size_t element_id = tuple_id * tuple_size_;
  while (begin != end) *begin++ = static_cast<double>(data_[element_id++]);
  return this;
}

template <typename Type>
AbstractArray* TypedArray<Type>::set_tuple(size_t tuple_id,
                                           const double* begin,
                                           const double* end) {
  assert((end - begin) == tuple_size_);

  size_t element_id = tuple_id * tuple_size_;
  while (begin != end) data_[element_id++] = static_cast<Type>(*begin++);
  return this;
}

template <typename Type>
double TypedArray<Type>::MinValue() const {
  const Type* rp = data();
  return static_cast<double>(*std::min_element(rp, rp + size()));
}

template <typename Type>
double TypedArray<Type>::MaxValue() const {
  const Type* rp = data();
  return static_cast<double>(*std::max_element(rp, rp + size()));
}

template <typename Type>
std::pair<double, double> TypedArray<Type>::MinMaxValue() const {
  const Type* rp = data();
  auto minmax = std::minmax_element(rp, rp + size());
  return {static_cast<double>(*minmax.first),
          static_cast<double>(*minmax.second)};
}

template <typename Type>
TypedArray<Type>::TypedArray() = default;

template <typename Type>
TypedArray<Type>::TypedArray(size_t tuple_number)
    : AbstractArray(), tuple_number_(tuple_number),
      data_(new Type[tuple_number]) {}

template <typename Type>
TypedArray<Type>::TypedArray(size_t tuple_number, Type* data)
    : AbstractArray(), tuple_number_(tuple_number), data_(data) {
  data = nullptr;
}

template <typename Type>
TypedArray<Type>::TypedArray(size_t tuple_number, size_t tuple_size)
    : AbstractArray(), tuple_number_(tuple_number), tuple_size_(tuple_size),
      data_(new Type[tuple_number * tuple_size]) {}

template <typename Type>
TypedArray<Type>::TypedArray(size_t tuple_number, size_t tuple_size,
                             Type* data)
    : AbstractArray(), tuple_number_(tuple_number),
      tuple_size_(tuple_size), data_(data) {
  data = nullptr;
}

}  // namespace internal
}  // namespace itl

#endif  // CORE_TYPED_ARRAY_IMPL_H_
