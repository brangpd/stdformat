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
#include <concepts>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
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
template <class Container> class __formatter_iterator;
template <class Container>
using __formatter_output_iterator_t = __formatter_iterator<Container>;
} // namespace __format_details

template <class Out, class CharT> class basic_format_context;
using format_context = basic_format_context<
    __format_details::__formatter_output_iterator_t<std::string>, char>;
using wformat_context = basic_format_context<
    __format_details::__formatter_output_iterator_t<std::wstring>, wchar_t>;

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
template <class T> struct __is_char_t : __is_one_of<T, char, wchar_t> {};
template <class T> constexpr bool __is_char_t_v = __is_char_t<T>::value;
template <class T> concept __char_t = __is_char_t_v<T>;

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

  [[noreturn]] static void __throw_mixing_indexing() {
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

  template <class Context2, class... Args>
  friend __format_arg_store<Context2, Args...>
  make_wformat_args(const Args &... args);

  template <class Visitor, class Context2>
  friend auto visit_format_arg(Visitor &&vis, basic_format_arg<Context2> arg);

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
            typename FormatContext::template formatter_type<T> f;
            parse_ctx.advance_to(f.parse(parse_ctx));
            format_ctx.advance_to(
                f.format(*static_cast<const T *>(ptr), format_ctx));
          }) {}

    friend basic_format_arg<FormatContext>;

  public:
    void format(basic_format_parse_context<char_type> &parse_ctx,
                FormatContext &format_ctx) const {
      return format_(parse_ctx, format_ctx, ptr_);
    }
  };

