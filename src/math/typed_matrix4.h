// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_TYPED_MATRIX4_H_
#define MATH_TYPED_MATRIX4_H_

#include <cstddef>

#include "math/math_export.h"

namespace itl {
namespace internal {

template <typename Type>
class MATH_EXPORT TypedMatrix4 {
 public:
  TypedMatrix4();
  TypedMatrix4(
      const Type& n00, const Type& n01, const Type& n02, const Type& n03,
      const Type& n10, const Type& n11, const Type& n12, const Type& n13,
      const Type& n20, const Type& n21, const Type& n22, const Type& n23,
      const Type& n30, const Type& n31, const Type& n32, const Type& n33);

  ~TypedMatrix4();

  TypedMatrix4(const TypedMatrix4& rhs);
  template <typename InnerType>
  TypedMatrix4(const TypedMatrix4<InnerType>& rhs);

  TypedMatrix4& operator=(const TypedMatrix4& rhs);
  template <typename InnerType>
  TypedMatrix4& operator=(const TypedMatrix4<InnerType>& rhs);

  Type get(size_t i, size_t j) const {
    return elements_[i + j * 4];
  }

  TypedMatrix4& set(size_t i, size_t j, const Type& value) {
    elements_[i + j * 4] = value;
    return *this;
  }

  Type* get_array() {
    return elements_;
  }

  const Type* get_array() const {
    return elements_;
  }

  TypedMatrix4& set_from_array(const Type* begin, const Type* end);

  TypedMatrix4& set(
      const Type& n00, const Type& n01, const Type& n02, const Type& n03,
      const Type& n10, const Type& n11, const Type& n12, const Type& n13,
      const Type& n20, const Type& n21, const Type& n22, const Type& n23,
      const Type& n30, const Type& n31, const Type& n32, const Type& n33);

  TypedMatrix4& Identity() {
    return set(1.0, 0.0, 0.0, 0.0,
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0);
  }

 private:
  union {
    struct {
      Type n00_, n10_, n20_, n30_,
           n01_, n11_, n21_, n31_,
           n02_, n12_, n22_, n32_,
           n03_, n13_, n23_, n33_;
    };
    Type elements_[16];
  };
};

}  // namespace internal
}  // namespace itl

#endif  // MATH_TYPED_MATRIX4_H_
