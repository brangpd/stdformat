#include "testutil.h"
#include <chrono>
#include <forward_list>
#include <iostream>

struct PerformanceTest : FormatTest {
protected:
  struct TimerGuard {
    chrono::time_point<chrono::system_clock, chrono::nanoseconds> timeBegin,
        timeEnd;
    string name;
    TimerGuard(string name) : name(name) { start(); }
    ~TimerGuard() {
      stop();
      auto duration = nanoseconds();
      cerr << format("[{:4}.{:06}ms] [{}]", duration / 1'000'000,
                     duration % 1'000'000, name)
           << endl;
    }
    void start() { timeBegin = chrono::system_clock::now(); }
    void stop() { timeEnd = chrono::system_clock::now(); }
    size_t nanoseconds() const { return (timeEnd - timeBegin).count(); }
  };
};

TEST_F(PerformanceTest, PerformanceTest_Format_Test) {
  {
    TimerGuard timerGuard("Format");
    for (int i = 0; i < 500'000; ++i) {
      (format("{} {:30b} {:30}", 42, 42, "HELLO WORLD"));
    }
  }
}

TEST_F(PerformanceTest, PerformanceTest_CharInsertionMethod_Test) {
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("Vector: insert 5'000'000 chars");
    vector<char> str;
    for (auto c : chars) {
      str.push_back(c);
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("Vector: insert 5'000'000 chars reserve size");
    vector<char> str;
    str.reserve(5'000'000);
    for (auto c : chars) {
      str.push_back(c);
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("String: insert 5'000'000 chars");
    string str;
    for (auto c : chars) {
      str += c;
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("String: insert 5'000'000 chars reserve size");
    string str;
    str.reserve(5'000'000);
    for (auto c : chars) {
      str += c;
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("String: insert 5'000'000 chars with inserter");
    string str;
    auto it = back_inserter(str);
    for (auto c : chars) {
      *it++ = c;
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard(
        "String: insert 5'000'000 chars with inserter reserve size");
    string str;
    str.reserve(5'000'000);
    auto it = back_inserter(str);
    for (auto c : chars) {
      *it++ = c;
    }
  }
  {
    string chars(5'000'000, 'c');
    TimerGuard timerGuard("Forward list: insert 5'000'000 chars");
    forward_list<char> forwardList;
    auto it = forwardList.before_begin();
    for (auto c : chars) {
      it = forwardList.insert_after(it, c);
    }
  }
  {
    string chars(1'000, 'c');
    TimerGuard timerGuard(
        "Insert new string to vector string first and copy to result");
    vector<string> strings;
    for (int i = 0; i < 5'000; ++i) {
      strings.push_back(chars);
    }
    string result;
    for (auto &str : strings) {
      result += std::move(str);
    }
  }
  {
    string chars(1'000, 'c');
    TimerGuard timerGuard(
        "Insert new string to list string first and copy to result");
    forward_list<string> strings;
    auto it = strings.before_begin();
    for (int i = 0; i < 5'000; ++i) {
      it = strings.insert_after(it, chars);
    }
    string result;
    for (auto &str : strings) {
      result += std::move(str);
    }
  }
  {
    string chars(1'000, 'c');
    TimerGuard timerGuard("Insert new string to result string directly");
    string result;
    for (int i = 0; i < 5'000; ++i) {
      result += chars;
    }
  }
  {
    string chars(1'000, 'c');
    forward_list<string> strings(5'000, chars);
    TimerGuard timerGuard("String: string concat from list move string");
    string result;
    for (auto &str : strings) {
      result += std::move(str);
    }
  }
  {
    string chars(1'000, 'c');
    vector<string> strings(5'000, chars);
    TimerGuard timerGuard("String: string concat from string move string");
    string result;
    for (auto &str : strings) {
      result += std::move(str);
    }
  }
  {
    string chars(1'000, 'c');
    vector<string> strings(5'000, chars);
    TimerGuard timerGuard("String: string concat from string copy string");
    string result;
    for (auto &str : strings) {
      result += str;
    }
  }
  {
    string chars(1'000, 'c');
    forward_list<string> strings(5'000, chars);
    TimerGuard timerGuard(
        "String: string concat from list reserve size copy chars");
    string result;
    result.reserve(5'000'000);
    for (auto &str : strings) {
      for (auto c : str) {
        result += c;
      }
    }
  }
  {
    string chars(1'000, 'c');
    forward_list<string> strings(5'000, chars);
    TimerGuard timerGuard(
        "String: string concat from list reserve size copy string view");
    string result;
    result.reserve(5'000'000);
    for (auto &str : strings) {
      result += string_view(str.begin(), str.end());
    }
  }
  {
    string chars(1'000, 'c');
    forward_list<string> strings(5'000, chars);
    TimerGuard timerGuard("String: string concat reserve size move string");
    string result;
    result.reserve(5'000'000);
    for (auto &str : strings) {
      result += std::move(str);
    }
  }
  {
    vector<char> chars(1'000, 'c');
    vector<vector<char>> strings(5'000, chars);
    TimerGuard timerGuard(
        "String: string concat from vector char copy string view");
    string result;
    for (auto &str : strings) {
      result += string_view(str.begin(), str.end());
    }
  }
  {
    forward_list<char> chars(1'000, 'c');
    forward_list<forward_list<char>> strings(5'000, chars);
    TimerGuard timerGuard("Forward list: string concat");
    string result;
    for (auto &str : strings) {
      for (auto c : str) {
        result += c;
      }
    }
  }
  {
    forward_list<char> chars(1'000, 'c');
    forward_list<forward_list<char>> strings(5'000, chars);
    TimerGuard timerGuard("Forward list: string concat reserve size");
    string result;
    result.reserve(5'000'000);
    for (auto &str : strings) {
      for (auto c : str) {
        result += c;
      }
    }
  }
}
