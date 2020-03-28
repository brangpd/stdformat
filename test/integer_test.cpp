#include "testutil.h"
#include <charconv>

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
