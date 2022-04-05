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
  ASSERT_EQ(fun1(2), 2);
  ASSERT_EQ(fun1(2), 2);
  ASSERT_TRUE(fun2());
  ASSERT_FALSE(fun3());
}

int main() {
  RUN_ALL_TESTS();
  return 0;
}
