// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef STAT_SAMPLER_H_
#define STAT_SAMPLER_H_

#include "stat/stat_export.h"

namespace itl {

class Histogram;

class STAT_EXPORT Sampler {
 public:
  static void Rejection(Histogram& hist, double height,
                        double* begin, double* end);
  static void InverseCDF(Histogram& hist, double* begin, double* end);
  static void Metropolis(Histogram& hist, double alpha,
                         double* begin, double* end);

 private:
  Sampler() = delete;
  ~Sampler() = delete;
  Sampler(const Sampler& rhs) = delete;
  Sampler& operator=(const Sampler& rhs) = delete;
};

}  // namespace itl

#endif  // STAT_SAMPLER_H_