private:
  variant<monostate, bool, char_type, int, unsigned int, long long int,
          unsigned long long int, float, double, long double, const char_type *,
          basic_string_view<char_type>, const void *, handle>
      value_;

  template <class T> explicit basic_format_arg(const T &v) noexcept {
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
auto visit_format_arg(Visitor &&vis, basic_format_arg<FormatContext> arg) {
  return std::visit(std::forward<Visitor>(vis), arg.value_);
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
 * The formatter iterator is an output iterator that provides a wrapper of the
 * underlying iterator (say the back insert iterator). It behaves as if the
 * underlying iterator is being used directly, except that it allows objects of
 * derived classes to determine whether the output operation should be finally
 * executed.
 * @tparam Container The container, namely the basic string to produce
 * formatting output.
 */
template <class Container> class __formatter_iterator {
  friend __format_details::__public_func;

protected:
  using __container_type = Container;

private:
  Container *container_;

protected:
  explicit __formatter_iterator() : container_() {}
  explicit __formatter_iterator(Container &c) : container_(&c) {}
  /**
   * Determine whether the output operation should be executed.
   * @return True if the output operation is expected, in which case new
   * character would be assigned and iterator would be advanced. Specify false
   * to disable the operation.
   */
  virtual bool operate() { return true; }

public:
  typedef output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;

  __formatter_iterator &
  operator=(const typename __container_type::value_type &c) {
    if (operate()) {
      if (container_) {
        container_->push_back(c);
      }
    }
    return *this;
  }
  __formatter_iterator &operator=(const __formatter_iterator &other) {
    container_ = other.container_;
    return *this;
  }
  // Those are all no-op operations for output iterators, only used to remain
  // consistency.
  __formatter_iterator &operator*() { return *this; }
  __formatter_iterator &operator++() { return *this; }
  __formatter_iterator &operator++(int) { return *this; }
};

/**
 * Counter wrapper for formatted_size's. It does not write any character but
 * only counts how many times it is operated.
 */
template <class Container>
class __counter_formatter_iterator : public __formatter_iterator<Container> {
  friend __format_details::__public_func;

private:
  size_t count_; ///< The counter.

protected:
  bool operate() override {
    ++count_;
    // disallow all operations
    return false;
  }

public:
  __counter_formatter_iterator()
      : __formatter_iterator<Container>(), count_(0) {}
  size_t count() const { return count_; }
};

/**
 * Limited wrapper for format_n's. It limits the maximum operations of output.
 */
template <class Container>
class __limited_formatter_iterator : public __formatter_iterator<Container> {
  friend __format_details::__public_func;

private:
  size_t avail_; ///< Available operations left.

protected:
  bool operate() override {
    // disallow further operations when avail_ becomes zero
    if (avail_ > 0) {
      --avail_;
      return true;
    }
    return false;
  }

public:
  __limited_formatter_iterator(Container &c, size_t maxOp)
      : __formatter_iterator<Container>(c), avail_(maxOp) {}
  size_t avail() const { return avail_; }
};

template <class CharT> class __formatter_ios : public basic_ios<CharT> {
  friend __formatter_base<CharT>;

  __formatter_ios() {}

public:
  template <class OutputIt> auto format_num(OutputIt destIt, uintmax_t v) {
    struct : num_put<CharT, OutputIt> {
    } np;
    return np.put(destIt, *this, this->fill(), v);
  }
  template <class OutputIt>
  auto format_str(OutputIt destIt, const basic_string_view<CharT> &s) {
    return copy(s.begin(), s.end(), destIt);
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
    none,
    plus,  ///< '+'
    minus, ///< '-'
    space, ///< ' '
  };
  align align_ : 2;
  sign sign_ : 2;
  bool sharp_ : 1;           ///< '#'
  bool zero_ : 1;            ///< '0'
  bool locale_specific_ : 1; ///< 'L'
  CharT fill_char_;
  enum : int { width_none = -1, precision_none = -1, type_none = 0 };
  bool width_nested_ : 1;
  bool precision_nested_ : 1;
  bool negative_ : 1;
  CharT type_;
  union {
    int width_;
    int width_idx_;
  }; ///< if using nested width, the index is stored in
     ///< width_idx_ and should be replaced by the number of
     ///< that index later. same idea for precision.
  union {
    int precision_;
    int precision_idx_;
  };
  __formatter_ios<CharT> ios_;

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
    switch (auto c = *it) {
    default:
      type_ = type_none;
      break;
    case 'a':
    case 'A':
    case 'b':
    case 'B':
    case 'c':
    case 'd':
    case 'e':
    case 'E':
    case 'f':
    case 'F':
    case 'g':
    case 'G':
    case 'o':
    case 'p':
    case 's':
    case 'x':
    case 'X':
      type_ = c;
      ++it;
      break;
    }
  }

  [[noreturn]] static void __throw_char_out_of_range() {
#if __cpp_exceptions
    throw format_error("char out of range");
#else
    terminate();
#endif
  }

  [[noreturn]] static void
  __throw_invalid_format(const char *why = "invalid format") {
#if __cpp_exceptions
    throw format_error(why);
#else
    terminate();
#endif
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_b(integral auto t,
                         basic_format_context<OutputIt, CharT> &fc) {
    // special check for 'b', since the standard io manipulators do not
    // support binary presentation.
    using unsigned_t = make_unsigned_t<decltype(t)>;
    unsigned_t ut = t >= 0 ? t : static_cast<unsigned_t>(-t);
    // prepare to redirect to string format
    CharT buf[numeric_limits<unsigned_t>::digits + 1 /*sign*/ + 2 /*0B*/];
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
      *bufit++ = type_;
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
    type_ = 's';
    return __format(basic_string_view(buf, bufit), fc);
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_c(integral auto t,
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

  auto __fill_and_output_wrap(size_t widthBeforeFill, auto &&func, auto &fc) {
    auto &width = widthBeforeFill;
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

    auto out = fc.out();
    // left fill
    for (size_t i = 0; i < fillL; ++i) {
      *out++ = fill_char_;
    }
    // core part
    out = func();
    // right fill
    for (size_t i = 0; i < fillR; ++i) {
      *out++ = fill_char_;
    }

    return out;
  }

  auto __fill_and_output_num(basic_stringstream<CharT> &ss, auto &fc) {
    return __fill_and_output_wrap(
        ss.tellp(),
        [&ss, &fc] {
          auto out = fc.out();
          if constexpr (is_same_v<decay_t<decltype(out)>,
                                  __formatter_iterator<CharT>>) {

          } else {
            for (CharT buf[64]; auto read = ss.readsome(buf, size(buf));) {
              for (auto it = buf, ite = buf + read; it != ite;) {
                *out++ = *it++;
              }
            }
          }
          return out;
        },
        fc);
  }

  auto __fill_and_output_str(const basic_string_view<CharT> &sv, auto &fc) {
    return __fill_and_output_wrap(
        sv.size(),
        [&sv, &fc] {
          auto out = fc.out();
          for (auto &&c : sv) {
            *out++ = c;
          }
          return out;
        },
        fc);
  }

  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral_odx(integral auto t,
                           basic_format_context<OutputIt, CharT> &fc) {
    // for other types: o/d/x
    auto out = fc.out();
    using unsigned_t = make_unsigned_t<decltype(t)>;
    // the value to produce final output, ut is the absolute value of t.
    // because the standard io treat the oct / hex form of negative integers
    // as the real binary form which does not meet the formatting library's
    // requirement.

    basic_stringstream<CharT> ss{}; // achieve the raw number without fills

    if (sharp_) {
      ss << showbase;
    }
    switch (type_) {
    case 'd':
    case type_none:
      ss << dec;
      break;
    case 'o':
      ss << oct;
      break;
    case 'X':
      ss << uppercase;
      [[fallthrough]];
    case 'x':
      ss << hex;
      break;
    }
    if (zero_) {
      ss << internal << setfill(static_cast<CharT>('0'));
      if (width_ != width_none) {
        if (t < 0) {
          if (width_ > 1) {
            ss << setw(width_ - 1);
          }
        } else {
          if (width_) {
            ss << setw(width_);
          }
        }
      }
    }
    if (t < 0) {
      ss << '-';
    } else {
      if (sign_ == sign::plus) {
        ss << '+';
      } else if (sign_ == sign::space) {
        ss << ' ';
      }
    }
    unsigned_t ut = t < 0 ? static_cast<unsigned_t>(-t) : t;
    ss << ut;

    return __fill_and_output_num(ss, fc);
  }

  // integral specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format_as_integral(integral auto t,
                       basic_format_context<OutputIt, CharT> &fc) {
    switch (type_) {
    case 'b':
    case 'B':
      return __format_as_integral_b(t, fc);
    case 'c':
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
    if (type_ == type_none || type_ == 's') {
      if (precision_ != precision_none) {
        return __fill_and_output_str(t.substr(0, precision_), fc);
      } else {
        return __fill_and_output_str(t, fc);
      }
    } else {
      __throw_invalid_format();
    }
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
    if (type_ == 's' || type_ == type_none) {
      // print bool as string
      basic_stringstream<CharT> ss{};
      ss << boolalpha << t;
      return __format(ss.str(), fc);
    } else {
      return __format(static_cast<unsigned char>(t), fc);
    }
  }

  // char & wchar_t specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(__format_details::__char_t auto t,
           basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == type_none || type_ == 'c') {
      auto out = fc.out();
      *out++ = t;
      return out;
    } else {
      return __format_as_integral(t, fc);
    }
  }

  // floating point specific
  template <class OutputIt>
  typename basic_format_context<OutputIt, CharT>::iterator
  __format(floating_point auto t, basic_format_context<OutputIt, CharT> &fc) {
    basic_stringstream<CharT> ss{};
    if (type_ == type_none) {
      if (precision_ != precision_none) {
        ss << defaultfloat;
      } else {
        // According to the standard, default behavior with no precision for
        // floating points is the same as calling to_chars(first, last, value),
        // which behaves as choosing the minimal length for printf()'s format
        // between specifiers %f and %e (prefer %f for a tie). For %f, there are
        // always 6 digits after the radix point; For %e, there are usually 12
        // digits in total for those who has its exponent less than 100 and 13
        // digits otherwise. Therefore, a value with less than 5 digits before
        // the radix point would be treated as fixed, and the others scientific.
        if (static_cast<decltype(t)>(1e5 - 1e-7) > t) {
          ss << fixed;
        } else {
          ss << scientific;
        }
      }
      goto L_output;
    } else if (type_ == 'a' || type_ == 'A') {
      ss << hexfloat;
    } else if (type_ == 'e' || type_ == 'E') {
      ss << scientific;
      if (precision_ == precision_none) {
        // for 'e' / 'f' / 'g', default precision is always 6.
        precision_ = 6;
      }
    } else if (type_ == 'f' || type_ == 'F') {
      ss << fixed;
      if (precision_ == precision_none) {
        precision_ = 6;
      }
    } else if (type_ == 'g' || type_ == 'G') {
      if (precision_ == precision_none) {
        precision_ = 6;
      }
    } else {
      __throw_invalid_format();
    }
    ss << setprecision(precision_);
    if (isupper(type_)) {
      ss << uppercase;
    }

  L_output:
    if (!isfinite(t)) {
      // for inf and nan, the positive sign is not added by standard io library
      if (signbit(t) == 0) {
        switch (sign_) {
        case sign::none:
        case sign::minus:
          break;
        case sign::plus:
          ss << '+';
          break;
        case sign::space:
          ss << ' ';
          break;
        }
      }
    }
    ss << t;
    return __fill_and_output_num(ss, fc);
  }

  // pointer specific
  template <class OutputIt, class PtrT>
      requires is_pointer_v<PtrT> ||
      is_null_pointer_v<PtrT> typename basic_format_context<OutputIt,
                                                            CharT>::iterator
      __format(PtrT t, basic_format_context<OutputIt, CharT> &fc) {
    if (type_ == type_none || type_ == 'p') {
      type_ = 'x';
#ifdef __intptr_t_defined
      return __format_as_integral(reinterpret_cast<uintptr_t>(t), fc);
#else
      // The behavior is implementation defined if uintptr_t is not defined.
      return __format_as_integral(reinterpret_cast<uintmax_t>(t), fc);
#endif
    } else {
      __throw_invalid_format();
    }
  }

  void __format_check(auto &fc) {
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
            }
            __THROW_FORMAT_ERROR("invalid width");
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
            }
            __THROW_FORMAT_ERROR("invalid precision");
          },
          fc.arg(precision_idx_));
      precision_nested_ = false;
    }
    if (align_ != align::none) {
      zero_ = false;
    }
  }

