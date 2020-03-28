#include <gtest/gtest.h>

#include <charconv>
#include <format>
#include <iterator>
#include <string>
using namespace std;

#define EXPECT_FORMAT_ERROR(exp) EXPECT_THROW(exp, format_error)

struct BasicFormatTest : testing::Test {};
struct FormatTest : testing::Test {};
struct FillAlignShiftTest;
struct IntegerFormatTest;
struct FloatingPointFormatTest;
struct UserDefinedFormatTest;

TEST_F(BasicFormatTest, BasicFormatTest_SimpleFormat_Test) {
  // HELLO WORLD
  EXPECT_EQ(format("{}", 42), "42");
}

TEST_F(BasicFormatTest, BasicFormatTest_NotFormatted_Test) {
  // Plain text that should not be formatted.
  EXPECT_EQ(format("Plain Text"), "Plain Text");
  EXPECT_EQ(format("Plain Text {{"), "Plain Text {");
  EXPECT_EQ(format("Plain Text {{{{"), "Plain Text {{");
  EXPECT_EQ(format("Plain Text {{}}"), "Plain Text {}");
  EXPECT_EQ(format("Plain Text {{}}", "Unused"), "Plain Text {}");
  EXPECT_EQ(format("Plain Text {{}}", "Unused", 42), "Plain Text {}");
}

TEST_F(BasicFormatTest, BasicFormatTest_BasicType_Test) {
  // Simple basic types formatting test.
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
  EXPECT_FORMAT_ERROR(format("{}{1}", 0, 1));
  EXPECT_FORMAT_ERROR(format("{:}{1:}", 0, 1));
  EXPECT_FORMAT_ERROR(format("{0:}{:}", 0, 1));
}

TEST_F(BasicFormatTest, BasicFormatTest_Specialized_Test) {
  auto pi = 3.1415926535;
  char buf[100];
  sprintf(buf, "%g %a %e %f", pi, pi, pi, pi);
  EXPECT_EQ(format("{:g} {:a} {:e} {:f}", pi, pi, pi, pi), buf);
}

struct IntegerFormatTest : FormatTest {
  using i8 = int8_t;
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using u8 = uint8_t;
  using u16 = uint16_t;
  using u32 = uint32_t;
  using u64 = uint64_t;
};

TEST_F(IntegerFormatTest, IntegerFormatTest_Basic_Test) {
  auto test_default = [](auto v) {
    EXPECT_EQ(format("{}", v), to_string(v)) << v;
  };
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

  auto test_default_max_min = [&test_default]<class T>(T) {
    test_default(numeric_limits<T>::max());
    test_default(numeric_limits<T>::min());
  };
  auto test_default_max_min_all_types = [&] {
    test_default_max_min(i8());
    test_default_max_min(i16());
    test_default_max_min(i32());
    test_default_max_min(i64());
    test_default_max_min(u8());
    test_default_max_min(u16());
    test_default_max_min(u32());
    test_default_max_min(u64());
  };

  // default format for all integral types
  // positive
  test_default_all_types(42);
  test_default_all_types(1);
  // negative
  test_default_all_types(-42);
  test_default_all_types(-1);
  // zero
  test_default_all_types(0);
  // max and min values
  test_default_max_min_all_types();

  auto to_chars_base = [](auto v, int base) -> string {
    char buf[100];
    auto &&[ptr, ec] = to_chars(begin(buf), end(buf), v, base);
    if (ec != errc{}) {
      throw;
    }
    return string(buf, ptr);
  };
  auto test_for_integer_type_spec = [&to_chars_base](int base) {
    auto test_base = [&to_chars_base](auto v, int base) {
      const char *fmt;
      switch (base) {
      case 2:
        fmt = "{:b}";
        break;
      case 8:
        fmt = "{:o}";
        break;
      case 10:
        fmt = "{:d}";
        break;
      case 16:
        fmt = "{:x}";
        break;
      default:
        throw;
      }
      EXPECT_EQ(format(fmt, v), to_chars_base(v, base))
          << "v: " << v << " base: " << base;
    };
    test_base(42, base);
    test_base(-42, base);
    test_base(0, base);
    test_base(1, base);
    test_base(-1, base);
    test_base(numeric_limits<uintmax_t>::max(), base);
    test_base(numeric_limits<uintmax_t>::max() - 1, base);
    test_base(numeric_limits<intmax_t>::min(), base);
    test_base(numeric_limits<intmax_t>::min() + 1, base);
  };

  auto test_chars = [] {
    auto test_char = [](int v) {
      if (v > numeric_limits<char>::max() || v < numeric_limits<char>::min()) {
        EXPECT_FORMAT_ERROR(format("{:c}", (int)v)) << v;
      } else {
        EXPECT_EQ(format("{:c}", (int)v), format("{}", (char)v)) << v;
      }
    };
    test_char(42);
    test_char(0);
    test_char(1);
    test_char(-1);
    test_char(numeric_limits<char>::min());
    test_char(numeric_limits<char>::min() + 1);
    test_char(numeric_limits<char>::min() - 1);
    test_char(numeric_limits<char>::max());
    test_char(numeric_limits<char>::max() - 1);
    test_char(numeric_limits<char>::max() + 1);
    test_char(127);
    test_char(128);
    test_char(129);
    test_char(254);
    test_char(255);
    test_char(256);
  };

  // type spec:
  // binary
  test_for_integer_type_spec(2);
  // char
  test_chars();
  // decimal
  test_for_integer_type_spec(10);
  // octal
  test_for_integer_type_spec(8);
  // hexadecimal
  test_for_integer_type_spec(16);
}

