#pragma once

#if __cplusplus > 201703

#include <array>
#include <bit>
#include <charconv>
#include <concepts>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <version>

/* synopsis:
namespace std {
// [format.functions], formatting functions
template<class... Args>
string format(string_view fmt, const Args&... args);
template<class... Args>
wstring format(wstring_view fmt, const Args&... args);
template<class... Args>
string format(const locale& loc, string_view fmt, const Args&... args);
template<class... Args>
wstring format(const locale& loc, wstring_view fmt, const Args&... args);

string vformat(string_view fmt, format_args args);
wstring vformat(wstring_view fmt, wformat_args args);
string vformat(const locale& loc, string_view fmt, format_args args);
wstring vformat(const locale& loc, wstring_view fmt, wformat_args args);

template<class Out, class... Args>
Out format_to(Out out, string_view fmt, const Args&... args);
template<class Out, class... Args>
Out format_to(Out out, wstring_view fmt, const Args&... args);
template<class Out, class... Args>
Out format_to(Out out, const locale& loc, string_view fmt, const Args&... args);
template<class Out, class... Args>
Out format_to(Out out, const locale& loc, wstring_view fmt, const Args&...
args);

template<class Out>
Out vformat_to(Out out, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template<class Out>
Out vformat_to(Out out, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);
template<class Out>
Out vformat_to(Out out, const locale& loc, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template<class Out>
Out vformat_to(Out out, const locale& loc, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);

template<class Out> struct format_to_n_result {
  Out out;
  iter_difference_t<Out> size;
};
template<class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    string_view fmt, const Args&... args);
template<class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    wstring_view fmt, const Args&... args);
template<class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale& loc, string_view fmt,
                                    const Args&... args);
template<class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale& loc, wstring_view fmt,
                                    const Args&... args);

template<class... Args>
size_t formatted_size(string_view fmt, const Args&... args);
template<class... Args>
size_t formatted_size(wstring_view fmt, const Args&... args);
template<class... Args>
size_t formatted_size(const locale& loc, string_view fmt, const Args&... args);
template<class... Args>
size_t formatted_size(const locale& loc, wstring_view fmt, const Args&... args);

// [format.formatter], formatter
template<class T, class charT = char> struct formatter;

// [format.parse.ctx], class template basic_­format_­parse_­context
template<class charT> class basic_format_parse_context;
using format_parse_context = basic_format_parse_context<char>;
using wformat_parse_context = basic_format_parse_context<wchar_t>;

template<class Out, class charT> class basic_format_context;
using format_context = basic_format_context<unspecified, char>;
using wformat_context = basic_format_context<unspecified, wchar_t>;

// [format.arguments], arguments
// [format.arg], class template basic_­format_­arg
template<class Context> class basic_format_arg;

template<class Visitor, class Context>
see below visit_format_arg(Visitor&& vis, basic_format_arg<Context> arg);

// [format.arg.store], class template format-arg-store
template<class Context, class... Args> struct format-arg-store;      //
exposition only

template<class Context = format_context, class... Args>
format-arg-store<Context, Args...>
make_format_args(const Args&... args);
template<class... Args>
format-arg-store<wformat_context, Args...>
make_wformat_args(const Args&... args);

// [format.args], class template basic_­format_­args
template<class Context> class basic_format_args;
using format_args = basic_format_args<format_context>;
using wformat_args = basic_format_args<wformat_context>;

template<class Out, class charT>
using format_args_t = basic_format_args<basic_format_context<Out, charT>>;

// [format.error], class format_­error
class format_error;
}*/

