//===--- recognizer_float_tests.cpp -----------------------------*- C++ -*-===//
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
///  Unit tests for recognition of floating strings.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(FloatTest5) {
  NumberRecognizer<> Recog;

  Recog.recognize("-1.2");

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
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 4);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "1.2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "1.2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "1.2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-1.2");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 4);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "2"));
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 4);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "-1.2"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), -1);
  BOOST_REQUIRE(Recog.to<double>() == -1.2);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(Float1Test) {
  NumberRecognizer<> Recog;

  Recog.remove_options(Floating);
  Recog.recognize("1e2");

  BOOST_REQUIRE(Recog.get_options() == (DefaultOptions & ~Floating));

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 3);

  BOOST_REQUIRE(!Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

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
  BOOST_REQUIRE_EQUAL(Recog.get_rest_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 1);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "1e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "1e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "1e2");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "1e2");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 1);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  p = Recog.rest_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "e2"));
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 1);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), 1);
  BOOST_REQUIRE(Recog.to<double>() == 1);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatTest5a) {
  NumberRecognizer<> Recog;

  Recog.recognize("-1.20");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 5);

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

  BOOST_REQUIRE(Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_rest_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 5);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "1.20");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "1.20");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "20");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "1.20");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-1.20");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 5);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "2"));
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 5);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "-1.20"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), -1);
  BOOST_REQUIRE(Recog.to<double>() == -1.2);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatTest5b) {
  NumberRecognizer<> Recog;

  Recog.recognize("-12.e1");

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
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 2);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 6);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 4);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 5);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "12.e1");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "12.e1");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "e1");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "1");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "12.e1");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-12.e1");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 6);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 2);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "12"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), ""));
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 1);
  p = Recog.exp_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 6);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "-12.e1"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), -120);
  BOOST_REQUIRE(Recog.to<double>() == -120);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatTest7) {
  NumberRecognizer<> Recog;

  Recog.recognize("+1.2e3");

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
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 6);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 5);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "1.2e3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "1.2e3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "2e3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "1.2e3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "+1.2e3");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 6);

  BOOST_REQUIRE_EQUAL(Recog.prefix_part().size(), 0);
  auto p = Recog.prefix_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), ""));
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "2"));
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 1);
  p = Recog.exp_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "3"));
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 6);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "+1.2e3"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), 1200);
  BOOST_REQUIRE(Recog.to<double>() == 1200);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatTest8) {
  NumberRecognizer<> Recog;

  Recog.recognize("+1.2e+3");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 7);

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

  BOOST_REQUIRE(Recog.has_exp_sign());
  BOOST_REQUIRE(Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_int_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_length(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 7);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 3);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 6);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "1.2e+3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "1.2e+3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "2e+3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "1.2e+3");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "+1.2e+3");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 7);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "1"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 1);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "2"));
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 1);
  p = Recog.exp_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "3"));
  BOOST_REQUIRE(Recog.rest_part().empty());

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), 1200);
  BOOST_REQUIRE(Recog.to<double>() == 1200);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatTest9) {
  NumberRecognizer<> Recog;

  Recog.recognize("-123.456E-789");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 13);

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

  BOOST_REQUIRE(Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.has_exp_plus());
  BOOST_REQUIRE(Recog.has_exp_minus());
  BOOST_REQUIRE(!Recog.is_exp_positive());
  BOOST_REQUIRE(Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 7);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 13);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 5);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 10);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "123.456E-789");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "123.456E-789");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "456E-789");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "789");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "123.456E-789");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-123.456E-789");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 7);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 13);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "123"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 3);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "456"));
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 3);
  p = Recog.exp_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "789"));
  BOOST_REQUIRE(Recog.rest_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.number_text().size(), 13);
  p = Recog.number_text();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "-123.456E-789"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), 0);
  BOOST_REQUIRE(Recog.get_status() == DoubleToInt);
  BOOST_REQUIRE(Recog.to<double>() == -0);
  BOOST_REQUIRE(Recog.get_status() == DoubleUnderflow);
}


BOOST_AUTO_TEST_CASE(FloatTest12) {
  NumberRecognizer<> Recog;

  Recog.recognize("-123.4567E+8E");

  BOOST_REQUIRE(Recog.get_options() == DefaultOptions);

  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE_EQUAL(Recog.size(), 13);

  BOOST_REQUIRE(Recog.is_float());
  BOOST_REQUIRE(!Recog.is_empty());

  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_plus());
  BOOST_REQUIRE(Recog.has_minus());
  BOOST_REQUIRE(!Recog.is_positive());
  BOOST_REQUIRE(Recog.is_negative());

  BOOST_REQUIRE(Recog.has_exp_sign());
  BOOST_REQUIRE(Recog.has_exp_plus());
  BOOST_REQUIRE(!Recog.has_exp_minus());
  BOOST_REQUIRE(Recog.is_exp_positive());
  BOOST_REQUIRE(!Recog.is_exp_negative());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_prefix_length(), 0);

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 4);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_length(), 8);
  BOOST_REQUIRE_EQUAL(Recog.get_number_length(), 12);

  BOOST_REQUIRE_EQUAL(Recog.get_prefix_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_int_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_frac_start(), 5);
  BOOST_REQUIRE_EQUAL(Recog.get_exp_start(), 11);
  BOOST_REQUIRE_EQUAL(Recog.get_mantissa_start(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_number_start(), 0);

  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_prefix()), "123.4567E+8E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_int()), "123.4567E+8E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_frac()), "4567E+8E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_exp()), "8E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_rest()), "E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_mantissa()), "123.4567E+8E");
  BOOST_REQUIRE_EQUAL(std::get<0>(Recog.get_number()), "-123.4567E+8E");

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_prefix()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 4);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_mantissa()), 8);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_number()), 12);

  BOOST_REQUIRE(Recog.prefix_part().empty());
  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto p = Recog.int_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "123"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 4);
  p = Recog.frac_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "4567"));
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 1);
  p = Recog.exp_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "8"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  p = Recog.rest_part();
  BOOST_REQUIRE(std::equal(p.begin(), p.end(), "E"));

  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.to<int>(), std::numeric_limits<int>::min());
  BOOST_REQUIRE(Recog.to<double>() == -12345670000);
  BOOST_REQUIRE(Recog.get_status() == OK);
}
