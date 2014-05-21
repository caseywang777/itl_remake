// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "algorithm/hist.h"

#include "core/field.h"
#include "stat/histogram.h"
#include "stat/joint_histogram2d.h"

namespace itl {

Histogram ComputeHistogram(Field* field, const std::shared_ptr<Bins> bins,
                           int* from, int* to, std::pair<int, int> id) {
  Histogram hist(bins);

  for (int k = from[2]; k != to[2]; k++) {
    for (int j = from[1]; j != to[1]; j++) {
      for (int i = from[0]; i != to[0]; i++) {
        hist.Insert(field->value_at_point(i, j, k, id.first, id.second));
      }
    }
  }

  return hist;
}

JointHistogram2D ComputeJointHistogram2D(Field* field,
                                         const std::shared_ptr<Bins> bins_x,
                                         const std::shared_ptr<Bins> bins_y,
                                         int* from, int* to,
                                         std::pair<int, int> id_x,
                                         std::pair<int, int> id_y) {
  JointHistogram2D hist(bins_x, bins_y);

  for (int k = from[2]; k != to[2]; k++) {
    for (int j = from[1]; j != to[1]; j++) {
      for (int i = from[0]; i != to[0]; i++) {
        hist.Insert(field->value_at_point(i, j, k, id_x.first, id_x.second),
                    field->value_at_point(i, j, k, id_y.first, id_y.second));
      }
    }
  }

  return hist;
}

}  // namespace itl