#undef __INIT_FORMAT_STREAM

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
    __format_check(fc);
    return __format(t, fc);
  }
};

/**
 * Formatter for C string to produce string output instead of the pointer's
 * value.
 */
template <__char_t CharT>
struct __c_string_formatter : __formatter_base<CharT> {
  inline auto format(const CharT *pstr, auto &fc) {
    return __formatter_base<CharT>::format(basic_string_view<CharT>(pstr), fc);
  }
};
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
///@}

namespace __format_details {
struct __public_func {
private:
  friend string std::vformat(string_view fmt, format_args args);
  friend wstring std::vformat(wstring_view fmt, wformat_args args);
  friend string std::vformat(const locale &, string_view fmt, format_args args);
  friend wstring std::vformat(const locale &, wstring_view fmt,
                              wformat_args args);

  static inline void __throw_invalid_format_if(bool b) {
    if (b) {
      __throw_invalid_format();
    }
  }

  [[noreturn]] static void __throw_invalid_format() {
    __THROW_FORMAT_ERROR("invalid format");
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

    // No-op for monostate.
    void operator()(monostate) {}

    // Built-in basic types.
    template <class T> void operator()(T &&v) {
      using formatter_type = typename basic_format_context<
          OutputIt, CharT>::template formatter_type<remove_cvref_t<T>>;
      formatter_type f;
      pc.advance_to(f.parse(pc));
      fc.advance_to(f.format(std::forward<T>(v), fc));
    }

    // Redirect for user defined formatter. See basic_format_arg::handle.
    void operator()(
        typename basic_format_arg<basic_format_context<OutputIt, CharT>>::handle
            handle) {
      handle.format(pc, fc);
    }
  };

