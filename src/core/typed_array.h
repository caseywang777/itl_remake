// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef CORE_TYPED_ARRAY_H_
#define CORE_TYPED_ARRAY_H_

#include <memory>

#include "core/abstract_array.h"

namespace itl {
namespace internal {

template <typename Type>
class CORE_EXPORT TypedArray : public AbstractArray {
 public:
  virtual ~TypedArray();

  virtual size_t size() const { return tuple_number_ * tuple_size_; }
  virtual size_t tuple_number() const { return tuple_number_; }
  virtual size_t tuple_size() const { return tuple_size_; }

  virtual double element(size_t data_id) const {
    return static_cast<double>(data_[data_id]);
  }

  virtual double element(size_t tuple_id, size_t element_id) const {
    return static_cast<double>(data_[tuple_id * tuple_size_ + element_id]);
  }

  virtual AbstractArray* set_element(size_t data_id, double value) {
    data_[data_id] = static_cast<Type>(value);
    return this;
  }

  virtual AbstractArray* set_element(size_t tuple_id, size_t element_id,
                                     double value) {
    data_[tuple_id * tuple_size_ + element_id] = static_cast<Type>(value);
    return this;
  }

  virtual const AbstractArray* tuple(size_t tuple_id,
                                     double* begin, double* end) const;
  virtual AbstractArray* set_tuple(size_t tuple_id,
                                   const double* begin, const double* end);

  virtual double MinValue() const;
  virtual double MaxValue() const;
  virtual std::pair<double, double> MinMaxValue() const;

  virtual size_t DataTypeSize() const { return sizeof(Type); }

  Type* data() { return data_.get(); }
  const Type* data() const { return data_.get(); }

 protected:
  TypedArray();
  explicit TypedArray(size_t tuple_number);
  TypedArray(size_t tuple_number, Type* data);
  TypedArray(size_t tuple_number, size_t tuple_size);
  TypedArray(size_t tuple_number, size_t tuple_size, Type* data);

 private:
  TypedArray(const TypedArray& rhs) = delete;
  TypedArray& operator=(const TypedArray& rhs) = delete;

  size_t tuple_number_ = 0, tuple_size_ = 1;
  std::unique_ptr<Type[]> data_;
};

}  // namespace internal
}  // namespace itl

#endif  // CORE_TYPED_ARRAY_H_
