// Copyright (c) 2014 Wenbin He. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "gtest/gtest.h"
#include "math/vector2.h"

namespace itl {

TEST(Vector2, Constructor) {
  Vector2 vec_a;
  EXPECT_DOUBLE_EQ(0.0, vec_a.x());
  EXPECT_DOUBLE_EQ(0.0, vec_a.y());

  Vector2 vec_b(2.0);
  EXPECT_DOUBLE_EQ(2.0, vec_b.x());
  EXPECT_DOUBLE_EQ(2.0, vec_b.y());

  Vector2 vec_c(2.0, 3.0);
  EXPECT_DOUBLE_EQ(2.0, vec_c.x());
  EXPECT_DOUBLE_EQ(3.0, vec_c.y());
}

TEST(Vector2, Copy) {
  Vector2 vec_a(2.0, 3.0);
  Vector2 vec_b(vec_a);
  EXPECT_EQ(vec_a, vec_b);

  Vector2F vec_c(vec_a);
  EXPECT_FLOAT_EQ(2.0f, vec_c.x());
  EXPECT_FLOAT_EQ(3.0f, vec_c.y());

  Vector2 vec_d(4.0, 5.0);
  vec_b = vec_d;
  EXPECT_EQ(vec_d, vec_b);

  vec_c = vec_d;
  EXPECT_FLOAT_EQ(4.0f, vec_c.x());
  EXPECT_FLOAT_EQ(5.0f, vec_c.y());
}

TEST(Vector2, Set_Get) {
  Vector2 vec_a;
  vec_a.set_x(2.0);
  vec_a.set_y(3.0);
  EXPECT_DOUBLE_EQ(2.0, vec_a.x());
  EXPECT_DOUBLE_EQ(3.0, vec_a.y());

  Vector2 vec_b;
  vec_b.set(2.0, 3.0);
  EXPECT_DOUBLE_EQ(2.0, vec_b.x());
  EXPECT_DOUBLE_EQ(3.0, vec_b.y());

  Vector2 vec_c;
  vec_c[0] = 2.0;
  vec_c[1] = 3.0;
  EXPECT_EQ(vec_a, vec_c);
}

TEST(Vector2, Negate) {
  Vector2 vec_a(2.0, 3.0);
  vec_a = -vec_a;
  EXPECT_DOUBLE_EQ(-2.0, vec_a.x());
  EXPECT_DOUBLE_EQ(-3.0, vec_a.y());
}

TEST(Vector2, Add) {
  Vector2 vec_a(2.0, 3.0);
  Vector2F vec_b(-2.0f, -3.0f);
  vec_a += vec_b;
  EXPECT_DOUBLE_EQ(0.0, vec_a.x());
  EXPECT_DOUBLE_EQ(0.0, vec_a.y());

  vec_a += 2.0;
  EXPECT_DOUBLE_EQ(2.0, vec_a.x());
  EXPECT_DOUBLE_EQ(2.0, vec_a.y());

  Vector2 vec_c = vec_a + vec_b;
  EXPECT_DOUBLE_EQ(0.0, vec_c.x());
  EXPECT_DOUBLE_EQ(-1.0, vec_c.y());
}

TEST(Vector2, Sub) {
  Vector2 vec_a(2.0, 3.0);
  Vector2F vec_b(-2.0f, -3.0f);
  vec_a -= vec_b;
  EXPECT_DOUBLE_EQ(4.0, vec_a.x());
  EXPECT_DOUBLE_EQ(6.0, vec_a.y());

  Vector2 vec_c = vec_a - vec_b;
  EXPECT_DOUBLE_EQ(6.0, vec_c.x());
  EXPECT_DOUBLE_EQ(9.0, vec_c.y());
}

TEST(Vector2, Multiply_Divide) {
  Vector2 vec_a(2.0, 3.0);
  vec_a *= -2.0;
  EXPECT_DOUBLE_EQ(-4.0, vec_a.x());
  EXPECT_DOUBLE_EQ(-6.0, vec_a.y());

  vec_a /= -2.0;
  EXPECT_DOUBLE_EQ(2.0, vec_a.x());
  EXPECT_DOUBLE_EQ(3.0, vec_a.y());
}

}  // namespace itl
