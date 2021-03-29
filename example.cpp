#include "ATestClass.h"
#include <codecvt>
#include <format>
#include <iostream>
using namespace std;

enum color { red, green, blue };
const char *color_names[] = {"red", "green", "blue"};

template <> struct std::formatter<color> : std::formatter<const char *> {
  auto format(color c, format_context &ctx) {
    return formatter<const char *>::format(color_names[c], ctx);
  }
};
struct S {
  int value;
};

template <> struct std::formatter<S> {
  size_t width_arg_id = 0;

  // Parses a width argument id in the format { digit }.
  constexpr auto parse(format_parse_context &ctx) {
    auto iter = ctx.begin();
    auto get_char = [&]() { return iter != ctx.end() ? *iter : 0; };
    if (get_char() != '{')
      return iter;
    ++iter;
    char c = get_char();
    if (!isdigit(c) || (++iter, get_char()) != '}')
      throw format_error("invalid format");
    width_arg_id = c - '0';
    ctx.check_arg_id(width_arg_id);
    return ++iter;
  }

  // Formats an S with width given by the argument width_­arg_­id.
  auto format(S s, format_context &ctx) {
    int width = visit_format_arg(
        [](auto value) -> int {
          if constexpr (!is_integral_v<decltype(value)>)
            throw format_error("width is not integral");
          else if (value < 0 || value > numeric_limits<int>::max())
            throw format_error("invalid width");
          else
            return value;
        },
        ctx.arg(width_arg_id));
    return format_to(ctx.out(), "{0:x<{1}}", s.value, width);
  }
};

struct slash : std::numpunct<char> {
  char do_decimal_point() const { return '/'; } // separate with slash
};

int main(int argc, char *argv[]) {
  cout << format("{:p}", nullptr) << endl;
  cout << format("{:p}", (void *)nullptr) << endl;

  cout << format("你好{:`>6}", "世界") << endl;
  cout << format("你好{:`<6}", "世界") << endl;
  cout << format("你好{:`^6}", "世界") << endl;

  cout << format(locale(locale::classic(), new slash), "{:L}", 1234.5678)
       << endl;

  cout << format("{:`^+20f}", 42.0) << endl;
  cout << format("{:+020f}", 42.0) << endl;
  cout << format("{:`<+20f}", 42.0) << endl;

  wstring_convert<codecvt_utf8<wchar_t>> cvt;
  cout << cvt.to_bytes(format(L"你好{:`>6}", L"世界")) << endl;
  cout << cvt.to_bytes(format(L"你好{:`<6}", L"世界")) << endl;
  cout << cvt.to_bytes(format(L"你好{:`^6}", L"世界")) << endl;

  cout << format("{1}``{0}", "世界", "你好") << endl;
  cout << format("{:0b}", (short)-1) << endl;
  cout << formatted_size("{}", "我") << endl;
  cout << format("{:`>10}", "我") << endl;
  cout << format("{:`<10}", numeric_limits<float>::quiet_NaN()) << endl;
  cout << format("{:`<#10}", numeric_limits<float>::quiet_NaN()) << endl;
  cout << format("{:`<+#10}", numeric_limits<float>::quiet_NaN()) << endl;
  cout << format("{:`<+#010}", numeric_limits<float>::quiet_NaN()) << endl;
  cout << format("{:`<#010}", numeric_limits<float>::quiet_NaN()) << endl;

  cout << std::format("{0:{1}}", S{42}, 10) << endl;
  cout << std::format("{}", red) << endl;
  ATestClass aClass;
  cout << format("{:b}", 42) << endl;
  cout << format("{: >b}", 42) << endl;
  cout << format("{: ^b}", 42) << endl;
  cout << format("{:#b}", 42) << endl;
  cout << format("{:#10B}", 42) << endl;
  cout << format("{}, {}!", "Hello", "World") << endl;
  cout << format("{} {} {:g}", 1, "2", 3.0) << endl;
  cout << format("{}", 100000.) << endl;
  cout << format("{}", 1e5) << endl;
  cout << format("{}", -0.0) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-7f) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-6f) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-5f) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-7) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-6) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-5) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-7f) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-6f) << endl;
  cout << format("{}", 1e5f - numeric_limits<float>::epsilon() - 1e-5f) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-7) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-6) << endl;
  cout << format("{}", 1e5 - numeric_limits<double>::epsilon() - 1e-5) << endl;
  cout << format("{:20}", 42) << endl;
  cout << format("{: <20}", 42) << endl;
  cout << format("{: ^20}", 42) << endl;
  cout << format("{: >+20x}", 42) << endl;
  cout << format("{: <+20x}", 42) << endl;
  cout << format("{: ^+20x}", 42) << endl;
  cout << format("{: >20x}", -42) << endl;
  cout << format("{: <20x}", -42) << endl;
  cout << format("{: ^20x}", -42) << endl;
  cout << format("{:*>20}", 42) << endl;
  cout << format("{:.<20}", 42) << endl;
  cout << format("{:0^20}", 42) << endl;
  cout << format("{:20}", 42.0) << endl;
  cout << format("{: <20}", 42.0) << endl;
  cout << format("{: ^20}", 42.0) << endl;
  cout << format("{:20g}", 42.0) << endl;
  cout << format("{: <20g}", 42.0) << endl;
  cout << format("{: ^20g}", 42.0) << endl;
  cout << format("{:20e}", 42.0) << endl;
  cout << format("{: <20e}", 42.0) << endl;
  cout << format("{: ^20e}", 42.0) << endl;
  cout << format("{: >20a}", 42.0) << endl;
  cout << format("{: <20a}", 42.0) << endl;
  cout << format("{: ^20a}", 42.0) << endl;
  cout << format("{: >20f}", 42.0) << endl;
  cout << format("{: <20f}", 42.0) << endl;
  cout << format("{: ^20f}", 42.0) << endl;
  cout << format("{: ^20.2f}", 42.0) << endl;
  cout << format("{:`^20.{}f}", 42.0, 2) << endl;
  cout << format("{:`^20.{}a}", 42.0, 2) << endl;
  cout << format("{:`^20.{}g}", 42.0, 2) << endl;
  cout << format("{:`^20.{}e}", 42.0, 2) << endl;
  cout << format("{0:`^20.{1}e}", 42.0, 2) << endl;
  cout << format("{0:`>10s}", "str") << endl;
  cout << format("{0:`<10s}", "str") << endl;
  cout << format("{0:`^10s}", "str") << endl;
  cout << format("{0:`>10.{1}s}", "strstrstrstr", 10) << endl;
  cout << format("{0:`<10.9}", "strstrstrstr") << endl;
  cout << format("{0:`^10.10s}", "strstrstrstr") << endl;
  return 0;
}
