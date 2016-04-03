//===--- converter_int_tests.cpp --------------------------------*- C++ -*-===//
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
///  Unit tests for recognition of integer decimal numbers.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_recognizer.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;


BOOST_AUTO_TEST_CASE(IntValuesTest) {
  NumberRecognizer<> Recog;

  BOOST_REQUIRE_EQUAL(Recog.init("0").to<char>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<unsigned char>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<short>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<unsigned short>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<int>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<unsigned int>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<unsigned long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<long long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<unsigned long long>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("0").to<float>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<double>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("0").to<long double>(), 0);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("123").to<char>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<unsigned char>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<short>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<unsigned short>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<int>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<unsigned int>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<long>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<unsigned long>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<long long>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<unsigned long long>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("123").to<float>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<double>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("123").to<long double>(), 123);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("127").to<char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<unsigned char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<short>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<unsigned short>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<int>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<unsigned int>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<long>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<unsigned long>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<long long>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<unsigned long long>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("127").to<float>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<double>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("127").to<long double>(), 127);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("128").to<char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == NegativeLimit);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<unsigned char>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<short>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<unsigned short>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<int>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<unsigned int>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<long>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<unsigned long>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<long long>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<unsigned long long>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("128").to<float>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<double>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("128").to<long double>(), 128);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("129").to<char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<unsigned char>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<short>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<unsigned short>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<int>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<unsigned int>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<long>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<unsigned long>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<long long>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<unsigned long long>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("129").to<float>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<double>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("129").to<long double>(), 129);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("255").to<char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<unsigned char>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<short>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<unsigned short>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<int>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<unsigned int>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<long>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<unsigned long>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<long long>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<unsigned long long>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("255").to<float>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<double>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("255").to<long double>(), 255);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("256").to<char>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<unsigned char>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<short>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<unsigned short>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<int>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<unsigned int>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<long>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<unsigned long>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<long long>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<unsigned long long>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("256").to<float>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<double>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("256").to<long double>(), 256);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<uint16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<int32_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<uint32_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<int64_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<uint64_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<float>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<double>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32767").to<long double>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == NegativeLimit);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<uint16_t>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<int32_t>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<uint32_t>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<int64_t>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<uint64_t>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<float>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<double>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32768").to<long double>(), 32768);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<uint16_t>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<int32_t>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<uint32_t>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<int64_t>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<uint64_t>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<float>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<double>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("32769").to<long double>(), 32769);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<int32_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<uint32_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<int64_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<uint64_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<float>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<double>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65535").to<long double>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<int32_t>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<uint32_t>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<int64_t>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<uint64_t>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<float>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<double>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("65536").to<long double>(), 65536);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<uint32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<int64_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<uint64_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<double>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483647").to<long double>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == NegativeLimit);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<uint32_t>(), 2147483648);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<int64_t>(), 2147483648);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<uint64_t>(), 2147483648);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<double>(), 2147483648);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483648").to<long double>(), 2147483648);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<uint32_t>(), 2147483649);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<int64_t>(), 2147483649);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<uint64_t>(), 2147483649);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<double>(), 2147483649);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("2147483649").to<long double>(), 2147483649);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<int64_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<uint64_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<double>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967295").to<long double>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<int64_t>(), 4294967296);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<uint64_t>(), 4294967296);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<double>(), 4294967296);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("4294967296").to<long double>(), 4294967296);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<int64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == OK);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775807").to<uint64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<int64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == NegativeLimit);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775808").to<uint64_t>(), 9223372036854775808ULL);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<int64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("9223372036854775809").to<uint64_t>(), 9223372036854775809ULL);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<int64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551615").to<uint64_t>(), 18446744073709551615ULL);
  BOOST_REQUIRE(Recog.get_status() == OK);

  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<int8_t>(), 127);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<uint8_t>(), 255);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<int16_t>(), 32767);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<uint16_t>(), 65535);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<int32_t>(), 2147483647);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<uint32_t>(), 4294967295);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<int64_t>(), 9223372036854775807LL);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
  BOOST_REQUIRE_EQUAL(Recog.init("18446744073709551616").to<uint64_t>(), 18446744073709551615ULL);
  BOOST_REQUIRE(Recog.get_status() == IntOverflow);
}


BOOST_AUTO_TEST_CASE(IntValuesTest2) {
  NumberRecognizer<> Recog;

  float val = Recog.init("2147483647").to<float>();
  float ref = float(2147483647);
  BOOST_REQUIRE_CLOSE(val, ref, 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("2147483648").to<float>();
  BOOST_REQUIRE_CLOSE(val, 2147483648.F, 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("4294967295").to<float>();
  BOOST_REQUIRE_CLOSE(val, 4294967295.F, 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("4294967296").to<float>();
  BOOST_REQUIRE_CLOSE(val, 4294967296.F, 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("9223372036854775807").to<float>();
  BOOST_REQUIRE_CLOSE(val, 9223372036854775807., 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("9223372036854775808").to<float>();
  BOOST_REQUIRE_CLOSE(val, 9223372036854775808., 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("18446744073709551615").to<float>();
  BOOST_REQUIRE_CLOSE(val, 18446744073709551615., 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("18446744073709551616").to<float>();
  BOOST_REQUIRE_CLOSE(val, 18446744073709551616., 0.00001);
  BOOST_REQUIRE(Recog.get_status() == OK);
}


BOOST_AUTO_TEST_CASE(IntValuesTest3) {
  NumberRecognizer<> Recog;

  double val = Recog.init("9223372036854775807").to<double>();
  BOOST_REQUIRE_CLOSE(val, 9223372036854775807., 0.0000000000001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  long double lval = Recog.init("9223372036854775807").to<long double>();
  BOOST_REQUIRE_CLOSE(lval, 9223372036854775807., 0.0000000000001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  val = Recog.init("18446744073709551615").to<double>();
  BOOST_REQUIRE_CLOSE(val, 18446744073709551615., 0.0000000000001);
  BOOST_REQUIRE(Recog.get_status() == OK);

  lval = Recog.init("18446744073709551615").to<long double>();
  BOOST_REQUIRE_CLOSE(lval, 18446744073709551615., 0.0000000000001);
  BOOST_REQUIRE(Recog.get_status() == OK);
}
