// Copyright 2021 siruser agamesok@gmail.com

#include <stdexcept>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(Example, EmptyTest) {
  EXPECT_THROW(example(), std::runtime_error);
}
