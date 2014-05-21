// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "stat/bins.h"

#include <cassert>
#include <cmath>
#include <limits>

namespace itl {

bool Bins::IsEqual(const Bins& rhs) const {
  const double epsilon = std::numeric_limits<double>::epsilon();
  if (get_bin_number() != rhs.get_bin_number() ||
      std::abs(get_min_value() - rhs.get_min_value()) > epsilon) {
    return false;
  } else {
    for (size_t i = 0, il = get_bin_number(); i < il; ++i) {
      if (std::abs(get_bin_width(i) - rhs.get_bin_width(i)) > epsilon)
        return false;
    }
    return true;
  }
}

Bins::Bins() = default;

Bins::~Bins() = default;

RegularBins::RegularBins(const double min_value, const double max_value,
                         const size_t bin_number)
    : Bins(), min_value_(min_value),
      bin_width_((max_value - min_value) / bin_number),
      bin_number_(bin_number) {
  assert(bin_number > 0);
  assert(max_value > min_value);
}

RegularBins::~RegularBins() = default;

double RegularBins::get_min_value() const {
  return min_value_;
}

double RegularBins::get_max_value() const {
  return min_value_ + bin_number_ * bin_width_;
}

size_t RegularBins::get_bin_number() const {
  return bin_number_;
}

double RegularBins::get_bin_width(const size_t bin_id) const {
  return bin_width_;
}

double RegularBins::get_bin_center(const size_t bin_id) const {
  return min_value_ + (bin_id + 0.5) * bin_width_;
}

std::pair<double, double> RegularBins::get_bin_interval(
    const size_t bin_id) const {
  return {min_value_ + bin_id * bin_width_,
          min_value_ + (bin_id + 1) * bin_width_};
}

// TODO(wenbin): improve the performance of this function.
size_t RegularBins::ValueToBinIndex(const double value) const {
  int bin_id = std::floor((value - min_value_) / bin_width_);
  const double epsilon = std::numeric_limits<double>::epsilon();
  if (bin_id >= 0 && bin_id < static_cast<int>(bin_number_))
    return bin_id;
  else if (std::abs(value - get_max_value()) < epsilon)
    return bin_number_ - 1;
  else
    return bin_number_;
}

IrregularBins::IrregularBins(const std::vector<double>& bin_intervals)
    : Bins(), bin_intervals_(bin_intervals) {
  assert(IsValid());
}

IrregularBins::~IrregularBins() = default;

double IrregularBins::get_min_value() const {
  return bin_intervals_[0];
}

double IrregularBins::get_max_value() const {
  return *(bin_intervals_.end() - 1);
}

size_t IrregularBins::get_bin_number() const {
  return bin_intervals_.size() - 1;
}

double IrregularBins::get_bin_width(const size_t bin_id) const {
  return bin_intervals_[bin_id + 1] - bin_intervals_[bin_id];
}

double IrregularBins::get_bin_center(const size_t bin_id) const {
  return (bin_intervals_[bin_id] + bin_intervals_[bin_id + 1]) / 2;
}

std::pair<double, double> IrregularBins::get_bin_interval(
    const size_t bin_id) const {
  return {bin_intervals_[bin_id], bin_intervals_[bin_id + 1]};
}

// TODO(wenbin): improve the performance of this function.
size_t IrregularBins::ValueToBinIndex(const double value) const {
  const size_t bin_number = get_bin_number();
  const double epsilon = std::numeric_limits<double>::epsilon();
  if (value >= get_min_value() && value < get_max_value()) {
    for (size_t i = 1, il = bin_intervals_.size(); i < il; ++i) {
      if (value < bin_intervals_[i])
        return i - 1;
    }
    return bin_number;
  } else if (std::abs(value - get_max_value()) < epsilon) {
    return bin_number - 1;
  } else {
    return bin_number;
  }
}

bool IrregularBins::IsValid() const {
  if (bin_intervals_.size() < 2) {
    return false;
  } else {
    for (size_t i = 0, il = get_bin_number() - 1; i < il; ++i) {
      if (bin_intervals_[i] >= bin_intervals_[i + 1])
        return false;
    }
    return true;
  }
}

}  // namespace itl
