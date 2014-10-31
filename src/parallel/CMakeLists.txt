# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Find the mpi package.
find_package (MPI REQUIRED)
set (CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set (CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories (MPI_INCLUDE_PATH)

# Use mpicxx to replace g++.
# Ensure that MPI compiler is using the right g++ compiler.
if (UNIX)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -cxx=${CMAKE_CXX_COMPILER} -std=c++11 -Wall")
endif ()
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

# Find diy package.
set (DIY_ROOT "" CACHE PATH "The root directory of the diy install prefix.")
set (DIY_INCLUDE_DIRS "${DIY_ROOT}/include")
set (DIY_LIBRARIES "${DIY_ROOT}/lib")

# Find zlib package (used by diy).
set (ZLIB_ROOT "" CACHE PATH "The root directory of the zlib install prefix.")
set (ZLIB_INCLUDE_DIRS "${ZLIB_ROOT}/include")
set (ZLIB_LIBRARIES "${ZLIB_ROOT}/lib")

# Include the diy directories.
include_directories (${DIY_INCLUDE_DIRS})
link_directories (${DIY_LIBRARIES})

# Add the core library to the project.
add_library (itl_parallel ParItl.cc)
target_link_libraries (itl_parallel itl_core itl_io itl_stat itl_algorithm diy z)

# Add executable.
add_executable (Block_io test/Block_io.cc)
target_link_libraries (Block_io itl_parallel)
