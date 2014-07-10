// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_ABSTRACT_ARRAY_H_
#define CORE_ABSTRACT_ARRAY_H_

#include <cstddef>
#include <utility>

#include "core/core_export.h"

namespace itl {

class CORE_EXPORT AbstractArray {
 public:
  virtual ~AbstractArray();

  virtual size_t size() const = 0;
  virtual size_t tuple_number() const = 0;
  virtual size_t tuple_size() const = 0;

  virtual double element(size_t data_id) const = 0;
  virtual double element(size_t tuple_id, size_t element_id) const = 0;
  virtual AbstractArray* set_element(size_t data_id, double value) = 0;
  virtual AbstractArray* set_element(size_t tuple_id, size_t element_id,
                                     double value) = 0;

  virtual const AbstractArray* tuple(size_t tuple_id,
                                     double* begin, double* end) const = 0;
  virtual AbstractArray* set_tuple(size_t tuple_id,
                                   const double* begin, const double* end) = 0;

  virtual double MinValue() const = 0;
  virtual double MaxValue() const = 0;
  virtual std::pair<double, double> MinMaxValue() const = 0;

  virtual int DataType() const = 0;
  virtual size_t DataTypeSize() const = 0;

 protected:
  AbstractArray() = default;

 private:
  AbstractArray(const AbstractArray& rhs) = delete;
  AbstractArray& operator=(const AbstractArray& rhs) = delete;
};

}  // namespace itl

#endif  // CORE_ABSTRACT_ARRAY_H_
