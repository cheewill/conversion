//===--- recognizer_error_tests.cpp -----------------------------*- C++ -*-===//
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
///  Unit tests for recognition of strings with errors or extra data.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(ErrorTest1) {
  NumberRecognizer<> Recog;

  Recog.recognize("+");
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(Recog.failure());
  BOOST_REQUIRE(!Recog.partial());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "+"));

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == NaN);
}


BOOST_AUTO_TEST_CASE(ErrorTest2) {
  NumberRecognizer<> Recog;

  Recog.recognize("-");
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(Recog.failure());
  BOOST_REQUIRE(!Recog.partial());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "-"));
}


BOOST_AUTO_TEST_CASE(ErrorTest3) {
  NumberRecognizer<> Recog;

  Recog.recognize("  +  0");
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(Recog.failure());
  BOOST_REQUIRE(!Recog.partial());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 6);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 6);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "  +  0"));
}


BOOST_AUTO_TEST_CASE(ErrorTest4) {
  NumberRecognizer<> Recog;

  Recog.recognize(".");
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(Recog.failure());
  BOOST_REQUIRE(!Recog.partial());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "."));
}


BOOST_AUTO_TEST_CASE(ErrorTest5) {
  NumberRecognizer<> Recog;

  Recog.recognize("e12");
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(Recog.failure());
  BOOST_REQUIRE(!Recog.partial());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 3);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 3);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "e12"));
}


BOOST_AUTO_TEST_CASE(PartialTest1) {
  NumberRecognizer<> Recog;
  const char *text = "12e";

  Recog.recognize("12e");

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_plus());
  BOOST_REQUIRE(!Recog.has_minus());
  BOOST_REQUIRE(Recog.is_positive());
  BOOST_REQUIRE(!Recog.is_negative());

  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 2);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_rest_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "12e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "12e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "12e");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "12e");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 2);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 2);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "12"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 2);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "12"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 2);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "12"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init(text);
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init(text).read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init(text).to<double>(), 12.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(PartialTest2) {
  NumberRecognizer<> Recog;
  const char *text = "12e+";

  Recog.recognize("12e+");

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 4);

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_plus());
  BOOST_REQUIRE(!Recog.has_minus());
  BOOST_REQUIRE(Recog.is_positive());
  BOOST_REQUIRE(!Recog.is_negative());

  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_rest_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 2);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "12e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "12e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "12e+");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "12e+");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 2);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 2);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "12"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 2);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "12"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 2);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "12"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init(text);
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init(text).read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 12);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init(text).to<double>(), 12.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}
