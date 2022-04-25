#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "centurion/render.hpp"
#include "centurion/window.hpp"

class RendererHandleTest : public testing::Test {
 protected:
  [[maybe_unused]] static void SetUpTestSuite()
  {
    window = std::make_unique<cen::window>();
    renderer = std::make_unique<cen::renderer>(window->make_renderer());
  }

  [[maybe_unused]] static void TearDownTestSuite()
  {
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::window> window;
  inline static std::unique_ptr<cen::renderer> renderer;
};

TEST_F(RendererHandleTest, RawPointerConstructor)
{
  {  // Null pointer
    cen::renderer_handle handle{nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // Valid pointer
    const cen::renderer_handle handle{renderer->get()};

    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST_F(RendererHandleTest, FromOwningRenderer)
{
  const cen::renderer_handle handle{*renderer};

  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(RendererHandleTest, StreamOperator)
{
  const cen::renderer_handle handle{*renderer};
  std::cout << handle << '\n';
}
