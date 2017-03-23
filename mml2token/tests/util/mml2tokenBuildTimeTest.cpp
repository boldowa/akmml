#include "CppUTest/TestHarness.h"
#include "mml2tokenBuildTime.h"

TEST_GROUP(mml2tokenBuildTime)
{
  mml2tokenBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new mml2tokenBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(mml2tokenBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

