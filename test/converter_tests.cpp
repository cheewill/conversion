//===--- converter_tests.cpp ------------------------------------*- C++ -*-===//
//
// Copyright(c) 2016, Serge Pavlov.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// - Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Unit tests for conversion::convert_int.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


template<typename IntType>
void do_integer_tests() {
  IntType value;
  Status st;

  value = 100;
  st = convert_int(value, "", 0, 10);

  BOOST_REQUIRE_EQUAL(st, NaN);
  BOOST_REQUIRE_EQUAL(value, 0);

  value = 100;
  st = convert_int(value, "0", 1, 10);

  BOOST_REQUIRE_EQUAL(st, OK);
  BOOST_REQUIRE_EQUAL(value, 0);

  value = 100;
  st = convert_int(value, "123", 3, 10);

  BOOST_REQUIRE_EQUAL(st, OK);
  BOOST_REQUIRE_EQUAL(value, 123);

  if (sizeof(IntType) == 1) {
    value = 100;
    st = convert_int(value, "127", strlen("127"), 10);

    BOOST_REQUIRE_EQUAL(st, OK);
    BOOST_REQUIRE_EQUAL(value, 127);

    if (std::numeric_limits<IntType>::is_signed) {
      value = 100;
      st = convert_int(value, "128", strlen("128"), 10);
      BOOST_REQUIRE_EQUAL(st, NegativeLimit);
      value = 100;
      st = convert_int(value, "129", strlen("129"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    } else {
      value = 100;
      st = convert_int(value, "255", strlen("255"), 10);
      BOOST_REQUIRE_EQUAL(st, OK);
      BOOST_REQUIRE_EQUAL(value, 255);

      value = 100;
      st = convert_int(value, "256", strlen("256"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    }
  }
  else if (sizeof(IntType) == 2) {
    value = 100;
    st = convert_int(value, "32767", strlen("32767"), 10);

    BOOST_REQUIRE_EQUAL(st, OK);
    BOOST_REQUIRE_EQUAL(value, 32767);

    if (std::numeric_limits<IntType>::is_signed) {
      value = 100;
      st = convert_int(value, "32768", strlen("32768"), 10);
      BOOST_REQUIRE_EQUAL(st, NegativeLimit);
      value = 100;
      st = convert_int(value, "32769", strlen("32769"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    } else {
      value = 100;
      st = convert_int(value, "65535", strlen("65535"), 10);
      BOOST_REQUIRE_EQUAL(st, OK);
      BOOST_REQUIRE_EQUAL(value, 65535);

      value = 100;
      st = convert_int(value, "65536", strlen("65536"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    }
  }
  else if (sizeof(IntType) == 4) {
    value = 100;
    st = convert_int(value, "2147483647", strlen("2147483647"), 10);

    BOOST_REQUIRE_EQUAL(st, OK);
    BOOST_REQUIRE_EQUAL(value, 2147483647);

    if (std::numeric_limits<IntType>::is_signed) {
      value = 100;
      st = convert_int(value, "2147483648", strlen("2147483648"), 10);
      BOOST_REQUIRE_EQUAL(st, NegativeLimit);
      value = 100;
      st = convert_int(value, "2147483649", strlen("2147483649"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    } else {
      value = 100;
      st = convert_int(value, "4294967295", strlen("4294967295"), 10);
      BOOST_REQUIRE_EQUAL(st, OK);
      BOOST_REQUIRE_EQUAL(value, 4294967295);

      value = 100;
      st = convert_int(value, "4294967296", strlen("4294967296"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    }
  }
  else if (sizeof(IntType) == 8) {
    value = 100;
    st = convert_int(value, "9223372036854775807", strlen("9223372036854775807"), 10);

    BOOST_REQUIRE_EQUAL(st, OK);
    BOOST_REQUIRE_EQUAL(value, 9223372036854775807);

    if (std::numeric_limits<IntType>::is_signed) {
      value = 100;
      st = convert_int(value, "9223372036854775808", strlen("9223372036854775808"), 10);
      BOOST_REQUIRE_EQUAL(st, NegativeLimit);
      value = 100;
      st = convert_int(value, "9223372036854775809", strlen("9223372036854775809"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    } else {
      value = 100;
      st = convert_int(value, "18446744073709551615", strlen("18446744073709551615"), 10);
      BOOST_REQUIRE_EQUAL(st, OK);
      BOOST_REQUIRE_EQUAL(value, 18446744073709551615ULL);

      value = 100;
      st = convert_int(value, "18446744073709551616", strlen("18446744073709551616"), 10);
      BOOST_REQUIRE_EQUAL(st, IntOverflow);
    }
  }
  else {
    assert(0); // Unknown integer size
  }
}

BOOST_AUTO_TEST_CASE(ConvertCharTests) {
  do_integer_tests<char>();
}

BOOST_AUTO_TEST_CASE(ConvertSignedCharTests) {
  do_integer_tests<signed char>();
}

BOOST_AUTO_TEST_CASE(ConvertUnsignedCharTests) {
  do_integer_tests<unsigned char>();
}

BOOST_AUTO_TEST_CASE(ConvertShortTests) {
  do_integer_tests<short>();
}

BOOST_AUTO_TEST_CASE(ConvertUnsignedShortTests) {
  do_integer_tests<unsigned short>();
}

BOOST_AUTO_TEST_CASE(ConvertIntTests) {
  do_integer_tests<int>();
}

BOOST_AUTO_TEST_CASE(ConvertUnsignedIntTests) {
  do_integer_tests<unsigned int>();
}

BOOST_AUTO_TEST_CASE(ConvertLongTests) {
  do_integer_tests<long>();
}

BOOST_AUTO_TEST_CASE(ConvertUnsignedLongTests) {
  do_integer_tests<unsigned long>();
}

BOOST_AUTO_TEST_CASE(ConvertLongLongTests) {
  do_integer_tests<long long>();
}

BOOST_AUTO_TEST_CASE(ConvertUnsignedLongLongTests) {
  do_integer_tests<unsigned long long>();
}


BOOST_AUTO_TEST_CASE(ConvertDoubleTest) {
  double value;
  Status st;

  value = 100;
  st = convert_int(value, "", 0, 10);

  BOOST_REQUIRE_EQUAL(st, NaN);
  BOOST_TEST(value == 0);

  value = 100;
  st = convert_int(value, "0", 1, 10);

  BOOST_REQUIRE_EQUAL(st, OK);
  BOOST_TEST(value == 0);

  value = 100;
  st = convert_int(value, "123", 3, 10);

  BOOST_REQUIRE_EQUAL(st, OK);
  BOOST_TEST(value == 123);
}


BOOST_AUTO_TEST_CASE(ConvertErrorTest) {
  int value;
  Status st;

  value = 100;
  st = convert_int(value, "", 0, 10);
  BOOST_REQUIRE_EQUAL(st, NaN);
  BOOST_TEST(value == 0);

  value = 100;
  st = convert_int(value, "123A", 4, 10);

  BOOST_REQUIRE_EQUAL(st, NaN);
}
