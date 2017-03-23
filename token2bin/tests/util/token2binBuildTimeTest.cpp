#include "CppUTest/TestHarness.h"
#include "token2binBuildTime.h"

TEST_GROUP(token2binBuildTime)
{
  token2binBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new token2binBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(token2binBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

