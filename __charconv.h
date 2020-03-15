#pragma once

#if __cplusplus >= 201703

// The current libstdc++ library misses floating point to_chars implementations.
namespace std {
struct to_chars_result;
enum class chars_format;
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
