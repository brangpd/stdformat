#pragma once

#if __cplusplus > 201703

/* synopsis ********************************************************************
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
template<class Context, class... Args> struct format-arg-store;

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
}
*******************************************************************************/

#include <array>
#include <bit>
#include <cmath>
#include <codecvt>
#include <forward_list>
#include <iomanip>
#include <iterator>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>

#ifdef __cpp_exceptions
#define __THROW_FORMAT_ERROR(why) throw std::format_error(why)
#define __IMPLEMENTATION_BUG()                                                 \
  throw runtime_error("implementation bug at " __FILE__ + ":"s +               \
                      to_string(__LINE__))
#else
#define __THROW_FORMAT_ERROR(why) std::exit(1)
#define __IMPLEMENTATION_BUG() std::exit(2)
#endif
namespace std {

namespace __format_details {
template <class CharT> class __formatter_iterator;
} // namespace __format_details

template <class Out, class CharT> class basic_format_context;
using format_context =
    basic_format_context<__format_details::__formatter_iterator<char>, char>;
using wformat_context =
    basic_format_context<__format_details::__formatter_iterator<wchar_t>,
                         wchar_t>;

// [format.args], class template basic_­format_­args
template <class Context> class basic_format_args;
using format_args = basic_format_args<format_context>;
using wformat_args = basic_format_args<wformat_context>;

template <class Out, class CharT>
using format_args_t = basic_format_args<basic_format_context<Out, CharT>>;

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
template <class T, class CharT = char> struct formatter;

// [format.parse.ctx], class template basic_­format_­parse_­context
template <class CharT> class basic_format_parse_context;
using format_parse_context = basic_format_parse_context<char>;
using wformat_parse_context = basic_format_parse_context<wchar_t>;

// [format.arguments], arguments
// [format.arg], class template basic_­format_­arg
template <class Context> class basic_format_arg;

template <class Visitor, class Context>
decltype(auto) visit_format_arg(Visitor &&vis, basic_format_arg<Context> arg);

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
// This struct is used to implement some formatting function exported.
struct __public_func;
// A base struct for all formatters.
template <class T> struct __formatter_base;

namespace { // Helper type traits
// 'plain integral': integral type other than char/wchar_t/bool
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

template <class T, class... Args>
struct __is_one_of : disjunction<is_same<T, Args>...> {};
template <class T, class... Args>
constexpr bool __is_one_of_v = __is_one_of<T, Args...>::value;
template <class T, class... Args> concept __one_of = __is_one_of_v<T, Args...>;
template <class T> struct __is_char_t : __is_one_of<T, char, wchar_t> {};
template <class T> constexpr bool __is_char_t_v = __is_char_t<T>::value;
template <class T> concept __char_t = __one_of<T, char, wchar_t>;
template <class T> concept __integral = is_integral_v<T>;
template <class T> concept __floating_point = is_floating_point_v<T>;

template <class T> struct __is_string : false_type {};
template <class CharT, class Trait>
struct __is_string<basic_string_view<CharT, Trait>> : true_type {};
template <class CharT, class Trait, class Alloc>
struct __is_string<basic_string<CharT, Trait, Alloc>> : true_type {};
template <__char_t CharT> struct __is_string<const CharT *> : true_type {};
template <class T> constexpr bool __is_string_v = __is_string<T>::value;

template <class T> struct __is_pointer : false_type{};
template <class T> struct __is_pointer<T *> : true_type{};
template <class T> struct __is_pointer<const T *> : true_type{};
template <> struct __is_pointer<nullptr_t> : true_type{};
template <class T> constexpr bool __is_pointer_v = __is_pointer<T>::value;

template <class T, class CharT> concept __handlable = requires(T &&t) {
  typename formatter<T, CharT>;
};
} // namespace

} // namespace __format_details

/**
 * Exception thrown on formatting errors.
 */
class format_error : public runtime_error {
public:
  explicit format_error(const string &what_arg) : runtime_error(what_arg) {}
  explicit format_error(const char *what_arg) : runtime_error(what_arg) {}
};

/**
 * Maintainer of formatting string's parsing state.
 * @tparam CharT The char type of the formatting string.
 */
