// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef STAT_BINS_H_
#define STAT_BINS_H_

#include <cstddef>
#include <utility>
#include <vector>

#include "stat/stat_export.h"

namespace itl {

/// Defines a base bins class. This class is used to represent the bins in
/// histograms. Defines several interfaces to get properties from the bins.
class STAT_EXPORT Bins {
 public:
  virtual double get_min_value() const = 0;
  virtual double get_max_value() const = 0;

  virtual size_t get_bin_number() const = 0;
  /// Get the width from the specified bin.
  virtual double get_bin_width(const size_t bin_id) const = 0;
  /// Get the center from the specified bin.
  virtual double get_bin_center(const size_t bin_id) const = 0;
  /// Get the interval from the specified bin.
  virtual std::pair<double, double> get_bin_interval(
      const size_t bin_id) const = 0;

  bool IsEqual(const Bins& rhs) const;

  /// Get the bin index of the given value. The intervals are left closed
  /// and right open, but both closed for the last bin. Return the index of
  /// the last bin plus one if the given value is out of range.
  virtual size_t ValueToBinIndex(const double value) const = 0;

 protected:
  Bins();
  virtual ~Bins();
  Bins(const Bins&) = delete;
  Bins& operator=(const Bins&) = delete;
};

/// Returns true if two bins objects have the same intervals.
inline bool operator==(const Bins& lhs, const Bins& rhs) {
  return lhs.IsEqual(rhs);
}

/// Defines the regular bins class inherited from the bins base class, which
/// represents the bins with equal bin width.
class STAT_EXPORT RegularBins : public Bins {
 public:
  RegularBins(const double min_value, const double max_value,
              const size_t bin_number);
  virtual ~RegularBins();

  virtual double get_min_value() const;
  virtual double get_max_value() const;

  virtual size_t get_bin_number() const;
  virtual double get_bin_width(const size_t bin_id) const;
  virtual double get_bin_center(const size_t bin_id) const;
  virtual std::pair<double, double> get_bin_interval(const size_t bin_id) const;

  virtual size_t ValueToBinIndex(const double value) const;

 private:
  RegularBins() = delete;
  RegularBins(const RegularBins&) = delete;
  RegularBins& operator=(const RegularBins&) = delete;

  double min_value_, bin_width_;
  size_t bin_number_;
};

/// Defines the irregular bins class inherited from the bins base class,
/// which represents the bins with unequal bin width.
class STAT_EXPORT IrregularBins : public Bins {
 public:
  explicit IrregularBins(const std::vector<double>& bin_intervals);
  virtual ~IrregularBins();

  virtual double get_min_value() const;
  virtual double get_max_value() const;

  virtual size_t get_bin_number() const;
  virtual double get_bin_width(const size_t bin_id) const;
  virtual double get_bin_center(const size_t bin_id) const;
  virtual std::pair<double, double> get_bin_interval(const size_t bin_id) const;

  virtual size_t ValueToBinIndex(const double value) const;

 private:
  IrregularBins() = delete;
  IrregularBins(const IrregularBins&) = delete;
  IrregularBins& operator=(const IrregularBins&) = delete;

  bool IsValid() const;

  std::vector<double> bin_intervals_;
};

}  // namespace itl

#endif  // STAT_BINS_H_
