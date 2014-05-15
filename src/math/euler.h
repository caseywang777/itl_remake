// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_EULER_H_
#define MATH_EULER_H_

#include "math/math_export.h"

namespace itl {

class MATH_EXPORT Euler {
 public:
  enum RotationOrders {kXYZ, kYZX, kZXY, kXZY, kYXZ, kZYX};
  static const RotationOrders kDefaultOrder = kXYZ;

  Euler() = default;
  Euler(double x, double y, double z, const RotationOrders& order)
      : x_(x), y_(y), z_(z), order_(order) {}

  ~Euler() = default;

  Euler(const Euler& rhs) = default;
  Euler& operator=(const Euler& rhs) = default;

  double x() const { return x_; }
  Euler& set_x(double x) {
    x_ = x;
    return *this;
  }

  double y() const { return y_; }
  Euler& set_y(double y) {
    y_ = y;
    return *this;
  }

  double z() const { return z_; }
  Euler& set_z(double z) {
    z_ = z;
    return *this;
  }

  RotationOrders order() const { return order_; }
  Euler& set_order(const RotationOrders& order) {
    order_ = order;
    return *this;
  }

 private:
  double x_ = 0.0, y_ = 0.0, z_ = 0.0;
  RotationOrders order_ = kDefaultOrder;
};

}  // namespace itl

#endif  // MATH_EULER_H_