  template <class OutputIt, class CharT>
  static OutputIt vformat_to(
      OutputIt &out, const locale &loc, const basic_string_view<CharT> &fmt,
      const basic_format_args<basic_format_context<OutputIt, CharT>> &args) {
    size_t argIdx;                ///< argument index
    size_t argsSize = args.size_; ///< size of args

    basic_format_context<OutputIt, CharT> fc(args, out, loc);
    // TODO: what is the second argument used for?
    basic_format_parse_context<CharT> pc(fmt, argsSize);

    for (auto it = pc.begin(); it != pc.end();) {
      if (*it != '{' && *it != '}') {
        // characters other than '{' and '}' are just copied directly
        *out++ = *it++;
        continue;
      }
      if (*it == '{') {
        // get started with a format spec.
        // process the argument index if exists, and [it, ite) currently stands
        // for the range of index field.
        ++it;
        __throw_invalid_format_if(it == pc.end());
        if (*it == '{') {
          // convert "{{" to "{" and copy to the output directly
          *out++ = *it++;
          continue;
        }
        // now it is one char past the beginning '{'
        auto ite = it;
        while (ite != pc.end() && *ite != ':' && *ite != '}') {
          // head till ':' or '}' for index
          ++ite;
        }
        __throw_invalid_format_if(ite == pc.end());
        // now ite ends at ':' or '}'
        bool argIdxSet = false;
        argIdx = 0;

        if (ite != it) {
          // 1 or more than 1 char between it and ite, that means there must be
          // an index (no matter ite is now at ':' or '}')
          argIdxSet = true;
          // extension: allow negative index
          bool negative = false;
          if (*it == '-') {
            ++it;
            negative = true;
          }
          while (it != ite) {
            // read the index number
            if (isdigit(*it)) {
              argIdx *= 10;
              argIdx += *it++ - '0';
            } else {
              __throw_invalid_format();
            }
          }
          if (negative && argIdx) {
            argIdx = argsSize - argIdx;
          }
        }
        // now it must equal ite
        if (*it == ':') {
          ++it;
        }

        // find the corresponding arg idx
        if (argIdxSet) {
          pc.check_arg_id(argIdx);
        } else {
          argIdx = pc.next_arg_id();
        }
        if (auto &&arg = fc.arg(argIdx)) {
          // do parse and format visit.
          // update the iterator in pc first.
          pc.advance_to(it);
          visit_format_arg(__visitor(pc, fc), std::move(arg));
        }
        it = pc.begin() + 1;
      } else /*if (c == '}')*/ {
        // now, only "}}" is accepted
        ++it;
        __throw_invalid_format_if(it == fmt.end() || *it != '}');
        // copy the '}' directly
        *out++ = *it++;
        continue;
      }
    }

    return fc.out();
  }

