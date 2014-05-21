// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "algorithm/entropy.h"

#include <cmath>
#include <limits>

#include "core/field.h"
#include "stat/histogram.h"
#include "algorithm/hist.h"

namespace itl {

double ComputeEntropy(const Histogram& hist) {
  std::vector<float> probabilities;
  hist.get_probabilities(probabilities);

  const double epsilon = std::numeric_limits<double>::epsilon();
  double entropy = 0;
  double log2 = std::log(2);
  for (const float& probability : probabilities) {
    if (std::abs(probability) > epsilon) {
      entropy -= probability * std::log(probability) / log2;
    }
  }
  return entropy;
}

double ComputeEntropy(Field* field, const std::shared_ptr<Bins> bins,
               int* from, int* to) {
  Histogram hist = ComputeHistogram(field, bins, from, to);
  return ComputeEntropy(hist);
}

}  // namespace itl
