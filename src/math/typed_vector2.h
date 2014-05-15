// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_VECTOR2_H_
#define MATH_TYPED_VECTOR2_H_

#include <cmath>
#include <cstddef>
#include <limits>

#include "math/math_export.h"

namespace itl {
namespace internal {

/// \todo
/// Implement Floor, Ceil, Round, and RoundToZero functions.
template <typename Type>
class MATH_EXPORT TypedVector2 {
 public:
  TypedVector2() : x_(0.0), y_(0.0) {}
  explicit TypedVector2(const Type& scalar) : x_(scalar), y_(scalar) {}
  TypedVector2(const Type& x, const Type& y) : x_(x), y_(y) {}

  ~TypedVector2() = default;

  TypedVector2(const TypedVector2& rhs) = default;
  /// \todo
  /// Figure out how to make this function explicit and the copy initialization
  /// still work.
  template <typename InnerType>
  TypedVector2(const TypedVector2<InnerType>& rhs)
      : x_(rhs.x()), y_(rhs.y()) {}

  TypedVector2& operator=(const TypedVector2& rhs) = default;
  template <typename InnerType>
  TypedVector2& operator=(const TypedVector2<InnerType>& rhs) {
    x_ = rhs.x(); y_ = rhs.y();
    return *this;
  }

  Type x() const { return x_; }
  TypedVector2& set_x(const Type& x) {
    x_ = x;
    return *this;
  }

  Type y() const { return y_; }
  TypedVector2& set_y(const Type& y) {
    y_ = y;
    return *this;
  }

  Type* get_array() {
    return elements_;
  }

  const Type* get_array() const {
    return elements_;
  }

  TypedVector2& set_from_array(const Type* begin, const Type* end);

  TypedVector2& set(const Type& x, const Type& y) {
    x_ = x; y_ = y;
    return *this;
  }

  Type& operator[](size_t i) { return elements_[i]; }
  const Type& operator[](size_t i) const { return elements_[i]; }

  template <typename InnerType>
  TypedVector2& operator+=(const TypedVector2<InnerType>& rhs) {
    x_ += rhs.x();
    y_ += rhs.y();
    return *this;
  }

  TypedVector2& operator+=(const Type& scalar) {
    x_ += scalar;
    y_ += scalar;
    return *this;
  }

  template <typename InnerType>
  TypedVector2& operator-=(const TypedVector2<InnerType>& rhs) {
    x_ -= rhs.x();
    y_ -= rhs.y();
    return *this;
  }

  TypedVector2& operator*=(const Type& scalar) {
    x_ *= scalar;
    y_ *= scalar;
    return *this;
  }

  TypedVector2& operator/=(const Type& scalar) {
    if (scalar != 0.0) {
      Type recip = 1.0 / scalar;
      x_ *= recip;
      y_ *= recip;
    } else {
      x_ = 0.0;
      y_ = 0.0;
    }
    return *this;
  }

  template <typename InnerTypeA, typename InnerTypeB>
  TypedVector2& Clamp(const TypedVector2<InnerTypeA>& min,
                      const TypedVector2<InnerTypeB>& max);

  TypedVector2& ClampScalar(const Type& min_scalar, const Type& max_scalar);

  Type LengthSq() const {
    return x_ * x_ + y_ * y_;
  }

  Type Length() const {
    return std::sqrt(LengthSq());
  }

  TypedVector2& SetLength(const Type& length) {
    Type old_length = Length();
    if (old_length != 0.0 && old_length != length)
      *this *= (length / old_length);
    return *this;
  }

  TypedVector2& Normalize() {
    return *this /= Length();
  }

 private:
  union {
    struct {
      Type x_, y_;
    };
    Type elements_[2];
  };
};

template <typename Type>
inline TypedVector2<Type> operator-(const TypedVector2<Type>& rhs) {
  return TypedVector2<Type>(-rhs.x(), -rhs.y());
}

template <typename LhsType, typename RhsType>
inline TypedVector2<LhsType> operator+(const TypedVector2<LhsType>& lhs,
                                       const TypedVector2<RhsType>& rhs) {
  return TypedVector2<LhsType>(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template <typename LhsType, typename RhsType>
inline TypedVector2<LhsType> operator-(const TypedVector2<LhsType>& lhs,
                                       const TypedVector2<RhsType>& rhs) {
  return TypedVector2<LhsType>(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

/// \todo
/// Figure out how to compare with different types.
template <typename Type>
inline bool operator==(const TypedVector2<Type>& lhs,
                       const TypedVector2<Type>& rhs) {
  Type epsilon = std::numeric_limits<Type>::epsilon();
  return (std::abs(lhs.x() - rhs.x()) <= epsilon) &&
         (std::abs(lhs.y() - rhs.y()) <= epsilon);
}

template <typename LhsType, typename RhsType>
inline TypedVector2<LhsType> Min(const TypedVector2<LhsType>& lhs,
                                 const TypedVector2<RhsType>& rhs) {
  return TypedVector2<LhsType>(lhs.x() < rhs.x() ? lhs.x() : rhs.x(),
                               lhs.y() < rhs.y() ? lhs.y() : rhs.y());
}

template <typename LhsType, typename RhsType>
inline TypedVector2<LhsType> Max(const TypedVector2<LhsType>& lhs,
                                 const TypedVector2<RhsType>& rhs) {
  return TypedVector2<LhsType>(lhs.x() > rhs.x() ? lhs.x() : rhs.x(),
                               lhs.y() > rhs.y() ? lhs.y() : rhs.y());
}

template <typename LhsType, typename RhsType>
inline LhsType Dot(const TypedVector2<LhsType>& lhs,
                   const TypedVector2<RhsType>& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

template <typename TypeA, typename TypeB>
inline TypeA DistanceSq(const TypedVector2<TypeA>& vec_a,
                        const TypedVector2<TypeB>& vec_b) {
  TypeA dx = vec_a.x() - vec_b.x(), dy = vec_a.y() - vec_b.y();
  return dx * dx + dy * dy;
}

template <typename TypeA, typename TypeB>
inline TypeA Distance(const TypedVector2<TypeA>& vec_a,
                      const TypedVector2<TypeB>& vec_b) {
  return std::sqrt(DistanceSq(vec_a, vec_b));
}

template <typename TypeA, typename TypeB>
inline TypedVector2<TypeA> Lerp(const TypedVector2<TypeA>& vec_a,
                                const TypedVector2<TypeB>& vec_b,
                                double t) {
  return TypedVector2<TypeA>(vec_a.x() + (vec_b.x() - vec_a.x()) * t,
                             vec_a.y() + (vec_b.y() - vec_a.y()) * t);
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_VECTOR2_H_