struct FloatingPointFormatTest : FormatTest {
  template <class T> constexpr static const char *tstr = "";
  template <> constexpr static const char *tstr<float> = "float";
  template <> constexpr static const char *tstr<double> = "double";
  template <> constexpr static const char *tstr<long double> = "long double";
};

TEST_F(FloatingPointFormatTest, FloatingPointFormatTest_DefaultFloat_Test) {
  // default float format chooses either fixed or scientific
  auto test_edge = []<floating_point T>(T) {
    auto test = [](T v) {
      char buf[100];
      char *bufe;
      bufe = to_chars(begin(buf), end(buf), v).ptr;
      EXPECT_EQ(format("{}", v), string(buf, bufe)) << tstr<T> << ' ' << v;
    };
    test(T(1e5) - numeric_limits<T>::epsilon() - T(1e-5));
    test(T(1e5) - numeric_limits<T>::epsilon() - T(1e-6));
    test(T(1e5) - numeric_limits<T>::epsilon() - T(1e-7));
    test(T(99999.9999990));
    test(T(99999.9999991));
    test(T(99999.9999992));
    test(T(99999.9999993));
    test(T(99999.9999994));
    test(T(99999.99999945));
    test(T(99999.99999949));
    test(T(99999.999999499));
    test(T(99999.9999995));
    test(T(99999.999999501));
    test(T(99999.9999995001));
    test(T(99999.99999950001));
    test(T(99999.999999500001));
    test(T(99999.999999505));
    test(T(99999.99999951));
    test(T(99999.9999996));
    test(T(99999.9999997));
    test(T(99999.9999998));
    test(T(99999.9999999));
  };
  test_edge((float){});
  test_edge((double){});
  test_edge((long double){});
}

