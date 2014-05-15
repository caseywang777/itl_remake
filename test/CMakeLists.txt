# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Load settings for the gtest project.
set (GTEST_ROOT "" CACHE PATH "The root directory of the gtest install prefix.")
find_package (GTest REQUIRED)
include_directories ("${GTEST_INCLUDE_DIRS}")

# Add subdirectories to the build.
add_subdirectory (math)
