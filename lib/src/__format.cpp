#include "__format.h"
#include <codecvt>

namespace std {
namespace __format_details {
size_t __basic_width_counter::width(char32_t cd) {
  if (cd < 0x1100) {
    return 1;
  }
  // following code points pairs are ranges of full width character
  static constexpr int codes[][2] = {
      {0x1100, 0x115f},   {0x2329, 0x232a},   {0x2e80, 0x303e},
      {0x3040, 0xa4cf},   {0xac00, 0xd7a3},   {0xf900, 0xfaff},
      {0xfe10, 0xfe19},   {0xfe30, 0xfe6f},   {0xff00, 0xff60},
      {0xffe0, 0xffe6},   {0x1f300, 0x1f64f}, {0x1f900, 0x1f9ff},
      {0x20000, 0x2fffd}, {0x30000, 0x3fffd},
  };
  for (auto &&[l, r] : codes) {
    if (r >= cd) {
      if (l <= cd) {
        return 2;
      }
      break;
    }
  }
  return 1;
}
size_t __width_counter<char>::width(const basic_string_view<char> &sv,
                                    const locale &loc) {
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
    auto inRes = f.in(mbstate, svp, svpe, fromNext, c32, c32 + buflen, toNext);
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
size_t __width_counter<wchar_t>::width(const basic_string_view<wchar_t> &sv,
                                       const locale &loc) {
  // Since standard library does not provide code converter from wchar_t to
  // char32_t, first convert a wchar_t character to char then convert the char
  // character to char32_t

  // FIXME: deprecated, use char8_t instead of char
  using cvt = codecvt<wchar_t, char, mbstate_t>;
  auto &&f = use_facet<cvt>(loc); // wchat_t to char
  mbstate_t mbstate{};

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
} // namespace __format_details
} // namespace std

// Extern explicit template instantiation.
namespace std {
template struct formatter<char, char>;
template struct formatter<char, wchar_t>;
template struct formatter<wchar_t, wchar_t>;
template struct formatter<char *, char>;
template struct formatter<wchar_t *, wchar_t>;
template struct formatter<const char *, char>;
template struct formatter<const wchar_t *, wchar_t>;
template struct formatter<string, char>;
template struct formatter<wstring, wchar_t>;
template struct formatter<string_view, char>;
template struct formatter<wstring_view, wchar_t>;
template struct formatter<int, char>;
template struct formatter<int, wchar_t>;
template struct formatter<unsigned int, char>;
template struct formatter<unsigned int, wchar_t>;
template struct formatter<long long, char>;
template struct formatter<long long, wchar_t>;
template struct formatter<unsigned long long, char>;
template struct formatter<unsigned long long, wchar_t>;
template struct formatter<float, char>;
template struct formatter<float, wchar_t>;
template struct formatter<double, char>;
template struct formatter<double, wchar_t>;
template struct formatter<long double, char>;
template struct formatter<long double, wchar_t>;
template struct formatter<nullptr_t, char>;
template struct formatter<nullptr_t, wchar_t>;
template struct formatter<void *, char>;
template struct formatter<void *, wchar_t>;
template struct formatter<const void *, char>;
template struct formatter<const void *, wchar_t>;
namespace __format_details {
template class __unicode_buf<char>;
template class __unicode_buf<wchar_t>;
template class __formatter_iterator<char>;
template class __formatter_iterator<wchar_t>;
template class __width_counter_formatter_iterator<char>;
template class __width_counter_formatter_iterator<wchar_t>;
template class __limited_formatter_iterator<__formatter_iterator<char>, char>;
template class __limited_formatter_iterator<__formatter_iterator<wchar_t>,
                                            wchar_t>;
template class __formatter_base<char>;
template class __formatter_base<wchar_t>;
} // namespace __format_details
} // namespace std
