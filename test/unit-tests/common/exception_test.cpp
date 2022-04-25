#include <gtest/gtest.h>

#include <type_traits>

#include "centurion/common.hpp"

static_assert(std::has_virtual_destructor_v<cen::exception>);
static_assert(std::is_default_constructible_v<cen::exception>);
static_assert(std::is_nothrow_move_constructible_v<cen::exception>);
static_assert(std::is_nothrow_destructible_v<cen::exception>);

TEST(Exception, CStringConstructor)
{
  const cen::exception exception{"Foo"};
  ASSERT_STREQ("Foo", exception.what());
}
