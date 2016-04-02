//===--- strtoint_tests.cpp -------------------------------------*- C++ -*-===//
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
/// Unit tests for strto<int> and related.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/strto.h"
#include <boost/test/unit_test.hpp>
#include <stdint.h>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(StoLongLongTest) {
  BOOST_TEST(strto<int64_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<int64_t>("123", strlen("123")) == 123);
  BOOST_TEST(strto<int64_t>("-123", strlen("-123")) == -123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  int64_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "1234567890";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890LL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "9223372036854775807";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 9223372036854775807LL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "9223372036854775808";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 9223372036854775807LL);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-9223372036854775808";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == (-9223372036854775807LL - 1));
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "-9223372036854775809";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == (-9223372036854775807LL - 1));
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "1234567890A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890LL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 10);
}


BOOST_AUTO_TEST_CASE(StoULongLongTest) {
  BOOST_TEST(strto<uint64_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<uint64_t>("123", strlen("123")) == 123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  uint64_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "1234567890";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890ULL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "9223372036854775807";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 9223372036854775807ULL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "9223372036854775808";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 9223372036854775808ULL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "18446744073709551615";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 18446744073709551615ULL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "18446744073709551616";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 18446744073709551615ULL);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "1234567890A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint64_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890LL);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 10);

  data = "-1234567890";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  // VS2015 returns some huge value
//   value = strto<uint64_t>(data, len, &ptr, 10, &status);
//   BOOST_TEST(value == 0);
//   BOOST_TEST(status == Failure);
//    BOOST_TEST(ptr == data);
}


BOOST_AUTO_TEST_CASE(StoIntTest) {
  BOOST_TEST(strto<int32_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<int32_t>("123", strlen("123")) == 123);
  BOOST_TEST(strto<int32_t>("-123", strlen("-123")) == -123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  int32_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "1234567890";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "2147483647";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 2147483647);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "2147483648";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 2147483647);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-2147483648";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == INT32_MIN);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "-2147483649";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == INT32_MIN);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "1234567890A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 10);
}


BOOST_AUTO_TEST_CASE(StoUIntTest) {
  BOOST_TEST(strto<uint32_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<uint32_t>("123", strlen("123")) == 123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  uint32_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "1234567890";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "2147483647";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 2147483647);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "2147483648";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 2147483648);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "4294967295";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == UINT32_MAX);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "4294967296";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == UINT32_MAX);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "1234567890A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint32_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 1234567890);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 10);
}


BOOST_AUTO_TEST_CASE(StoShortTest) {
  BOOST_TEST(strto<int16_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<int16_t>("123", strlen("123")) == 123);
  BOOST_TEST(strto<int16_t>("-123", strlen("-123")) == -123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  int16_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "12345";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 12345);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "32767";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 32767);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "32768";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 32767);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-32768";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == INT16_MIN);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "-32769";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == INT16_MIN);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "12345A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 12345);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 5);
}


BOOST_AUTO_TEST_CASE(StoUShortTest) {
  BOOST_TEST(strto<uint16_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<uint16_t>("123", strlen("123")) == 123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  uint16_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "12345";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 12345);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "32767";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 32767);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "32768";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 32768);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "65535";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == UINT16_MAX);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "65536";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == UINT16_MAX);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "12345A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint16_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 12345);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 5);
}


BOOST_AUTO_TEST_CASE(StoCharTest) {
  BOOST_TEST(strto<int8_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<int8_t>("123", strlen("123")) == 123);
  BOOST_TEST(strto<int8_t>("-123", strlen("-123")) == -123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  int8_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "127";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 127);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "128";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == 127);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-128";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == INT8_MIN);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "-129";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == INT8_MIN);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "123A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<int8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == 123);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 3);
}


BOOST_AUTO_TEST_CASE(StoUCharTest) {
  BOOST_TEST(strto<uint8_t>("0", strlen("0")) == 0);
  BOOST_TEST(strto<uint8_t>("123", strlen("123")) == 123);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  uint8_t value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "127";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 127);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "128";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == 128);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "255";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == UINT8_MAX);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "256";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == UINT8_MAX);
  BOOST_TEST(status == IntOverflow);
  BOOST_TEST(ptr == data + len);

  data = "123A";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<uint8_t>(data, len, &ptr, 10, &status);
  BOOST_TEST(int(value) == 123);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 3);
}

