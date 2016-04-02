//===--- strtofloat_tests.cpp -----------------------------------*- C++ -*-===//
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
/// Unit tests for strto<float> and related.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/strto.h"
#include <boost/test/unit_test.hpp>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(StoFloatTest, *boost::unit_test::tolerance(0.0000001)) {
  BOOST_TEST(strto<float>("0", strlen("0")) == 0);
  BOOST_TEST(strto<float>("11.2", strlen("11.2")) == 11.2F);
  BOOST_TEST(strto<float>("-611.213", strlen("-611.213")) == -611.213F);
  BOOST_TEST(strto<float>("611.E12", strlen("611.E12")) == 611.E12F);
  BOOST_TEST(strto<float>("611.E-12", strlen("611.E-12")) == 611.E-12F);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  float value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == .0F);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.F);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456F);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456e+06";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456e+06F);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == NaN);
  BOOST_TEST(ptr == data);

  data = "123.456e+40";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value > 0);
  BOOST_TEST(value == std::numeric_limits<float>::infinity());
  BOOST_TEST(status == DoubleOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-123.456e+40";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value < 0);
  BOOST_TEST(value == -std::numeric_limits<float>::infinity());
  BOOST_TEST(status == DoubleOverflow);
  BOOST_TEST(ptr == data + len);

  data = "123.456e-40";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value > 0);
  // VS2015 returns mantissa from converted value
  BOOST_TEST(log10(value) <= -38 + 1);
  //  BOOST_TEST(value == std::numeric_limits<float>::min());
  BOOST_TEST((status == DoubleUnderflow || status == OK));
  BOOST_TEST(ptr == data + len);

  data = "-123.456e-40";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  // VS2015 returns value of any sign
  BOOST_TEST(log10(abs(value)) <= -38 + 1);
  // see n1750 7.22.1.3p10
  //  BOOST_TEST(value > 0);
  //  BOOST_TEST(value == std::numeric_limits<float>::min());
  //
  BOOST_TEST((status == DoubleUnderflow || status == OK));
  BOOST_TEST(ptr == data + len);

  data = "-123.456e-";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<float>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == -123.456);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 8);
}


BOOST_AUTO_TEST_CASE(StoDoubleTest, *boost::unit_test::tolerance(0.0000000000001)) {
  BOOST_TEST(strto<double>("0", strlen("0")) == 0);
  BOOST_TEST(strto<double>("11.2", strlen("11.2")) == 11.2);
  BOOST_TEST(strto<double>("-611.213", strlen("-611.213")) == -611.213);
  BOOST_TEST(strto<double>("611.E12", strlen("611.E12")) == 611.E12);
  BOOST_TEST(strto<double>("611.E-12", strlen("611.E-12")) == 611.E-12);

  const char *data;
  unsigned len;
  char *ptr;
  int status;
  double value;

  data = "0";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == .0);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456e+06";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456e+06);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 0);
  BOOST_TEST(status == NaN);
  BOOST_TEST(ptr == data);

  data = "123.456e+140";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456e+140);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456e-140";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == 123.456e-140);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + len);

  data = "123.456e+309";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value > 0);
  BOOST_TEST(value == std::numeric_limits<double>::infinity());
  BOOST_TEST(status == DoubleOverflow);
  BOOST_TEST(ptr == data + len);

  data = "-123.456e+309";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value < 0);
  BOOST_TEST(value == -std::numeric_limits<double>::infinity());
  BOOST_TEST(status == DoubleOverflow);
  BOOST_TEST(ptr == data + len);

  data = "123.456e-309";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value > 0);
  // VS2015 returns mantissa from converted value
  BOOST_TEST(log10(value) <= -308 + 2);
  //  BOOST_TEST(value == std::numeric_limits<double>::min());
  BOOST_TEST((status == DoubleUnderflow || status == OK));
  BOOST_TEST(ptr == data + len);

  data = "-123.456e-309";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  // VS2015 returns value of any sign
  BOOST_TEST(log10(abs(value)) <= -308 + 2);
  // see n1750 7.22.1.3p10
  //  BOOST_TEST(value > 0);
  //  BOOST_TEST(value == std::numeric_limits<double>::min());
  //
  BOOST_TEST((status == DoubleUnderflow || status == OK));
  BOOST_TEST(ptr == data + len);

  data = "-123.456e-";
  len = strlen(data);
  ptr = nullptr;
  status = OK;
  value = strto<double>(data, len, &ptr, 10, &status);
  BOOST_TEST(value == -123.456);
  BOOST_TEST(status == OK);
  BOOST_TEST(ptr == data + 8);
}
