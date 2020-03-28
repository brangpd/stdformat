#include "__format.h"

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
template class __width_counter<char>;
template class __width_counter<wchar_t>;
template class __unicode_buf<char>;
template class __unicode_buf<wchar_t>;
template class __formatter_iterator_impl<char>;
template class __formatter_iterator_impl<wchar_t>;
template class __formatter_iterator<char>;
template class __formatter_iterator<wchar_t>;
template class __width_counter_formatter_iterator<char>;
template class __width_counter_formatter_iterator<wchar_t>;
template class __counter_formatter_iterator<char>;
template class __counter_formatter_iterator<wchar_t>;
template class __limited_formatter_iterator<__formatter_iterator<char>,
                                                   char>;
template class __limited_formatter_iterator<
    __formatter_iterator<wchar_t>, wchar_t>;
template class __formatter_base<char>;
template class __formatter_base<wchar_t>;
} // namespace __format_details
} // namespace std
