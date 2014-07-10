// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "stat/histogram.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <limits>
#include <numeric>

namespace itl {

Histogram::Histogram(const std::shared_ptr<const Bins>& bins)
    : bins_(bins), frequencies_(bins->get_bin_number()) {
}

Histogram::~Histogram() = default;

Histogram::Histogram(const Histogram&) = default;

Histogram& Histogram::operator=(const Histogram&) = default;

// TODO(wenbin): implement this function.
void Histogram::set_bins(const std::shared_ptr<const Bins>& bins) {}

float Histogram::get_frequency(const double value) const {
  size_t bin_id = bins_->ValueToBinIndex(value);
  if (bin_id < frequencies_.size())
    return frequencies_[bin_id];
  else
    return 0.0f;
}

float Histogram::get_sample_size() const {
  return std::accumulate(frequencies_.begin(), frequencies_.end(), 0.0f);
}

void Histogram::get_probabilities(std::vector<float>& p) const {
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

void Histogram::get_cumulative_probabilities(std::vector<float>& cp) const {
  get_probabilities(cp);
  for (auto it = cp.begin() + 1; it < cp.end(); ++it)
    *it += *(it - 1);
}

Histogram& Histogram::Normalize() {
  const float epsilon = std::numeric_limits<float>::epsilon();
  float sample_size = get_sample_size();
  if (sample_size > epsilon) {
    for (float& f : frequencies_)
      f /= sample_size;
  }
  return *this;
}

Histogram& Histogram::Clear() {
  for (float& f : frequencies_)
    f = 0.0f;
  return *this;
}

Histogram& Histogram::Insert(const double value) {
  size_t bin_id = bins_->ValueToBinIndex(value);
  if (bin_id < frequencies_.size())
    frequencies_[bin_id] += 1.0f;
  return *this;
}

Histogram& Histogram::Insert(const double value, const double weight) {
  size_t bin_id = bins_->ValueToBinIndex(value);
  if (bin_id < frequencies_.size())
    frequencies_[bin_id] += weight;
  return *this;
}

// TODO(wenbin): implement these functions.
// double Histogram::Mean() const;
// double Histogram::Median() const;
// double Histogram::Mode() const;
// double Histogram::Variance(const double mean, bool inference) const;
// double Histogram::StandardDeviation(const double mean, bool inference) const;

bool Histogram::IsAligned(const Histogram& h) const {
  if (bins_ == h.bins())
    return true;
  else
    return *bins_ == *h.bins();
}

// TODO(wenbin): check this function after finishing the set_bins() function.
Histogram& Histogram::AlignWith(const Histogram& h) {
  set_bins(h.bins());
  return *this;
}

Histogram& Histogram::operator+=(const Histogram& rhs) {
  assert(IsAligned(rhs));
  for (size_t i = 0, il = frequencies_.size(); i < il; ++i)
    frequencies_[i] += rhs.frequencies()[i];
  return *this;
}

Histogram& Histogram::operator-=(const Histogram& rhs) {
  assert(IsAligned(rhs));
  for (size_t i = 0, il = frequencies_.size(); i < il; ++i)
    frequencies_[i] = std::max(frequencies_[i] - rhs.frequencies()[i], 0.0f);
  return *this;
}

double Histogram::Entropy() {
  Normalize();
  const double epsilon = std::numeric_limits<double>::epsilon();
  double entropy = 0.0;
  double log2 = std::log(2);
  for (const float& probability : frequencies_) {
    if (std::abs(probability) > epsilon) {
      entropy -= probability * std::log(probability) / log2;
    }
  }
  return entropy;
}

}  // namespace itl
