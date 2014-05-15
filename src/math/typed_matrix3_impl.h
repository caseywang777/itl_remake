// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_MATRIX3_IMPL_H_
#define MATH_TYPED_MATRIX3_IMPL_H_

#include "math/typed_matrix3.h"

#include <cassert>
#include <cmath>

#include "io/console.h"

namespace itl {
namespace internal {

template <typename Type>
TypedMatrix3<Type>& TypedMatrix3<Type>::set_from_array(const Type* begin,
                                                       const Type* end) {
  assert((end - begin) == 9);
  for (size_t i = 0; i != 9; ++i)
    elements_[i] = *(begin + i);
  return *this;
}

template <typename Type>
TypedMatrix3<Type>& TypedMatrix3<Type>::operator*=(const Type& scalar) {
  for (size_t i = 0; i != 9; ++i)
    elements_[i] *= scalar;
  return *this;
}

template <typename Type>
TypedMatrix3<Type>& TypedMatrix3<Type>::Inverse() {
  Type det = Determinant();
  if (std::abs(det) > 0.0) {
    Type n00 = n00_, n10 = n10_, n20 = n20_,
         n01 = n01_, n11 = n11_, n21 = n21_,
         n02 = n02_, n12 = n12_, n22 = n22_;
    Type recip = 1.0 / det;
    set((n11 * n22 - n12 * n21) * recip,
        (n02 * n21 - n01 * n22) * recip,
        (n01 * n12 - n02 * n11) * recip,
        (n12 * n20 - n10 * n22) * recip,
        (n00 * n22 - n02 * n20) * recip,
        (n02 * n10 - n00 * n12) * recip,
        (n10 * n21 - n11 * n20) * recip,
        (n01 * n20 - n00 * n21) * recip,
        (n00 * n11 - n01 * n10) * recip);
  } else {
    Console::Warn("Can't invert matrix, determinant is zero.");
  }
  return *this;
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_MATRIX3_IMPL_H_
