// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef EXTRAS_PYPLOT_H_
#define EXTRAS_PYPLOT_H_

#include "Python.h"

#include "stat/histogram.h"

namespace itl {

void PyPlot(const Histogram& hist);

void PyPlot(const double* data, size_t size);

}  // namespace itl

#endif  // EXTRAS_PYPLOT_H_
