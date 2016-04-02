//===--- number_convert.h ---------------------------------------*- C++ -*-===//
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
/// Some numeric number properties missed from std::numeric_limits.
///
//===----------------------------------------------------------------------===//
#ifndef CONVERSION_NUMBER_CONVERT_H_
#define CONVERSION_NUMBER_CONVERT_H_

//------ Dependencies ----------------------------------------------------------
#include <limits>
//------------------------------------------------------------------------------

namespace conversion {


/// Possible status codes returned by conversion functions.
///
enum Status {
  OK,                   ///< Conversion was successful
  NegativeLimit,        ///< Converted value is absolute value of the minimal
                        ///< possible value of the selected integer type.
  DoubleToInt,          ///< Double was read as integer, fractional part is lost
  IntToDouble,          ///< Integer was read as double, precision is lost
  IntOverflow,          ///< Integer is too large
  IntOverflowNegative,  ///< Negative integer is too large by magnitude
  DoubleOverflow,       ///< Double value is too large
  DoubleUnderflow,      ///< Double value is too small
  NaN                   ///< Not a number or number format error
};


namespace internal {

/// \brief Helper class used to convert value of one type to another when both
/// source and target types are of the same kind (integer or floating).
///
template<typename DType, typename SType, bool IsInt, bool ToNarrow>
class Narrowing;

// No narrowing.
template<typename DType, typename SType, bool IsInt>
class Narrowing<DType, SType, IsInt, false> {
public:
  static DType convert(const SType &x, int *status) { return x; }
};

// Int narrowing.
template<typename DType, typename SType>
class Narrowing<DType, SType, true, true> {
public:
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");

  static DType convert(const SType &x, int *status) {
    if (x > static_cast<SType>(std::numeric_limits<DType>::max())) {
      if (status)
        *status = Status::IntOverflow;
      return std::numeric_limits<DType>::max();
    }
    if (x < static_cast<SType>(std::numeric_limits<DType>::min())) {
      if (status)
        *status = Status::IntOverflow;
      return std::numeric_limits<DType>::min();
    }
    return static_cast<DType>(x);
  }
};

// Float narrowing.
template<typename DType, typename SType>
class Narrowing<DType, SType, false, true> {
public:
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");

  static DType convert(const SType &x, int *status) {
    if (x > static_cast<SType>(std::numeric_limits<DType>::max())) {
      if (status)
        *status = Status::DoubleOverflow;
      return std::numeric_limits<DType>::max();
    }
    if (x < static_cast<SType>(-std::numeric_limits<DType>::max())) {
      if (status)
        *status = Status::DoubleOverflow;
      return -std::numeric_limits<DType>::max();
    }
    return static_cast<DType>(x);
  }
};


template<typename DType, typename SType>
class ConvertToInt {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
public:
  static DType convert(const SType &x, int *status) {
    if (x > static_cast<SType>(std::numeric_limits<DType>::max())) {
      if (status)
        *status = Status::IntOverflow;
      return std::numeric_limits<DType>::max();
    }
    if (x < static_cast<SType>(std::numeric_limits<DType>::min())) {
      if (status)
        *status = Status::IntOverflow;
      return std::numeric_limits<DType>::min();
    }
    return static_cast<DType>(x);
  }
};


template<typename DType, typename SType>
class ConvertToFloat {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
public:
  static DType convert(const SType &x, int *status) {
    if (x > static_cast<SType>(std::numeric_limits<DType>::max())) {
      if (status)
        *status = Status::DoubleOverflow;
      return std::numeric_limits<DType>::max();
    }
    if (x < static_cast<SType>(std::numeric_limits<DType>::min())) {
      if (status)
        *status = Status::DoubleOverflow;
      return std::numeric_limits<DType>::min();
    }
    return static_cast<DType>(x);
  }
};


template<typename DType, typename SType, bool IntDest, bool IntSrc>
class ConvertImpl;

// Int to int conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, true, true> {
  static const bool ToNarrow =
    std::numeric_limits<DType>::digits < std::numeric_limits<SType>::digits;
public:
  static DType convert(const SType &x, int *status) {
    return Narrowing<DType, SType, true, ToNarrow>::convert(x, status);
  }
};

// Float to float conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, false, false> {
  static const bool ToNarrow =
    std::numeric_limits<DType>::digits < std::numeric_limits<SType>::digits;
public:
  static DType convert(const SType &x, int *status) {
    return Narrowing<DType, SType, false, ToNarrow>::convert(x, status);
  }
};

// Float to int conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, true, false> {
public:
  static DType convert(const SType &x, int *status) {
    return ConvertToInt<DType, SType>::convert(x, status);
  }
};

// Int to float conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, false, true> {
public:
  static DType convert(const SType &x, int *status) {
    return ConvertToFloat<DType, SType>::convert(x, status);
  }
};

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template<typename DestType, typename SrcType>
DestType convert_to(const SrcType &x, int *status = nullptr) {
    return internal::ConvertImpl<DestType, SrcType,
                                 std::numeric_limits<DestType>::is_integer,
                                 std::numeric_limits<SrcType>::is_integer>
      ::convert(x, status);
}


}
#endif
