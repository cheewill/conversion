//===--- recognizer_tests.cpp -----------------------------------*- C++ -*-===//
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
///  Unit tests for recognition of numeric strings.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(PartialTest2a) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("+0R");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "R"));
}


BOOST_AUTO_TEST_CASE(PartialTest3) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("+0  R");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 2);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE(Recog.frac_part().empty());
  BOOST_REQUIRE(Recog.exp_part().empty());
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto ir = Recog.rest_part();
  BOOST_REQUIRE(std::equal(ir.begin(), ir.end(), "R"));
}


BOOST_AUTO_TEST_CASE(BinaryTest1) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("0b101");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "b101"));

  Recog.set_options(Prefix0b);

  Res = Recog.recognize("0b101");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 2);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "101"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(BinaryTest2) {
  NumberRecognizer<> Recog(Prefix0b);

  auto Res = Recog.recognize("0b0101");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 2);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "101"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(BinaryTest3) {
  NumberRecognizer<> Recog(Prefix0b);

  auto Res = Recog.recognize("0b101201");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 2);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 3);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "101"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 3);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "201"));
}


BOOST_AUTO_TEST_CASE(BinaryTest4) {
  NumberRecognizer<> Recog(Prefix0b);

  auto Res = Recog.recognize("0b201");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "b201"));
}


BOOST_AUTO_TEST_CASE(BinaryTest5) {
  NumberRecognizer<> Recog(Prefix0b);

  auto Res = Recog.recognize("0b");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "b"));
}


BOOST_AUTO_TEST_CASE(OctalTest1) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("0o101");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "o101"));

  Recog.set_options(Prefix0o);

  Res = Recog.recognize("0o377");
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.success());
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "377"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest2) {
  NumberRecognizer<> Recog(Prefix0o);

  auto Res = Recog.recognize("0o0345");
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.success());
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "345"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest3) {
  NumberRecognizer<> Recog(Prefix0o);

  auto Res = Recog.recognize("0o56780");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "567"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "80"));
}


BOOST_AUTO_TEST_CASE(OctalTest4) {
  NumberRecognizer<> Recog(Prefix0o);

  auto Res = Recog.recognize("0o877");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "o877"));
}


BOOST_AUTO_TEST_CASE(OctalTest5) {
  NumberRecognizer<> Recog(Prefix0o);

  auto Res = Recog.recognize("0o");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "o"));
}


BOOST_AUTO_TEST_CASE(OctalTest1a) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("0q101");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "q101"));

  Recog.set_options(Prefix0q);

  Res = Recog.recognize("0Q377");
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.success());
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "377"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest2a) {
  NumberRecognizer<> Recog(Prefix0q);

  auto Res = Recog.recognize("0q0345");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "345"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest3a) {
  NumberRecognizer<> Recog(Prefix0q);

  auto Res = Recog.recognize("0Q56780");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "567"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "80"));
}


BOOST_AUTO_TEST_CASE(OctalTest4a) {
  NumberRecognizer<> Recog(Prefix0q);

  auto Res = Recog.recognize("0q877");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "q877"));
}


BOOST_AUTO_TEST_CASE(OctalTest5a) {
  NumberRecognizer<> Recog(Prefix0q);

  auto Res = Recog.recognize("0Q");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "Q"));
}


BOOST_AUTO_TEST_CASE(OctalTest1b) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("0377");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(!Recog.partial());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "377"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);

  Recog.set_options(Prefix0);

  Res = Recog.recognize("0377");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "377"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest2b) {
  NumberRecognizer<> Recog(Prefix0);

  auto Res = Recog.recognize("0345");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "345"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(OctalTest3b) {
  NumberRecognizer<> Recog(Prefix0);

  auto Res = Recog.recognize("056780");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 8);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "567"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "80"));
}


BOOST_AUTO_TEST_CASE(HexTest1) {
  NumberRecognizer<> Recog;

  auto Res = Recog.recognize("0x1234");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.recognized());
  BOOST_REQUIRE(!Recog.success());
  BOOST_REQUIRE(!Recog.failure());
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 5);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 5);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "x1234"));

  Recog.set_options(Prefix0x);

  Res = Recog.recognize("0x1234");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 16);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 4);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 4);
  ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "1234"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(HexTest2) {
  NumberRecognizer<> Recog(Prefix0x);

  auto Res = Recog.recognize("0x0345");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 16);
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

  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 1);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 3);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 3);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "345"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);
}


BOOST_AUTO_TEST_CASE(HexTest3) {
  NumberRecognizer<> Recog(Prefix0x);

  auto Res = Recog.recognize("0x56AFG0");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 16);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 4);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 2);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 4);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "56AF"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 2);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "G0"));
}


BOOST_AUTO_TEST_CASE(HexTest4) {
  NumberRecognizer<> Recog(Prefix0x);

  auto Res = Recog.recognize("0xG87");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 4);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 4);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "xG87"));
}


BOOST_AUTO_TEST_CASE(HexTest5) {
  NumberRecognizer<> Recog(Prefix0x);

  auto Res = Recog.recognize("0x");
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 10);
  BOOST_REQUIRE(Recog.partial());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 1);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 1);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 1);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "0"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 1);
  auto irst = Recog.rest_part();
  BOOST_REQUIRE(std::equal(irst.begin(), irst.end(), "x"));
}


BOOST_AUTO_TEST_CASE(BaseTest1) {
  NumberRecognizer<> Recog;

  Recog.init("FFFF");
  Recog.set_base(16);
  Recog.recognize();
  BOOST_REQUIRE_EQUAL(Recog.get_base(), 16);
  BOOST_REQUIRE(Recog.success());

  BOOST_REQUIRE(!Recog.has_sign());
  BOOST_REQUIRE(!Recog.has_exp_sign());
  BOOST_REQUIRE(!Recog.is_float());

  BOOST_REQUIRE_EQUAL(Recog.get_leading_ws(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_leading_zeros(), 0);
  BOOST_REQUIRE_EQUAL(Recog.get_trailing_ws(), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_int()), 4);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_frac()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_exp()), 0);
  BOOST_REQUIRE_EQUAL(std::get<1>(Recog.get_rest()), 0);

  BOOST_REQUIRE_EQUAL(Recog.int_part().size(), 4);
  auto ip = Recog.int_part();
  BOOST_REQUIRE(std::equal(ip.begin(), ip.end(), "FFFF"));
  BOOST_REQUIRE_EQUAL(Recog.frac_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.exp_part().size(), 0);
  BOOST_REQUIRE_EQUAL(Recog.rest_part().size(), 0);

  int value = 111;
  Recog.read(value);
  BOOST_REQUIRE_EQUAL(value, 65535);
}

