#include <gtest/gtest.h>

#include <format>
using namespace std;

struct FormatTest : testing::Test {};

struct BasicFormatTest : FormatTest {};

TEST_F(FormatTest, FormatTest_SimpleFormat_Test) {
  EXPECT_EQ(format("{}", 42), "42");
}

TEST_F(BasicFormatTest, BasicFormatTest_BasicType_Test) {
  EXPECT_EQ(format("{}", 'x'), "x");
  EXPECT_EQ(format("{}", "x"), "x");
  EXPECT_EQ(format("{}", false), "false");
  EXPECT_EQ(format("{}", true), "true");
  EXPECT_EQ(format("{}", (int8_t)42), "42");
  EXPECT_EQ(format("{}", (uint8_t)42), "42");
  EXPECT_EQ(format("{}", (short)42), "42");
  EXPECT_EQ(format("{}", (unsigned short)42), "42");
  EXPECT_EQ(format("{}", 42), "42");
  EXPECT_EQ(format("{}", 42U), "42");
  EXPECT_EQ(format("{}", 42L), "42");
  EXPECT_EQ(format("{}", 42UL), "42");
  EXPECT_EQ(format("{}", 42LL), "42");
  EXPECT_EQ(format("{}", 42ULL), "42");
  EXPECT_EQ(format("{}", 42.0), "42.000000");
  EXPECT_EQ(format("{}", 42.0F), "42.000000");
  EXPECT_EQ(format("{}", 42.0L), "42.000000");
}

TEST_F(BasicFormatTest, BasicFormatTest_Indexed_Test) {
  // empty format
  EXPECT_EQ(format("{}, {}. {}", 1, 2, 3), "1, 2. 3");
  EXPECT_EQ(format("{}{}{}", 3, 2, 1), "321");
  // empty format with a trivial colon
  EXPECT_EQ(format("{:}{:}{:}", 1, 2, 3), "123");
  EXPECT_EQ(format("{:}{:}{}", 1, 2, 3), "123");
  // indexed
  EXPECT_EQ(format("{0}{0}{0}", 1, 2, 3), "111");
  EXPECT_EQ(format("{2}{1}{0}", 1, 2, 3), "321");
  // indexed with a trivial colon
  EXPECT_EQ(format("{0:}{0:}{0:}", 1, 2, 3), "111");
  EXPECT_EQ(format("{2:}{1:}{0}", 1, 2, 3), "321");
  // error: mixed use of auto indexing and manual indexing
  EXPECT_THROW(format("{}{1}", 0, 1), format_error);
  EXPECT_THROW(format("{:}{1:}", 0, 1), format_error);
  EXPECT_THROW(format("{0:}{:}", 0, 1), format_error);
}
