// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef STAT_HISTOGRAM_H_
#define STAT_HISTOGRAM_H_

#include <memory>

#include "stat/bins.h"

namespace itl {

/// Defines a histogram class, which is used to represent an estimation of
/// a distribution.
class STAT_EXPORT Histogram {
 public:
  explicit Histogram(const std::shared_ptr<const Bins>& bins);
  ~Histogram();
  Histogram(const Histogram&);
  Histogram& operator=(const Histogram&);

  const std::shared_ptr<const Bins>& bins() const { return bins_; }
  /// Set bins will reestimate the histogram based on the new bins.
  void set_bins(const std::shared_ptr<const Bins>& bins);

  const std::vector<float>& frequencies() const { return frequencies_; }
  /// Get the frequency from the specified bin.
  float get_frequency(const size_t bin_id) const {
    return frequencies_[bin_id];
  }
  /// Estimate the frequency for the specified value.
  float get_frequency(const double value) const;

  float get_sample_size() const;
  // TODO(wenbin): need a better way to deal with pdf and cdf.
  void get_probabilities(std::vector<float>& p) const;
  void get_cumulative_probabilities(std::vector<float>& cp) const;
  Histogram& Normalize();

  Histogram& Clear();
  Histogram& Insert(const double value);
  Histogram& Insert(const double value, const double weight);

  double Mean() const;
  double Median() const;
  double Mode() const;
  double Variance(const double mean, bool inference = false) const;
  double StandardDeviation(const double mean, bool inference = false) const;

  /// Returns true if two histograms have same or equal bins.
  bool IsAligned(const Histogram& h) const;
  /// Reestimate the histogram based on the bins of the given histogram.
  Histogram& AlignWith(const Histogram& h);

  Histogram& operator+=(const Histogram& rhs);
  Histogram& operator-=(const Histogram& rhs);

 private:
  Histogram() = delete;

  std::shared_ptr<const Bins> bins_;
  std::vector<float> frequencies_;
};

inline Histogram operator+(const Histogram& lhs, const Histogram& rhs) {
  Histogram h(lhs);
  return h += rhs;
}

inline Histogram operator-(const Histogram& lhs, const Histogram& rhs) {
  Histogram h(lhs);
  return h -= rhs;
}

}  // namespace itl

#endif  // STAT_HISTOGRAM_H_
