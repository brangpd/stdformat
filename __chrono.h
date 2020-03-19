#pragma once

#if __cplusplus > 201703

#include <format>

namespace std {

// duration
namespace chrono {
using days = duration<int32_t, ratio<86400>>;
using weeks = duration<int32_t, ratio<604800>>;
using months = duration<int32_t, ratio<2629746>>;
using years = duration<int32_t, ratio<31556952>>;

template <class Duration>
using sys_time = chrono::time_point<chrono::system_clock, Duration>;
using sys_seconds = sys_time<chrono::seconds>;
using sys_days = sys_time<chrono::days>;
} // namespace chrono

namespace __format_details {
template <class CharT>
struct __chrono_formatter_base : __formatter_base<CharT> {
private:
  enum class conversion_specifier {
    none,
    percent_literal,
    n,
    t,
    H,
    OH,
    I,
    OI,
    M,
    OM,
    S,
    OS,
    p,
    R,
    T,
    r,
    X,
    EX,
    C,
    EC,
    y,
    Oy,
    Ey,
    Y,
    EY,
    b,
    h,
    B,
    m,
    Om,
    d,
    Od,
    e,
    Oe,
    a,
    A,
    u,
    Ou,
    w,
    Ow,
    g,
    G,
    V,
    OV,
    j,
    U,
    OU,
    W,
    OW,
    D,
    F,
    x,
    Ex,
    c,
    Ec,
    z,
    Ez,
    Oz,
    Z,
  };
  conversion_specifier conversion_specifier_;

  auto __parse_chrono_spec(auto &it) {
    conversion_specifier_ = conversion_specifier::none;
    if (*it != '%') {
      return;
    }
    ++it;
    if (*it == '%') {
      conversion_specifier_ = conversion_specifier::percent_literal;
      return;
    }
#define CASE_OF_SPECIFIER(specifier)                                           \
  if constexpr (size(#specifier) == 2) {                                       \
    if (#specifier[0] == *it) {                                                \
      conversion_specifier_ = conversion_specifier::specifier;                 \
    }                                                                          \
  } else if constexpr (size(#specifier) == 3) {                                \
    if (#specifier[0] == *it && #specifier[1] == *(it + 1)) {                  \
      conversion_specifier_ = conversion_specifier::specifier;                 \
    }                                                                          \
  }

    CASE_OF_SPECIFIER(n);
    CASE_OF_SPECIFIER(t);
    CASE_OF_SPECIFIER(H);
    CASE_OF_SPECIFIER(OH);
    CASE_OF_SPECIFIER(I);
    CASE_OF_SPECIFIER(OI);
    CASE_OF_SPECIFIER(M);
    CASE_OF_SPECIFIER(OM);

#undef CASE_OF_SPECIFIER
  }

  [[noreturn]] void __throw_invalid_specifier() {
#ifdef __cpp_exceptions
    throw format_error("invalid specifier");
#else
    terminate();
#endif
  }

public:
  auto parse(auto &pc) {
    auto it = __formatter_base<CharT>::parse(pc);
    __parse_chrono_spec(it);
    return it;
  }

  auto format(auto &&t, auto &fc) {
    return __formatter_base<CharT>::format(t, fc);
  }
};
} // namespace __format_details

///@{ Standard specializations for library types
template <class Rep, class Period, class CharT>
struct formatter<chrono::duration<Rep, Period>, CharT>
    : __format_details::__chrono_formatter_base<CharT> {};
template <class Duration, class CharT>
struct formatter<chrono::sys_time<Duration>, CharT>
    : __format_details::__chrono_formatter_base<CharT> {};
///@}
} // namespace std

#endif
