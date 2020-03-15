#pragma once

#if __cplusplus > 201703

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

///@{ Standard specializations for library types
template <class Rep, class Period, class CharT>
struct formatter<chrono::duration<Rep, Period>, CharT>;
template <class Duration, class CharT>
struct formatter<chrono::sys_time<Duration>, CharT>;

///@}
} // namespace std

#endif
