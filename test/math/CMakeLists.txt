# Copyright (c) 2014 Wenbin He. All rights reserved.
# Use of this source code is governed by a MIT-style license that can be
# found in the LICENSE file.

# Add the test executables to the project.
add_executable (vector2_test vector2_test.cc)
target_link_libraries (vector2_test ${GTEST_BOTH_LIBRARIES})

# Add tests to the project.
add_test (AllTestsInVector2 vector2_test)
