#pragma once

#if __cplusplus >= 201703

// The floating point to_chars implementations is missing in current libstdc++
// library. Exclude this if they are implemented.
namespace std {
extern to_chars_result to_chars(char *first, char *last, float value);
extern to_chars_result to_chars(char *first, char *last, double value);
extern to_chars_result to_chars(char *first, char *last, long double value);
extern to_chars_result to_chars(char *first, char *last, float value,
                                chars_format fmt);
extern to_chars_result to_chars(char *first, char *last, double value,
                                chars_format fmt);
extern to_chars_result to_chars(char *first, char *last, long double value,
                                chars_format fmt);
extern to_chars_result to_chars(char *first, char *last, float value,
                                chars_format fmt, int precision);
extern to_chars_result to_chars(char *first, char *last, double value,
                                chars_format fmt, int precision);
extern to_chars_result to_chars(char *first, char *last, long double value,
                                chars_format fmt, int precision);
} // namespace std

#endif
