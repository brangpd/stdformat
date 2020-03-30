#pragma once

#include <gtest/gtest.h>

#include <format>
using namespace std;

#define EXPECT_FORMAT_ERROR(exp) EXPECT_THROW(exp, format_error)

struct FormatTestError : runtime_error {
  FormatTestError(const char *string = "format test error")
      : runtime_error(string) {}
};

struct FormatTest : testing::Test {};