TEST_F(FloatingPointFormatTest, FloatingPointFormatTest_SpecialValues_Test) {
  // check special values inf & nan
  auto test_special = []<floating_point T>(T) {
    EXPECT_EQ(format("{}", numeric_limits<T>::quiet_NaN()), "nan") << tstr<T>;
    EXPECT_EQ(format("{:+}", numeric_limits<T>::quiet_NaN()), "+nan")
        << tstr<T>;
    EXPECT_EQ(format("{:-}", numeric_limits<T>::quiet_NaN()), "nan") << tstr<T>;
    EXPECT_EQ(format("{: }", numeric_limits<T>::quiet_NaN()), " nan")
        << tstr<T>;
    EXPECT_EQ(format("{}", -numeric_limits<T>::quiet_NaN()), "-nan") << tstr<T>;
    EXPECT_EQ(format("{:+}", -numeric_limits<T>::quiet_NaN()), "-nan")
        << tstr<T>;
    EXPECT_EQ(format("{:-}", -numeric_limits<T>::quiet_NaN()), "-nan")
        << tstr<T>;
    EXPECT_EQ(format("{: }", -numeric_limits<T>::quiet_NaN()), "-nan")
        << tstr<T>;
    EXPECT_EQ(format("{}", numeric_limits<T>::infinity()), "inf") << tstr<T>;
    EXPECT_EQ(format("{:+}", numeric_limits<T>::infinity()), "+inf") << tstr<T>;
    EXPECT_EQ(format("{:-}", numeric_limits<T>::infinity()), "inf") << tstr<T>;
    EXPECT_EQ(format("{: }", numeric_limits<T>::infinity()), " inf") << tstr<T>;
    EXPECT_EQ(format("{}", -numeric_limits<T>::infinity()), "-inf") << tstr<T>;
    EXPECT_EQ(format("{:+}", -numeric_limits<T>::infinity()), "-inf")
        << tstr<T>;
    EXPECT_EQ(format("{:-}", -numeric_limits<T>::infinity()), "-inf")
        << tstr<T>;
    EXPECT_EQ(format("{: }", -numeric_limits<T>::infinity()), "-inf")
        << tstr<T>;
    EXPECT_EQ(format("{:`<5}", numeric_limits<T>::quiet_NaN()), "nan``")
        << tstr<T>;
    EXPECT_EQ(format("{:`^5}", numeric_limits<T>::quiet_NaN()), "`nan`")
        << tstr<T>;
    EXPECT_EQ(format("{:`>5}", numeric_limits<T>::quiet_NaN()), "``nan")
        << tstr<T>;
    EXPECT_EQ(format("{:`<5.0}", numeric_limits<T>::quiet_NaN()), "nan``")
        << tstr<T>;
  };

  test_special((float){});
  test_special((double){});
  test_special((long double){});
}

struct FillAlignShiftTest : FormatTest {};

TEST_F(FillAlignShiftTest, FillAlignShiftTest_Decimal_Test) {
  EXPECT_EQ(format("{:10}", 42), "        42");
  EXPECT_EQ(format("{:`>10}", 42), "````````42");
  EXPECT_EQ(format("{:`<10}", 42), "42````````");
  EXPECT_EQ(format("{:`^10}", 42), "````42````");
  EXPECT_EQ(format("{:`^11}", 42), "````42`````");
  EXPECT_EQ(format("{:`>11}", 42), "`````````42");
  EXPECT_EQ(format("{:`<11}", 42), "42`````````");

  EXPECT_EQ(format("{:10}", -42), "       -42");
  EXPECT_EQ(format("{:`>10}", -42), "```````-42");
  EXPECT_EQ(format("{:`<10}", -42), "-42```````");
  EXPECT_EQ(format("{:`^10}", -42), "```-42````");
  EXPECT_EQ(format("{:`^11}", -42), "````-42````");
  EXPECT_EQ(format("{:`>11}", -42), "````````-42");
  EXPECT_EQ(format("{:`<11}", -42), "-42````````");
}

