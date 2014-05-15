// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_VECTOR2_IMPL_H_
#define MATH_TYPED_VECTOR2_IMPL_H_

#include "math/typed_vector2.h"

#include <cassert>

namespace itl {
namespace internal {

template <typename Type>
TypedVector2<Type>& TypedVector2<Type>::set_from_array(const Type* begin,
                                                       const Type* end) {
  assert((end - begin) == 2);
  for (size_t i = 0; i != 2; ++i)
    elements_[i] = *(begin + i);
  return *this;
}

template <typename Type>
template <typename InnerTypeA, typename InnerTypeB>
TypedVector2<Type>& TypedVector2<Type>::Clamp(
    const TypedVector2<InnerTypeA>& min,
    const TypedVector2<InnerTypeB>& max) {
  assert(min.x() <= max.x());
  assert(min.y() <= max.y());

  if (x_ < min.x())
    x_ = min.x();
  else if (x_ > max.x())
    x_ = max.x();

  if (y_ < min.y())
    y_ = min.y();
  else if (y_ > max.y())
    y_ = max.y();

  return *this;
}

template <typename Type>
TypedVector2<Type>& TypedVector2<Type>::ClampScalar(const Type& min_scalar,
                                                    const Type& max_scalar) {
  assert(min_scalar <= max_scalar);

  if (x_ < min_scalar)
    x_ = min_scalar;
  else if (x_ > max_scalar)
    x_ = max_scalar;

  if (y_ < min_scalar)
    y_ = min_scalar;
  else if (y_ > max_scalar)
    y_ = max_scalar;

  return *this;
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_VECTOR2_IMPL_H_
