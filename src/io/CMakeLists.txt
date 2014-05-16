# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Add the io library to the project.
add_library (itl_io console.cc raw_reader.cc)
target_link_libraries (itl_io itl_core)
