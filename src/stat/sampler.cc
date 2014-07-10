// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "stat/sampler.h"

#include <cstdlib>

#include "stat/histogram.h"

namespace itl {

void Sampler::Rejection(Histogram& hist, double height,
                        double* begin, double* end) {
  size_t sample_number = end - begin;
  double min = hist.bins()->get_min_value(),
         max = hist.bins()->get_max_value();

  while (sample_number > 0) {
    double gx = static_cast<double>(rand()) / RAND_MAX * (max - min) + min;
    double u = static_cast<double>(rand()) / RAND_MAX * height;

    if (u <= hist.get_frequency(hist.bins()->ValueToBinIndex(gx)))
      *(end - sample_number--) = gx;
  }
}

void Sampler::InverseCDF(Histogram& hist, double* begin, double* end) {
  size_t sample_number = end - begin;
  std::vector<float> cdf;
  hist.get_cumulative_probabilities(cdf);

  while (sample_number > 0) {
    double x = static_cast<double>(rand()) / RAND_MAX;
    auto it = cdf.begin();
    while (x > *it) ++it;
    *(end - sample_number--) = hist.bins()->get_bin_center(it - cdf.begin());
  }
}

void Sampler::Metropolis(Histogram& hist, double alpha,
                         double* begin, double* end) {
  size_t sample_number = end - begin;

  double min = hist.bins()->get_min_value(),
         max = hist.bins()->get_max_value();

  double x = static_cast<double>(rand()) / RAND_MAX * (max - min) + min;

  while (sample_number > 0) {
    double gx = static_cast<double>(rand()) / RAND_MAX * (max - min) + min;

    if (alpha * hist.get_frequency(hist.bins()->ValueToBinIndex(x)) <
        hist.get_frequency(hist.bins()->ValueToBinIndex(gx))) {
      *(end - sample_number--) = gx;
      x = gx;
    }
    else {
      *(end - sample_number--) = x;
    }
  }
}

}  // namespace itl
