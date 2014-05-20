// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_IMPL_H_
#define CORE_TYPED_ARRAY_IMPL_H_

#include "core/typed_array.h"

#include <cassert>
#include <algorithm>

namespace itl {

template <typename Type>
void TypedArray<Type>::tuple(const size_t tuple_id,
                             double* begin, double* end) const {
  // TODO(wenbin): figure out how to deal with different tuple size.
  assert((end - begin) == tuple_size_);

  size_t element_id = tuple_id * tuple_size_;
  while (begin != end) *begin++ = static_cast<double>(data_[element_id++]);
}

template <typename Type>
void TypedArray<Type>::set_tuple(const size_t tuple_id,
                                 const double* begin, const double* end) {
  // TODO(wenbin): figure out how to deal with different tuple size.
  assert((end - begin) == tuple_size_);

  size_t element_id = tuple_id * tuple_size_;
  while (begin != end) data_[element_id++] = static_cast<Type>(*begin++);
}

template <typename Type>
void TypedArray<Type>::Clear() {
  // TODO(wenbin): do we really need clear?
  tuple_number_ = 0;
  tuple_size_ = 1;
  data_.reset();
}

template <typename Type>
void TypedArray<Type>::Resize(const size_t tuple_number,
                              const size_t tuple_size) {
  // TODO(wenbin): do we need to keep the old data?
  tuple_number_ = tuple_number;
  tuple_size_ = tuple_size;
  data_.reset(new Type[tuple_number * tuple_size]);
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

// TODO(wenbin): implement get min and max magnitude functions.
template <typename Type>
double TypedArray<Type>::MinMagnitude() const {
  return 0.0;
}

template <typename Type>
double TypedArray<Type>::MaxMagnitude() const {
  return 0.0;
}

template <typename Type>
std::pair<double, double> TypedArray<Type>::MinMaxMagnitude() const {
  return {0.0, 0.0};
}

template <typename Type>
Type* TypedArray<Type>::data() { return data_.get(); }

template <typename Type>
const Type* TypedArray<Type>::data() const { return data_.get(); }

template <typename Type>
Type& TypedArray<Type>::operator[](const size_t n) {
  return data_[n];
}

template <typename Type>
const Type& TypedArray<Type>::operator[](const size_t n) const {
  return data_[n];
}

template <typename Type>
TypedArray<Type>::TypedArray() = default;

template <typename Type>
TypedArray<Type>::TypedArray(const size_t tuple_number)
    : AbstractArray(), tuple_number_(tuple_number),
      data_(new Type[tuple_number]) {
}

template <typename Type>
TypedArray<Type>::TypedArray(const size_t tuple_number,
                             const size_t tuple_size)
    : AbstractArray(), tuple_number_(tuple_number),
      tuple_size_(tuple_size), data_(new Type[tuple_number * tuple_size]) {
}

template <typename Type>
TypedArray<Type>::TypedArray(const size_t tuple_number, const size_t tuple_size,
                             Type* data)
    : AbstractArray(), tuple_number_(tuple_number), tuple_size_(tuple_size),
      data_(data) {
  data = nullptr;
}

template <typename Type>
TypedArray<Type>::~TypedArray() = default;

}  // namespace itl

#endif  // CORE_TYPED_ARRAY_IMPL_H_
