#include <gtest/gtest.h>

#include "centurion/concurrency.hpp"
#include "core_mocks.hpp"
#include "thread_mocks.hpp"

class ConditionTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(ConditionTest, Constructor)
{
  ASSERT_THROW(cen::condition{}, cen::sdl_error);
}
