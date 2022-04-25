#include <gtest/gtest.h>

#include "centurion/concurrency.hpp"
#include "core_mocks.hpp"
#include "thread_mocks.hpp"

class SemaphoreTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(SemaphoreTest, Constructor)
{
  ASSERT_THROW(cen::semaphore{0}, cen::sdl_error);
}
