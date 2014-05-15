// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef MATH_QUATERNION_H_
#define MATH_QUATERNION_H_

#include <cmath>
#include <limits>

#include "math/math_export.h"

namespace itl {

class MATH_EXPORT Quaternion {
 public:
  Quaternion() = default;
  Quaternion(double x, double y, double z, double w)
      : x_(x), y_(y), z_(z), w_(w) {}

  ~Quaternion() = default;

  Quaternion(const Quaternion& rhs) = default;
  Quaternion& operator=(const Quaternion& rhs) = default;

  double x() const { return x_; }
  Quaternion& set_x(double x) {
    x_ = x;
    return *this;
  }

  double y() const { return y_; }
  Quaternion& set_y(double y) {
    y_ = y;
    return *this;
  }

  double z() const { return z_; }
  Quaternion& set_z(double z) {
    z_ = z;
    return *this;
  }

  double w() const { return w_; }
  Quaternion& set_w(double w) {
    w_ = w;
    return *this;
  }

  Quaternion& set(double x, double y, double z, double w) {
    x_ = x; y_ = y; z_ = z; w_ = w;
    return *this;
  }

  Quaternion& operator*=(const Quaternion& rhs) {
    double qlx = x_, qly = y_, qlz = z_, qlw = w_;
    double qrx = rhs.x(), qry = rhs.y(), qrz = rhs.z(), qrw = rhs.w();
    x_ = qlx * qrw + qlw * qrx + qly * qrz - qlz * qry;
    y_ = qly * qrw + qlw * qry + qlz * qrx - qlx * qrz;
    z_ = qlz * qrw + qlw * qrz + qlx * qry - qly * qrx;
    w_ = qlw * qrw - qlx * qrx - qly * qry - qlz * qrz;
    return *this;
  }

  double LengthSq() const {
    return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
  }

  double Length() const {
    return std::sqrt(LengthSq());
  }

  Quaternion& Normalize();

  Quaternion& Conjugate() {
    x_ = -x_; y_ = -y_; z_ = -z_;
    return *this;
  }

  Quaternion& Inverse() {
    Conjugate().Normalize();
    return *this;
  }

 private:
  double x_ = 0.0, y_ = 0.0, z_ = 0.0, w_ = 1.0;
};

inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) {
  double qlx = lhs.x(), qly = lhs.y(), qlz = lhs.z(), qlw = lhs.w();
  double qrx = rhs.x(), qry = rhs.y(), qrz = rhs.z(), qrw = rhs.w();
  return Quaternion(qlx * qrw + qlw * qrx + qly * qrz - qlz * qry,
                    qly * qrw + qlw * qry + qlz * qrx - qlx * qrz,
                    qlz * qrw + qlw * qrz + qlx * qry - qly * qrx,
                    qlw * qrw - qlx * qrx - qly * qry - qlz * qrz);
}

inline bool operator==(const Quaternion& lhs, const Quaternion& rhs) {
  double epsilon = std::numeric_limits<double>::epsilon();
  return (std::abs(lhs.x() - rhs.x()) <= epsilon) &&
         (std::abs(lhs.y() - rhs.y()) <= epsilon) &&
         (std::abs(lhs.z() - rhs.z()) <= epsilon) &&
         (std::abs(lhs.w() - rhs.w()) <= epsilon);
}

}  // namespace itl

#endif  // MATH_QUATERNION_H_
