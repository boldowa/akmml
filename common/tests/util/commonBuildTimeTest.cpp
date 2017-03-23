#include "CppUTest/TestHarness.h"
#include "commonBuildTime.h"

TEST_GROUP(commonBuildTime)
{
  commonBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new commonBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(commonBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

