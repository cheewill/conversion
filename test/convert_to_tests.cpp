//===--- converter_to_tests.cpp ---------------------------------*- C++ -*-===//
//
// Copyright(c) 2017, Serge Pavlov.
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
///  Unit tests for convert_to.
///
//===----------------------------------------------------------------------===//

//------ Dependencies ----------------------------------------------------------
#include "conversion/number_convert.h"
#include <boost/test/unit_test.hpp>
#include <memory>
//------------------------------------------------------------------------------

using namespace conversion;

//====== char -> ... ============================

BOOST_AUTO_TEST_CASE(CharToCharTests) {
  auto Res = convert_to<char>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 'a');
}


BOOST_AUTO_TEST_CASE(CharToWCharTests) {
  auto Res = convert_to<wchar_t>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), L'a');
}


BOOST_AUTO_TEST_CASE(CharToChar16Tests) {
  auto Res = convert_to<char16_t>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), u'a');
}


BOOST_AUTO_TEST_CASE(CharToChar32Tests) {
  auto Res = convert_to<char32_t>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), U'a');
}


BOOST_AUTO_TEST_CASE(CharToShortTests) {
  auto Res = convert_to<short>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), short('a'));
}


BOOST_AUTO_TEST_CASE(CharToUShortTests) {
  auto Res = convert_to<unsigned short>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned short('a'));
}


BOOST_AUTO_TEST_CASE(CharToIntTests) {
  auto Res = convert_to<int>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), int('a'));
}


BOOST_AUTO_TEST_CASE(CharToUIntTests) {
  auto Res = convert_to<unsigned int>('a');

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned int('a'));
}


//====== signed char -> ... =====================

BOOST_AUTO_TEST_CASE(SCharToSCharTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<signed char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (signed char)10);
}


BOOST_AUTO_TEST_CASE(SCharToUCharTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<unsigned char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(10));

  const signed char V2 = (signed char)-10;
  Res = convert_to<unsigned char>(V2);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));
}


BOOST_AUTO_TEST_CASE(SCharToWCharTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<wchar_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (wchar_t)10);
}


BOOST_AUTO_TEST_CASE(SCharToChar16Tests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<char16_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (char16_t)10);
}


BOOST_AUTO_TEST_CASE(SCharToChar32Tests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<char16_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (char32_t)10);
}


BOOST_AUTO_TEST_CASE(SCharToIntTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<int>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (int)10);
}


BOOST_AUTO_TEST_CASE(SCharToUIntTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<unsigned int>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (unsigned int)10);
}


BOOST_AUTO_TEST_CASE(SCharToFloatTests) {
  const signed char V = (signed char)10;
  auto Res = convert_to<float>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (float)10);
}


//====== unsigned char -> ... ===================

BOOST_AUTO_TEST_CASE(UCharToSCharTests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<signed char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (signed char)10);
}


BOOST_AUTO_TEST_CASE(UCharToUCharTests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<unsigned char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(10));
}


BOOST_AUTO_TEST_CASE(UCharToWCharTests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<wchar_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (wchar_t)10);
}


BOOST_AUTO_TEST_CASE(UCharToChar16Tests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<char16_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (char16_t)10);
}


BOOST_AUTO_TEST_CASE(UCharToChar32Tests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<char32_t>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (char32_t)10);
}


BOOST_AUTO_TEST_CASE(UCharToIntTests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<int>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (int)10);
}


BOOST_AUTO_TEST_CASE(UCharToFloatTests) {
  const unsigned char V = (unsigned char)10;
  auto Res = convert_to<float>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), (float)10);
}


//====== wchar_t -> ... =========================

BOOST_AUTO_TEST_CASE(WCharToCharTests) {
  const wchar_t V = (wchar_t)'A';
  auto Res = convert_to<char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), L'A');
}

BOOST_AUTO_TEST_CASE(WCharToSCharTests) {
  const wchar_t V = (wchar_t)'A';
  auto Res = convert_to<signed char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(L'A'));
}

BOOST_AUTO_TEST_CASE(WCharToUCharTests) {
  const wchar_t V = (wchar_t)'A';
  auto Res = convert_to<unsigned char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(L'A'));
}


