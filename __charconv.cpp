#include <charconv>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

namespace {
template <class T>
string __c_floating_format_string(char format, int precision) {
  string res = "%";
  if (precision) {
    res += to_string(precision);
  }
  if constexpr (is_same_v<decay_t<T>, long double>) {
    res += 'L';
  }
  if (format) {
    res += format;
  }
  return res;
}

to_chars_result __to_chars(char *first, char *last, auto value);
to_chars_result __to_chars(char *first, char *last, auto value,
                           chars_format fmt);
to_chars_result __to_chars(char *first, char *last, auto value,
                           chars_format fmt, int precision);

to_chars_result __to_chars(char *first, char *last, auto value) {
  auto fmtf = __c_floating_format_string<decltype(value)>('f', 0);
  auto fmte = __c_floating_format_string<decltype(value)>('e', 0);
  to_chars_result res;
  // TODO: choose %f or %e in a more efficient way
  auto maxlen = last - first;
  auto buff = (char *)alloca(maxlen);
  auto bufe = (char *)alloca(maxlen);
  auto lenf = snprintf(buff, maxlen, fmtf.data(), value);
  auto lene = snprintf(bufe, maxlen, fmte.data(), value);
  decltype(buff) buf;
  decltype(lenf) len;
  if (lenf > lene) {
    len = lene;
    buf = bufe;
  } else {
    len = lenf;
    buf = buff;
  }
  if (len > maxlen) {
    res.ptr = last;
    res.ec = errc::value_too_large;
  } else {
    res.ptr = first + len;
    res.ec = errc();
    memcpy(first, buf, len);
  }
  return res;
}
to_chars_result __to_chars(char *first, char *last, auto value,
                           chars_format fmt) {
  return __to_chars(first, last, value, fmt, 0);
}
to_chars_result __to_chars(char *first, char *last, auto value,
                           chars_format fmt, int precision) {
  to_chars_result res;
  char format;
  switch (fmt) {
  case chars_format::scientific:
    format = 'e';
    break;
  case chars_format::fixed:
    format = 'f';
    break;
  case chars_format::hex:
    format = 'a';
    break;
  case chars_format::general:
    format = 'g';
    break;
  }
  auto formatString =
      __c_floating_format_string<decltype(value)>(format, precision);
  auto maxlen = last - first;
  auto len = snprintf(first, maxlen, formatString.data(), value);
  if (len > maxlen) {
    res.ptr = last;
    res.ec = errc::value_too_large;
  } else {
    res.ptr = first + len;
    res.ec = errc();
  }
  return res;
}
} // namespace

namespace std {
to_chars_result to_chars(char *first, char *last, float value) {
  return __to_chars(first, last, value);
}
to_chars_result to_chars(char *first, char *last, double value) {
  return __to_chars(first, last, value);
}
to_chars_result to_chars(char *first, char *last, long double value) {
  return __to_chars(first, last, value);
}
to_chars_result to_chars(char *first, char *last, float value,
                         chars_format fmt) {
  return __to_chars(first, last, value, fmt);
}
to_chars_result to_chars(char *first, char *last, double value,
                         chars_format fmt) {
  return __to_chars(first, last, value, fmt);
}
to_chars_result to_chars(char *first, char *last, long double value,
                         chars_format fmt) {
  return __to_chars(first, last, value, fmt);
}
to_chars_result to_chars(char *first, char *last, float value, chars_format fmt,
                         int precision) {
  return __to_chars(first, last, value, fmt, precision);
}
to_chars_result to_chars(char *first, char *last, double value,
                         chars_format fmt, int precision) {
  return __to_chars(first, last, value, fmt, precision);
}
to_chars_result to_chars(char *first, char *last, long double value,
                         chars_format fmt, int precision) {
  return __to_chars(first, last, value, fmt, precision);
}
} // namespace std