// synopsis
namespace std {

template <class Out, class charT> class basic_format_context;
using format_context =
    basic_format_context<std::back_insert_iterator<std::string>, char>;
using wformat_context =
    basic_format_context<std::back_insert_iterator<std::string>, wchar_t>;

// [format.args], class template basic_­format_­args
template <class Context> class basic_format_args;
using format_args = basic_format_args<format_context>;
using wformat_args = basic_format_args<wformat_context>;

template <class Out, class charT>
using format_args_t = basic_format_args<basic_format_context<Out, charT>>;

// [format.error], class format_­error
class format_error;

// [format.functions], formatting functions
template <class... Args> string format(string_view fmt, const Args &... args);
template <class... Args> wstring format(wstring_view fmt, const Args &... args);
template <class... Args>
string format(const locale &loc, string_view fmt, const Args &... args);
template <class... Args>
wstring format(const locale &loc, wstring_view fmt, const Args &... args);

string vformat(string_view fmt, format_args args);
wstring vformat(wstring_view fmt, wformat_args args);
string vformat(const locale &loc, string_view fmt, format_args args);
wstring vformat(const locale &loc, wstring_view fmt, wformat_args args);

template <class Out, class... Args>
Out format_to(Out out, string_view fmt, const Args &... args);
template <class Out, class... Args>
Out format_to(Out out, wstring_view fmt, const Args &... args);
template <class Out, class... Args>
Out format_to(Out out, const locale &loc, string_view fmt,
              const Args &... args);
template <class Out, class... Args>
Out format_to(Out out, const locale &loc, wstring_view fmt,
              const Args &... args);

template <class Out>
Out vformat_to(Out out, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template <class Out>
Out vformat_to(Out out, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);
template <class Out>
Out vformat_to(Out out, const locale &loc, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template <class Out>
Out vformat_to(Out out, const locale &loc, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);

template <class Out> struct format_to_n_result {
  Out out;
  iter_difference_t<Out> size;
};
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    string_view fmt, const Args &... args);
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    wstring_view fmt, const Args &... args);
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale &loc, string_view fmt,
                                    const Args &... args);
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale &loc, wstring_view fmt,
                                    const Args &... args);

template <class... Args>
size_t formatted_size(string_view fmt, const Args &... args);
template <class... Args>
size_t formatted_size(wstring_view fmt, const Args &... args);
template <class... Args>
size_t formatted_size(const locale &loc, string_view fmt, const Args &... args);
template <class... Args>
size_t formatted_size(const locale &loc, wstring_view fmt,
                      const Args &... args);

// [format.formatter], formatter
template <class T, class charT = char> struct formatter;

// [format.parse.ctx], class template basic_­format_­parse_­context
template <class charT> class basic_format_parse_context;
using format_parse_context = basic_format_parse_context<char>;
using wformat_parse_context = basic_format_parse_context<wchar_t>;

// [format.arguments], arguments
// [format.arg], class template basic_­format_­arg
template <class Context> class basic_format_arg;

template <class Visitor, class Context>
auto visit_format_arg(Visitor &&vis, basic_format_arg<Context> arg);

// [format.arg.store], class template format-arg-store
template <class Context, class... Args> struct __format_arg_store;

template <class Context = format_context, class... Args>
__format_arg_store<Context, Args...> make_format_args(const Args &... args);
template <class... Args>
__format_arg_store<wformat_context, Args...>
make_wformat_args(const Args &... args);

} // namespace std