template <class CharT> class basic_format_parse_context {
  friend __format_details::__public_func;

public:
  using char_type = CharT;
  using const_iterator = typename basic_string_view<CharT>::const_iterator;
  using iterator = const_iterator;

private:
  iterator begin_; ///< The beginning of the formatting string.
  iterator end_;   ///< The end of the formatting string.
  enum indexing { unknown, manual, automatic };
  indexing indexing_;  ///< The indexing type, used to ensure that automatic and
                       ///< manual indexing are not mixed.
  size_t next_arg_id_; ///< The next argument id.
  size_t num_args_;    ///< The number of arguments in total.

  [[noreturn]] static inline void __throw_mixing_indexing() {
    __THROW_FORMAT_ERROR("mixing of automatic and manual argument indexing");
  }

public:
  constexpr explicit basic_format_parse_context(basic_string_view<CharT> fmt,
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

/**
 * Provide access to arguments.
 * @tparam FormatContext The format context.
 * @note The value maintained is accessed through visit_format_arg().
 */
template <class FormatContext> class basic_format_arg {
  template <class Context2, class... Args>
  friend __format_arg_store<Context2, Args...>
  make_format_args(const Args &... args);

  template <class... Args>
  friend __format_arg_store<wformat_context, Args...>
  make_wformat_args(const Args &... args);

  template <class Visitor, class Context2>
  friend decltype(auto) visit_format_arg(Visitor &&vis,
                                         basic_format_arg<Context2> arg);

private:
  using char_type = typename FormatContext::char_type;

public:
  /**
   * Provide type erased access to user defined formatter.
   */
  class handle {
    const void *ptr_;
    void (*format_)(basic_format_parse_context<char_type> &, FormatContext &,
                    const void *);

    template <class T>
    explicit handle(const T &val) noexcept
        : ptr_(addressof(val)),
          format_([](basic_format_parse_context<char_type> &parse_ctx,
                     FormatContext &format_ctx, const void *ptr) {
            typename FormatContext::template formatter_type<decay_t<T>> f;
            parse_ctx.advance_to(f.parse(parse_ctx));
            format_ctx.advance_to(
                f.format(*static_cast<const T *>(ptr), format_ctx));
          }) {}

    friend basic_format_arg<FormatContext>;

  public:
    void format(basic_format_parse_context<char_type> &parse_ctx,
                FormatContext &format_ctx) const {
      format_(parse_ctx, format_ctx, ptr_);
    }
  };

private:
  variant<monostate, bool, char_type, int, unsigned int, long long int,
          unsigned long long int, float, double, long double, const char_type *,
          basic_string_view<char_type>, const void *, handle>
      value_;

  template <__format_details::__handlable<char_type> T>
  explicit basic_format_arg(const T &v) noexcept {
    using namespace __format_details;
    if constexpr (__is_one_of_v<T, bool, char_type>) {
      value_ = v;
    } else if constexpr (__is_char_t_v<T>) {
      value_ = static_cast<wchar_t>(v);
    } else if constexpr (is_signed_v<T> && sizeof(T) <= sizeof(int)) {
      value_ = static_cast<int>(v);
    } else if constexpr (is_unsigned_v<T> &&
                         sizeof(T) <= sizeof(unsigned int)) {
      value_ = static_cast<unsigned int>(v);
    } else if constexpr (is_signed_v<T> && sizeof(T) <= sizeof(long long int)) {
      value_ = static_cast<long long int>(v);
    } else if constexpr (is_unsigned_v<T> &&
                         sizeof(T) <= sizeof(unsigned long long int)) {
      value_ = static_cast<unsigned long long int>(v);
    } else {
      value_ = handle(v);
    }
  }
  explicit basic_format_arg(float n) noexcept : value_(n) {}
  explicit basic_format_arg(double n) noexcept : value_(n) {}
  explicit basic_format_arg(long double n) noexcept : value_(n) {}
  explicit basic_format_arg(const char_type *s) : value_(s) {}

  template <class traits>
  explicit basic_format_arg(basic_string_view<char_type, traits> s) noexcept
      : value_(s) {}

  template <class traits, class Allocator>
  explicit basic_format_arg(
      const basic_string<char_type, traits, Allocator> &s) noexcept
      : value_(basic_string_view<char_type>(s.data(), s.size())) {}

  explicit basic_format_arg(nullptr_t) noexcept
      : value_(static_cast<const void *>(nullptr)) {}

  template <class T>
  requires is_void_v<T> explicit basic_format_arg(const T *p) noexcept
      : value_(p) {}

public:
  basic_format_arg() noexcept : value_(monostate()) {}

  explicit operator bool() const noexcept {
    return !holds_alternative<monostate>(value_);
  }
};

/**
 * Visitation interface for user-defined arguments.
 * @tparam Visitor The visitor.
 * @tparam FormatContext The format context.
 * @param vis The visitor.
 * @param arg The argument packed by basic_format_arg.
 * @return Depends on the return value of visitor's operator().
 */
template <class Visitor, class FormatContext>
decltype(auto) visit_format_arg(Visitor &&vis,
                                basic_format_arg<FormatContext> arg) {
  return std::visit(std::forward<Visitor>(vis), arg.value_);
}

template <class FormatContext, class... Args> struct __format_arg_store {
  array<basic_format_arg<FormatContext>, sizeof...(Args)> args;
};

template <class FormatContext, class... Args>
__format_arg_store<FormatContext, Args...>
make_format_args(const Args &... args) {
  return {basic_format_arg<FormatContext>(args)...};
}
template <class... Args>
__format_arg_store<wformat_context, Args...>
make_wformat_args(const Args &... args) {
  return {basic_format_arg<wformat_context>(args)...};
}

/**
 * Pack basic format arguments.
 * @tparam FormatContext The format context.
 */
template <class FormatContext> class basic_format_args {
  friend __format_details::__public_func;

private:
  size_t size_;
  const basic_format_arg<FormatContext> *data_;

public:
  basic_format_args() noexcept : size_(), data_() {}

  template <class... Args>
  basic_format_args(
      const __format_arg_store<FormatContext, Args...> &store) noexcept
      : size_(sizeof...(Args)), data_(store.args.data()) {}

  basic_format_arg<FormatContext> get(size_t i) const noexcept {
    return i < size_ ? data_[i] : basic_format_arg<FormatContext>();
  }
};

/**
 * Maintainer of the formatting state including the output iterator, the locale,
 * and all arguments.
 * @tparam OutputIt The output iterator.
 * @tparam CharT The char type to produce output.
 */
template <class OutputIt, class CharT> class basic_format_context {
  friend __format_details::__public_func;

private:
  basic_format_args<basic_format_context> args_;
  OutputIt out_;
  std::locale locale_;

  basic_format_context(basic_format_args<basic_format_context> args,
                       OutputIt out, std::locale loc = std::locale())
      : args_(std::move(args)), out_(std::move(out)), locale_(std::move(loc)) {}

public:
  using iterator = OutputIt;
  using char_type = CharT;
  template <class T> using formatter_type = formatter<T, CharT>;

  basic_format_arg<basic_format_context> arg(size_t id) const {
    return args_.get(id);
  }
  std::locale locale() { return locale_; }

  iterator out() { return out_; }
  void advance_to(iterator it) { out_ = it; }
};

namespace __format_details {
/**
 * For output, full width character should be treated as width of 2. The width
 * appears in the formatting string means the displaying width in the terminal
 * instead of the length it is encoded. A basic width counter provide the width
 * calculation given a value of char32_t (UTF-32) which is exactly equal to the
 * code point's numerical value.
 */
class __basic_width_counter {
  template <class> friend class __width_counter;
  /**
   * Given a character of char32_t, calculate its width.
   * @param cd The UTF-32 encoded character.
   * @return 2 if the character is full width, or 1 if half width.
   */
  static size_t width(char32_t cd) {
    // ASCII codes would be used more often so provide a quick check.
    if (cd < 128) {
      return 1;
    }
    // following code points pairs are ranges of full width character
    static constexpr int codes[][2] = {
        {0, -1}, // for binary search convenience
        {0x1100, 0x115f},
        {0x2329, 0x232a},
        {0x2e80, 0x303e},
        {0x3040, 0xa4cf},
        {0xac00, 0xd7a3},
        {0xf900, 0xfaff},
        {0xfe30, 0xfe6f},
        {0xff00, 0xff60},
        {0xffe0, 0xffe6},
        {0x1f900, 0x1f9ff},
        {0x20000, 0x2fffd},
        {0x30000, 0x3fffd},
    };
    auto it =
        upper_bound(begin(codes), end(codes), cd,
                    [](char32_t v, const int it[2]) { return v < it[0]; });
    auto pair = it[-1];
    // now cd >= pair[0]
    if (cd <= pair[1]) {
      return 2;
    }
    return 1;
  }
};
template <class CharT> class __width_counter;
/**
 * Width counter for char.
 */
template <> class __width_counter<char> {
public:
  static size_t width(const basic_string_view<char> &sv, const locale &loc) {
    enum { buflen = 16 };
    char32_t c32[buflen];
    size_t count = 0;
    mbstate_t mbstate{};
    // Note: The cuchar library function mbrtoc32 takes the global c locale for
    // conversion which is not thread safe, thus have to use C++ codecvt.

    // FIXME: deprecated, use char8_t instead of char.
    using cvt = codecvt<char32_t, char, mbstate_t>;
    auto &&f = use_facet<cvt>(loc);

    const char *svp = sv.data();
    const char *svpe = svp + sv.size(); // end of svp

    const char *fromNext{};
    char32_t *toNext{};

    while (svp < svpe) {
      auto inRes =
          f.in(mbstate, svp, svpe, fromNext, c32, c32 + buflen, toNext);
      if (svp == fromNext) {
        break;
      }
      svp = fromNext;
      switch (inRes) {
      case codecvt_base::ok:
      case codecvt_base::partial:
        for (auto it = c32; it != toNext; ++it) {
          count += __basic_width_counter::width(*it);
        }
        break;
      case codecvt_base::error:
      case codecvt_base::noconv:
        goto L_break_while;
      }
      if (inRes == codecvt_base::ok) {
        break;
      }
    }
  L_break_while:
    return count;
  }
  static inline size_t width(char, const locale &) { return 1; }
};
extern template class __width_counter<char>;
/**
 * Width counter for wchar_t.
 */
template <> class __width_counter<wchar_t> {
public:
  static size_t width(const basic_string_view<wchar_t> &sv, const locale &loc) {
    // Since standard library does not provide code converter from wchar_t to
    // char32_t, first convert a wchar_t character to char then convert the char
    // character to char32_t

    // FIXME: deprecated, use char8_t instead of char
    using cvt = codecvt<wchar_t, char, mbstate_t>;
    auto &&f = use_facet<cvt>(loc); // wchat_t to char
    mbstate_t mbstate{};

    char32_t c32{};
    size_t count = 0;
    enum { cdataSize = 16 };
    char cdata[cdataSize];

    const wchar_t *svp = sv.data();
    const wchar_t *svpe = svp + sv.size();
    const wchar_t *fromNext{};
    char *toNext{};

    while (svp < svpe) {
      // part 1: from wchar_t to char
      auto outRes =
          f.out(mbstate, svp, svpe, fromNext, cdata, cdata + cdataSize, toNext);
      if (svp == fromNext) {
        break;
      }
      svp = fromNext;
      switch (outRes) {
      case codecvt_base::ok:
      case codecvt_base::partial:
        break;
      case codecvt_base::error:
      case codecvt_base::noconv:
        goto L_break_while;
      }

      // part 2: from char to char32_t, redirect to width counter of char
      count += __width_counter<char>::width(
          basic_string_view<char>(cdata, toNext - cdata), loc);
      if (outRes == codecvt_base::ok) {
        break;
      }
    }
  L_break_while:
    return count;
  }
  static inline size_t width(wchar_t wc, const locale &loc) {
    return width(basic_string_view<wchar_t>(&wc, 1), loc);
  }
};
extern template class __width_counter<wchar_t>;

/**
 * The buf to store unicode characters for width calculation.
 */
template <class CharT> class __unicode_buf {
private:
  enum { buflen = 4, width_dirty = -1 };
  CharT buf_[buflen];
  uint8_t cur_{};
  locale loc_;
  mutable size_t width_{}; // width cache

public:
  explicit __unicode_buf(const locale &loc) : loc_(loc) {}
  inline operator bool() const { return width(); }
  inline void out(auto &it) {
    if (*this) {
      it = copy(buf_, buf_ + cur_, it);
    }
  }
  inline void reset() {
    cur_ = 0;
    width_ = 0;
  }
  inline size_t width() const {
    return width_ == width_dirty
               ? width_ = __width_counter<CharT>::width({buf_, cur_}, loc_)
               : width_;
  }
  inline size_t size() const { return cur_; }
  inline decltype(auto) operator+=(CharT c) {
    if (cur_ == buflen) {
      __IMPLEMENTATION_BUG();
    }
    width_ = width_dirty;
    buf_[cur_++] = c;
    return *this;
  }
};
extern template class __unicode_buf<char>;
extern template class __unicode_buf<wchar_t>;

template <class CharT> class __formatter_iterator_impl {
  forward_list<basic_string<CharT>>
      list_; ///< list of strings to be merged on getting result
  typename forward_list<basic_string<CharT>>::iterator
      it_; ///< iterator to current string in the list
  back_insert_iterator<basic_string<CharT>>
      inserter_;            ///< the inserter of current string
  size_t delayed_capacity_; ///< used for += string size cache

public:
  __formatter_iterator_impl() {
    delayed_capacity_ = 0;
    list_.emplace_after(list_.before_begin());
    it_ = list_.begin();
    inserter_ = back_inserter(*it_);
  }

  basic_string<CharT> result() {
    auto it = list_.begin();
    auto &res = *it;
    res.reserve(res.size() + delayed_capacity_);
    while (++it != list_.end()) {
      res += std::move(*it);
    }
    return std::move(res);
  }

  inline decltype(auto) operator=(CharT c) { *inserter_++ = c; }
  inline decltype(auto) operator=(basic_string<CharT> &&s) {
    delayed_capacity_ += s.size();
    it_ = list_.insert_after(it_, std::move(s));
    inserter_ = back_inserter(*it_);
  }
  inline decltype(auto) operator=(const basic_string_view<CharT> &sv) {
    auto size = it_->size();
    it_->resize(size + sv.size(), 0);
    copy(sv.begin(), sv.end(), it_->data() + size);
  }
};
extern template class __formatter_iterator_impl<char>;
extern template class __formatter_iterator_impl<wchar_t>;
/**
 * The formatter iterator is an output iterator that provides a wrapper of the
 * underlying iterator (say the back insert iterator). It behaves as if the
 * underlying iterator is being used directly, except that it allows objects of
 * derived classes to determine whether the output operation should be finally
 * executed.
 * @tparam Container The container, namely the basic string to produce
 * formatting output.
 */
template <class CharT> class __formatter_iterator {
  friend __format_details::__public_func;

private:
  __formatter_iterator_impl<CharT> *impl_;

protected:
  __formatter_iterator(__formatter_iterator_impl<CharT> &impl) : impl_(&impl) {}

public:
  __formatter_iterator(const __formatter_iterator &other)
      : impl_(other.impl_) {}
  inline basic_string<CharT> result() { return impl_->result(); }
  inline decltype(auto) operator=(CharT c) {
    impl_->operator=(c);
    return *this;
  }
  inline decltype(auto) operator=(basic_string<CharT> &&s) {
    impl_->operator=(std::move(s));
    return *this;
  }
  inline decltype(auto) operator=(const basic_string_view<CharT> &sv) {
    impl_->operator=(sv);
    return *this;
  }
  // Those are all no-op operations for output iterators, only used to remain
  // consistency.
  constexpr inline decltype(auto) operator*() { return *this; }
  constexpr inline decltype(auto) operator++() { return *this; }
  constexpr inline decltype(auto) operator++(int) { return *this; }
};
extern template class __formatter_iterator<char>;
extern template class __formatter_iterator<wchar_t>;

/**
 * Counter wrapper for formatted_size's. It does not write any character but
 * only counts the width of output characters.
 */
template <class CharT> class __width_counter_formatter_iterator {
  friend __format_details::__public_func;

private:
  size_t count_; ///< The counter.
  __unicode_buf<CharT> unicode_buf_;

public:
  __width_counter_formatter_iterator(const locale &loc)
      : count_(0), unicode_buf_(loc) {}
  size_t count() const { return count_; }

  __width_counter_formatter_iterator &operator=(CharT c) {
    if (unicode_buf_ += c) {
      count_ += unicode_buf_.width();
      unicode_buf_.reset();
    }
    return *this;
  }
  inline void out(output_iterator<CharT> auto &oit) { unicode_buf_.out(oit); }
  constexpr inline decltype(auto) operator*() { return *this; }
  constexpr inline decltype(auto) operator++() { return *this; }
  constexpr inline decltype(auto) operator++(int) { return *this; }
};
extern template class __width_counter_formatter_iterator<char>;
extern template class __width_counter_formatter_iterator<wchar_t>;

/**
 * Counter wrapper for formatted_size's. It does not write any character but
 * only counts the length of output characters.
 */
template <class CharT> class __counter_formatter_iterator {
  friend __format_details::__public_func;

private:
  size_t count_{};
  CharT c_;

public:
  size_t count() const { return count_; }
  inline decltype(auto) operator=(CharT c) {
    ++count_;
    c_ = c;
    return *this;
  }
  inline void out(output_iterator<CharT> auto &oit) { *oit++ = c_; }
  constexpr inline decltype(auto) operator*() { return *this; }
  constexpr inline decltype(auto) operator++() { return *this; }
  constexpr inline decltype(auto) operator++(int) { return *this; }
};
extern template class __counter_formatter_iterator<char>;
extern template class __counter_formatter_iterator<wchar_t>;

/**
 * Limited wrapper for format_n's. It limits the maximum width of output.
 */
template <class WrappedOutputIterator, class CharT>
class __limited_formatter_iterator {
  friend __format_details::__public_func;

private:
  size_t avail_; ///< Available operations left.
  WrappedOutputIterator *oit_;
  __unicode_buf<CharT> unicode_buf_;

public:
  __limited_formatter_iterator(WrappedOutputIterator &woit, size_t maxOp,
                               const locale &loc)
      : oit_(&woit), avail_(maxOp), unicode_buf_(loc) {}
  inline WrappedOutputIterator out() const { return *oit_; }
  inline size_t avail() const { return avail_; }

  __limited_formatter_iterator &operator=(CharT c) {
    if (avail_ > 0) {
      if (unicode_buf_ += c) {
        auto width = unicode_buf_.width();
        if (avail_ >= width) {
          avail_ -= width;
          unicode_buf_.out(*oit_);
          unicode_buf_.reset();
        } else {
          avail_ = 0;
        }
      }
    }
    return *this;
  }
  constexpr inline decltype(auto) operator*() { return *this; }
  constexpr inline decltype(auto) operator++() { return *this; }
  constexpr inline decltype(auto) operator++(int) { return *this; }
};
extern template class __limited_formatter_iterator<__formatter_iterator<char>,
                                                   char>;
extern template class __limited_formatter_iterator<
    __formatter_iterator<wchar_t>, wchar_t>;

/**
 * Unfortunately, the GNU C++ library does not provide specalizations for
 * has/use_facet<num_put<CharT, OutputIt>>, so have to use the num_put
 * directly.
 */
template <class CharT, class OutputIt>
struct __formatter_num_put : num_put<CharT, OutputIt> {};
struct __formatter_ios_base : ios_base {
  __formatter_ios_base() = default;
  __formatter_ios_base(const __formatter_ios_base &other) {
    flags(other.flags());
    width(other.width());
    precision(other.precision());
    imbue(other.getloc());
  }
};

template <class CharT> struct __formatter_base {
  // The format spec consists of zero or more of the following fields in order:
  // fill_and_align_ sign_ sharp_ zero_ width_ precision_ locale_specific_ type_
private:
  enum class align : uint8_t {
    none,
    left,   ///< '<'
    right,  ///< '>'
    center, ///< '^'
  };
  enum class sign : uint8_t {
    plus,  ///< '+'
    minus, ///< '-'
    space, ///< ' '
  };
  enum class type : uint8_t {
    none,
    a,
    A,
    b,
    B,
    c,
    d,
    e,
    E,
    f,
    F,
    g,
    G,
    o,
    p,
    s,
    x,
    X,
  };
  align align_ : 2;
  sign sign_ : 2;
  bool sharp_ : 1;           ///< '#'
  bool zero_ : 1;            ///< '0'
  bool locale_specific_ : 1; ///< 'L'
  bool width_nested_ : 1;
  bool precision_nested_ : 1;
  bool type_upper_ : 1;
  type type_ : 5;
  CharT fill_char_;
  enum : int { width_none = -1, precision_none = -1 };

  ///< if using nested width, the index is stored in
  ///< width_idx_ and should be replaced by the number of
  ///< that index later. same idea for precision.
  int width_;
  int &width_idx_ = width_;
  int precision_;
  int &precision_idx_ = precision_;

  void __parse_fill_and_align(auto &it) {
    auto opt = *(it + 1);
    switch (opt) {
    case '<':
      align_ = align::left;
      break;
    case '>':
      align_ = align::right;
      break;
    case '^':
      align_ = align::center;
      break;
    default:
      align_ = align::none;
      fill_char_ = ' ';
      return;
    }
    fill_char_ = *it;
    it += 2;
  }

  void __parse_sign_sharp_zero(auto &it) {
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
      sign_ = sign::minus;
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
      // if there is a fill char specified, 0 is ignored
      zero_ = true;
      ++it;
    } else {
      zero_ = false;
    }
  }

  static size_t __parse_a_number(auto &it) {
    size_t res = 0;
    while (isdigit(*it)) {
      res *= 10;
      res += *it++ - '0';
    }
    return res;
  }

  void __parse_width_precision(auto &pc, auto &it) {
    // parse helper for both width and precision
    auto parse_part = [&pc, &it](auto &field) -> bool /*nested*/ {
      bool nested = false;
      if (*it == '{') {
        nested = true;
        // recursive width or precision
        ++it;
        if (isdigit(*it)) {
          field = __parse_a_number(it);
          pc.check_arg_id(field);
        } else {
          // auto index
          field = pc.next_arg_id();
        }
        if (*it == '}') {
          ++it;
        } else {
          __throw_invalid_format();
        }
      } else if (isdigit(*it)) {
        field = __parse_a_number(it);
      }
      return nested;
    };

    width_ = width_none;
    precision_ = precision_none;

    width_nested_ = parse_part(width_);
    if (*it == '.') {
      ++it;
      precision_nested_ = parse_part(precision_);
    } else {
      precision_nested_ = false;
    }
  }

  void __parse_locale_specific(auto &it) {
    if (*it == 'L') {
      locale_specific_ = true;
      ++it;
    } else {
      locale_specific_ = false;
    }
  }

  void __parse_type(auto &it) {
    auto c = *it;
    switch (c) {

#define __caseof(x)                                                            \
  case *#x:                                                                    \
    type_ = type::x;                                                           \
    ++it;                                                                      \
    break;
      __caseof(a);
      __caseof(A);
      __caseof(b);
      __caseof(B);
      __caseof(c);
      __caseof(d);
      __caseof(e);
      __caseof(E);
      __caseof(f);
      __caseof(F);
      __caseof(g);
      __caseof(G);
      __caseof(o);
      __caseof(p);
      __caseof(s);
      __caseof(x);
      __caseof(X);
#undef __caseof

    default:
      type_ = type::none;
      type_upper_ = false;
      return;
    }

    type_upper_ = isupper(c);
  }

  [[noreturn]] static inline void __throw_char_out_of_range() {
    __THROW_FORMAT_ERROR("char out of range");
  }

  [[noreturn]] static inline void
  __throw_invalid_format(const char *why = "invalid format") {
    __THROW_FORMAT_ERROR(why);
  }

  [[noreturn]] static inline void __throw_invalid_format_type() {
    __THROW_FORMAT_ERROR("invalid format type");
  }

  /**
   * Fill with fill char and output to fc.out(). This calculate the output width
   * using __width_counter, sv is either a string or a string_view.
   */
  auto __fill_and_output(auto &&sv, auto &fc) {
    auto width = __width_counter<CharT>::width(sv, fc.locale());
    size_t fillL = 0, fillR = 0;

    if (width_ != width_none && width < width_) {
      auto distance = width_ - width;
      switch (align_) {
      case align::left:
        fillR = distance;
        break;
      case align::right:
      case align::none:
        fillL = distance;
        break;
      case align::center:
        fillL = distance / 2;
        fillR = distance - fillL;
        break;
      }
    }

    if constexpr (is_same_v<wchar_t, decltype(fill_char_)>) {
      // fill char may only be full width for wchar_t.
      auto fillW = __width_counter<wchar_t>::width(fill_char_, fc.locale());
      if (fillW == 2) {
        fillL = (fillL + 1) / 2;
        fillR /= 2;
      }
    }

    auto out = fc.out();
    // left fill
    for (size_t i = 0; i < fillL; ++i) {
      *out++ = fill_char_;
    }
    // core number part
    if constexpr (requires { { *out++ = std::forward<decltype(sv)>(sv)}; }) {
      // For a string, if the output iterator is __formatter_iterator,
      // we make use of that temporary string.
      *out++ = std::forward<decltype(sv)>(sv);
    } else {
      // otherwise, just output one by one.
      out = copy(sv.begin(), sv.end(), out);
    }
    // right fill
    for (size_t i = 0; i < fillR; ++i) {
      *out++ = fill_char_;
    }

    return out;
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_b(__format_details::__integral auto t,
                         basic_format_context<OutputIt, CharT> &fc) {
    // special check for 'b', since the standard io manipulators do not
    // support binary presentation.
    using unsigned_t = make_unsigned_t<decltype(t)>;
    unsigned_t ut = t >= 0 ? t : static_cast<unsigned_t>(-t);
    // prepare to redirect to string format
    CharT buf[numeric_limits<uintmax_t>::digits + 1 /*sign*/ + 2 /*0B*/];
    auto bufit = buf;
    if (t < 0) {
      *bufit++ = '-';
    } else {
      if (sign_ == sign::plus) {
        *bufit++ = '+';
      } else if (sign_ == sign::space) {
        *bufit++ = ' ';
      }
    }
    size_t width;
    if (sharp_) {
      *bufit++ = '0';
      *bufit++ = type_upper_ ? 'B' : 'b';
    }
    if (align_ != align::none) {
      zero_ = false;
    }
    if (zero_) {
      width = numeric_limits<unsigned_t>::digits;
    } else {
      width = bit_width(ut);
    }
    if (0 != width) {
      unsigned_t mask = 1U;
      mask <<= width - 1;
      while (mask) {
        *bufit++ = (ut & mask ? '1' : '0');
        mask >>= 1;
      }
    } else {
      *bufit++ = '0';
    }

    // redirect to string format
    if (align_ == align::none) {
      align_ = align::right;
    }
    return __fill_and_output(basic_string_view<CharT>(buf, bufit - buf), fc);
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_c(__format_details::__integral auto t,
                         basic_format_context<OutputIt, CharT> &fc) {
    // special check for 'c'
    // check out of range first
    if (numeric_limits<CharT>::max() < t || numeric_limits<CharT>::min() > t) {
      __throw_char_out_of_range();
    }
    auto c = static_cast<CharT>(t);
    auto out = fc.out();
    *out++ = c;
    return out;
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_odx(__format_details::__integral auto t,
                           basic_format_context<OutputIt, CharT> &fc) {
    // for other types: o/d/x
    auto out = fc.out();
    using unsigned_t = make_unsigned_t<decltype(t)>;
    // the value to produce final output, ut is the absolute value of t.
    // because the standard io treat the oct / hex form of negative integers
    // as the real binary form which does not meet the formatting library's
    // requirement.
    unsigned_t ut = t < 0 ? static_cast<unsigned_t>(-t) : t;

    // the ios base to set ios flags for num_put.
    __formatter_ios_base iosb;
    if (locale_specific_) {
      iosb.imbue(fc.locale());
    }

    if (sharp_) {
      iosb.setf(ios::showbase);
    }
    switch (type_) {
    default:
      break;
    case type::d:
    case type::none:
      iosb.setf(ios::dec);
      break;
    case type::o:
      iosb.setf(ios::oct);
      break;
    case type::X:
      iosb.setf(ios::uppercase);
      [[fallthrough]];
    case type::x:
      iosb.setf(ios::hex);
      break;
    }
    CharT sign{};
    if (t < 0) {
      sign = '-';
    } else {
      if (sign_ == sign::space) {
        sign = ' ';
      } else if (sign_ == sign::plus) {
        sign = '+';
      }
    }

    CharT fillOrZero = fill_char_;
    if (zero_) {
      iosb.setf(ios::internal, ios::adjustfield);
      fillOrZero = '0';
      if (width_ != width_none) {
        if (sign && width_ > 1) {
          --width_;
        }
        iosb.width(width_);
      }
    }

    using counter_t = __counter_formatter_iterator<CharT>;
    counter_t cit;
    __formatter_ios_base iostmp(iosb); // width may be erased by a put operation
    cit = __formatter_num_put<CharT, counter_t>().put(
        cit, iostmp, fillOrZero, static_cast<uintmax_t>(ut));
    basic_string<CharT> str{};
    CharT *begin;

    if (sign) {
      str.resize(cit.count() + 1);
      *str.data() = sign;
      begin = str.data() + 1;
    } else {
      str.resize(cit.count());
      begin = str.data();
    }
    __formatter_num_put<CharT, CharT *>().put(begin, iosb, fillOrZero,
                                              static_cast<uintmax_t>(ut));
    return __fill_and_output(std::move(str), fc);
  }

  // floating point specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(__format_details::__floating_point auto t,
           basic_format_context<OutputIt, CharT> &fc) {
    __formatter_ios_base iosb;
    if (locale_specific_) {
      iosb.imbue(fc.locale());
    }
    CharT sign{};
    // make t always positive to provide consistency with inf and nan, since
    // they do not produce positive sign with the standard io library
    if (signbit(t)) {
      sign = '-';
      t = -t;
    } else {
      if (sign_ == sign::plus) {
        sign = '+';
      } else if (sign_ == sign::space) {
        sign = ' ';
      }
    }

    CharT fillOrZero = fill_char_;
    if (zero_) {
      // padding leading zeros, since we deal with sign before, just pad before
      // and set adjustfield to right.
      iosb.setf(ios::right, ios::adjustfield);
      fillOrZero = '0';
      if (width_ != width_none) {
        if (sign && width_ > 1) {
          --width_;
        }
        iosb.width(width_);
      }
    }

    switch (type_) {
    default:
      break;
    case type::none:
      if (precision_ != precision_none) {
        // fresh ios base does nothing for default float
      } else {
        // According to the standard, default behavior with no precision for
        // floating points is the same as calling to_chars(first, last, value),
        // which behaves as choosing the minimal length for printf()'s format
        // between specifiers %f and %e (prefer %f for a tie). For %f, there are
        // always 6 digits after the radix point; For %e, there are usually 12
        // digits in total for those who has its exponent less than 100 and 13
        // digits otherwise. Therefore, a value with less than 5 digits before
        // the radix point would be treated as fixed, and the others scientific.

        // The solution is to compare t with (double)99999.9999995.
        // for floats, 99999.9999995 uses
        // more bits of mantissa a float can hold;
        // for doubles or long doubles, they use more bits of mantissa and the
        // rounding correctly works.
        if (99999.9999995 < t) {
          iosb.setf(ios::scientific, ios::floatfield);
        } else {
          iosb.setf(ios::fixed, ios::floatfield);
        }
      }
      break;
    case type::a:
    case type::A:
      // hex float is fixed or scientific
      iosb.setf(ios::fixed | ios::scientific, ios::floatfield);
      break;
    case type::e:
    case type::E:
      iosb.setf(ios::scientific, ios::floatfield);
      break;
    case type::f:
    case type::F:
      iosb.setf(ios::fixed, ios::floatfield);
      break;
    }
    if (type_upper_) {
      iosb.setf(ios::uppercase);
    }
    if (precision_ == precision_none) {
      // default precision is always 6. ignored by 'a' & 'A'.
      precision_ = 6;
    }
    iosb.precision(precision_);

    using counter_t = __counter_formatter_iterator<CharT>;
    counter_t cit;
    __formatter_ios_base iostmp(iosb);
    cit =
        __formatter_num_put<CharT, counter_t>().put(cit, iostmp, fillOrZero, t);

    basic_string<CharT> str{};
    CharT *begin;

    if (sign) {
      str.resize(1 + cit.count());
      *str.data() = sign;
      begin = str.data() + 1;
    } else {
      str.resize(cit.count());
      begin = str.data();
    }
    __formatter_num_put<CharT, CharT *>().put(begin, iosb, fillOrZero, t);
    return __fill_and_output(std::move(str), fc);
  }

  // integral specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral(__format_details::__integral auto t,
                       basic_format_context<OutputIt, CharT> &fc) {
    switch (type_) {
    case type::b:
    case type::B:
      return __format_as_integral_b(t, fc);
    case type::c:
      return __format_as_integral_c(t, fc);
    default:
      return __format_as_integral_odx(t, fc);
    }
  }

  // string / string_view / c-string specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(const basic_string_view<CharT> &t,
           basic_format_context<OutputIt, CharT> &fc) {
    if (precision_ != precision_none) {
      // TODO: calculate width
      return __fill_and_output(t.substr(0, precision_), fc);
    } else {
      return __fill_and_output(t, fc);
    };
  }

  // plain integral specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(__format_details::__plain_integral auto t,
           basic_format_context<OutputIt, CharT> &fc) {
    return __format_as_integral(t, fc);
  }

  // bool specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(bool t, basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == type::s || type_ == type::none) {
      // print bool as string
      type_ = type::s;
      locale loc = locale_specific_ ? fc.locale() : locale::classic();
      if (t) {
        return __fill_and_output(use_facet<numpunct<CharT>>(loc).truename(),
                                 fc);
      } else {
        return __fill_and_output(use_facet<numpunct<CharT>>(loc).falsename(),
                                 fc);
      }
    } else {
      return __format(static_cast<unsigned char>(t), fc);
    }
  }

  // char & wchar_t specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(__format_details::__char_t auto t,
           basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == type::none || type_ == type::c) {
      auto out = fc.out();
      *out++ = t;
      return out;
    } else {
      return __format_as_integral(t, fc);
    }
  }

  // pointer specific
  template <class OutputIt, class PtrT>
      requires is_pointer_v<PtrT> ||
      is_null_pointer_v<PtrT> typename basic_format_context<OutputIt,
                                                            CharT>::iterator
      __format(PtrT t, basic_format_context<OutputIt, CharT> &fc) {
    type_ = type::x;
#ifdef __intptr_t_defined
    return __format_as_integral(reinterpret_cast<uintptr_t>(t), fc);
#else
    // The behavior is implementation defined if uintptr_t is not defined.
    return __format_as_integral(reinterpret_cast<uintmax_t>(t), fc);
#endif
  }

  // c-string specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(const CharT *cstr, basic_format_context<OutputIt, CharT> &fc) {
    return __format(basic_string_view<CharT>(cstr), fc);
  }

  template <class T> void __format_check_type_align(const T &) {
    if constexpr (__is_string_v<T>) {
      if (type_ == type::none) {
        type_ = type::s;
      }
      if (type_ != type::s) {
        __throw_invalid_format_type();
      }
    } else if constexpr (__is_plain_integral_v<T>) {
      switch (type_) {
      case type::none:
        type_ = type::d;
        break;
      case type::b:
      case type::B:
      case type::c:
      case type::d:
      case type::o:
      case type::x:
      case type::X:
        break;
      default:
        __throw_invalid_format_type();
      }
    } else if constexpr (__is_char_t_v<T>) {
      switch (type_) {
      case type::none:
        type_ = type::c;
        break;
      case type::b:
      case type::B:
      case type::d:
      case type::o:
      case type::x:
      case type::X:
        break;
      default:
        __throw_invalid_format_type();
      }
    } else if constexpr (is_same_v<T, bool>) {
      switch (type_) {
      case type::none:
        type_ = type::s;
        break;
      case type::b:
      case type::B:
      case type::c:
      case type::d:
      case type::o:
      case type::x:
      case type::X:
        break;
      default:
        __throw_invalid_format_type();
      }
    } else if constexpr (is_floating_point_v<T>) {
      switch (type_) {
      case type::none:
      case type::a:
      case type::A:
      case type::e:
      case type::E:
      case type::f:
      case type::F:
      case type::g:
      case type::G:
        break;
      default:
        __throw_invalid_format_type();
      }
    } else if constexpr (__is_pointer_v<T>) {
      if (type_ == type::none) {
        type_ = type::p;
      }
      if (type_ != type::p) {
        __throw_invalid_format_type();
      }
    }

    if (align_ == align::none) {
      if constexpr (__is_string_v<T>) {
        align_ = align::left;
      } else {
        if (!zero_) {
          // for numeric's, default align to right if no padding zeros only
          align_ = align::right;
        }
      }
    }
    if (align_ != align::none) {
      // now if align is specified, zero should be ignored
      zero_ = false;
    }
  }

  void __format_check_width_precision(auto &fc) {
    // check nested width & precision
    if (width_nested_) {
      width_ = visit_format_arg(
          []<class T>(T && v)->int {
            if constexpr (is_integral_v<decay_t<T>>) {
              // width should be positive
              if (v > 0 && v <= numeric_limits<decltype(width_)>::max()) {
                return v;
              }
              __THROW_FORMAT_ERROR("width should be positive");
            } else {
              __THROW_FORMAT_ERROR("width should be integral");
            }
          },
          fc.arg(width_idx_));
      width_nested_ = false;
    }
    if (precision_nested_) {
      precision_ = visit_format_arg(
          []<class T>(T && v)->int {
            if constexpr (is_integral_v<decay_t<T>>) {
              // precision should be non-negative
              if (v >= 0 && v <= numeric_limits<decltype(precision_)>::max()) {
                return v;
              }
              __THROW_FORMAT_ERROR("precision should be non-negative");
            } else {
              __THROW_FORMAT_ERROR("precision should be integral");
            }
          },
          fc.arg(precision_idx_));
      precision_nested_ = false;
    }
  }

