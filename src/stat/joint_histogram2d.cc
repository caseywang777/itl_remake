// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "stat/joint_histogram2d.h"

#include <cassert>
#include <algorithm>
#include <limits>
#include <numeric>

namespace itl {

JointHistogram2D::JointHistogram2D(const std::shared_ptr<const Bins>& bins_x,
                                   const std::shared_ptr<const Bins>& bins_y)
    : bins_x_(bins_x), bins_y_(bins_y),
      frequencies_(bins_x->get_bin_number() * bins_y->get_bin_number()) {
}

JointHistogram2D::~JointHistogram2D() = default;

JointHistogram2D::JointHistogram2D(const JointHistogram2D&) = default;

JointHistogram2D& JointHistogram2D::operator=(
    const JointHistogram2D&) = default;

float JointHistogram2D::get_frequency(double v1, double v2) const {
  size_t x = bins_x_->ValueToBinIndex(v1);
  size_t y = bins_y_->ValueToBinIndex(v2);
  if (x < bins_x_->get_bin_number() && y < bins_y_->get_bin_number())
    return frequencies_[Index2DTo1D(x, y)];
  else
    return 0.0f;
}

float JointHistogram2D::get_sample_size() const {
  return std::accumulate(frequencies_.begin(), frequencies_.end(), 0.0f);
}

void JointHistogram2D::get_probabilities(std::vector<float>& p) const {
  const float epsilon = std::numeric_limits<float>::epsilon();
  float sample_size = get_sample_size();
  p.clear();
  if (sample_size < epsilon) {
    for (size_t i = 0, il = frequencies_.size(); i < il; ++i)
      p.push_back(0.0f);
  } else {
    for (float f : frequencies_)
      p.push_back(f / sample_size);
  }
}

JointHistogram2D& JointHistogram2D::Normalize() {
  const float epsilon = std::numeric_limits<float>::epsilon();
  float sample_size = get_sample_size();
  if (sample_size > epsilon) {
    for (float& f : frequencies_)
      f /= sample_size;
  }
  return *this;
}

JointHistogram2D& JointHistogram2D::Clear() {
  for (float& f : frequencies_)
    f = 0.0f;
  return *this;
}

JointHistogram2D& JointHistogram2D::Insert(double v1, double v2) {
  size_t x = bins_x_->ValueToBinIndex(v1);
  size_t y = bins_y_->ValueToBinIndex(v2);
  if (x < bins_x_->get_bin_number() && y < bins_y_->get_bin_number())
    frequencies_[Index2DTo1D(x, y)] += 1.0f;
  return *this;
}

JointHistogram2D& JointHistogram2D::Insert(double v1, double v2,
                                           double weight) {
  size_t x = bins_x_->ValueToBinIndex(v1);
  size_t y = bins_y_->ValueToBinIndex(v2);
  if (x < bins_x_->get_bin_number() && y < bins_y_->get_bin_number())
    frequencies_[Index2DTo1D(x, y)] += weight;
  return *this;
}

}  // namespace itl