//====== char16_t -> ... ========================

BOOST_AUTO_TEST_CASE(Char16ToCharTests) {
  const auto V = u'A';
  auto Res = convert_to<char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 'A');
}

BOOST_AUTO_TEST_CASE(Char16ToSCharTests) {
  const auto V = u'A';
  auto Res = convert_to<signed char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(u'A'));
}

BOOST_AUTO_TEST_CASE(Char16ToUCharTests) {
  const auto V = u'A';
  auto Res = convert_to<unsigned char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(u'A'));
}


//====== char32_t -> ... ========================

BOOST_AUTO_TEST_CASE(Char32ToCharTests) {
  const auto V = U'A';
  auto Res = convert_to<char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 'A');
}

BOOST_AUTO_TEST_CASE(Char32ToSCharTests) {
  const auto V = U'A';
  auto Res = convert_to<signed char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(U'A'));
}

BOOST_AUTO_TEST_CASE(Char32ToUCharTests) {
  const auto V = U'A';
  auto Res = convert_to<unsigned char>(V);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(U'A'));
}


//====== int -> ... =============================

BOOST_AUTO_TEST_CASE(IntToCharTests) {
  auto Res = convert_to<char>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), char(10));
}


BOOST_AUTO_TEST_CASE(IntToUCharTests) {
  auto Res = convert_to<unsigned char>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(10));

  Res = convert_to<unsigned char>(255);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  Res = convert_to<unsigned char>(256);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  Res = convert_to<unsigned char>(0);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));

  Res = convert_to<unsigned char>(-1);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));
}


BOOST_AUTO_TEST_CASE(IntToSCharTests) {
  auto Res = convert_to<signed char>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(10));

  Res = convert_to<signed char>(127);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(128);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(0);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(0));

  Res = convert_to<signed char>(-127);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-127));

  Res = convert_to<signed char>(-128);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-128));
}


BOOST_AUTO_TEST_CASE(IntToWCharTests) {
  auto Res = convert_to<wchar_t>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), wchar_t(10));
}


BOOST_AUTO_TEST_CASE(IntToChar16Tests) {
  auto Res = convert_to<char16_t>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), char16_t(10));
}


BOOST_AUTO_TEST_CASE(IntToChar32Tests) {
  auto Res = convert_to<char32_t>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), char32_t(10));
}


BOOST_AUTO_TEST_CASE(IntToShortTests) {
  auto Res = convert_to<short>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), short(10));
}


BOOST_AUTO_TEST_CASE(IntToUShortTests) {
  auto Res = convert_to<unsigned short>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned short(10));
}


BOOST_AUTO_TEST_CASE(IntToIntTests) {
  auto Res = convert_to<int>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), int(10));
}


BOOST_AUTO_TEST_CASE(IntToUIntTests) {
  auto Res = convert_to<unsigned int>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned int(10));
}


BOOST_AUTO_TEST_CASE(IntToLongTests) {
  auto Res = convert_to<long>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), long(10));
}


BOOST_AUTO_TEST_CASE(IntToULongTests) {
  auto Res = convert_to<unsigned long>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned long(10));
}


BOOST_AUTO_TEST_CASE(IntToLongLongTests) {
  auto Res = convert_to<long long>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), long long(10));
}


BOOST_AUTO_TEST_CASE(IntToULongLongTests) {
  auto Res = convert_to<unsigned long long>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned long long(10));
}


BOOST_AUTO_TEST_CASE(IntToFloatTests) {
  auto Res = convert_to<float>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), float(10));
}


BOOST_AUTO_TEST_CASE(IntToDoubleTests) {
  auto Res = convert_to<double>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), double(10));
}


BOOST_AUTO_TEST_CASE(IntToLongDoubleTests) {
  auto Res = convert_to<long double>(10);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), long double(10));
}

BOOST_AUTO_TEST_CASE(IntOverflow_I8toI8Tests) {
  const signed char i8 = -120;
  auto Res = convert_to<signed char>(i8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-120));

  const signed char i8a = -128;
  Res = convert_to<signed char>(i8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-128));

  const signed char i8b = 127;
  Res = convert_to<signed char>(i8b);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));
}

