#include "testutil.h"
#include <charconv>

struct FloatingPointFormatTest : FormatTest {};

namespace {
template <class T> const char *tstr = "";
template <> const char *tstr<float> = "float";
template <> const char *tstr<double> = "double";
template <> const char *tstr<long double> = "long double";
} // namespace

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