  template <class OutputIt, class CharT>
  static basic_string<CharT> vformat(
      const locale &loc, const basic_string_view<CharT> &fmt,
      const basic_format_args<basic_format_context<OutputIt, CharT>> &args) {
    using container_t = basic_string<CharT>;
    using iterator_t = __formatter_iterator<container_t>;
    container_t res{};  // formatted result
    iterator_t it(res); // wrap inserter with formatter iterator
    vformat_to(it, loc, fmt, args);
    return res;
  }

  template <class OutputIt, class CharT>
  static format_to_n_result<OutputIt> __vformat_to_n(
      OutputIt &out, iter_difference_t<OutputIt> n, const locale &loc,
      const basic_string_view<CharT> &fmt,
      const basic_format_args<basic_format_context<OutputIt, CharT>> &args) {
    using container_t = basic_string<CharT>;
    using iterator_t = __limited_formatter_iterator<container_t>;
    container_t res{};
    auto N = static_cast<size_t>(max(0, n)); // disallow negative n
    iterator_t it(res, N); // wrap insert iterator with limited iterator
    it = vformat_to(it, loc, fmt, args);
    auto written = N - it.avail();
  }

  template <class CharT> class __counter_empty_container {
  public:
    using value_type = CharT;
  };

  template <class CharT, class... Args>
  static size_t formatted_size(const locale &loc,
                               const basic_string_view<CharT> &fmt,
                               const Args &... args) {
    using container_t = __counter_empty_container<CharT>;
    using iterator_t = __counter_formatter_iterator<container_t>;
    using context_t = basic_format_context<iterator_t, CharT>;
    return __vformatted_size(loc, fmt, make_format_args<context_t>(args...));
  }