BOOST_AUTO_TEST_CASE(IntOverflow_U8toU8Tests) {
  const unsigned char u8 = 250;
  auto Res = convert_to<unsigned char>(u8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(250));

  const unsigned char u8a = 255;
  Res = convert_to<unsigned char>(u8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  const unsigned char u8b = 0;
  Res = convert_to<unsigned char>(u8b);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_I8toU8Tests) {
  const signed char i8 = -120;
  auto Res = convert_to<unsigned char>(i8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));

  const signed char i8a = 127;
  Res = convert_to<unsigned char>(i8a);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(127));

  const signed char i8b = 0;
  Res = convert_to<unsigned char>(i8b);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_U8toI8Tests) {
  const unsigned char u8 = 250;
  auto Res = convert_to<signed char>(u8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  const unsigned char u8a = 127;
  Res = convert_to<signed char>(u8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  const unsigned char u8b = 0;
  Res = convert_to<signed char>(u8b);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_I8toI32_Tests) {
  const signed char i8 = -120;
  auto Res = convert_to<int>(i8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), -120);

  const signed char i8a = 127;
  Res = convert_to<int>(i8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 127);

  const signed char i8b = -128;
  Res = convert_to<int>(i8b);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), -128);
}

BOOST_AUTO_TEST_CASE(IntOverflow_I32toI8_Tests) {
  auto Res = convert_to<signed char>(2000);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(127);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(-2000);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-128));

  Res = convert_to<signed char>(-126);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-126));

  Res = convert_to<signed char>(-128);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(-128));
}

BOOST_AUTO_TEST_CASE(IntOverflow_I8toU32_Tests) {
  const signed char i8 = -120;
  auto Res = convert_to<unsigned>(i8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned(0));

  const signed char i8a = 127;
  Res = convert_to<unsigned>(i8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned(127));

  const signed char i8b = 0;
  Res = convert_to<unsigned>(i8b);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_U32toI8_Tests) {
  auto Res = convert_to<signed char>(2000U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(127U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(127));

  Res = convert_to<signed char>(0U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), signed char(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_I32toU8_Tests) {
  auto Res = convert_to<unsigned char>(2000);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  Res = convert_to<unsigned char>(255);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  Res = convert_to<unsigned char>(-1);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));

  Res = convert_to<unsigned char>(0);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(0));
}

BOOST_AUTO_TEST_CASE(IntOverflow_U8toI32_Tests) {
  const unsigned char u8 = 0;
  auto Res = convert_to<int>(u8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 0);

  const unsigned char u8a = 255;
  Res = convert_to<int>(u8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 255);
}

BOOST_AUTO_TEST_CASE(IntOverflow_U8toU32_Tests) {
  const unsigned char u8 = 0;
  auto Res = convert_to<unsigned>(u8);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 0U);

  const unsigned char u8a = 255;
  Res = convert_to<unsigned>(u8a);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 255U);
}

BOOST_AUTO_TEST_CASE(IntOverflow_U32toU8_Tests) {
  auto Res = convert_to<unsigned char>(2000U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), unsigned char(255));

  Res = convert_to<unsigned char>(255U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 255U);

  Res = convert_to<unsigned char>(0U);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::OK);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 0U);
}

BOOST_AUTO_TEST_CASE(DoubleToI32_Tests) {
  auto Res = convert_to<int>(2000.5);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::DoubleToInt);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 2000);

  Res = convert_to<int>(1E66);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflow);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), std::numeric_limits<int>::max());

  Res = convert_to<int>(-1E66);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::IntOverflowNegative);
  BOOST_REQUIRE(!Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), std::numeric_limits<int>::min());

  Res = convert_to<int>(0.1);

  BOOST_REQUIRE_EQUAL(Res.status(), Status::DoubleToInt);
  BOOST_REQUIRE(Res.ok());
  BOOST_REQUIRE(!Res.bad());
  BOOST_REQUIRE(!Res.overflow());
  BOOST_REQUIRE(!Res.underflow());
  BOOST_REQUIRE_EQUAL(Res.value(), 0);
}
