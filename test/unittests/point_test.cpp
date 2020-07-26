#include "point.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "log.hpp"

TEST_CASE("point::to_string", "[point]")
{
  const ctn::ipoint ip{123, 456};
  ctn::log::info(ctn::log::category::test, "%s", ctn::to_string(ip).c_str());

  const ctn::fpoint fp{12.3f, 45.6f};
  ctn::log::info(ctn::log::category::test, "%s", ctn::to_string(fp).c_str());

  std::cout << "COUT: " << fp << '\n';
  std::cout << "COUT: " << fp << '\n';
}

TEST_CASE("point::distance", "[point]")
{
  SECTION("Unit x-step")
  {
    const ctn::ipoint a{0, 123};
    const ctn::ipoint b{1, 123};

    CHECK(ctn::distance(a, b) == 1);
    CHECK(ctn::distance(b, a) == 1);
  }

  SECTION("Unit y-step")
  {
    const ctn::ipoint a{42, 0};
    const ctn::ipoint b{42, 1};

    CHECK(ctn::distance(a, b) == 1);
    CHECK(ctn::distance(b, a) == 1);
  }

  SECTION("Non-trivial distance")
  {
    const ctn::fpoint a{189.2f, 86.9f};
    const ctn::fpoint b{66.5f, 36.6f};

    const auto expected =
        std::sqrt(std::abs(a.x() - b.x()) + std::abs(a.y() - b.y()));

    CHECK(ctn::distance(a, b) == expected);
    CHECK(ctn::distance(b, a) == expected);
  }
}

