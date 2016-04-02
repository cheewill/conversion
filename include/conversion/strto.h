//===--- strto.h ------------------------------------------------*- C++ -*-===//
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
/// Generic interface to the set of strto* standard functions.
///
//===----------------------------------------------------------------------===//
#ifndef CONVERSION_STRTO_H_
#define CONVERSION_STRTO_H_

//------ Dependencies ----------------------------------------------------------
#include "number_convert.h"   // for error codes
#include <limits>
#include <memory>
#include <assert.h>
#include <math.h>
#include <memory.h>
//------------------------------------------------------------------------------


namespace conversion {

namespace internal {

/// Selector class used to find wider integer type for which standard conversion
/// function from text to number exists.
///
template<typename NumberType, bool Unsigned, bool WiderThanLong>
struct select_wider_type;

// Signed type not wider than long.
template<typename NumberType>
struct select_wider_type<NumberType, false, false> {
  typedef long long type;
};

// Unsigned type not wider than unsigned long.
template<typename NumberType>
struct select_wider_type<NumberType, true, false> {
  typedef unsigned long type;
};

// Signed type wider than long.
template<typename NumberType>
struct select_wider_type<NumberType, false, true> {
  static_assert(sizeof(NumberType) <= sizeof(long long),
                "Too wide integer type, so strto* exists");
  typedef long long type;
};

// Unsigned type wider than unsigned long
template<typename NumberType>
struct select_wider_type<NumberType, true, true> {
  static_assert(sizeof(NumberType) <= sizeof(unsigned long long),
                "Too wide integer type, so strto* exists");
  typedef unsigned long long type;
};


/// Helper class used to select wider integer type for which standard conversion
/// function from text to number exists. Convenience wrapper.
///
template<typename NumberType>
struct wider_int {
  typedef typename select_wider_type<
    NumberType,
    !std::numeric_limits<NumberType>::is_signed,
    (std::numeric_limits<NumberType>::digits
       <= std::numeric_limits<long long>::digits)
  >::type type;
};


/// Helper function that converts text to number using given standard function.
/// This function is restricted by floating types.
///
/// The function uses interface similar to functions like strtod with additional
/// parameter representing numeric code of conversion status.
///
template<typename NumberType, typename ChT,
         NumberType conv_func(const ChT *, ChT **)>
NumberType strto_floattype(const ChT *str, unsigned len, ChT **endp, int *status) {
  std::unique_ptr<ChT[]> buff(new ChT[len + 1]);
  memcpy(buff.get(), str, len);
  buff.get()[len] = 0;
  ChT *cvend = nullptr;
  int cvstatus = OK;
  errno = 0;
  NumberType value = conv_func(buff.get(), &cvend);
  if (cvend == buff.get()) {
    cvstatus = NaN;
  } else if (errno == ERANGE) {
    if (isinf(value)) {
      cvstatus = DoubleOverflow;
    } else {
      // Must be underflow.
      value = std::numeric_limits<NumberType>::min();
      cvstatus = DoubleUnderflow;
    }
  } else if (errno) {
    cvstatus = NaN;
  }
  if (status)
    *status = cvstatus;
  if (endp)
    *endp = const_cast<ChT*>(str + (cvend - buff.get()));
  return value;
}


/// Helper function that converts text to number using given standard function.
/// This function is restricted by integer types.
///
/// The function uses interface similar to functions like strtol with additional
/// parameter representing numeric code of conversion status.
///
template<typename NumberType, typename ChT,
         NumberType conv_func(const ChT *, ChT **, int)>
NumberType strto_longtype(const ChT *str, unsigned len, ChT **endp, int base,
                          int *status) {
  std::unique_ptr<ChT[]> buff(new ChT[len + 1]);
  memcpy(buff.get(), str, len);
  buff.get()[len] = 0;
  ChT *cvend = nullptr;
  int cvstatus = OK;
  errno = 0;
  NumberType value = conv_func(buff.get(), &cvend, base);
  if (cvend == buff.get()) {
    cvstatus = NaN;
  } else if (errno == ERANGE) {
    assert(value == std::numeric_limits<NumberType>::max() ||
           value == std::numeric_limits<NumberType>::min());
    cvstatus = IntOverflow;
  }
  if (status)
    *status = cvstatus;
  if (endp)
    *endp = const_cast<ChT*>(str + (cvend - buff.get()));
  return value;
}

}


//------------------------------------------------------------------------------
// Template function: strto<NumType>
//
// The function template provides generic interface to string to number
// conversion functions.
//------------------------------------------------------------------------------


/// Function that converts a text representing a number to a value of the number
/// type.
///
/// Default implementation is for integer types. It tries to convert text by
/// reading it as 'long' or 'long long', then casts it to required type.
///
template<typename NumberType, typename ChT>
NumberType strto(const ChT *str, unsigned len, ChT **endp = nullptr,
                 int base = 10, int *status = nullptr) {
  static_assert(std::numeric_limits<NumberType>::is_integer,
                "Must be integer type");
  static_assert(std::numeric_limits<NumberType>::digits
                <= std::numeric_limits<long long>::digits, "Too wide type");
  typedef typename internal::wider_int<NumberType>::type wider_type;
  int local_status = OK;
  wider_type wide_value = strto<wider_type, ChT>(str, len, endp, base,
                                                 &local_status);
  NumberType value = convert_to<NumberType>(wide_value, &local_status);
  if (status)
    *status = local_status;
  return value;
}


template<>
inline float strto<float, char>(const char *str, unsigned len, char **endp,
                                int base, int *status) {
  return internal::strto_floattype<float, char, ::strtof>(str, len, endp, status);
}

template<>
inline double strto<double, char>(const char *str, unsigned len, char **endp,
                                  int base, int *status) {
  return internal::strto_floattype<double, char, ::strtod>(str, len, endp,
                                                           status);
}

template<>
inline long double strto<long double, char>(const char *str, unsigned len,
                                           char **endp, int base, int *status) {
  return internal::strto_floattype<long double, char, ::strtold>(str, len, endp,
                                                                 status);
}

template<>
inline float strto<float, wchar_t>(const wchar_t *str, unsigned len,
                                   wchar_t **endp, int base, int *status) {
  return internal::strto_floattype<float, wchar_t, ::wcstof>(str, len, endp,
                                                             status);
}

template<>
inline double strto<double, wchar_t>(const wchar_t *str, unsigned len,
                                     wchar_t **endp, int base, int *status) {
  return internal::strto_floattype<double, wchar_t, ::wcstod>(str, len, endp,
                                                              status);
}

template<>
inline long double strto<long double, wchar_t>(const wchar_t *str, unsigned len,
                                        wchar_t **endp, int base, int *status) {
  return internal::strto_floattype<long double, wchar_t, ::wcstold>(str, len,
                                                                  endp, status);
}

template<>
inline long long strto<long long, char>(const char *str, unsigned len,
                                        char **endp, int base, int *status) {
  return internal::strto_longtype<long long, char, ::strtoll>(str, len, endp,
                                                              base, status);
}

template<>
inline unsigned long long strto<unsigned long long, char>(const char *str,
                             unsigned len, char **endp, int base, int *status) {
  return internal::strto_longtype<unsigned long long, char, ::strtoull>(str,
                                                       len, endp, base, status);
}

template<>
inline long long strto<long long, wchar_t>(const wchar_t *str, unsigned len,
                                    wchar_t **endp, int base, int *status) {
  return internal::strto_longtype<long long, wchar_t, ::wcstoll>(str, len, endp,
                                                              base, status);
}

template<>
inline unsigned long long strto<unsigned long long, wchar_t>(const wchar_t *str,
                          unsigned len, wchar_t **endp, int base, int *status) {
  return internal::strto_longtype<unsigned long long, wchar_t, ::wcstoull>(str,
                                                       len, endp, base, status);
}

template<>
inline long strto<long, char>(const char *str, unsigned len,
                                        char **endp, int base, int *status) {
  return internal::strto_longtype<long, char, ::strtol>(str, len, endp, base,
                                                        status);
}

template<>
inline unsigned long strto<unsigned long, char>(const char *str,
                             unsigned len, char **endp, int base, int *status) {
  return internal::strto_longtype<unsigned long, char, ::strtoul>(str, len,
                                                            endp, base, status);
}

template<>
inline long strto<long, wchar_t>(const wchar_t *str, unsigned len,
                                    wchar_t **endp, int base, int *status) {
  return internal::strto_longtype<long, wchar_t, ::wcstol>(str, len, endp, base,
                                                           status);
}

template<>
inline unsigned long strto<unsigned long, wchar_t>(const wchar_t *str,
                          unsigned len, wchar_t **endp, int base, int *status) {
  return internal::strto_longtype<unsigned long, wchar_t, ::wcstoul>(str, len,
                                                            endp, base, status);
}

}
#endif
