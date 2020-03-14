#include <gtest/gtest.h>

#include <format>

class FormatTest : public testing::Test {};

TEST_F(FormatTest, FormatTest_SimpleFormat_Test) {
  using namespace std;
  EXPECT_EQ(format("{}", 'x'), "x");
  EXPECT_EQ(format("{}", 42), "42");
  EXPECT_EQ(format("{}", 42L), "42");
  EXPECT_EQ(format("{}", 42LL), "42");
  EXPECT_EQ(format("{}", "x"), "x");
  EXPECT_EQ(format("{}", false), "false");
}