// implementation
namespace std {
namespace __format_details {
struct __vformat_func;
template <class T> struct __formatter_base;
} // namespace __format_details

class format_error : public runtime_error {
public:
  explicit format_error(const string &what_arg) : runtime_error(what_arg) {}
  explicit format_error(const char *what_arg) : runtime_error(what_arg) {}
};

template <class charT> class basic_format_parse_context {
  friend __format_details::__vformat_func;

public:
  using char_type = charT;
  using const_iterator = typename basic_string_view<charT>::const_iterator;
  using iterator = const_iterator;

private:
  iterator begin_;
  iterator end_;
  enum indexing { unknown, manual, automatic };
  indexing indexing_;
  size_t next_arg_id_;
  size_t num_args_;

  [[noreturn]] static void __throw_mixing_indexing() {
#if __cpp_exceptions
    throw format_error("mixing of automatic and manual argument indexing");
#else
    terminate();
#endif
  }

public:
  constexpr explicit basic_format_parse_context(basic_string_view<charT> fmt,
                                                size_t num_args = 0) noexcept
      : begin_(fmt.begin()), end_(fmt.end()), indexing_(unknown),
        next_arg_id_(0), num_args_(num_args) {}
  basic_format_parse_context(const basic_format_parse_context &) = delete;

  basic_format_parse_context &
  operator=(const basic_format_parse_context &) = delete;
  constexpr const_iterator begin() const noexcept { return begin_; }
  constexpr const_iterator end() const noexcept { return end_; }

  constexpr void advance_to(const_iterator it) { begin_ = it; }
  constexpr size_t next_arg_id() {
    if (indexing_ != manual) {
      if (indexing_ == unknown) {
        indexing_ = automatic;
      }
      return next_arg_id_++;
    } else {
      __throw_mixing_indexing();
    }
  }
  constexpr void check_arg_id(size_t id) {
    if (indexing_ != automatic) {
      if (indexing_ == unknown) {
        indexing_ = manual;
      }
      if (id >= num_args_) {
        // TODO: what is id used for? what if id >= num_args_?
      }
    } else {
      __throw_mixing_indexing();
    }
  }
};

template <class Context> class basic_format_arg {
  template <class Context2, class... Args>
  friend __format_arg_store<Context2, Args...>
  make_format_args(const Args &... args);

  template <class Context2, class... Args>
  friend __format_arg_store<Context2, Args...>
  make_wformat_args(const Args &... args);

  template <class Visitor, class Context2>
  friend auto visit_format_arg(Visitor &&vis, basic_format_arg<Context2> arg);

private:
  using char_type = typename Context::char_type;

public:
  class handle {
    const void *ptr_;
    void (*format_)(basic_format_parse_context<char_type> &, Context &,
                    const void *);

    template <class T>
    explicit handle(const T &val) noexcept
        : ptr_(addressof(val)),
          format_([](basic_format_parse_context<char_type> &parse_ctx,
                     Context &format_ctx, const void *ptr) {
            typename Context::template formatter_type<T> f;
            parse_ctx.advance_to(f.parse(parse_ctx));
            format_ctx.advance_to(
                f.format(*static_cast<const T *>(ptr), format_ctx));
          }) {}

    friend basic_format_arg<Context>;

  public:
    void format(basic_format_parse_context<char_type> &parse_ctx,
                Context &format_ctx) const {
      return format_(parse_ctx, format_ctx, ptr_);
    }
  };

private:
  variant<monostate, bool, char_type, int, unsigned int, long long int,
          unsigned long long int, float, double, long double, const char_type *,
          basic_string_view<char_type>, const void *, handle>
      value;

  template <class T> explicit basic_format_arg(const T &v) noexcept {
    if constexpr (is_same_v<T, bool> || is_same_v<T, char_type>) {
      value = v;
    } else if constexpr (is_same_v<T, char> && is_same_v<char_type, wchar_t>) {
      value = static_cast<wchar_t>(v);
    } else if constexpr (is_signed_v<T> && sizeof(T) <= sizeof(int)) {
      value = static_cast<int>(v);
    } else if constexpr (is_unsigned_v<T> &&
                         sizeof(T) <= sizeof(unsigned int)) {
      value = static_cast<unsigned int>(v);
    } else if constexpr (is_signed_v<T> && sizeof(T) <= sizeof(long long int)) {
      value = static_cast<long long int>(v);
    } else if constexpr (is_unsigned_v<T> &&
                         sizeof(T) <= sizeof(unsigned long long int)) {
      value = static_cast<unsigned long long int>(v);
    } else {
      value = handle(v);
    }
  }
  explicit basic_format_arg(float n) noexcept : value(n) {}
  explicit basic_format_arg(double n) noexcept : value(n) {}
  explicit basic_format_arg(long double n) noexcept : value(n) {}
  explicit basic_format_arg(const char_type *s) : value(s) {
    // TODO: Preconditions: s points to a NTCTS
  }

  template <class traits>
  explicit basic_format_arg(basic_string_view<char_type, traits> s) noexcept
      : value(s) {}

  template <class traits, class Allocator>
  explicit basic_format_arg(
      const basic_string<char_type, traits, Allocator> &s) noexcept
      : value(basic_string_view<char_type>(s.data(), s.size())) {}

  explicit basic_format_arg(nullptr_t) noexcept
      : value(static_cast<const void *>(nullptr)) {}

  template <class T>
  requires is_void_v<T> explicit basic_format_arg(const T *p) noexcept
      : value(p) {}

public:
  basic_format_arg() noexcept : value(monostate()) {}

  explicit operator bool() const noexcept {
    return !holds_alternative<monostate>(value);
  }
};

template <class Visitor, class Context>
auto visit_format_arg(Visitor &&vis, basic_format_arg<Context> arg) {
  return std::visit(std::forward<Visitor>(vis), arg.value);
}

template <class Context, class... Args> struct __format_arg_store {
  array<basic_format_arg<Context>, sizeof...(Args)> args;
};

template <class Context, class... Args>
__format_arg_store<Context, Args...> make_format_args(const Args &... args) {
  return {basic_format_arg<Context>(args)...};
}
template <class... Args>
__format_arg_store<wformat_context, Args...>
make_wformat_args(const Args &... args) {
  return {basic_format_arg<wformat_context>(args)...};
}

template <class Context> class basic_format_args {
  friend __format_details::__vformat_func;

private:
  size_t size_;
  const basic_format_arg<Context> *data_;

public:
  basic_format_args() noexcept : size_(), data_() {}

  template <class... Args>
  basic_format_args(const __format_arg_store<Context, Args...> &store) noexcept
      : size_(sizeof...(Args)), data_(store.args.data()) {}

  basic_format_arg<Context> get(size_t i) const noexcept {
    return i < size_ ? data_[i] : basic_format_arg<Context>();
  }
};

template <class Out, class charT> class basic_format_context {
  friend __format_details::__vformat_func;

private:
  basic_format_args<basic_format_context> args_;
  Out out_;

  basic_format_context(basic_format_args<basic_format_context> args, Out out)
      : args_(args), out_(out) {}

public:
  using iterator = Out;
  using char_type = charT;
  template <class T> using formatter_type = formatter<T, charT>;

  basic_format_arg<basic_format_context> arg(size_t id) const {
    return args_.get(id);
  }
  std::locale locale() { return std::locale(); }

  iterator out() { return out_; }
  void advance_to(iterator it) { out_ = it; }
};

namespace __format_details {

// 'other integral': integral type other than char/wchar_t/bool
template <class T, bool Int = is_integral_v<T>>
struct __is_plain_integral : true_type {};
template <class T> struct __is_plain_integral<T, false> : false_type {};
template <> struct __is_plain_integral<char> : false_type {};
template <> struct __is_plain_integral<wchar_t> : false_type {};
template <> struct __is_plain_integral<char8_t> : false_type {};
template <> struct __is_plain_integral<char16_t> : false_type {};
template <> struct __is_plain_integral<char32_t> : false_type {};
template <> struct __is_plain_integral<bool> : false_type {};
template <class T>
constexpr bool __is_plain_integral_v = __is_plain_integral<T>::value;
template <class T> concept __plain_integral = __is_plain_integral_v<T>;

template <class T> struct __is_char_t : false_type {};
template <> struct __is_char_t<char> : true_type {};
template <> struct __is_char_t<wchar_t> : true_type {};
template <class T> constexpr bool __is_char_t_v = __is_char_t<T>::value;
template <class T> concept __char_t = __is_char_t_v<T>;

template <class T> struct __is_bool : false_type {};
template <class T> constexpr bool __is_bool_v = __is_bool<T>::value;
template <> struct __is_bool<bool> : true_type {};

template <class T> struct __is_string : false_type {};
template <> struct __is_string<char *> : true_type {};
template <> struct __is_string<const char *> : true_type {};
template <size_t N> struct __is_string<const char[N]> : true_type {};
template <class CharT, class Traits, class Alloc>
struct __is_string<basic_string<CharT, Traits, Alloc>> : true_type {};
template <class CharT, class Traits>
struct __is_string<basic_string_view<CharT, Traits>> : true_type {};
template <class T> constexpr auto __is_string_v = __is_string<T>::value;

template <class T, class... Args>
struct __is_one_of : disjunction<is_same<T, Args>...> {};
template <class T, class... Args>
constexpr bool __is_one_of_v = __is_one_of<T, Args...>::value;
template <class T, class... Args> concept __one_of = __is_one_of_v<T, Args...>;

template <class CharT> struct __formatter_base {
  // fill_and_align_(optional) sign_(optional) sharp_(optional) zero_(optional)
  // width_(optional) precision_(optional) locale_specific_(optional)
  // type_(optional)
private:
  enum class fill_and_align {
    none,
    left,
    right,
    center,
  };
  enum class sign {
    none,
    plus,
    minus,
    space,
  };
  fill_and_align fill_and_align_ : 2;
  sign sign_ : 2;
  bool sharp_ : 1;
  bool zero_ : 1;
  bool locale_specific_ : 1;
  char fill_char_;
  char type_;
  size_t width_;
  size_t precision_;

private:
  auto __parse_fill_and_align(auto &it) {
    switch (*it) {
    case '<':
      fill_and_align_ = fill_and_align::left;
      break;
    case '>':
      fill_and_align_ = fill_and_align::right;
      break;
    case '^':
      fill_and_align_ = fill_and_align::center;
      break;
    default:
      fill_and_align_ = fill_and_align::none;
      return it;
    }
    return ++it;
  }

  auto __parse_sign_sharp_zero(auto &it) {
    switch (*it) {
    case ' ':
      sign_ = sign::space;
      break;
    case '+':
      sign_ = sign::plus;
      break;
    case '-':
      sign_ = sign::minus;
      break;
    default:
      sign_ = sign::none;
      goto L_end_sign;
    }
    ++it;

  L_end_sign:
    if (*it == '#') {
      sharp_ = true;
      ++it;
    } else {
      sharp_ = false;
    }

    if (*it == '0') {
      zero_ = true;
      ++it;
    } else {
      zero_ = false;
    }
  }

  auto __parse_width_precision(auto &it) {
    // TODO parse width precision
    return;
  }

  auto __parse_locale_specific(auto &it) {
    if (*it == 'L') {
      locale_specific_ = true;
      ++it;
    } else {
      locale_specific_ = false;
    }
  }

  auto __parse_type(auto &it) {
    switch (auto c = *it) {
    default:
      type_ = 0;
      break;
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'f':
    case 'F':
    case 's':
    case 'g':
    case 'G':
    case 'p':
    case 'c':
    case 'b':
    case 'B':
    case 'd':
    case 'o':
    case 'x':
    case 'X':
      type_ = c;
      ++it;
      break;
    }
  }

  void __output(auto &outputIt, const basic_string_view<CharT> &data) {
    for (auto &&c : data) {
      *outputIt++ = c;
    }
  }

  void __output(auto &outputIt, __format_details::__char_t auto c) {
    *outputIt++ = c;
  }

  static void __throw_char_out_of_range() {
#if __cpp_exceptions
    throw format_error("char out of range");
#else
    terminate();
#endif
  }

  [[noreturn]] static void __throw_invalid_format() {
#if __cpp_exceptions
    throw format_error("incomplete format");
#else
    terminate();
#endif
  }

public:
  typename basic_format_parse_context<CharT>::iterator
  parse(basic_format_parse_context<CharT> &pc) {
    auto it = pc.begin();

    __parse_fill_and_align(it);
    __parse_sign_sharp_zero(it);
    __parse_width_precision(it);
    __parse_locale_specific(it);
    __parse_type(it);

    return it;
  }

  template <class OutputIt, class Integral>
  typename basic_format_context<OutputIt, char>::iterator
  __format_as_integral(Integral t, basic_format_context<OutputIt, CharT> &fc) {
    char buf[numeric_limits<uintmax_t>::digits10 * 2];
    auto outIt = fc.out();
    if (type_ == 'b' || type_ == 'B') {
      // binary format
      __output(outIt, (type_ == 'b') ? "0b" : "0B");
      auto res = to_chars(begin(buf), end(buf), t, 2);
      __output(outIt, {begin(buf), res.ptr});
    } else if (type_ == 'c') {
      // char
      auto c = static_cast<char>(t);
      if (static_cast<Integral>(c) != t) {
        __throw_char_out_of_range();
      }
      __output(outIt, c);
    } else if (type_ == 'd' || type_ == 0) {
      auto res = to_chars(begin(buf), end(buf), t, 10);
      __output(outIt, {begin(buf), res.ptr});
    } else if (type_ == 'o') {
      if (t == 0) {
        __output(outIt, '0');
      } else {
        auto res = to_chars(begin(buf), end(buf), t, 8);
        __output(outIt, {begin(buf), res.ptr});
      }
    } else if (type_ == 'x' || type_ == 'X') {
      auto res = to_chars(begin(buf), end(buf), t, 16);
      if (type_ == 'X') {
        for (auto it = begin(buf); it != res.ptr; ++it) {
          *it = toupper(*it);
        }
      }
      __output(outIt, {begin(buf), res.ptr});
    } else {
      __throw_invalid_format();
    }
    return outIt;
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  format(const string_view &t, basic_format_context<OutputIt, CharT> &fc) {
    auto outIt = fc.out();
    if (type_ == 0 || type_ == 's') {
      __output(outIt, t);
    } else {
      __throw_invalid_format();
    }
    return outIt;
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, char>::iterator
  format(__format_details::__plain_integral auto t,
         basic_format_context<OutputIt, CharT> &fc) {
    return __format_as_integral(t, fc);
  }

  // bool specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  format(bool t, basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == 's' || type_ == 0) {
      // TODO: handle locale specific form
      auto outIt = fc.out();
      __output(outIt, t ? "true" : "false");
      return outIt;
    } else {
      return format(static_cast<unsigned char>(t), fc);
    }
  }

  // char & wchar_t specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  format(__format_details::__char_t auto t,
         basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == 0 || type_ == 'c') {
      auto outIt = fc.out();
      __output(outIt, t);
      return outIt;
    } else {
      return __format_as_integral(t, fc);
    }
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  format(floating_point auto t, basic_format_context<OutputIt, CharT> &fc) {
    char buf[64];
    auto it = fc.out();

    return it;
  }

