// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "core/cartesian_grid.h"

namespace itl {

CartesianGrid::CartesianGrid() = default;

CartesianGrid::CartesianGrid(size_t x_dim, size_t y_dim, size_t z_dim)
    : Grid(x_dim, y_dim, z_dim) {}

CartesianGrid::CartesianGrid(size_t x_dim, size_t y_dim, size_t z_dim,
                             size_t x_bias, size_t y_bias, size_t z_bias)
    : Grid(x_dim, y_dim, z_dim, x_bias, y_bias, z_bias) {}

CartesianGrid::~CartesianGrid() = default;

}  // namespace itl