public:
  typename basic_format_parse_context<CharT>::iterator
  parse(basic_format_parse_context<CharT> &pc) {
    auto it = pc.begin();

    __parse_fill_and_align(it);
    __parse_sign_sharp_zero(it);
    __parse_width_precision(pc, it);
    __parse_locale_specific(it);
    __parse_type(it);

    return it;
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  format(const auto &t, basic_format_context<OutputIt, CharT> &fc) {
    // do some common check before formatting
    __format_check_type_align(t);
    __format_check_width_precision(fc);
    return __format(t, fc);
  }
};
extern template class __formatter_base<char>;
extern template class __formatter_base<wchar_t>;
} // namespace __format_details

///@{ Standard specializations for basic types and string types
/*******************************************************************************
// basic char types
template<> struct formatter<char, char>;
template<> struct formatter<char, wchar_t>;
template<> struct formatter<wchar_t, wchar_t>;

// for CharT as char & wchar_t:
// basic string types
template<> struct formatter<CharT*, CharT>;
template<> struct formatter<const CharT*, CharT>;
template<std::size_t N> struct formatter<const CharT[N], CharT>;
template<class Traits, class Alloc>
  struct formatter<std::basic_string<CharT, Traits, Alloc>, CharT>;
template<class Traits>
  struct formatter<std::basic_string_view<CharT, Traits>, CharT>;

// arithmetic types
template<> struct formatter<ArithmeticT, CharT>;

// pointer types
template<> struct formatter<std::nullptr_t, CharT>;
template<> struct formatter<void*, CharT>;
template<> struct formatter<const void*, CharT>;
*******************************************************************************/
template <>
struct formatter<char, char> : __format_details::__formatter_base<char> {};
template <>
struct formatter<char, wchar_t> : __format_details::__formatter_base<wchar_t> {
};
template <>
struct formatter<wchar_t, wchar_t>
    : __format_details::__formatter_base<wchar_t> {};