  template <class OutputIt, class PtrT>
      requires is_pointer_v<PtrT> ||
      is_null_pointer_v<PtrT> typename basic_format_context<OutputIt,
                                                            CharT>::iterator
      format(PtrT t, basic_format_context<OutputIt, CharT> &fc) {
#ifdef __intptr_t_defined
    if (type_ == 0 || type_ == 'p') {
      char buf[numeric_limits<uintptr_t>::digits10 + 2];
      auto res =
          to_chars(begin(buf), end(buf), reinterpret_cast<uintptr_t>(t), 16);
      auto it = fc.out();
      __output(it, {begin(buf), res.ptr});
      return it;
    } else {
      __throw_invalid_format();
    }
#else
    // TODO: format when uintptr_t is not defined.
#endif
  }
};

template <__char_t charT, __char_t charU>
requires(!(is_same_v<charT, wchar_t> &&
           is_same_v<charU, char>)) struct __char_formatter
    : __formatter_base<charU> {};

template <__char_t charT>
struct __c_string_formatter : __formatter_base<charT> {
  auto format(basic_string_view<charT> sv, auto &fc) {
    return __formatter_base<charT>::format(sv, fc);
  }
};

template <class Traits, class Allocator, __char_t charT>
struct __basic_string_formatter : __formatter_base<charT> {
  auto format(const basic_string<charT> &s, auto &fc) {
    return __formatter_base<charT>::format(string_view(s), fc);
  }
};

template <class Traits, __char_t charT>
struct __basic_string_view_formatter : private __formatter_base<charT> {
  auto parse(auto &pc) { return __formatter_base<charT>::parse(pc); }
  auto format(auto sv, auto &fc) {
    return __formatter_base<charT>::format(sv, fc);
  }
};

template <class ArithmeticT, __char_t charT>
    requires(!__is_one_of_v<char, wchar_t, char8_t, char16_t, char32_t>) &&
    is_arithmetic_v<ArithmeticT> struct __arithmetic_formatter
    : __formatter_base<charT> {};

template <__char_t charT> struct __pointer_formatter : __formatter_base<charT> {
  auto parse(auto &pc) { return __formatter_base<charT>::parse(pc); }
  auto format(auto p, auto &fc) {
    return __formatter_base<charT>::format(p, fc);
  }
};
} // namespace __format_details

