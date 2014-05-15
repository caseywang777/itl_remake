// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_MATRIX4_IMPL_H_
#define MATH_TYPED_MATRIX4_IMPL_H_

#include "math/typed_matrix4.h"

#include <cassert>

namespace itl {
namespace internal {

template <typename Type>
TypedMatrix4<Type>::TypedMatrix4()
    : n00_(1.0), n10_(0.0), n20_(0.0), n30_(0.0),
      n01_(0.0), n11_(1.0), n21_(0.0), n31_(0.0),
      n02_(0.0), n12_(0.0), n22_(1.0), n32_(0.0),
      n03_(0.0), n13_(0.0), n23_(0.0), n33_(1.0) {}

template <typename Type>
TypedMatrix4<Type>::TypedMatrix4(
    const Type& n00, const Type& n01, const Type& n02, const Type& n03,
    const Type& n10, const Type& n11, const Type& n12, const Type& n13,
    const Type& n20, const Type& n21, const Type& n22, const Type& n23,
    const Type& n30, const Type& n31, const Type& n32, const Type& n33)
    : n00_(n00), n10_(n10), n20_(n20), n30_(n30),
      n01_(n01), n11_(n11), n21_(n21), n31_(n31),
      n02_(n02), n12_(n12), n22_(n22), n32_(n32),
      n03_(n03), n13_(n13), n23_(n23), n33_(n33) {}

template <typename Type>
TypedMatrix4<Type>::~TypedMatrix4() = default;

template <typename Type>
TypedMatrix4<Type>::TypedMatrix4(const TypedMatrix4& rhs) = default;

template <typename Type>
template <typename InnerType>
TypedMatrix4<Type>::TypedMatrix4(const TypedMatrix4<InnerType>& rhs)
    : n00_(rhs.get(0, 0)), n10_(rhs.get(1, 0)), n20_(rhs.get(2, 0)),
      n30_(rhs.get(3, 0)),
      n01_(rhs.get(0, 1)), n11_(rhs.get(1, 1)), n21_(rhs.get(2, 1)),
      n31_(rhs.get(3, 1)),
      n02_(rhs.get(0, 2)), n12_(rhs.get(1, 2)), n22_(rhs.get(2, 2)),
      n32_(rhs.get(3, 2)),
      n03_(rhs.get(0, 3)), n13_(rhs.get(1, 3)), n23_(rhs.get(2, 3)),
      n33_(rhs.get(3, 3)) {}

template <typename Type>
TypedMatrix4<Type>& TypedMatrix4<Type>::operator=(
    const TypedMatrix4& rhs) = default;

template <typename Type>
template <typename InnerType>
TypedMatrix4<Type>& TypedMatrix4<Type>::operator=(
    const TypedMatrix4<InnerType>& rhs) {
  n00_ = rhs.get(0, 0); n10_ = rhs.get(1, 0); n20_ = rhs.get(2, 0);
  n30_ = rhs.get(3, 0);
  n01_ = rhs.get(0, 1); n11_ = rhs.get(1, 1); n21_ = rhs.get(2, 1);
  n31_ = rhs.get(3, 1);
  n02_ = rhs.get(0, 2); n12_ = rhs.get(1, 2); n22_ = rhs.get(2, 2);
  n32_ = rhs.get(3, 2);
  n03_ = rhs.get(0, 3); n13_ = rhs.get(1, 3); n23_ = rhs.get(2, 3);
  n33_ = rhs.get(3, 3);
  return *this;
}

template <typename Type>
TypedMatrix4<Type>& TypedMatrix4<Type>::set_from_array(const Type* begin,
                                                       const Type* end) {
  assert((end - begin) == 16);
  for (size_t i = 0; i != 16; ++i)
    elements_[i] = *(begin + i);
  return *this;
}

template <typename Type>
TypedMatrix4<Type>& TypedMatrix4<Type>::set(
    const Type& n00, const Type& n01, const Type& n02, const Type& n03,
    const Type& n10, const Type& n11, const Type& n12, const Type& n13,
    const Type& n20, const Type& n21, const Type& n22, const Type& n23,
    const Type& n30, const Type& n31, const Type& n32, const Type& n33) {
  n00_ = n00; n10_ = n10; n20_ = n20; n30_ = n30;
  n01_ = n01; n11_ = n11; n21_ = n21; n31_ = n31;
  n02_ = n02; n12_ = n12; n22_ = n22; n32_ = n32;
  n03_ = n03; n13_ = n13; n23_ = n23; n33_ = n33;
  return *this;
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_MATRIX4_IMPL_H_