TEST_F(FillAlignShiftTest, FillAlignShiftTest_Hexadecimal_Test) {
  EXPECT_EQ(format("{:10x}", -0x2a), "       -2a");
  EXPECT_EQ(format("{:`>10x}", -0x2a), "```````-2a");
  EXPECT_EQ(format("{:`<10x}", -0x2a), "-2a```````");
  EXPECT_EQ(format("{:`^10x}", -0x2a), "```-2a````");
  EXPECT_EQ(format("{:`^11x}", -0x2a), "````-2a````");
  EXPECT_EQ(format("{:`>11x}", -0x2a), "````````-2a");
  EXPECT_EQ(format("{:`<11x}", -0x2a), "-2a````````");

  EXPECT_EQ(format("{:#10X}", -0x2a), "     -0X2A");
  EXPECT_EQ(format("{:`>#10X}", -0x2a), "`````-0X2A");
  EXPECT_EQ(format("{:`<#10X}", -0x2a), "-0X2A`````");
  EXPECT_EQ(format("{:`^#10X}", -0x2a), "``-0X2A```");
  EXPECT_EQ(format("{:`^#11X}", -0x2a), "```-0X2A```");
  EXPECT_EQ(format("{:`>#11X}", -0x2a), "``````-0X2A");
  EXPECT_EQ(format("{:`<#11X}", -0x2a), "-0X2A``````");

  EXPECT_EQ(format("{: #10X}", 0x2a), "      0X2A");
  EXPECT_EQ(format("{:`> #10X}", 0x2a), "````` 0X2A");
  EXPECT_EQ(format("{:`< #10X}", 0x2a), " 0X2A`````");
  EXPECT_EQ(format("{:`^ #10X}", 0x2a), "`` 0X2A```");
  EXPECT_EQ(format("{:`^ #11X}", 0x2a), "``` 0X2A```");
  EXPECT_EQ(format("{:`> #11X}", 0x2a), "`````` 0X2A");
  EXPECT_EQ(format("{:`< #11X}", 0x2a), " 0X2A``````");

  EXPECT_EQ(format("{:+#10X}", 0x2a), "     +0X2A");
  EXPECT_EQ(format("{:`>+#10X}", 0x2a), "`````+0X2A");
  EXPECT_EQ(format("{:`<+#10X}", 0x2a), "+0X2A`````");
  EXPECT_EQ(format("{:`^+#10X}", 0x2a), "``+0X2A```");
  EXPECT_EQ(format("{:`^+#11X}", 0x2a), "```+0X2A```");
  EXPECT_EQ(format("{:`>+#11X}", 0x2a), "``````+0X2A");
  EXPECT_EQ(format("{:`<+#11X}", 0x2a), "+0X2A``````");
}

TEST_F(FillAlignShiftTest, FillAlignShiftTest_Binary_Test) {
  EXPECT_EQ(format("{:#10b}", -0b1010), "   -0b1010");
  EXPECT_EQ(format("{:`>#10b}", -0b1010), "```-0b1010");
  EXPECT_EQ(format("{:`<#10b}", -0b1010), "-0b1010```");
  EXPECT_EQ(format("{:`^#10b}", -0b1010), "`-0b1010``");
  EXPECT_EQ(format("{:`^#11b}", -0b1010), "``-0b1010``");
  EXPECT_EQ(format("{:`>#11b}", -0b1010), "````-0b1010");
  EXPECT_EQ(format("{:`<#11b}", -0b1010), "-0b1010````");

  EXPECT_EQ(format("{: #10B}", 0b1010), "    0B1010");
  EXPECT_EQ(format("{:`> #10B}", 0b1010), "``` 0B1010");
  EXPECT_EQ(format("{:`< #10B}", 0b1010), " 0B1010```");
  EXPECT_EQ(format("{:`^ #10B}", 0b1010), "` 0B1010``");
  EXPECT_EQ(format("{:`^ #11B}", 0b1010), "`` 0B1010``");
  EXPECT_EQ(format("{:`> #11B}", 0b1010), "```` 0B1010");
  EXPECT_EQ(format("{:`< #11B}", 0b1010), " 0B1010````");
}

