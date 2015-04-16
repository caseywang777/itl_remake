// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef ALGORITHM_HIST_H_
#define ALGORITHM_HIST_H_

#include <memory>
#include <utility>

#include "algorithm/algorithm_export.h"

namespace itl {

class Field;
class Bins;
class Histogram;
class JointHistogram2D;

Histogram ComputeHistogram(Field* field, const std::shared_ptr<Bins> bins,
                           int* from = nullptr, int* to = nullptr,
                           std::pair<int, int> id = {0, 0});

JointHistogram2D ComputeJointHistogram2D(Field* field,
                                         const std::shared_ptr<Bins> bins_x,
                                         const std::shared_ptr<Bins> bins_y,
                                         std::pair<int, int> id_x,
                                         std::pair<int, int> id_y,
                                         int* from = nullptr,
                                         int* to = nullptr);

// JointHistogram2D ComputeJointHistogram2D(Field* field,
//                                          const std::shared_ptr<Bins> bins_x,
//                                          const std::shared_ptr<Bins> bins_y,
//                                          int* from, int* to,
//                                          std::initializer_list<std::pair<int, int>> ids);

}  // namespace itl

#endif  // ALGORITHM_HIST_H_
