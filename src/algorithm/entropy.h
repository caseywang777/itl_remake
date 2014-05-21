// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef ALGORITHM_ENTROPY_H_
#define ALGORITHM_ENTROPY_H_

#include <memory>

#include "algorithm/algorithm_export.h"

namespace itl {

class Field;
class Bins;
class Histogram;

double ComputeEntropy(const Histogram& hist);

double ComputeEntropy(Field* field, const std::shared_ptr<Bins> bins,
                      int* from, int* to);

}  // namespace itl

#endif  // ALGORITHM_ENTROPY_H_
