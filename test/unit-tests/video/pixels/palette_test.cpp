#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/color.hpp"
#include "centurion/pixels.hpp"

TEST(Palette, Constructor)
{
  ASSERT_THROW(cen::palette{0}, cen::exception);
  ASSERT_THROW(cen::palette{-1}, cen::exception);
  ASSERT_NO_THROW(cen::palette{1});
}

TEST(Palette, SetColor)
{
  cen::palette palette{4};

  ASSERT_TRUE(palette.set_color(0, cen::colors::coral));
  ASSERT_EQ(cen::colors::coral, palette.at(0));

  ASSERT_TRUE(palette.set_color(1, cen::colors::cyan));
  ASSERT_EQ(cen::colors::cyan, palette.at(1));

  ASSERT_TRUE(palette.set_color(2, cen::colors::magenta));
  ASSERT_EQ(cen::colors::magenta, palette.at(2));

  ASSERT_TRUE(palette.set_color(3, cen::colors::red));
  ASSERT_EQ(cen::colors::red, palette.at(3));
}

TEST(Palette, Iteration)
{
  {
    cen::palette single{1};
    const auto count = single.end() - single.begin();

    ASSERT_EQ(1, count);
  }

  {
    cen::palette palette{4};
    const auto count = palette.end() - palette.begin();

    ASSERT_EQ(4, count);
  }
}

TEST(Palette, GetColor)
{
  cen::palette palette{4};
  ASSERT_NO_THROW(palette.at(0));
  ASSERT_NO_THROW(palette.at(3));
  ASSERT_THROW(palette.at(-1), cen::exception);
  ASSERT_THROW(palette.at(4), cen::exception);
}

TEST(Palette, GetSize)
{
  const cen::palette palette{7};
  ASSERT_EQ(7, palette.size());
}

TEST(Palette, StreamOperator)
{
  const cen::palette palette{7};
  std::cout << palette << '\n';
}