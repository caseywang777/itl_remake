// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_FIELD_H_
#define CORE_FIELD_H_

#include <memory>
#include <vector>

#include "core/abstract_array.h"
#include "core/grid.h"

namespace itl {

class CORE_EXPORT Field {
 public:
  Field();
  ~Field();

  Grid* grid() { return grid_.get(); }
  const Grid* grid() const { return grid_.get(); }

  Field& set_grid(Grid* grid) {
    grid_.reset(grid);
    grid = nullptr;
    return *this;
  }

  AbstractArray* variable(size_t i) { return variables_[i].get(); }
  const AbstractArray* variable(size_t i) const { return variables_[i].get(); }

  Field& attach_variable(AbstractArray* variable) {
    variables_.push_back(std::unique_ptr<AbstractArray>(variable));
    variable = nullptr;
    return *this;
  }

  double value_at_point(size_t i, size_t j, size_t k, size_t vi = 0,
                        size_t ei = 0) {
    return variables_[vi]->element(grid_->Index3DTo1D(i, j, k), ei);
  }

 private:
  Field(const Field& rhs) = delete;
  Field& operator=(const Field& rhs) = delete;

  std::unique_ptr<Grid> grid_;
  std::vector<std::unique_ptr<AbstractArray>> variables_;
};

}  // namespace itl

#endif  // CORE_FIELD_H_
