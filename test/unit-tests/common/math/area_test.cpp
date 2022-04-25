#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/math.hpp"
#include "serialization_utils.hpp"

TEST(Area, DefaultConstruction)
{
  const cen::iarea area;
  ASSERT_EQ(area.width, 0);
  ASSERT_EQ(area.height, 0);
}

TEST(Area, Construction)
{
  const auto width = 7353;
  const auto height = 8395;
  const cen::iarea area{width, height};

  ASSERT_EQ(area.width, width);
  ASSERT_EQ(area.height, height);
}

TEST(Area, AsI)
{
  const cen::farea source{84.3f, 29.6f};
  const auto result = source.as_i();

  ASSERT_EQ(result.width, static_cast<int>(source.width));
  ASSERT_EQ(result.height, static_cast<int>(source.height));
}

TEST(Area, AsF)
{
  const cen::iarea source{843, 203};
  const auto result = source.as_f();

  ASSERT_EQ(result.width, static_cast<float>(source.width));
  ASSERT_EQ(result.height, static_cast<float>(source.height));
}

TEST(Area, Area)
{
  const cen::iarea iarea{123, 456};
  const cen::farea farea{12.3f, 45.6f};

  ASSERT_EQ(123, iarea.width);
  ASSERT_EQ(456, iarea.height);

  ASSERT_EQ(12.3f, farea.width);
  ASSERT_EQ(45.6f, farea.height);
}

TEST(Area, EqComparisonReflexivity)
{
  const cen::iarea area{234, 12};
  ASSERT_EQ(area, area);
}

TEST(Area, EqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  ASSERT_EQ(first, second);
  ASSERT_EQ(second, first);
}

TEST(Area, EqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
}

TEST(Area, NotEqComparisonSelf)
{
  const cen::iarea area{234, 12};
  ASSERT_FALSE(area != area);
}

TEST(Area, NotEqComparisonSame)
{
  const cen::iarea first{47, 9123};
  const cen::iarea second{first};
  ASSERT_FALSE(first != second);
  ASSERT_FALSE(second != first);
}

TEST(Area, NotEqComparisonDifferent)
{
  const cen::iarea first{1238, 594};
  const cen::iarea second{8882, 123};
  ASSERT_NE(first, second);
  ASSERT_NE(second, first);
}

TEST(Area, StreamOperator)
{
  constexpr cen::iarea ia{123, 456};
  constexpr cen::farea fa{12.3f, 45.6f};
  std::cout << ia << '\n';
  std::cout << fa << '\n';
}

TEST(Area, Cast)
{
  {  // iarea -> farea
    const cen::iarea area{123, 456};
    const auto res = cen::cast<cen::farea>(area);
    ASSERT_EQ(static_cast<float>(area.width), res.width);
    ASSERT_EQ(static_cast<float>(area.height), res.height);
  }

  {  // farea -> iarea
    const cen::farea area{12.3f, 4.56f};
    const auto res = cen::cast<cen::iarea>(area);
    ASSERT_EQ(static_cast<int>(area.width), res.width);
    ASSERT_EQ(static_cast<int>(area.height), res.height);
  }
}

TEST(Area, AreaOf)
{
  const cen::farea area{123, 456};
  ASSERT_FLOAT_EQ(cen::area_of(area), area.width * area.height);
}

TEST(Area, Serialization)
{
  const auto width = 123;
  const auto height = 845;
  serialize_save("area.binary", cen::iarea{width, height});

  const auto other = serialize_create<cen::iarea>("area.binary");
  ASSERT_EQ(width, other.width);
  ASSERT_EQ(height, other.height);
}