// template <class T, class charT>
// struct formatter : private __format_details::__formatter_base<char> {
//  auto parse(basic_format_parse_context<charT> &pc) {
//    return this->__parse(pc);
//  }
//  template <class OutputIt>
//  auto format(T &&t, basic_format_context<OutputIt, charT> &fc) {
//    return this->__format(t, fc);
//  }
//};

template <>
struct formatter<char, char> : __format_details::__formatter_base<char> {};

template <>
struct formatter<char, wchar_t> : __format_details::__formatter_base<char> {
  auto parse(auto &pc) {
    return __format_details::__formatter_base<char>::parse(pc);
  }
  template <class OutputIt> auto format(char t, auto &fc) {
    return __format_details::__formatter_base<char>::format(t, fc);
  }
};

template <>
struct formatter<wchar_t, wchar_t> : __format_details::__formatter_base<char> {
};

template <__format_details::__char_t CharT>
struct formatter<CharT *, CharT>
    : __format_details::__c_string_formatter<CharT> {};
template <__format_details::__char_t CharT>
struct formatter<const CharT *, CharT>
    : __format_details::__c_string_formatter<CharT> {};
template <size_t N, __format_details::__char_t CharT>
struct formatter<const CharT[N], CharT>
    : __format_details::__c_string_formatter<CharT> {};

