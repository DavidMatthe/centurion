#include <gtest/gtest.h>

#include "centurion/surface.hpp"

namespace {
inline constexpr auto path = "resources/panda.png";
}  // namespace

TEST(SurfaceHandle, Constructor)
{
  ASSERT_FALSE(cen::surface_handle{nullptr});

  const cen::surface surface{path};
  cen::surface_handle handle{surface.get()};

  ASSERT_TRUE(handle);
}
