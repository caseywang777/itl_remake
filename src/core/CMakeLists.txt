# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Add the core library to the project.
add_library (itl_core abstract_array.cc float_array.cc grid.cc
             cartesian_grid.cc field.cc)
