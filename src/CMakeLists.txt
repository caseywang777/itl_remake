# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Add subdirectories to the build.
add_subdirectory (core)
add_subdirectory (io)
add_subdirectory (math)
add_subdirectory (stat)
add_subdirectory (algorithm)
add_subdirectory (extras)

option (ITL_BUILD_PARALLEL "Build the parallel library." OFF)

if (ITL_BUILD_PARALLEL)
  add_subdirectory (parallel)
endif ()
