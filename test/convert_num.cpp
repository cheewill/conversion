#include "numbers.h"
#include <boost/test/unit_test.hpp>
#include <memory>

using namespace conversion;


BOOST_AUTO_TEST_CASE(SimpleSignedCharTest) {
  signed char x = 120;
  signed char y = 111;
  int status = 0;

  y = convert_to<signed char>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 120);

  y = 111;
  y = convert_to<signed char>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 120);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleSignedShortTest) {
  short x = 12000;
  short y = 111;
  int status = 0;

  y = convert_to<short>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000);

  y = 111;
  y = convert_to<short>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleSignedIntTest) {
  int x = 120000;
  int y = 111;
  int status = 0;

  y = convert_to<int>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 120000);

  y = 111;
  y = convert_to<int>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 120000);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleSignedLongTest) {
  long x = 12000000L;
  long y = 111;
  int status = 0;

  y = convert_to<long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000000L);

  y = 111;
  y = convert_to<long>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000000L);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleSignedLongLongTest) {
  long long x = 12000000LL;
  long long y = 111;
  int status = 0;

  y = convert_to<long long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000000LL);

  y = 111;
  y = convert_to<long long>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000000LL);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleUnsignedCharTest) {
  unsigned char x = 120;
  unsigned char y = 111;
  int status = 0;

  y = convert_to<unsigned char>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 120);

  y = 111;
  y = convert_to<unsigned char>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 120);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleUnsignedShortTest) {
  unsigned short x = 12000;
  unsigned short y = 111;
  int status = 0;

  y = convert_to<unsigned short>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000);

  y = 111;
  y = convert_to<unsigned short>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleUnsignedIntTest) {
  unsigned int x = 120000;
  unsigned int y = 111;
  int status = 0;

  y = convert_to<unsigned int>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 120000);

  y = 111;
  y = convert_to<unsigned int>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 120000);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleUnsignedLongTest) {
  unsigned long x = 12000000UL;
  unsigned long y = 111;
  int status = 0;

  y = convert_to<unsigned long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000000UL);

  y = 111;
  y = convert_to<unsigned long>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000000UL);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleUnsignedLongLongTest) {
  unsigned long long x = 12000000ULL;
  unsigned long long y = 111;
  int status = 0;

  y = convert_to<unsigned long long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12000000ULL);

  y = 111;
  y = convert_to<unsigned long long>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12000000ULL);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleFloatTest) {
  float x = 12.13F;
  float y = 111;
  int status = 0;

  y = convert_to<float>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12.13F);

  y = 111;
  y = convert_to<float>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12.13F);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleDoubleTest) {
  double x = 12.13;
  double y = 111;
  int status = 0;

  y = convert_to<double>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12.13);

  y = 111;
  y = convert_to<double>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12.13);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(SimpleLongDoubleTest) {
  long double x = 12.13L;
  long double y = 111;
  int status = 0;

  y = convert_to<long double>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12.13L);

  y = 111;
  y = convert_to<long double>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12.13L);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(WideningSignedCharTest) {
  signed char x = 120;
  int status = 0;

  short y1 = 111;
  y1 = convert_to<short>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y1, 120);

  y1 = 111;
  y1 = convert_to<short>(x, &status);
  BOOST_REQUIRE_EQUAL(y1, 120);
  BOOST_REQUIRE_EQUAL(status, OK);

  int y2 = 111;
  y2 = convert_to<int>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y2, 120);

  y2 = 111;
  y2 = convert_to<int>(x, &status);
  BOOST_REQUIRE_EQUAL(y2, 120);
  BOOST_REQUIRE_EQUAL(status, OK);

  long y3 = 111;
  y3 = convert_to<long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y3, 120);

  y3 = 111;
  y3 = convert_to<long>(x, &status);
  BOOST_REQUIRE_EQUAL(y3, 120);
  BOOST_REQUIRE_EQUAL(status, OK);

  long long y4 = 111;
  y4 = convert_to<long long>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y4, 120);

  y4 = 111;
  y4 = convert_to<long long>(x, &status);
  BOOST_REQUIRE_EQUAL(y4, 120);
  BOOST_REQUIRE_EQUAL(status, OK);
}


BOOST_AUTO_TEST_CASE(NarrowingIntTest1) {
  signed char y = 111;
  int status = 0;

  short x1 = 120;
  y = convert_to<signed char>(x1, nullptr);
  BOOST_REQUIRE_EQUAL(y, 120);

  y = 111;
  y = convert_to<signed char>(x1, &status);
  BOOST_REQUIRE_EQUAL(y, 120);
  BOOST_REQUIRE_EQUAL(status, OK);

  x1 = 127;
  y = convert_to<signed char>(x1, &status);
  BOOST_REQUIRE_EQUAL(y, 127);
  BOOST_REQUIRE_EQUAL(status, OK);

  x1 = 128;
  y = convert_to<signed char>(x1, &status);
  BOOST_REQUIRE_EQUAL(y, 127);
  BOOST_REQUIRE_EQUAL(status, IntOverflow);

  x1 = 0x7FFF;
  status = OK;
  y = convert_to<signed char>(x1, &status);
  BOOST_REQUIRE_EQUAL(y, 127);
  BOOST_REQUIRE_EQUAL(status, IntOverflow);
}


BOOST_AUTO_TEST_CASE(NarrowingFloatTest) {
  double x = 12.13;
  float y = 111;
  int status = 0;

  y = convert_to<float>(x, nullptr);
  BOOST_REQUIRE_EQUAL(y, 12.13F);

  y = 111;
  y = convert_to<float>(x, &status);
  BOOST_REQUIRE_EQUAL(y, 12.13F);
  BOOST_REQUIRE_EQUAL(status, OK);
}
