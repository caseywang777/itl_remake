// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_GRID_H_
#define CORE_GRID_H_

#include <cstddef>

#include "core/core_export.h"

namespace itl {

class CORE_EXPORT Grid {
 public:
  virtual ~Grid();

  size_t x_dim() const { return x_dim_; }
  size_t y_dim() const { return y_dim_; }
  size_t z_dim() const { return z_dim_; }

  size_t Index3DTo1D(size_t i, size_t j, size_t k) const {
    return (k - z_bias_) * x_dim_ * y_dim_ + (j - y_bias_) * x_dim_ +
           (i - x_bias_);
  }

 protected:
  Grid() = default;
  Grid(size_t x_dim, size_t y_dim, size_t z_dim) : x_dim_(x_dim), y_dim_(y_dim),
                                                   z_dim_(z_dim) {}
  Grid(size_t x_dim, size_t y_dim, size_t z_dim,
       size_t x_bias, size_t y_bias, size_t z_bias)
      : x_dim_(x_dim), y_dim_(y_dim), z_dim_(z_dim),
        x_bias_(x_bias), y_bias_(y_bias), z_bias_(z_bias) {}

 private:
  Grid(const Grid& rhs) = delete;
  Grid& operator=(const Grid& rhs) = delete;

  size_t x_dim_ = 0, y_dim_ = 0, z_dim_ = 0,
         x_bias_ = 0, y_bias_ = 0, z_bias_ = 0;
};

}  // namespace itl

#endif  // CORE_GRID_H_