template <__format_details::__char_t CharT>
struct formatter<CharT *, CharT> : __format_details::__formatter_base<CharT> {};
template <__format_details::__char_t CharT>
struct formatter<const CharT *, CharT>
    : __format_details::__formatter_base<CharT> {};
template <size_t N, __format_details::__char_t CharT>
struct formatter<const CharT[N], CharT>
    : __format_details::__formatter_base<CharT> {};

template <class Traits, class Allocator, __format_details::__char_t CharT>
struct formatter<basic_string<CharT, Traits, Allocator>, CharT>
    : __format_details::__formatter_base<CharT> {};

template <class Traits, __format_details::__char_t CharT>
struct formatter<basic_string_view<CharT, Traits>, CharT>
    : __format_details::__formatter_base<CharT> {};

template <class ArithmeticT, __format_details::__char_t CharT>
    requires(!__format_details::__is_one_of_v<ArithmeticT, char, wchar_t,
                                              char8_t, char16_t, char32_t>) &&
    is_arithmetic_v<ArithmeticT> struct formatter<ArithmeticT, CharT>
    : __format_details::__formatter_base<CharT> {};

template <__format_details::__one_of<nullptr_t, void *, const void *> PtrT,
          __format_details::__char_t CharT>
struct formatter<PtrT, CharT> : __format_details::__formatter_base<CharT> {};

