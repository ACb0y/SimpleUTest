//
// Created by ACb0y on 2022/4/5.
//

#include <iostream>
#include "UTestCore.h"
using namespace std;

int fun1(int value) {
  return value;
}

bool fun2() {
  return true;
}

bool fun3() {
  return false;
}

TEST_CASE(fun1Test) {
  ASSERT_EQ(fun1(1), 1);
  ASSERT_TRUE(fun2());
  ASSERT_FALSE(fun3());
  // !=
  ASSERT_NE(fun1(1), 0);
  // >
  ASSERT_GT(fun1(1), 0);
  // >=
  ASSERT_GE(fun1(1), 1);
  // <
  ASSERT_LT(fun1(2), 3);
  // <=
  ASSERT_LE(fun1(2), 2);
}

TEST_CASE(func2Test) {
  ASSERT_TRUE(not fun3());
}

RUN_ALL_TESTS();
