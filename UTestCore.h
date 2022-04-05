//
// Created ACb0y on 2022/4/3.
//

#pragma once

#include <string>
#include <vector>

namespace SimpleUTest {

class TestCase {
public:
  virtual void Run() = 0;
  virtual void Before() {}
  virtual void After() {}
  bool Result() {
    return result;
  }
  void SetResult(bool ret) {
    result = ret;
  }
  std::string CaseName() {
    return caseName;
  }
  TestCase(std::string name) : caseName(name) { result = true; }
private:
  bool result;
  std::string caseName;
};

class UnitTestCore {
public:
  static UnitTestCore * GetInstance() {
    static UnitTestCore instance;
    return &instance;
  }

  void Run() {
    failedCnt = 0;
    successCnt = 0;
    testResult = true;
    std::cout << "[==============================] Running " << testCases.size() << " test case." << std::endl;
    for (int i = 0; i < testCases.size(); i++) {
      std::cout << "Run TestCase:" << testCases[i]->CaseName() << std::endl;
      testCases[i]->Before();
      testCases[i]->Run();
      testCases[i]->After();
      std::cout << "End TestCase:" << testCases[i]->CaseName() << std::endl;
      if (testCases[i]->Result()) {
        successCnt++;
      } else {
        failedCnt++;
        testResult = false;
      }
    }
    std::cout << "[==============================] Total TestCase:" << testCases.size() << std::endl;
    std::cout << "Passed:" << successCnt << std::endl;
    std::cout << "Failed:" << failedCnt << std::endl;
  }

  TestCase * RegisterTestCase(TestCase * testCase) {
    testCases.push_back(testCase);
    return testCase;
  }

private:
  bool testResult;
  int32_t successCnt;
  int32_t failedCnt;
  std::vector<TestCase *> testCases; // 测试用例集合
};

#define TEST_CASE_CLASS(test_case_name) \
class test_case_name##_TEST : public SimpleUTest::TestCase { \
public:                             \
  test_case_name##_TEST(std::string caseName) : SimpleUTest::TestCase(caseName) {} \
  virtual void Run();               \
private:                            \
  static SimpleUTest::TestCase * const testcase; \
};                                  \
SimpleUTest::TestCase * const test_case_name##_TEST::testcase = \
  SimpleUTest::UnitTestCore::GetInstance()->RegisterTestCase(new test_case_name##_TEST(#test_case_name)); \
void test_case_name##_TEST::Run()

#define TEST_CASE(test_case_name) \
  TEST_CASE_CLASS(test_case_name)

#define ASSERT_EQ(left, right) \
  if (left != right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << "!=" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_NE(left, right) \
  if (left == right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << "==" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_LT(left, right) \
  if (left >= right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << ">=" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_LE(left, right) \
  if (left > right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << ">" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_GT(left, right) \
  if (left <= right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << "<=" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_GE(left, right) \
  if (left < right) \
  { \
    std::cout << "failed at " <<  __FILE__ << ":" << __LINE__ << "." << left << "<" << right << std::endl; \
    SetResult(false); \
    return; \
  }

#define ASSERT_TRUE(expr) ASSERT_EQ(expr, true)
#define ASSERT_FALSE(expr) ASSERT_EQ(expr, false)

#define RUN_ALL_TESTS() \
  SimpleUTest::UnitTestCore::GetInstance()->Run()

}

