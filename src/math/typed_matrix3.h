// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_MATRIX3_H_
#define MATH_TYPED_MATRIX3_H_

#include <cstddef>

#include "math/math_export.h"

namespace itl {
namespace internal {

/// \todo
/// Implement the NormalMatrix function.
template <typename Type>
class MATH_EXPORT TypedMatrix3 {
 public:
  TypedMatrix3() : n00_(1.0), n10_(0.0), n20_(0.0),
                   n01_(0.0), n11_(1.0), n21_(0.0),
                   n02_(0.0), n12_(0.0), n22_(1.0) {}
  TypedMatrix3(const Type& n00, const Type& n01, const Type& n02,
               const Type& n10, const Type& n11, const Type& n12,
               const Type& n20, const Type& n21, const Type& n22)
      : n00_(n00), n10_(n10), n20_(n20),
        n01_(n01), n11_(n11), n21_(n21),
        n02_(n02), n12_(n12), n22_(n22) {}

  ~TypedMatrix3() = default;

  TypedMatrix3(const TypedMatrix3& rhs) = default;
  /// \todo
  /// Figure out how to make this function explicit and the copy initialization
  /// still work.
  template <typename InnerType>
  TypedMatrix3(const TypedMatrix3<InnerType>& rhs)
      : n00_(rhs.get(0, 0)), n10_(rhs.get(1, 0)), n20_(rhs.get(2, 0)),
        n01_(rhs.get(0, 1)), n11_(rhs.get(1, 1)), n21_(rhs.get(2, 1)),
        n02_(rhs.get(0, 2)), n12_(rhs.get(1, 2)), n22_(rhs.get(2, 2)) {}

  TypedMatrix3& operator=(const TypedMatrix3& rhs) = default;
  template <typename InnerType>
  TypedMatrix3& operator=(const TypedMatrix3<InnerType>& rhs) {
    n00_ = rhs.get(0, 0); n10_ = rhs.get(1, 0); n20_ = rhs.get(2, 0);
    n01_ = rhs.get(0, 1); n11_ = rhs.get(1, 1); n21_ = rhs.get(2, 1);
    n02_ = rhs.get(0, 2); n12_ = rhs.get(1, 2); n22_ = rhs.get(2, 2);
    return *this;
  }

  Type get(size_t i, size_t j) const {
    return elements_[i + j * 3];
  }

  TypedMatrix3& set(size_t i, size_t j, const Type& value) {
    elements_[i + j * 3] = value;
    return *this;
  }

  Type* get_array() {
    return elements_;
  }

  const Type* get_array() const {
    return elements_;
  }

  TypedMatrix3& set_from_array(const Type* begin, const Type* end);

  TypedMatrix3& set(const Type& n00, const Type& n01, const Type& n02,
                    const Type& n10, const Type& n11, const Type& n12,
                    const Type& n20, const Type& n21, const Type& n22) {
    n00_ = n00; n10_ = n10; n20_ = n20;
    n01_ = n01; n11_ = n11; n21_ = n21;
    n02_ = n02; n12_ = n12; n22_ = n22;
    return *this;
  }

  TypedMatrix3& Identity() {
    return set(1.0, 0.0, 0.0,
               0.0, 1.0, 0.0,
               0.0, 0.0, 1.0);
  }

  TypedMatrix3& operator*=(const Type& scalar);

  Type Determinant() const {
    return n00_ * (n11_ * n22_ - n12_ * n21_) +
           n01_ * (n12_ * n20_ - n10_ * n22_) +
           n02_ * (n10_ * n21_ - n11_ * n20_);
  }

  TypedMatrix3& Transpose() {
    Type temp;
    temp = n10_; n10_ = n01_; n01_ = temp;
    temp = n20_; n20_ = n02_; n02_ = temp;
    temp = n21_; n21_ = n12_; n12_ = temp;
    return *this;
  }

  TypedMatrix3& Inverse();

 private:
  union {
    struct {
      Type n00_, n10_, n20_,
           n01_, n11_, n21_,
           n02_, n12_, n22_;
    };
    Type elements_[9];
  };
};

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_MATRIX3_H_
