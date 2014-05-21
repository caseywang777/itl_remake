// Copyright (c) 2014 The ITLREMAKE Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_H_
#define CORE_TYPED_ARRAY_H_

#include <memory>

#include "core/abstract_array.h"
#include "core/core_export.h"

namespace itl {

/// A template for a typed array class derived from the abstract array class.
/// The underly array is stored in a unique_ptr.
template <typename Type>
class CORE_EXPORT TypedArray : public AbstractArray {
 public:
  virtual ~TypedArray();

  virtual size_t size() const { return tuple_number_ * tuple_size_; }
  virtual size_t tuple_number() const { return tuple_number_; }
  virtual size_t tuple_size() const { return tuple_size_; }

  virtual double element(const size_t data_id) const {
    return static_cast<double>(data_[data_id]);
  }

  virtual double element(const size_t tuple_id,
                         const size_t element_id) const {
    return static_cast<double>(data_[tuple_id * tuple_size_ + element_id]);
  }

  virtual void set_element(const size_t data_id, const double value) {
    data_[data_id] = static_cast<Type>(value);
  }

  virtual void set_element(const size_t tuple_id, const size_t element_id,
                           const double value) {
    data_[tuple_id * tuple_size_ + element_id] = static_cast<Type>(value);
  }

  virtual void tuple(const size_t tuple_id,
                     double* begin, double* end) const;
  virtual void set_tuple(const size_t tuple_id,
                         const double* begin, const double* end);

  virtual size_t DataTypeSize() const { return sizeof(Type); }

  virtual bool Empty() const { return size() == 0; }
  virtual void Clear();
  virtual void Resize(const size_t tuple_number,
                      const size_t tuple_size);

  virtual double MinValue() const;
  virtual double MaxValue() const;
  virtual std::pair<double, double> MinMaxValue() const;
  virtual double MinMagnitude() const;
  virtual double MaxMagnitude() const;
  virtual std::pair<double, double> MinMaxMagnitude() const;

  /// Returns a direct pointer to the memory array.
  Type* data();
  /// Returns a const direct pointer to the memory array.
  const Type* data() const;

  /// Returns a reference to the element at position n in the array.
  Type& operator[](const size_t n);
  /// Returns a const reference to the element at position n in the array.
  const Type& operator[](const size_t n) const;

  // TODO(wenbin): figure out how to set & get data by the original type.

  // TODO(wenbin): design swap, conversion, deep copy, and transformation
  // behaviors.

 protected:
  TypedArray();
  explicit TypedArray(const size_t tuple_number);
  TypedArray(const size_t tuple_number, const size_t tuple_size);
  /// It is the user's responsibility to make sure that the length of the data
  /// array is equal to the production of the tuple number and tuple size.
  TypedArray(const size_t tuple_number, const size_t tuple_size,
             Type* data);
  TypedArray(const TypedArray&) = delete;
  TypedArray& operator=(const TypedArray&) = delete;

 private:
  size_t tuple_number_ = 0, tuple_size_ = 1;
  std::unique_ptr<Type[]> data_;
};

}  // namespace itl

#endif  // CORE_TYPED_ARRAY_H_
