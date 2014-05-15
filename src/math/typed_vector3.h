// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_VECTOR3_H_
#define MATH_TYPED_VECTOR3_H_

#include <cmath>
#include <cstddef>
#include <limits>

#include "math/math_export.h"

namespace itl {
namespace internal {

template <typename Type>
class MATH_EXPORT TypedVector3 {
 public:
  TypedVector3() : x_(0.0), y_(0.0), z_(0.0) {}
  explicit TypedVector3(const Type& scalar)
      : x_(scalar), y_(scalar), z_(scalar) {}
  TypedVector3(const Type& x, const Type& y, const Type& z)
      : x_(x), y_(y), z_(z) {}

  ~TypedVector3() = default;

  TypedVector3(const TypedVector3& rhs) = default;
  template <typename InnerType>
  TypedVector3(const TypedVector3<InnerType>& rhs)
      : x_(rhs.x()), y_(rhs.y()), z_(rhs.z()) {}

  TypedVector3& operator=(const TypedVector3& rhs) = default;
  template <typename InnerType>
  TypedVector3& operator=(const TypedVector3<InnerType>& rhs) {
    x_ = rhs.x(); y_ = rhs.y(); z_ = rhs.z();
    return *this;
  }

  Type x() const { return x_; }
  TypedVector3& set_x(const Type& x) {
    x_ = x;
    return *this;
  }

  Type y() const { return y_; }
  TypedVector3& set_y(const Type& y) {
    y_ = y;
    return *this;
  }

  Type z() const { return z_; }
  TypedVector3& set_z(const Type& z) {
    z_ = z;
    return *this;
  }

  TypedVector3& set(const Type& x, const Type& y, const Type& z) {
    x_ = x; y_ = y; z_ = z;
    return *this;
  }

  Type& operator[](size_t i) { return elements_[i]; }
  const Type& operator[](size_t i) const { return elements_[i]; }

  template <typename InnerType>
  TypedVector3& operator+=(const TypedVector3<InnerType>& rhs) {
    x_ += rhs.x();
    y_ += rhs.y();
    z_ += rhs.z();
    return *this;
  }

  TypedVector3& operator+=(const Type& scalar) {
    x_ += scalar;
    y_ += scalar;
    z_ += scalar;
    return *this;
  }

  template <typename InnerType>
  TypedVector3& operator-=(const TypedVector3<InnerType>& rhs) {
    x_ -= rhs.x();
    y_ -= rhs.y();
    z_ -= rhs.z();
    return *this;
  }

  TypedVector3& operator*=(const Type& scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    return *this;
  }

  TypedVector3& operator/=(const Type& scalar) {
    if (scalar != 0.0) {
      Type recip = 1.0 / scalar;
      x_ *= recip;
      y_ *= recip;
      z_ *= recip;
    } else {
      x_ = 0.0;
      y_ = 0.0;
      z_ = 0.0;
    }
    return *this;
  }

  template <typename InnerTypeA, typename InnerTypeB>
  TypedVector3& Clamp(const TypedVector3<InnerTypeA>& min,
                      const TypedVector3<InnerTypeB>& max);

  TypedVector3& ClampScalar(const Type& min_scalar, const Type& max_scalar);

  Type LengthSq() const {
    return x_ * x_ + y_ * y_ + z_ * z_;
  }

  Type Length() const {
    return std::sqrt(LengthSq());
  }

  Type LengthManhattan() const {
    return std::abs(x_) + std::abs(y_) + std::abs(z_);
  }

  TypedVector3& SetLength(const Type& length) {
    Type old_length = Length();
    if (old_length != 0.0 && old_length != length)
      *this *= (length / old_length);
    return *this;
  }

  TypedVector3& Normalize() {
    return *this /= Length();
  }

 private:
  union {
    struct {
      Type x_, y_, z_;
    };
    Type elements_[3];
  };
};

template <typename Type>
inline TypedVector3<Type> operator-(const TypedVector3<Type>& rhs) {
  return TypedVector3<Type>(-rhs.x(), -rhs.y(), -rhs.z());
}

template <typename LhsType, typename RhsType>
inline TypedVector3<LhsType> operator+(const TypedVector3<LhsType>& lhs,
                                       const TypedVector3<RhsType>& rhs) {
  return TypedVector3<LhsType>(lhs.x() + rhs.x(), lhs.y() + rhs.y(),
                               lhs.z() + rhs.z());
}

template <typename LhsType, typename RhsType>
inline TypedVector3<LhsType> operator-(const TypedVector3<LhsType>& lhs,
                                       const TypedVector3<RhsType>& rhs) {
  return TypedVector3<LhsType>(lhs.x() - rhs.x(), lhs.y() - rhs.y(),
                               lhs.z() - rhs.z());
}

template <typename Type>
inline bool operator==(const TypedVector3<Type>& lhs,
                       const TypedVector3<Type>& rhs) {
  Type epsilon = std::numeric_limits<Type>::epsilon();
  return (std::abs(lhs.x() - rhs.x()) <= epsilon) &&
         (std::abs(lhs.y() - rhs.y()) <= epsilon) &&
         (std::abs(lhs.z() - rhs.z()) <= epsilon);
}

template <typename LhsType, typename RhsType>
inline TypedVector3<LhsType> Min(const TypedVector3<LhsType>& lhs,
                                 const TypedVector3<RhsType>& rhs) {
  return TypedVector3<LhsType>(lhs.x() < rhs.x() ? lhs.x() : rhs.x(),
                               lhs.y() < rhs.y() ? lhs.y() : rhs.y(),
                               lhs.z() < rhs.z() ? lhs.z() : rhs.z());
}

template <typename LhsType, typename RhsType>
inline TypedVector3<LhsType> Max(const TypedVector3<LhsType>& lhs,
                                 const TypedVector3<RhsType>& rhs) {
  return TypedVector3<LhsType>(lhs.x() > rhs.x() ? lhs.x() : rhs.x(),
                               lhs.y() > rhs.y() ? lhs.y() : rhs.y(),
                               lhs.z() > rhs.z() ? lhs.z() : rhs.z());
}

template <typename LhsType, typename RhsType>
inline LhsType Dot(const TypedVector3<LhsType>& lhs,
                   const TypedVector3<RhsType>& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

template <typename LhsType, typename RhsType>
inline TypedVector3<LhsType> Cross(const TypedVector3<LhsType>& lhs,
                                   const TypedVector3<RhsType>& rhs) {
  return TypedVector3<LhsType>(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                               lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                               lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

template <typename TypeA, typename TypeB>
inline TypeA DistanceSq(const TypedVector3<TypeA>& vec_a,
                        const TypedVector3<TypeB>& vec_b) {
  TypeA dx = vec_a.x() - vec_b.x(),
        dy = vec_a.y() - vec_b.y(),
        dz = vec_a.z() - vec_b.z();
  return dx * dx + dy * dy + dz * dz;
}

template <typename TypeA, typename TypeB>
inline TypeA Distance(const TypedVector3<TypeA>& vec_a,
                      const TypedVector3<TypeB>& vec_b) {
  return std::sqrt(DistanceSq(vec_a, vec_b));
}

template <typename TypeA, typename TypeB>
inline TypedVector3<TypeA> Lerp(const TypedVector3<TypeA>& vec_a,
                                const TypedVector3<TypeB>& vec_b,
                                double t) {
  return TypedVector3<TypeA>(vec_a.x() + (vec_b.x() - vec_a.x()) * t,
                             vec_a.y() + (vec_b.y() - vec_a.y()) * t,
                             vec_a.z() + (vec_b.z() - vec_a.z()) * t);
}

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_VECTOR3_H_
