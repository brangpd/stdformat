#pragma once

#if __cplusplus > 201703

#include <concepts>
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>

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
template <class Context, class... Args>
struct format_arg_store; // exposition only

template <class Context = format_context, class... Args>
format_arg_store<Context, Args...> make_format_args(const Args &... args);
template <class... Args>
format_arg_store<wformat_context, Args...>
make_wformat_args(const Args &... args);

} // namespace std

// implementation
namespace std {
class format_error : public runtime_error {
public:
  explicit format_error(const string &what_arg) : runtime_error(what_arg) {}
  explicit format_error(const char *what_arg) : runtime_error(what_arg) {}
};

template <class charT> class basic_format_parse_context {
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
    }
    throw format_error("Mixing of automatic and manual argument indexing.");
  }
  constexpr void check_arg_id(size_t id) {
    if (indexing_ != automatic) {
      if (indexing_ == unknown) {
        indexing_ = manual;
      }
    }
    throw format_error("Mixing of automatic and manual argument indexing.");
  }
};

template <class Context> class basic_format_arg {
private:
  using char_type = typename Context::char_type;

public:
  class handle {
    const void *ptr_;
    void (*format_)(basic_format_parse_context<char_type> &, Context &,
                    const void *);

    template <class T>
    explicit handle(const T &val) noexcept
        : ptr_(val),
          format_([](basic_format_parse_context<char_type> &parse_ctx,
                     Context &format_ctx, const void *ptr) {
            typename Context::template formatter_type<T> f;
            parse_ctx.advance_to(f.parse(parse_ctx));
            format_ctx.advance_to(
                f.format(*static_cast<const T *>(ptr), format_ctx));
          }) {}

    friend class basic_format_arg<Context>;

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
      value; // exposition only

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

  template <class T> explicit basic_format_arg(const T *p) noexcept : value(p) {
    static_assert(is_void_v<T>);
  }

public:
  basic_format_arg() noexcept { assert(!(*this)); }

  explicit operator bool() const noexcept {
    return !holds_alternative<monostate>(value);
  }
};

template <class Context, class... Args>
struct format_arg_store { // exposition only
  array<basic_format_arg<Context>, sizeof...(Args)> args;
};

template <class Context, class... Args>
format_arg_store<Context, Args...> make_format_args(const Args &... args) {
  return {basic_format_arg<Context>(args)...};
}
template <class... Args>
format_arg_store<wformat_context, Args...>
make_wformat_args(const Args &... args) {
  return make_format_args<wformat_context>(args...);
}

template <class Context> class basic_format_args {
private:
  size_t size_;
  const basic_format_arg<Context> *data_;

public:
  basic_format_args() noexcept : size_(), data_() {}

  template <class... Args>
  basic_format_args(const format_arg_store<Context, Args...> &store) noexcept
      : size_(sizeof...(Args)), data_(store.args.data()) {}

  basic_format_arg<Context> get(size_t i) const noexcept {
    return i < size_ ? data_[i] : basic_format_arg<Context>();
  }
};

/** An instance of basic_­format_­context holds formatting state consisting of
 * the formatting arguments and the output iterator.
 * @tparam Out shall model output_­iterator<const charT&>.
 * @tparam charT
 */
template <class Out, class charT> class basic_format_context {
private:
  basic_format_args<basic_format_context> args_;
  Out out_;

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

template <class Formatter>
constexpr bool __is_formatter_v = is_default_constructible_v<Formatter>
    &&is_copy_constructible_v<Formatter> &&is_copy_assignable_v<Formatter>
    &&is_swappable_v<Formatter> &&is_destructible_v<Formatter>;

template <class T, class charT> struct formatter {};

template <> struct formatter<char, char> {
  auto parse(std::basic_format_parse_context<char> pc) {}
  auto format(char t, basic_format_context<char,char>fc) {}
};

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

string vformat(string_view fmt, format_args args) {}
wstring vformat(wstring_view fmt, wformat_args args) {}
string vformat(const locale &loc, string_view fmt, format_args args) {}
wstring vformat(const locale &loc, wstring_view fmt, wformat_args args) {}

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

} // namespace std

#endif
