// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "io/raw_reader.h"

#include "core/basic_types.h"
#include "core/cartesian_grid.h"
#include "core/field.h"
#include "core/float_array.h"
#include "io/console.h"

namespace itl {

std::unique_ptr<Field> RawReader::LoadData(
    std::initializer_list<std::pair<const char*, int>> file_list,
    bool with_header) {
  if (with_header) {
    FILE* file;
    file = fopen(file_list.begin()->first, "rb");
    int dimensions[3];
    fread(dimensions, sizeof(int), 3, file);
    set_dimensions(dimensions[0], dimensions[1], dimensions[2]);
    fclose(file);
  }

  int data_size = x_dim_ * y_dim_ * z_dim_;
  std::unique_ptr<Grid> grid(new CartesianGrid(x_dim_, y_dim_, z_dim_,
                                               x_bias_, y_bias_, z_bias_));

  std::unique_ptr<Field> field(new Field());
  field->set_grid(grid.release());

  for (auto it = file_list.begin(); it != file_list.end(); ++it) {
    FILE* file;
    file = fopen(it->first, "rb");

    if (with_header) {
      int dimensions[3];
      fread(dimensions, sizeof(int), 3, file);
    }

    std::unique_ptr<AbstractArray> array;

    switch (it->second) {
      case kFloat:
        array.reset(new FloatArray(data_size));
        fread(static_cast<FloatArray*>(array.get())->data(),
              sizeof(float), data_size, file);
        break;
      default:
        Console::Warn("RawReader::LoadData() given unsupported data type.");
    }

    fclose(file);
    field->attach_variable(array.release());
  }

  return field;
}

}  // namespace itl
