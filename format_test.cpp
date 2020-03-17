#include <gtest/gtest.h>

#include <format>
using namespace std;

struct BasicFormatTest : testing::Test {};

struct FormatTest : testing::Test {};

struct IntegerFormatTest : FormatTest {};

TEST_F(BasicFormatTest, BasicFormatTest_SimpleFormat_Test) {
  EXPECT_EQ(format("{}", 42), "42");
}

TEST_F(BasicFormatTest, BasicFormatTest_NotFormatted_Test) {
  EXPECT_EQ(format("Plain Text"), "Plain Text");
  EXPECT_EQ(format("Plain Text {{"), "Plain Text {");
  EXPECT_EQ(format("Plain Text {{{{"), "Plain Text {{");
  EXPECT_EQ(format("Plain Text {{}}"), "Plain Text {}");
  EXPECT_EQ(format("Plain Text {{}}", "Unused"), "Plain Text {}");
  EXPECT_EQ(format("Plain Text {{}}", "Unused", 42), "Plain Text {}");
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
  EXPECT_EQ(format("{}", nullptr), "0");
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

TEST_F(BasicFormatTest, BasicFormatTest_Specialized_Test) {
  auto pi = 3.1415926535;
  char buf[100];
  sprintf(buf, "%g %a %e %f", pi, pi, pi, pi);
  EXPECT_EQ(format("{:g} {:a} {:e} {:f}", pi, pi, pi, pi), buf);
}

TEST_F(IntegerFormatTest, IntegerFormatTest_Basic_Test) {
  using i8 = int8_t;
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using u8 = uint8_t;
  using u16 = uint16_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  auto test_default = [](auto v) { EXPECT_EQ(format("{}", v), to_string(v)); };
  auto test_default_all_types = [&test_default](auto v) {
    test_default(i8(v));
    test_default(i16(v));
    test_default(i32(v));
    test_default(i64(v));
    test_default(u8(v));
    test_default(u16(v));
    test_default(u32(v));
    test_default(u64(v));
  };

  auto test_default_max_min = [&test_default]<class T>() {
    test_default(numeric_limits<T>::max());
    test_default(numeric_limits<T>::min());
  };
  auto test_default_max_min_all_types = [&] {
    test_default_max_min.operator()<i8>();
    test_default_max_min.operator()<i16>();
    test_default_max_min.operator()<i32>();
    test_default_max_min.operator()<i64>();
    test_default_max_min.operator()<u8>();
    test_default_max_min.operator()<u16>();
    test_default_max_min.operator()<u32>();
    test_default_max_min.operator()<u64>();
  };

  // default format for all integral types
  // positive
  test_default_all_types(42);
  // negative
  test_default_all_types(-42);
  // zero
  test_default_all_types(0);
  // max and min values
  test_default_max_min_all_types();
}