TEST_CASE("point::operator==", "[point]")
{
  SECTION("Self")
  {
    const ctn::ipoint ip{};
    const ctn::fpoint fp{};
    CHECK(ip == ip);
    CHECK(fp == fp);
  }

  SECTION("Not equal")
  {
    SECTION("ipoint")
    {
      const ctn::ipoint fst{839, 902};
      const ctn::ipoint snd{73483, 1289};
      CHECK_FALSE(fst == snd);
      CHECK_FALSE(snd == fst);
    }

    SECTION("fpoint")
    {
      const ctn::fpoint fst{531.5f, 8313.4f};
      const ctn::fpoint snd{34.2f, 173.3f};
      CHECK_FALSE(fst == snd);
      CHECK_FALSE(snd == fst);
    }
  }

  SECTION("Equal")
  {
    SECTION("ipoint")
    {
      const ctn::ipoint fst{883, 922};
      const ctn::ipoint snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("fpoint")
    {
      const ctn::fpoint fst{211.5f, 823.1f};
      const ctn::fpoint snd{fst};
      CHECK(fst == snd);
      CHECK(snd == fst);
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }
  }
}

TEST_CASE("point::operator!=", "[point]")
{
  SECTION("Self")
  {
    const ctn::ipoint ip{};
    const ctn::fpoint fp{};
    CHECK_FALSE(ip != ip);
    CHECK_FALSE(fp != fp);
  }

  SECTION("Not equal")
  {
    SECTION("ipoint")
    {
      const ctn::ipoint fst{1234, 12412421};
      const ctn::ipoint snd{4345, 7712};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }

    SECTION("fpoint")
    {
      const ctn::fpoint fst{8392.5f, 12452.4f};
      const ctn::fpoint snd{5236.2f, 321.3f};
      CHECK(fst != snd);
      CHECK(snd != fst);
    }
  }

  SECTION("Equal")
  {
    SECTION("ipoint")
    {
      const ctn::ipoint fst{883, 922};
      const ctn::ipoint snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }

    SECTION("fpoint")
    {
      const ctn::fpoint fst{211.5f, 823.1f};
      const ctn::fpoint snd{fst};
      CHECK_FALSE(fst != snd);
      CHECK_FALSE(snd != fst);
    }
  }
}

TEST_CASE("point::operator+", "[point]")
{
  SECTION("ipoint")
  {
    const ctn::ipoint fst{738, 912};
    const ctn::ipoint snd{123, 423};

    const auto expectedX = fst.x() + snd.x();
    const auto expectedY = fst.y() + snd.y();

    const auto fstSnd = fst + snd;
    CHECK(fstSnd.x() == expectedX);
    CHECK(fstSnd.y() == expectedY);

    const auto sndFst = snd + fst;
    CHECK(sndFst.x() == expectedX);
    CHECK(sndFst.y() == expectedY);
  }

  SECTION("fpoint")
  {
    const ctn::fpoint fst{62.4f, 381.3f};
    const ctn::fpoint snd{779.3f, 819.3f};

    const auto expectedX = fst.x() + snd.x();
    const auto expectedY = fst.y() + snd.y();

    const auto fstSnd = fst + snd;
    CHECK(fstSnd.x() == expectedX);
    CHECK(fstSnd.y() == expectedY);

    const auto sndFst = snd + fst;
    CHECK(sndFst.x() == expectedX);
    CHECK(sndFst.y() == expectedY);
  }
}

TEST_CASE("point::operator-", "[point]")
{
  const ctn::ipoint fst{673, 123};
  const ctn::ipoint snd{-547, 451};

  CHECK((fst - snd) != (snd - fst));

  SECTION("fst - snd")
  {
    const ctn::ipoint diff = fst - snd;

    CHECK(diff.x() == fst.x() - snd.x());
    CHECK(diff.y() == fst.y() - snd.y());
  }

  SECTION("snd - fst")
  {
    const ctn::ipoint diff = snd - fst;

    CHECK(diff.x() == snd.x() - fst.x());
    CHECK(diff.y() == snd.y() - fst.y());
  }
}

TEST_CASE("Conversions")
{
  SECTION("ipoint -> fpoint")
  {
    const ctn::ipoint from{684, 912};
    const auto to = ctn::cast<ctn::fpoint>(from);

    CHECK(to.x() == static_cast<float>(from.x()));
    CHECK(to.y() == static_cast<float>(from.y()));
  }

  SECTION("fpoint -> ipoint")
  {
    const ctn::fpoint from{58.8f, 123.4f};
    const auto to = ctn::cast<ctn::ipoint>(from);

    CHECK(to.x() == static_cast<int>(std::round(from.x())));
    CHECK(to.y() == static_cast<int>(std::round(from.y())));
  }

  SECTION("ipoint -> const SDL_Point*")
  {
    ctn::ipoint point{843, 9123};

    SECTION("Non-const")
    {
      auto* ptr = static_cast<SDL_Point*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }

    SECTION("Const")
    {
      const auto* ptr = static_cast<const SDL_Point*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }
  }

  SECTION("fpoint -> const SDL_FPoint*")
  {
    ctn::fpoint point{3813.3f, 892.5f};

    SECTION("Non-const")
    {
      auto* ptr = static_cast<SDL_FPoint*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }

    SECTION("Const")
    {
      const auto* ptr = static_cast<const SDL_FPoint*>(point);
      CHECK(point.x() == ptr->x);
      CHECK(point.y() == ptr->y);
    }
  }
}

TEST_CASE("point::get", "[point]")
{
  SECTION("ipoint")
  {
    const ctn::ipoint point{393, 934};
    const auto sdl = point.get();

    CHECK(point.x() == sdl.x);
    CHECK(point.y() == sdl.y);
  }

  SECTION("fpoint")
  {
    const ctn::fpoint point{3923.3f, 7718.1f};
    const auto sdl = point.get();

    CHECK(point.x() == sdl.x);
    CHECK(point.y() == sdl.y);
  }
}

TEST_CASE("point::make_point", "[point]")
{
  SECTION("ipoint")
  {
    const auto empty = ctn::make_point<int>();
    CHECK(empty.x() == 0);
    CHECK(empty.y() == 0);

    const auto x = 8125;
    const auto y = 3784;
    const auto point = ctn::make_point<int>(x, y);
    CHECK(point.x() == x);
    CHECK(point.y() == y);
  }

  SECTION("fpoint")
  {
    const auto empty = ctn::make_point<float>();
    CHECK(empty.x() == 0);
    CHECK(empty.y() == 0);

    const auto x = 735.3f;
    const auto y = 173.4f;
    const auto point = ctn::make_point<float>(x, y);
    CHECK(point.x() == x);
    CHECK(point.y() == y);
  }
}

// TEST_CASE("fpoint::equals", "[fpoint]")
//{
//  const ctn::fpoint point{11.7f, 38.9f};
//  const ctn::fpoint other{point};
//
//  CHECK(point.equals(point));
//  CHECK(point.equals(other));
//  CHECK(other.equals(point));
//}
