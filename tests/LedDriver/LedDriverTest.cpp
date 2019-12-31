#include "LedDriver.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(LedDriver)
{
  LedDriver* ledDriver;

  void setup()
  {
    ledDriver = new LedDriver();
  }
  void teardown()
  {
    delete ledDriver;
  }
};

TEST(LedDriver, Create)
{
  FAIL("Start here");
}

