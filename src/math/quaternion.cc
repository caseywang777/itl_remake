// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "math/quaternion.h"

namespace itl {

Quaternion& Quaternion::Normalize() {
  double length = Length();
  if (length != 0.0) {
    double recip = 1.0 / length;
    x_ *= recip;
    y_ *= recip;
    z_ *= recip;
    w_ *= recip;
  } else {
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
    w_ = 1.0;
  }
  return *this;
}

}  // namespace itl