extern template struct formatter<char, char>;
extern template struct formatter<char, wchar_t>;
extern template struct formatter<wchar_t, wchar_t>;
extern template struct formatter<char *, char>;
extern template struct formatter<wchar_t *, wchar_t>;
extern template struct formatter<const char *, char>;
extern template struct formatter<const wchar_t *, wchar_t>;
extern template struct formatter<string, char>;
extern template struct formatter<wstring, wchar_t>;
extern template struct formatter<string_view, char>;
extern template struct formatter<wstring_view, wchar_t>;
extern template struct formatter<int, char>;
extern template struct formatter<int, wchar_t>;
extern template struct formatter<unsigned int, char>;
extern template struct formatter<unsigned int, wchar_t>;
extern template struct formatter<long long, char>;
extern template struct formatter<long long, wchar_t>;
extern template struct formatter<unsigned long long, char>;
extern template struct formatter<unsigned long long, wchar_t>;
extern template struct formatter<float, char>;
extern template struct formatter<float, wchar_t>;
extern template struct formatter<double, char>;
extern template struct formatter<double, wchar_t>;
extern template struct formatter<long double, char>;
extern template struct formatter<long double, wchar_t>;
extern template struct formatter<nullptr_t, char>;
extern template struct formatter<nullptr_t, wchar_t>;
extern template struct formatter<void *, char>;
extern template struct formatter<void *, wchar_t>;
extern template struct formatter<const void *, char>;
extern template struct formatter<const void *, wchar_t>;
///@}

