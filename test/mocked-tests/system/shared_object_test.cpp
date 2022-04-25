#include <gtest/gtest.h>

#include "centurion/system.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VOID_FUNC(SDL_UnloadObject, void*)
  FAKE_VALUE_FUNC(void*, SDL_LoadObject, const char*)
  FAKE_VALUE_FUNC(void*, SDL_LoadFunction, void*, const char*)
}

class SharedObjectTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_UnloadObject)
    RESET_FAKE(SDL_LoadObject)
    RESET_FAKE(SDL_LoadFunction)
  }

  cen::shared_object object;
};

TEST_F(SharedObjectTest, LoadFunction)
{
  using namespace std::string_literals;
  const auto name = "foo"s;

  auto* ptr [[maybe_unused]] = object.load_function<void(int, float)>(name);

  ASSERT_EQ(1u, SDL_LoadFunction_fake.call_count);
  ASSERT_EQ(name, SDL_LoadFunction_fake.arg1_val);
}
