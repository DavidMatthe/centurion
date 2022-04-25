#include <gtest/gtest.h>

#include <iostream>  // clog

#include "centurion/detail/stdlib.hpp"

TEST(AddressOf, Correctness)
{
  {  // Non-null pointer
    int i = 42;
    const auto str = cen::detail::address_of(&i);

    ASSERT_FALSE(str.empty());

#if CENTURION_HAS_FEATURE_CPP20
    ASSERT_TRUE(str.starts_with("0x"));
#endif  // CENTURION_HAS_FEATURE_CPP20

    std::cout << "detail::address_of output: " << str << '\n';
  }

  {  // Null pointer
    int* i{};
    ASSERT_NO_THROW(cen::detail::address_of(i));

    const auto str = cen::detail::address_of(i);
    ASSERT_TRUE(str.empty());
  }
}
