// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_CARTESIAN_GRID_H_
#define CORE_CARTESIAN_GRID_H_

#include "core/grid.h"

namespace itl {

class CORE_EXPORT CartesianGrid : public Grid {
 public:
  CartesianGrid();
  CartesianGrid(size_t x_dim, size_t y_dim, size_t z_dim);
  CartesianGrid(size_t x_dim, size_t y_dim, size_t z_dim,
                size_t x_bias, size_t y_bias, size_t z_bias);

  ~CartesianGrid();

 private:
  CartesianGrid(const CartesianGrid& rhs) = delete;
  CartesianGrid& operator=(const CartesianGrid& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_CARTESIAN_GRID_H_
