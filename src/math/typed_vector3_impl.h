// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_VECTOR3_IMPL_H_
#define MATH_TYPED_VECTOR3_IMPL_H_

#include "math/typed_vector3.h"

namespace itl {
namespace internal {

template <typename Type>
template <typename InnerTypeA, typename InnerTypeB>
TypedVector3<Type>& TypedVector3<Type>::Clamp(
    const TypedVector3<InnerTypeA>& min,
    const TypedVector3<InnerTypeB>& max) {
  assert(min.x() <= max.x());
  assert(min.y() <= max.y());
  assert(min.z() <= max.z());

  if (x_ < min.x())
    x_ = min.x();
  else if (x_ > max.x())
    x_ = max.x();

  if (y_ < min.y())
    y_ = min.y();
  else if (y_ > max.y())
    y_ = max.y();

  if (z_ < min.z())
    z_ = min.z();
  else if (z_ > max.z())
    z_ = max.z();

  return *this;
}

template <typename Type>
TypedVector3<Type>& TypedVector3<Type>::ClampScalar(const Type& min_scalar,
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

  if (z_ < min_scalar)
    z_ = min_scalar;
  else if (z_ > max_scalar)
    z_ = max_scalar;

  return *this;
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_VECTOR3_IMPL_H_
