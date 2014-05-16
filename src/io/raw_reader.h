// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef IO_RAW_READER_H_
#define IO_RAW_READER_H_

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

#include "io/io_export.h"

namespace itl {

class Field;

class IO_EXPORT RawReader {
 public:
  RawReader() = default;
  RawReader(size_t x_dim, size_t y_dim, size_t z_dim)
      : x_dim_(x_dim), y_dim_(y_dim), z_dim_(z_dim) {}
  RawReader(size_t x_dim, size_t y_dim, size_t z_dim,
            size_t x_bias, size_t y_bias, size_t z_bias)
      : x_dim_(x_dim), y_dim_(y_dim), z_dim_(z_dim),
        x_bias_(x_bias), y_bias_(y_bias), z_bias_(z_bias) {}

  ~RawReader() = default;

  size_t x_dim() const { return x_dim_; }
  size_t y_dim() const { return y_dim_; }
  size_t z_dim() const { return z_dim_; }

  RawReader& set_dimensions(size_t x_dim, size_t y_dim, size_t z_dim) {
    x_dim_ = x_dim; y_dim_ = y_dim; z_dim_ = z_dim;
    return *this;
  }

  size_t x_bias() const { return x_bias_; }
  size_t y_bias() const { return y_bias_; }
  size_t z_bias() const { return z_bias_; }

  RawReader& set_biases(size_t x_bias, size_t y_bias, size_t z_bias) {
    x_bias_ = x_bias; y_bias_ = y_bias; z_bias_ = z_bias;
    return *this;
  }

  std::unique_ptr<Field> LoadData(
      std::initializer_list<std::pair<const char*, int>> file_list,
      bool with_header = false);

 private:
  RawReader(const RawReader& rhs) = delete;
  RawReader& operator=(const RawReader& rhs) = delete;

  size_t x_dim_ = 0, y_dim_ = 0, z_dim_ = 0,
         x_bias_ = 0, y_bias_ = 0, z_bias_ = 0;
};

}  // namespace itl

#endif  // IO_RAW_READER_H_
