//===--- number_properties.h ------------------------------------*- C++ -*-===//
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
/// Some number properties missed from std::numeric_limits.
///
//===----------------------------------------------------------------------===//
#ifndef CONVERSION_NUMBER_PROPERTIES_H_
#define CONVERSION_NUMBER_PROPERTIES_H_

//------ Dependencies ----------------------------------------------------------
#include <limits>
//------------------------------------------------------------------------------


namespace extra {

namespace internal {

/// \brief Helper class for calculation of minimal value for the given integer
/// type.
///
template<typename NumType, bool IsInteger>
class MinValue;

template<typename NumType>
class MinValue<NumType, true> {
public:
  static NumType get() { return std::numeric_limits<NumType>::min(); }
};

template<typename NumType>
class MinValue<NumType, false> {
public:
  static NumType get() { return -std::numeric_limits<NumType>::max(); }
};

}


/// \brief Provides default values for additional number properties.
///
template<typename NumberType>
struct number_property_base {
  /// \brief Binary exponent of the number closest to zero.
  /// If denormalized numbers are allowed, this value is denormalized.
  static const int denorm_min_exponent =
    std::numeric_limits<NumberType>::min_exponent;

  /// \brief Decimal exponent of the number closest to zero.
  /// If denormalized numbers are allowed, this value is denormalized.
  static const int denorm_min_exponent10 =
    std::numeric_limits<NumberType>::min_exponent10;

  /// \brief Returns lowest possible value.
  /// This method is required because std::numeric_limits<...>::min has
  /// different meaning for integer and float types.
  static NumberType lowest() {
    return internal::MinValue<NumberType,
      std::numeric_limits<NumberType>::is_integer>::get();
  }
};


template<typename NumberType>
struct number_property : public number_property_base<NumberType> {
  // Default implementation of the template is for types that do not have
  // denormal numbers or do not allow user operations on them.
};


template<>
struct number_property<float> : public number_property_base<float> {
  // See https://en.wikipedia.org/wiki/IEEE_754-1985 for particular values.
  static const int denorm_min_exponent = -149;
  static const int denorm_min_exponent10 = -45;
};


template<>
struct number_property<double> : public number_property_base<double> {
  // See https://en.wikipedia.org/wiki/IEEE_754-1985 for particular values.
  static const int denorm_min_exponent = -1074;
  static const int denorm_min_exponent10 = -324;
};


#ifndef _MSC_VER
// TODO: use actual values which are dependent on platform and compiler options.
template<>
struct number_property<long double> : public number_property_base<long double> {
  // See https://en.wikipedia.org/wiki/IEEE_754-1985 for particular values.
  static const int denorm_min_exponent = -1074;
  static const int denorm_min_exponent10 = -324;
};
#endif // _MSVC

}
#endif
