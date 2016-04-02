//===--- recognizer_zero_float_tests.cpp ------------------------*- C++ -*-===//
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
///  Unit tests for recognition of zero numbers with fractional part.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(ZeroTest9) {
  NumberRecognizer<> Recog;

  Recog.recognize("0.");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 2);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 2);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 2);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 2);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "0."));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("0.");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("0.").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("0.").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest10) {
  NumberRecognizer<> Recog;

  Recog.recognize(".0");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 2);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 2);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 2);

  BOOST_REQUIRE(Recog.int_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  auto ir = Recog.frac_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 2);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), ".0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 2);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), ".0"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init(".0");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init(".0").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init(".0").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest11) {
  NumberRecognizer<> Recog;

  Recog.recognize("0.0");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 3);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 3);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 3);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "0.0"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("0.0");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("0.0").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest12) {
  NumberRecognizer<> Recog;

  Recog.recognize("00.");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 3);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 3);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 3);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "00."));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("00.");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("00.").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("00.").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest13) {
  NumberRecognizer<> Recog;

  Recog.recognize(".00");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 3);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 3);

  BOOST_REQUIRE(Recog.int_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  auto ir = Recog.frac_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 2);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), ".0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 3);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), ".00"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init(".00");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init(".00").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init(".00").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest14) {
  NumberRecognizer<> Recog;

  Recog.recognize("00.0");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 4);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 4);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 3);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 4);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 4);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "00.0"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("00.0");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("00.0").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("00.0").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest15) {
  NumberRecognizer<> Recog;

  Recog.recognize("0.00");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 4);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 4);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 4);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 4);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "0.00"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("0.00");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("0.00").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("0.00").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest16) {
  NumberRecognizer<> Recog;

  Recog.recognize("00.00");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 5);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 5);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 5);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin());
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 3);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 5);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 5);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "00.00"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("00.00");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("00.00").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("00.00").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest17) {
  NumberRecognizer<> Recog;

  Recog.recognize("+0.");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

  BOOST_REQUIRE(Recog.has_sign());
  BOOST_REQUIRE(Recog.has_plus());
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
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 3);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 3);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 3);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "+0."));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("+0.");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("+0.").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("+0.").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest18) {
  NumberRecognizer<> Recog;

  Recog.recognize("+00.");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 4);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

  BOOST_REQUIRE(Recog.has_sign());
  BOOST_REQUIRE(Recog.has_plus());
  BOOST_REQUIRE(!Recog.has_minus());
  BOOST_REQUIRE(Recog.is_positive());
  BOOST_REQUIRE(!Recog.is_negative());

  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 4);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 4);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 4);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "+00."));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("+00.");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("+00.").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("+00.").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest19) {
  NumberRecognizer<> Recog;

  Recog.recognize("-00.00");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 6);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

  BOOST_REQUIRE(Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_plus());
  BOOST_REQUIRE(Recog.has_minus());
  BOOST_REQUIRE(!Recog.is_positive());
  BOOST_REQUIRE(Recog.is_negative());

  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 6);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 6);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE(std::get<0>(Recog.get_prefix()) == Recog.begin() + 1);
  BOOST_REQUIRE(std::get<0>(Recog.get_int()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_frac()) == Recog.begin() + 4);
  BOOST_REQUIRE(std::get<0>(Recog.get_exp()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_rest()) == Recog.end());
  BOOST_REQUIRE(std::get<0>(Recog.get_mantissa()) == Recog.begin() + 2);
  BOOST_REQUIRE(std::get<0>(Recog.get_number()) == Recog.begin());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 6);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ir = Recog.int_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 1);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 6);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "-00.00"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init("-00.00");
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init("-00.00").read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("-00.00").to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(ZeroTest20) {
  NumberRecognizer<> Recog;
  const char *text = "-.0";

  Recog.recognize("-.0");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

  BOOST_REQUIRE(Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_plus());
  BOOST_REQUIRE(Recog.has_minus());
  BOOST_REQUIRE(!Recog.is_positive());
  BOOST_REQUIRE(Recog.is_negative());

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
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 3);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), ".0");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), ".0");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "0");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), ".0");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-.0");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 3);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE(Recog.int_part().empty());
  auto ir = Recog.frac_part();
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "0"));
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.mantissa_part().size(), 2);
  auto mr = Recog.mantissa_part();
  BOOST_REQUIRE(std::equal(mr.begin(), mr.end(), ".0"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 3);
  auto nr = Recog.number_text();
  BOOST_REQUIRE(std::equal(nr.begin(), nr.end(), "-.0"));

  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE(Recog.to<int>() == 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  Recog.init(text);
  BOOST_REQUIRE(Recog.get_status() == OK);
  int value = 111;
  BOOST_REQUIRE(Recog.read(value) == OK);
  BOOST_REQUIRE_EQUAL(value, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long long llvalue = 111;
  BOOST_REQUIRE(Recog.init(text).read(llvalue) == OK);
  BOOST_REQUIRE_EQUAL(llvalue, 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init(text).to<double>(), 0.0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}