  template <class OutputIt, class Context, class CharT>
  static size_t __vformatted_size(const locale &loc,
                                  const basic_string_view<CharT> &fmt,
                                  const basic_format_args<Context> &args) {
    using container_t = __counter_empty_container<CharT>;
    using iterator_t = __counter_formatter_iterator<container_t>;
    using context_t = basic_format_context<iterator_t, CharT>;
    iterator_t it{};
    it = vformat_to(it, loc, fmt, args);
    return it.count();
  }

  template <class OutputIt, class CharT, class... Args>
  static format_to_n_result<OutputIt>
  format_to_n(OutputIt &out, iter_difference_t<OutputIt> n, const locale &loc,
              const basic_string_view<CharT> &fmt, const Args &... args) {
    using context_t = basic_format_context<OutputIt, CharT>;
    return __vformat_to_n(out, n, loc, fmt,
                          make_format_args<context_t>(args...));
  }

  template <class OutputIt, class CharT, class... Args>
  static OutputIt format_to(OutputIt out, const locale &loc,
                            const basic_string_view<CharT> &fmt,
                            const Args &... args) {
    using context_t = basic_format_context<OutputIt, CharT>;
    return vformat_to(out, fmt, make_format_args<context_t>(args...));
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
  return __format_details::__public_func::vformat(locale(), fmt,
                                                  std::move(args));
}
inline wstring vformat(wstring_view fmt, wformat_args args) {
  return __format_details::__public_func::vformat(locale(), fmt,
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
  return __format_details::__public_func::format_to(
      out, locale(), fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, wstring_view fmt,
                          const Args &... args) {
  return __format_details::__public_func::format_to(
      out, locale(), fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, const locale &loc, string_view fmt,
                          const Args &... args) {
  return __format_details::__public_func::format_to(
      out, loc, fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline OutputIt format_to(OutputIt out, const locale &loc, wstring_view fmt,
                          const Args &... args) {
  return __format_details::__public_func::format_to(
      out, loc, fmt, std::forward<Args>(args)...);
}

template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, string_view fmt,
           format_args_t<type_identity_t<OutputIt>, char> args) {
  return __format_details::__public_func::vformat_to(out, locale(), fmt,
                                                     std::move(args));
}
template <class OutputIt>
inline OutputIt
vformat_to(OutputIt out, wstring_view fmt,
           format_args_t<type_identity_t<OutputIt>, wchar_t> args) {
  return __format_details::__public_func::vformat_to(out, locale(), fmt,
                                                     std::move(args));
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
  return __format_details::__public_func::format_to_n(
      out, n, locale(), fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, wstring_view fmt,
            const Args &... args) {
  return __format_details::__public_func::format_to_n(
      out, n, locale(), fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, const locale &loc,
            string_view fmt, const Args &... args) {
  return __format_details::__public_func::format_to_n(
      out, n, loc, fmt, std::forward<Args>(args)...);
}
template <class OutputIt, class... Args>
inline format_to_n_result<OutputIt>
format_to_n(OutputIt out, iter_difference_t<OutputIt> n, const locale &loc,
            wstring_view fmt, const Args &... args) {
  return __format_details::__public_func::format_to_n(
      out, n, loc, fmt, std::forward<Args>(args)...);
}

template <class... Args>
inline size_t formatted_size(string_view fmt, const Args &... args) {
  return __format_details::__public_func::formatted_size(
      locale(), fmt, std::forward<Args>(args)...);
}
template <class... Args>
inline size_t formatted_size(wstring_view fmt, const Args &... args) {
  return __format_details::__public_func::formatted_size(
      locale(), fmt, std::forward<Args>(args)...);
}
template <class... Args>
inline size_t formatted_size(const locale &loc, string_view fmt,
                             const Args &... args) {
  return __format_details::__public_func::formatted_size(
      loc, fmt, std::forward<Args>(args)...);
}
template <class... Args>
inline size_t formatted_size(const locale &loc, wstring_view fmt,
                             const Args &... args) {
  return __format_details::__public_func::formatted_size(
      loc, fmt, std::forward<Args>(args)...);
}
} // namespace std

#undef __THROW_FORMAT_ERROR

#endif // C++20
