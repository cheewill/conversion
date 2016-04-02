//===--- converter_float_tests.cpp ------------------------------*- C++ -*-===//
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
///  Unit tests for recognition of floating numbers.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(FloatValuesTest1) {
  NumberRecognizer<> Recog;

  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<char>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<unsigned char>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<short>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<unsigned short>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<int>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<unsigned int>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<unsigned long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<long long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<unsigned long long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<float>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<double>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0.0").to<long double>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(FloatValuesTest2) {
  NumberRecognizer<> Recog;

  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<char>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<unsigned char>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<short>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<unsigned short>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<int>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<unsigned int>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<long>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<unsigned long>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<long long>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<unsigned long long>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<float>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<double>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("1E2").to<long double>(), 100);
  BOOST_REQUIRE(Recog.get_status() == OK);
}