TEST_F(FillAlignShiftTest, FillAlignShiftTest_Octal_Test) {
  // 0 should never be 00
  EXPECT_EQ(format("{:10o}", 00), "         0");
  EXPECT_EQ(format("{:`>10o}", 00), "`````````0");
  EXPECT_EQ(format("{:`<10o}", 00), "0`````````");
  EXPECT_EQ(format("{:`^10o}", 00), "````0`````");
  EXPECT_EQ(format("{:`^11o}", 00), "`````0`````");
  EXPECT_EQ(format("{:`>11o}", 00), "``````````0");
  EXPECT_EQ(format("{:`<11o}", 00), "0``````````");

  EXPECT_EQ(format("{:#10o}", 00), "         0");
  EXPECT_EQ(format("{:`>#10o}", 00), "`````````0");
  EXPECT_EQ(format("{:`<#10o}", 00), "0`````````");
  EXPECT_EQ(format("{:`^#10o}", 00), "````0`````");
  EXPECT_EQ(format("{:`^#11o}", 00), "`````0`````");
  EXPECT_EQ(format("{:`>#11o}", 00), "``````````0");
  EXPECT_EQ(format("{:`<#11o}", 00), "0``````````");

  EXPECT_EQ(format("{:10o}", 01234), "      1234");
  EXPECT_EQ(format("{:`>10o}", 01234), "``````1234");
  EXPECT_EQ(format("{:`<10o}", 01234), "1234``````");
  EXPECT_EQ(format("{:`^10o}", 01234), "```1234```");
  EXPECT_EQ(format("{:`^11o}", 01234), "```1234````");
  EXPECT_EQ(format("{:`>11o}", 01234), "```````1234");
  EXPECT_EQ(format("{:`<11o}", 01234), "1234```````");

  EXPECT_EQ(format("{:+10o}", 00), "        +0");
  EXPECT_EQ(format("{:`>+10o}", 00), "````````+0");
  EXPECT_EQ(format("{:`<+10o}", 00), "+0````````");
  EXPECT_EQ(format("{:`^+10o}", 00), "````+0````");
  EXPECT_EQ(format("{:`^+11o}", 00), "````+0`````");
  EXPECT_EQ(format("{:`>+11o}", 00), "`````````+0");
  EXPECT_EQ(format("{:`<+11o}", 00), "+0`````````");

  EXPECT_EQ(format("{:#10o}", 01234), "     01234");
  EXPECT_EQ(format("{:`>#10o}", 01234), "`````01234");
  EXPECT_EQ(format("{:`<#10o}", 01234), "01234`````");
  EXPECT_EQ(format("{:`^#10o}", 01234), "``01234```");
  EXPECT_EQ(format("{:`^#11o}", 01234), "```01234```");
  EXPECT_EQ(format("{:`>#11o}", 01234), "``````01234");
  EXPECT_EQ(format("{:`<#11o}", 01234), "01234``````");
}

TEST_F(FillAlignShiftTest, FillAlignShiftTest_String_Test) {
  // default alignment is right, default fill char is space
  EXPECT_EQ(format("{:10}", "hello"), "hello     ");
  EXPECT_EQ(format("{:`>}", "hello"), "hello");
  
  EXPECT_EQ(format("{:`>10}", "hello"), "`````hello");
  EXPECT_EQ(format("{:`<10}", "hello"), "hello`````");
  EXPECT_EQ(format("{:`^10}", "hello"), "``hello```");
  EXPECT_EQ(format("{:`>11}", "hello"), "``````hello");
  EXPECT_EQ(format("{:`<11}", "hello"), "hello``````");
  EXPECT_EQ(format("{:`^11}", "hello"), "```hello```");
}

TEST_F(FillAlignShiftTest, FillAlignShiftTest_FullWidthCharacter_Test) {
  EXPECT_EQ(format("{}{}", "你好", "世界"), "你好世界");
  EXPECT_EQ(format("{}{}", "字符串OK", "字符串"), "字符串OK字符串");
  EXPECT_EQ(format("{:`^4}", "全角"), "全角");
  EXPECT_EQ(format("{:`<4}", "全角"), "全角");
  EXPECT_EQ(format("{:`>4}", "全角"), "全角");
  EXPECT_EQ(format("{:`^6}", "全角"), "`全角`");
  EXPECT_EQ(format("{:`<6}", "全角"), "全角``");
  EXPECT_EQ(format("{:`>6}", "全角"), "``全角");
  EXPECT_EQ(format("{:`^5}", "全角"), "全角`");
  EXPECT_EQ(format("{:`<5}", "全角"), "全角`");
  EXPECT_EQ(format("{:`>5}", "全角"), "`全角");
}

struct UserDefinedFormatTest : FormatTest {};

TEST_F(UserDefinedFormatTest, UserDefinedFormatTest) {

}