template <class Traits, class Allocator, __format_details::__char_t CharT>
struct formatter<basic_string<CharT, Traits, Allocator>, CharT>
    : __format_details::__basic_string_formatter<Traits, Allocator, CharT> {};

template <class Traits, __format_details::__char_t CharT>
struct formatter<basic_string_view<CharT, Traits>, CharT>
    : __format_details::__basic_string_view_formatter<Traits, CharT> {};

template <class ArithmeticT, __format_details::__char_t CharT>
    requires(!__format_details::__is_one_of_v<ArithmeticT, char, wchar_t,
                                              char8_t, char16_t, char32_t>) &&
    is_arithmetic_v<ArithmeticT> struct formatter<ArithmeticT, CharT>
    : __format_details::__formatter_base<CharT> {
  auto parse(auto &pc) {
    return __format_details::__formatter_base<CharT>::parse(pc);
  }
  auto format(ArithmeticT t, auto &fc) {
    return __format_details::__formatter_base<CharT>::format(t, fc);
  }
};

template <__format_details::__one_of<nullptr_t, void *, const void *> PtrT,
          __format_details::__char_t CharT>
struct formatter<PtrT, CharT>
    : private __format_details::__pointer_formatter<CharT> {
  auto parse(auto &pc) {
    return __format_details::__pointer_formatter<CharT>::parse(pc);
  }
  auto format(auto t, auto &fc) {
    return __format_details::__pointer_formatter<CharT>::format(t, fc);
  }
};