namespace __format_details {
// Helper struct to implement global format functions.
struct __public_func {
private:
  friend string std::vformat(string_view fmt, format_args args);
  friend wstring std::vformat(wstring_view fmt, wformat_args args);
  friend string std::vformat(const locale &loc, string_view fmt,
                             format_args args);
  friend wstring std::vformat(const locale &loc, wstring_view fmt,
                              wformat_args args);

  template <class Out>
  friend Out std::vformat_to(Out out, string_view fmt,
                             format_args_t<type_identity_t<Out>, char> args);
  template <class Out>
  friend Out std::vformat_to(Out out, wstring_view fmt,
                             format_args_t<type_identity_t<Out>, wchar_t> args);
  template <class Out>
  friend Out std::vformat_to(Out out, const locale &loc, string_view fmt,
                             format_args_t<type_identity_t<Out>, char> args);
  template <class Out>
  friend Out std::vformat_to(Out out, const locale &loc, wstring_view fmt,
                             format_args_t<type_identity_t<Out>, wchar_t> args);

  template <class Out, class... Args>
  friend format_to_n_result<Out>
  std::format_to_n(Out out, iter_difference_t<Out> n, string_view fmt,
                   const Args &... args);
  template <class Out, class... Args>
  friend format_to_n_result<Out>
  std::format_to_n(Out out, iter_difference_t<Out> n, wstring_view fmt,
                   const Args &... args);
  template <class Out, class... Args>
  friend format_to_n_result<Out>
  std::format_to_n(Out out, iter_difference_t<Out> n, const locale &loc,
                   string_view fmt, const Args &... args);
  template <class Out, class... Args>
  friend format_to_n_result<Out>
  std::format_to_n(Out out, iter_difference_t<Out> n, const locale &loc,
                   wstring_view fmt, const Args &... args);

