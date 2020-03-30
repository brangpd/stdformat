#include "testutil.h"

struct UserDefinedFormatterTest : FormatTest {};

namespace standard_example {
// examples given in the standard draft
enum color { red, green, blue };
const char *color_names[] = {"red", "green", "blue"};

struct S {
  int value;
};
} // namespace standard_example

template <>
struct std::formatter<standard_example::color> : std::formatter<const char *> {
  auto format(standard_example::color c, format_context &ctx) {
    return formatter<const char *>::format(standard_example::color_names[c],
                                           ctx);
  }
};

template <> struct std::formatter<standard_example::S> {
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
  auto format(standard_example::S s, format_context &ctx) {
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

TEST_F(UserDefinedFormatterTest,
       UserDefinedFormatterTest_StandardExamples_Test) {
  using namespace standard_example;
  EXPECT_EQ(format("{0:{1}}", S{42}, 10), "42xxxxxxxx");
  EXPECT_EQ(format("{} {} {}", color::red, color::blue, color::green),
            "red blue green");
}