namespace __format_details {
struct __vformat_func {
private:
  friend string std::vformat(string_view fmt, format_args args);
  friend wstring std::vformat(wstring_view fmt, wformat_args args);
  friend string std::vformat(const locale &, string_view fmt, format_args args);
  friend wstring std::vformat(const locale &, wstring_view fmt,
                              wformat_args args);

  [[noreturn]] static void __throw_incomplete_format() {
#if __cpp_exceptions
    throw format_error("incomplete format");
#else
    terminate();
#endif
  }

  static void __throw_incomplete_format_if(bool b) {
    if (b) {
      __throw_incomplete_format();
    }
  }

  [[noreturn]] static void __throw_invalid_format() {
#if __cpp_exceptions
    throw format_error("invalid format");
#else
    terminate();
#endif
  }

  template <class Out, class Char> struct __visitor {
    basic_format_parse_context<Char> &pc;
    basic_format_context<Out, Char> &fc;

    __visitor(basic_format_parse_context<Char> &pc,
              basic_format_context<Out, Char> &fc)
        : pc(pc), fc(fc) {}

    template <class T> void operator()(T &&v) {
      typename basic_format_context<Out,
                                    Char>::template formatter_type<decay_t<T>>
          f;
      pc.advance_to(f.parse(pc));
      fc.advance_to(f.format(v, fc));
    }

    void operator()(monostate) {}

    void operator()(
        typename basic_format_arg<basic_format_context<Out, Char>>::handle
            handle) {
      handle.format(pc, fc);
    }
  };

  string doit(string_view fmt, format_args args) {
    string res;
    bool inField{false};
    size_t argIdx;
    size_t argsSize = args.size_;
    format_context fc(args, back_inserter(res));
    // TODO: what is the second argument used for?
    format_parse_context pc(fmt);

    for (auto it = fmt.begin(); it != fmt.end();) {
      if (*it != '{' && *it != '}') {
        // characters other than '{' and '}' are just copied directly
        res += *it++;
        continue;
      }
      if (*it == '{') {
        // get started with a format spec.
        // process the argument index if exists, and [it, ite) currently stands
        // for the range of index field.
        ++it;
        __throw_incomplete_format_if(it == fmt.end());
        if (*it == '{') {
          // convert "{{" to "{" and copy to the output directly
          res += *it++;
          continue;
        }
        auto ite = it;
        while (ite != fmt.end() && *ite != ':' && *ite != '}') {
          // head till ':' for index
          ++ite;
        }
        __throw_incomplete_format_if(ite == fmt.end());
        bool argIdxSet = false;
        argIdx = 0;
        // after parsing the index, [it, ite) now stands for the range of format
        // spec field
        if (*ite == '}') {
          // encounter an empty format
          it = ite;
        } else if (*ite == ':') {
          if (ite != it) {
            // set the index
            argIdx = 0;
            // extension: allow negative index
            bool negative = false;
            if (*it == '-') {
              ++it;
              negative = true;
            }
            while (it != ite) {
              if (isdigit(*it)) {
                argIdxSet = true;
                argIdx *= 10;
                argIdx += *it++;
              } else {
                __throw_invalid_format();
              }
            }
            if (negative && argIdx) {
              argIdx = argsSize - argIdx;
            }
          }
          it = ++ite;
          while (ite != fmt.end() && *ite != '}') {
            // head till '}'
            ++ite;
          }
          __throw_incomplete_format_if(ite == fmt.end());
          // now ite has '}'
        }
        if (argIdxSet) {
          pc.check_arg_id(argIdx);
        } else {
          argIdx = pc.next_arg_id();
        }
        if (auto &&arg = fc.arg(argIdx)) {
          visit_format_arg(__visitor(pc, fc), std::move(arg));
        }
        it = ++ite;
      } else /*if (c == '}')*/ {
        // now, only "}}" is accepted
        ++it;
        __throw_incomplete_format_if(it == fmt.end() || *it != '}');
        // copy the '}' directly
        res += *it++;
        continue;
      }
    }
    return res;
  }

