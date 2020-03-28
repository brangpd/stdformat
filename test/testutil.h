#pragma once

#include <gtest/gtest.h>
#include <format>
using namespace std;

#define EXPECT_FORMAT_ERROR(exp) EXPECT_THROW(exp, format_error)

struct FormatTest : testing::Test {};
