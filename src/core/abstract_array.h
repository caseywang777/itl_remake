// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_ABSTRACT_ARRAY_H_
#define CORE_ABSTRACT_ARRAY_H_

#include <cstddef>
#include <utility>

#include "core/core_export.h"

namespace itl {

/// Defines the abstract array class. Provides several interfaces to access and
/// modify the underlying data array.
class CORE_EXPORT AbstractArray {
 public:
  virtual ~AbstractArray();

  /// Get number of elements for the whole array.
  virtual size_t size() const = 0;
  /// Get number of tuples.
  virtual size_t tuple_number() const = 0;
  /// Get number of elements per tuple.
  virtual size_t tuple_size() const = 0;

  /// Get element value from the specified location.
  virtual double element(const size_t data_id) const = 0;
  /// Get element value from the specified location of the specified tuple.
  virtual double element(const size_t tuple_id,
                         const size_t element_id) const = 0;
  /// Set element value at the specified location.
  virtual void set_element(const size_t data_id, const double value) = 0;
  /// Set element value at the specified location of the specified tuple.
  virtual void set_element(const size_t tuple_id, const size_t element_id,
                           const double value) = 0;

  /// Get tuple from the specified location.
  virtual void tuple(const size_t tuple_id,
                     double* begin, double* end) const = 0;
  /// Set tuple at the specified location.
  virtual void set_tuple(const size_t tuple_id,
                         const double* begin, const double* end) = 0;

  /// Returns data type of the array. For example, kFloat is the data type of
  /// an array which contains floats.
  virtual int DataType() const = 0;
  /// Returns the size of the array's data type.
  virtual size_t DataTypeSize() const = 0;

  /// Returns true if the array is empty.
  virtual bool Empty() const = 0;
  /// Remove all elements from the array.
  virtual void Clear() = 0;
  /// Resize the array based on the specified tuple number and tuple size.
  virtual void Resize(const size_t tuple_number,
                      const size_t tuple_size) = 0;

  /// Get min value of the array.
  virtual double MinValue() const = 0;
  /// Get max value of the array.
  virtual double MaxValue() const = 0;
  /// Get both min and max value of the array.
  virtual std::pair<double, double> MinMaxValue() const = 0;
  /// Get min magnitude of the tuples.
  virtual double MinMagnitude() const = 0;
  /// Get max magnitude of the tuples.
  virtual double MaxMagnitude() const = 0;
  /// Get both min and max magnitude of the tuples.
  virtual std::pair<double, double> MinMaxMagnitude() const = 0;

 protected:
  AbstractArray();
  AbstractArray(const AbstractArray&) = delete;
  AbstractArray& operator=(const AbstractArray&) = delete;
};

}  // namespace itl

#endif  // CORE_ABSTRACT_ARRAY_H_