  template <class... Args>
  friend size_t std::formatted_size(string_view fmt, const Args &... args);
  template <class... Args>
  friend size_t std::formatted_size(wstring_view fmt, const Args &... args);
  template <class... Args>
  friend size_t std::formatted_size(const locale &loc, string_view fmt,
                                    const Args &... args);
  template <class... Args>
  friend size_t std::formatted_size(const locale &loc, wstring_view fmt,
                                    const Args &... args);

  static inline void __throw_invalid_format_if(bool b) {
    if (b) {
      __throw_invalid_format();
    }
  }

  [[noreturn]] static inline void __throw_invalid_format() {
    __THROW_FORMAT_ERROR("invalid format");
  }

  [[noreturn]] static inline void __throw_invalid_argument() {
    __THROW_FORMAT_ERROR("invalid argument");
  }

  /**
   * Visitor for basic types or user-defined classes.
   * @tparam OutputIt The output iterator.
   * @tparam CharT The char type of output.
   */
  template <class OutputIt, class CharT> struct __visitor {
    basic_format_parse_context<CharT> &pc;
    basic_format_context<OutputIt, CharT> &fc;

    __visitor(basic_format_parse_context<CharT> &pc,
              basic_format_context<OutputIt, CharT> &fc)
        : pc(pc), fc(fc) {}

    // Unreachable
    void operator()(const monostate &) { __IMPLEMENTATION_BUG(); }

    // Built-in basic types.
    template <class T> void operator()(const T &v) {
      using formatter_type = typename basic_format_context<
          OutputIt, CharT>::template formatter_type<remove_cvref_t<T>>;
      formatter_type f;
      pc.advance_to(f.parse(pc));
      fc.advance_to(f.format(v, fc));
    }

    // Redirect for user defined formatter. See basic_format_arg::handle.
    void operator()(const typename basic_format_arg<
                    basic_format_context<OutputIt, CharT>>::handle &handle) {
      const_cast<decay_t<decltype(handle)> &>(handle).format(pc, fc);
    }
  };

  inline static const locale &__default_locale() {
    static locale loc = [] {
      try {
        return locale("C.UTF-8");
      } catch (...) {
        return locale("");
      }
    }();
    return loc;
  }