  wstring doit(wstring_view fmt, wformat_args args) { return fmt.data(); }
};

} // namespace __format_details

// [format.functions], formatting functions
template <class... Args> string format(string_view fmt, const Args &... args) {
  return vformat(fmt, make_format_args(args...));
}
template <class... Args>
wstring format(wstring_view fmt, const Args &... args) {
  return vformat(fmt, make_wformat_args(args...));
}
template <class... Args>
string format(const locale &loc, string_view fmt, const Args &... args) {
  return vformat(loc, fmt, make_format_args(args...));
}
template <class... Args>
wstring format(const locale &loc, wstring_view fmt, const Args &... args) {
  return vformat(loc, fmt, make_wformat_args(args...));
}

inline string vformat(string_view fmt, format_args args) {
  using namespace __format_details;
  return __vformat_func().doit(fmt, args);
}
inline wstring vformat(wstring_view fmt, wformat_args args) {
  using namespace __format_details;
  return __vformat_func().doit(fmt, args);
}
inline string vformat(const locale &loc, string_view fmt, format_args args) {
  // TODO vformat
  return fmt.data();
}
inline wstring vformat(const locale &loc, wstring_view fmt, wformat_args args) {
  // TODO vformat
  return fmt.data();
}

template <class Out, class... Args>
Out format_to(Out out, string_view fmt, const Args &... args) {
  using context = basic_format_context<Out, decltype(fmt)::value_type>;
  return vformat_to(out, fmt, make_format_args<context>(args...));
}
template <class Out, class... Args>
Out format_to(Out out, wstring_view fmt, const Args &... args) {
  using context = basic_format_context<Out, decltype(fmt)::value_type>;
  return vformat_to(out, fmt, make_format_args<context>(args...));
}
template <class Out, class... Args>
Out format_to(Out out, const locale &loc, string_view fmt,
              const Args &... args) {}
template <class Out, class... Args>
Out format_to(Out out, const locale &loc, wstring_view fmt,
              const Args &... args) {}

template <class Out>
Out vformat_to(Out out, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template <class Out>
Out vformat_to(Out out, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);
template <class Out>
Out vformat_to(Out out, const locale &loc, string_view fmt,
               format_args_t<type_identity_t<Out>, char> args);
template <class Out>
Out vformat_to(Out out, const locale &loc, wstring_view fmt,
               format_args_t<type_identity_t<Out>, wchar_t> args);

template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    string_view fmt, const Args &... args) {}
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    wstring_view fmt, const Args &... args) {}
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale &loc, string_view fmt,
                                    const Args &... args) {}
template <class Out, class... Args>
format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
                                    const locale &loc, wstring_view fmt,
                                    const Args &... args) {}

template <class... Args>
size_t formatted_size(string_view fmt, const Args &... args) {}
template <class... Args>
size_t formatted_size(wstring_view fmt, const Args &... args) {}
template <class... Args>
size_t formatted_size(const locale &loc, string_view fmt,
                      const Args &... args) {}
template <class... Args>
size_t formatted_size(const locale &loc, wstring_view fmt,
                      const Args &... args) {}
} // namespace std

#endif // C++20
