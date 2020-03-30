#include "testutil.h"
#include <charconv>

namespace {
template <class T> const char *tstr = "";
template <> const char *tstr<int8_t> = "int8_t";
template <> const char *tstr<uint8_t> = "uint8_t";
template <> const char *tstr<int16_t> = "int16_t";
template <> const char *tstr<uint16_t> = "uint16_t";
template <> const char *tstr<int32_t> = "int32_t";
template <> const char *tstr<uint32_t> = "uint32_t";
template <> const char *tstr<int64_t> = "int64_t";
template <> const char *tstr<uint64_t> = "uint64_t";
} // namespace

struct IntegerFormatTest : FormatTest {};

TEST_F(IntegerFormatTest, IntegerFormatTest_DefaultFormat_Test) {
  auto test_default = []<class T>(T v) {
    EXPECT_EQ(format("{}", v), to_string(v)) << tstr<T> << " v: " << v;
  };
  auto test_default_all_types = [&test_default](auto v) {
    test_default(int8_t(v));
    test_default(int16_t(v));
    test_default(int32_t(v));
    test_default(int64_t(v));
    test_default(uint8_t(v));
    test_default(uint16_t(v));
    test_default(uint32_t(v));
    test_default(uint64_t(v));
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

  auto test_default_max_min = [&test_default]<class T>(T) {
    test_default(numeric_limits<T>::max());
    test_default(numeric_limits<T>::min());
  };
  test_default_max_min(int8_t());
  test_default_max_min(int16_t());
  test_default_max_min(int32_t());
  test_default_max_min(int64_t());
  test_default_max_min(uint8_t());
  test_default_max_min(uint16_t());
  test_default_max_min(uint32_t());
  test_default_max_min(uint64_t());
}

TEST_F(IntegerFormatTest, IntegerFormatTest_IntegerAsChar_Test) {
  auto test_char = [](int v) {
    if (v > numeric_limits<char>::max() || v < numeric_limits<char>::min()) {
      EXPECT_FORMAT_ERROR(format("{:c}", (int)v)) << "v: " << v;
    } else {
      EXPECT_EQ(format("{:c}", (int)v), format("{}", (char)v)) << "v: " << v;
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
  test_char(numeric_limits<signed char>::min());
  test_char(numeric_limits<signed char>::min() + 1);
  test_char(numeric_limits<signed char>::min() - 1);
  test_char(numeric_limits<signed char>::max());
  test_char(numeric_limits<signed char>::max() - 1);
  test_char(numeric_limits<signed char>::max() + 1);
  test_char(numeric_limits<unsigned char>::min());
  test_char(numeric_limits<unsigned char>::min() + 1);
  test_char(numeric_limits<unsigned char>::min() - 1);
  test_char(numeric_limits<unsigned char>::max());
  test_char(numeric_limits<unsigned char>::max() - 1);
  test_char(numeric_limits<unsigned char>::max() + 1);
  test_char(127);
  test_char(128);
  test_char(129);
  test_char(254);
  test_char(255);
  test_char(256);
}

TEST_F(IntegerFormatTest, IntegerFormatTest_BasicInteger_Test) {
  auto to_chars_base = [](auto v, int base) -> string {
    char buf[100];
    auto &&[ptr, ec] = to_chars(begin(buf), end(buf), v, base);
    if (ec != errc{}) {
      throw FormatTestError();
    }
    return string(buf, ptr);
  };
  auto test_for_integer_type_spec = [&to_chars_base](int base,
                                                     const char *fmt) {
    auto test_base = [&to_chars_base, base, fmt](auto v) {
      EXPECT_EQ(format(fmt, v), to_chars_base(v, base))
          << "v: " << v << " base: " << base;
    };
    test_base(42);
    test_base(-42);
    test_base(0);
    test_base(1);
    test_base(-1);
    test_base(numeric_limits<uintmax_t>::max());
    test_base(numeric_limits<uintmax_t>::max() - 1);
    test_base(numeric_limits<intmax_t>::min());
    test_base(numeric_limits<intmax_t>::min() + 1);
  };

  // type spec:
  // binary
  test_for_integer_type_spec(2, "{:b}");
  // decimal
  test_for_integer_type_spec(10, "{:d}");
  // octal
  test_for_integer_type_spec(8, "{:o}");
  // hexadecimal
  test_for_integer_type_spec(16, "{:x}");
}