  template <class OutputIt, class CharT>
  static OutputIt vformat_to(OutputIt &out, const locale &loc,
                             const basic_string_view<CharT> &fmt,
                             const format_args_t<OutputIt, CharT> &args) {
    size_t argIdx;                ///< argument index
    size_t argsSize = args.size_; ///< size of args

    basic_format_context<OutputIt, CharT> fc(args, out, loc);
    // TODO: what is the second argument used for?
    basic_format_parse_context<CharT> pc(fmt, argsSize);

    for (auto it = pc.begin(), ite = pc.end(); it != ite;) {
      if (*it != '{' && *it != '}') {
        // characters other than '{' and '}' are just copied directly
        *out++ = *it++;
        continue;
      }
      if (*it == '{') {
        // get started with a format field.
        // process the argument index if exists, and [it, ite) currently stands
        // for the range of index field.
        ++it;
        __throw_invalid_format_if(it == ite);
        if (*it == '{') {
          // convert "{{" to "{" and copy to the output directly
          *out++ = *it++;
          continue;
        }
        // now it is one char past the beginning '{'
        if (isdigit(*it)) {
          // met the index
          argIdx = 0;
          while (isdigit(*it)) {
            argIdx *= 10;
            argIdx += *it++ - '0';
          }
          pc.check_arg_id(argIdx);
        } else {
          argIdx = pc.next_arg_id();
        }
        __throw_invalid_format_if(it == ite);
        if (*it == ':') {
          ++it;
          __throw_invalid_format_if(it == ite);
        }
        // update the iterator in pc first.
        pc.advance_to(it);
        if (auto arg = fc.arg(argIdx)) {
          visit_format_arg(__visitor(pc, fc), std::move(arg));
        } else {
          __throw_invalid_argument();
        }
        // after the parse, pc.begin() must point at '}'
        it = pc.begin();
        __throw_invalid_format_if(it == ite || *it != '}');
        ++it;
      } else /*if (c == '}')*/ {
        // now, only "}}" is accepted
        ++it;
        __throw_invalid_format_if(it == ite || *it != '}');
        // copy the '}' directly
        *out++ = *it++;
        continue;
      }
    }

    return fc.out();
  }

  inline static string vformat(const locale &loc, const string_view &fmt,
                               const format_args &args) {
    __formatter_iterator_impl<char> itImpl;
    __formatter_iterator<char> it(itImpl);
    it = vformat_to(it, loc, fmt, args);
    return it.result();
  }

  inline static wstring vformat(const locale &loc, const wstring_view &fmt,
                                const wformat_args &args) {
    __formatter_iterator_impl<wchar_t> itImpl;
    __formatter_iterator<wchar_t> it(itImpl);
    it = vformat_to(it, loc, fmt, args);
    return it.result();
  }

  template <class OutputIt, class CharT, class... Args>
  static inline format_to_n_result<OutputIt>
  format_to_n(OutputIt &out, iter_difference_t<OutputIt> n, const locale &loc,
              const basic_string_view<CharT> &fmt, const Args &... args) {
    using iterator_t = __limited_formatter_iterator<OutputIt, CharT>;
    using context_t = basic_format_context<iterator_t, CharT>;
    auto N = n > 0 ? n : 0;
    iterator_t it(out, N, loc);
    it = vformat_to(it, loc, fmt,
                    basic_format_args(make_format_args<context_t>(args...)));
    decltype(n) written = N - it.avail();
    return {.out = it.out(), .size = written};
  }

  template <class CharT, class... Args>
  static size_t formatted_size(const locale &loc,
                               const basic_string_view<CharT> &fmt,
                               const Args &... args) {
    using iterator_t = __width_counter_formatter_iterator<CharT>;
    using context_t = basic_format_context<iterator_t, CharT>;
    iterator_t it(loc);
    it = vformat_to(it, loc, fmt,
                    basic_format_args(make_format_args<context_t>(args...)));
    return it.count();
  }
};
} // namespace __format_details

// [format.functions], formatting functions
template <class... Args>
inline string format(string_view fmt, const Args &... args) {
  return vformat(fmt, make_format_args(args...));
}
template <class... Args>
inline wstring format(wstring_view fmt, const Args &... args) {
  return vformat(fmt, make_wformat_args(args...));
}
template <class... Args>
inline string format(const locale &loc, string_view fmt, const Args &... args) {
  return vformat(loc, fmt, make_format_args(args...));
}
template <class... Args>
inline wstring format(const locale &loc, wstring_view fmt,
                      const Args &... args) {
  return vformat(loc, fmt, make_wformat_args(args...));
}

inline string vformat(string_view fmt, format_args args) {
  return vformat(__format_details::__public_func::__default_locale(), fmt,
                 std::move(args));
}
inline wstring vformat(wstring_view fmt, wformat_args args) {
  return vformat(__format_details::__public_func::__default_locale(), fmt,
                 std::move(args));
}
inline string vformat(const locale &loc, string_view fmt, format_args args) {
  return __format_details::__public_func::vformat(loc, fmt, std::move(args));
}
inline wstring vformat(const locale &loc, wstring_view fmt, wformat_args args) {
  return __format_details::__public_func::vformat(loc, fmt, std::move(args));
}

template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, string_view fmt, const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, char>;
  return vformat_to(out, fmt, make_format_args<context_t>(args...));
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, wstring_view fmt,
                          const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, wchar_t>;
  return vformat_to(out, fmt, make_format_args<context_t>(args...));
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, const locale &loc, string_view fmt,
                          const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, char>;
  return vformat_to(out, loc, fmt, make_format_args<context_t>(args...));
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, const locale &loc, wstring_view fmt,
                          const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, wchar_t>;
  return vformat_to(out, loc, fmt, make_format_args<context_t>(args...));
}

template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, string_view fmt,
           format_args_t<type_identity_t<OutputIt>, char> args) {
  return vformat_to(out, __format_details::__public_func::__default_locale(),
                    fmt, std::move(args));
}
template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, wstring_view fmt,
           format_args_t<type_identity_t<OutputIt>, wchar_t> args) {
  return vformat_to(out, __format_details::__public_func::__default_locale(),
                    fmt, std::move(args));
}
template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, const locale &loc, string_view fmt,
           format_args_t<type_identity_t<OutputIt>, char> args) {
  return __format_details::__public_func::vformat_to(out, loc, fmt,
                                                     std::move(args));
}
template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, const locale &loc, wstring_view fmt,
           format_args_t<type_identity_t<OutputIt>, wchar_t> args) {
  return __format_details::__public_func::vformat_to(out, loc, fmt,
                                                     std::move(args));
}

template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, string_view fmt,
            const Args &... args) {
  return format_to_n(out, n,
                     __format_details::__public_func::__default_locale(), fmt,
                     args...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, wstring_view fmt,
            const Args &... args) {
  return format_to_n(out, n,
                     __format_details::__public_func::__default_locale(), fmt,
                     args...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, const locale &loc,
            string_view fmt, const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, char>;
  return __format_details::__public_func::format_to_n(out, n, loc, fmt,
                                                      args...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, const locale &loc,
            wstring_view fmt, const Args &... args) {
  using context_t = basic_format_context<type_identity_t<OutputIt>, wchar_t>;
  return __format_details::__public_func::format_to_n(out, n, loc, fmt,
                                                      args...);
}

template <class... Args>
inline size_t formatted_size(string_view fmt, const Args &... args) {
  return formatted_size(__format_details::__public_func::__default_locale(),
                        fmt, args...);
}
template <class... Args>
inline size_t formatted_size(wstring_view fmt, const Args &... args) {
  return formatted_size(__format_details::__public_func::__default_locale(),
                        fmt, args...);
}
template <class... Args>
inline size_t formatted_size(const locale &loc, string_view fmt,
                             const Args &... args) {
  return __format_details::__public_func::formatted_size(loc, fmt, args...);
}
template <class... Args>
inline size_t formatted_size(const locale &loc, wstring_view fmt,
                             const Args &... args) {
  return __format_details::__public_func::formatted_size(loc, fmt, args...);
}
} // namespace std

#undef __THROW_FORMAT_ERROR
#undef __IMPLEMENTATION_BUG

#endif // C++20
