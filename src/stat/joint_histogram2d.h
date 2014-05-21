// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef STAT_JOINT_HISTOGRAM2D_H_
#define STAT_JOINT_HISTOGRAM2D_H_

#include <memory>

#include "stat/bins.h"

namespace itl {

class STAT_EXPORT JointHistogram2D {
 public:
  JointHistogram2D(const std::shared_ptr<const Bins>& bins_x,
                   const std::shared_ptr<const Bins>& bins_y);
  ~JointHistogram2D();
  JointHistogram2D(const JointHistogram2D&);
  JointHistogram2D& operator=(const JointHistogram2D&);

  const std::shared_ptr<const Bins>& bins_x() const { return bins_x_; }
  const std::shared_ptr<const Bins>& bins_y() const { return bins_y_; }

  const std::vector<float>& frequencies() const { return frequencies_; }
  float get_frequency(size_t x, size_t y) const {
    return frequencies_[Index2DTo1D(x, y)];
  }
  float get_frequency(double v1, double v2) const;

  float get_sample_size() const;
  void get_probabilities(std::vector<float>& p) const;
  // void get_cumulative_probabilities(std::vector<float>& cp) const;
  JointHistogram2D& Normalize();

  JointHistogram2D& Clear();
  JointHistogram2D& Insert(double v1, double v2);
  JointHistogram2D& Insert(double v1, double v2, double weight);

 private:
  JointHistogram2D() = delete;

  size_t Index2DTo1D(size_t x, size_t y) const {
    return y + x * bins_y_->get_bin_number();
  }

  std::shared_ptr<const Bins> bins_x_, bins_y_;
  std::vector<float> frequencies_;
};

}  // namespace itl

#endif  // STAT_JOINT_HISTOGRAM2D_H_
