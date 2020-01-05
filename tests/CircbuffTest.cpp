#include "Circbuff.h"

/*
See if new buffer is empty
See if new buffer is not full
Reading a new buffer returns 0 (todo: exception? error?)
Write a value, see if it's not empty
Write a value, read, check if empty.
Write two ints, read them back in the right order
Reading a new buffer, then writing, then reading returns value written
Fill the buffer up, check if it’s full
Fill the buffer up, check if it’s not empty
Fill the buffer up, write one more, check if it’s full
Fill the buffer up, write one more, check if it’s not empty
Fill a buffer up, read one value, check if it’s not full.
Fill buffer up, read all values out. Check if it's empty.
Fill buffer up, write one more. Check if first value written is read.

Can construct with uint8_t, uint16_t uint32_t, float
*/


//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include <cstdlib>

typedef float TestType;

TEST_GROUP(Circbuff)
{
  static const int SIZE=4;
  Circbuff<SIZE, TestType>* circbuff;

  void setup()
  {
    circbuff = new Circbuff<SIZE, TestType>();
  }
  void teardown()
  {
    delete circbuff;
  }
};

TestType random_value();
TestType random_value() {
  return static_cast<TestType>(rand());
}

TEST(Circbuff, NewCBIsEmpty)
{
  CHECK_TRUE(circbuff->is_empty());
}

TEST(Circbuff, NewCBIsNotFull)
{
  CHECK_FALSE(circbuff->is_full());
}

TEST(Circbuff, ReadEmptyCBReturns0)
{
  LONGS_EQUAL(circbuff->read(), 0);
}

TEST(Circbuff, WriteThenSeeIfEmpty)
{
  TestType some_val = random_value();
  circbuff->write(some_val);
  CHECK_FALSE(circbuff->is_empty());
}

TEST(Circbuff, WriteThenSeeIfNotFull)
{
  TestType some_val = random_value();
  circbuff->write(some_val);
  CHECK_FALSE(circbuff->is_full());
}

TEST(Circbuff, WriteThenReadSameVal)
{
  TestType some_val = random_value();
  circbuff->write(some_val);
  LONGS_EQUAL(some_val, circbuff->read());
}

TEST(Circbuff, WriteThenReadThenCheckEmpty)
{
    circbuff->write(random_value());
    circbuff->read();
    CHECK_TRUE(circbuff->is_empty());
}

TEST(Circbuff, WriteTwoIntsReadBackSameOrder)
{
  TestType some_val_A = random_value();
  TestType some_val_B = random_value();
  circbuff->write(some_val_A);
  circbuff->write(some_val_B);
  LONGS_EQUAL(some_val_A, circbuff->read());
  LONGS_EQUAL(some_val_B, circbuff->read());
}

TEST(Circbuff, ReadNewCBThenWriteThenReadBack)
{
  circbuff->read();
  TestType some_val = random_value();
  circbuff->write(some_val);
  LONGS_EQUAL(some_val, circbuff->read());
}

TEST(Circbuff, FillBufferThenSeeIfFull)
{
  for (int i=0;i<SIZE;i++)
    circbuff->write(random_value());
  CHECK_TRUE(circbuff->is_full());
}

TEST(Circbuff, FillBufferThenSeeIfNotEmpty)
{
  for (int i=0;i<SIZE;i++)
    circbuff->write(random_value());
  CHECK_FALSE(circbuff->is_empty());
}

TEST(Circbuff, FillBufferPlusOneThenSeeIfFull)
{
  for (int i=0;i<(SIZE+1);i++)
    circbuff->write(random_value());
  CHECK_TRUE(circbuff->is_full());
}

TEST(Circbuff, FillBufferPlusOneThenSeeIfNotEmpty)
{
  for (int i=0;i<(SIZE+1);i++)
    circbuff->write(random_value());
  CHECK_FALSE(circbuff->is_empty());
}

TEST(Circbuff, FillBufferThenReadThenSeeIfNotFull)
{
  for (int i=0;i<SIZE;i++)
    circbuff->write(random_value());
  circbuff->read();
  CHECK_FALSE(circbuff->is_full());
}

TEST(Circbuff, FillBufferThenReadAllThenSeeIfEmpty)
{
  for (int i=0;i<SIZE;i++)
    circbuff->write(random_value());

  for (int i=0;i<SIZE;i++)
    circbuff->read();

  CHECK_TRUE(circbuff->is_empty());
}

TEST(Circbuff, FillBufferPlusOneThenCheckReadValue)
{
  circbuff->write(random_value());

  TestType second_value_written=random_value();
  circbuff->write(second_value_written);

  for (int i=0; i<(SIZE-1); i++) {
    circbuff->write(random_value());
  }
  LONGS_EQUAL(second_value_written, circbuff->read());
}

TEST(Circbuff, FillBufferPlusOneThenReadSizeThenSeeIfEmpty)
{
  for (int i=0;i<(SIZE+1);i++)
    circbuff->write(random_value());

  for (int i=0;i<SIZE;i++)
    circbuff->read();

  CHECK_TRUE(circbuff->is_empty());
}

