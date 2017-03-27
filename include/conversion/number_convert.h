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
/// Conversions between numeric types.
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
enum Status : unsigned {
  OK,                     ///< Conversion was successful
  NegativeLimit,          ///< Converted value is absolute value of the minimal
                          ///< possible value of the selected integer type.
  DoubleToInt,            ///< Double was read as integer, fractional part is lost
  IntToDouble,            ///< Integer was read as double, precision is lost
  OkCodes,                ///< Number of OK codes.
  IntOverflow = OkCodes,  ///< Integer is too large
  IntOverflowNegative,    ///< Negative integer is too large by magnitude
  DoubleOverflow,         ///< Double value is too large
  DoubleOverflowNegative, ///< Double value is too large
  DoubleUnderflow,        ///< Double value is too small
  NaN                     ///< Not a number or number format error
};


/// \brief Helper class that packs represents both the converted value and the
/// conversion status.
///
template<typename NumType>
class Result {
  NumType value_;
  Status status_;
public:
  constexpr Result(NumType v, Status st = OK) : value_(v), status_(st) {}
  constexpr const NumType &value() const { return value_; }
  constexpr Status status() const { return status_; }
  constexpr bool ok() const { return status_ < OkCodes; }
  constexpr bool overflow() const {
    return status_ >= OkCodes && status_ <= DoubleOverflowNegative;
  }
  constexpr bool underflow() const { return status_ == DoubleUnderflow; }
  constexpr bool bad() const { return status_ == NaN; }
};


namespace internal {

/// \brief Helper class used to convert value of one type to another when both
/// source and target types are of the same kind (integer or floating).
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
/// \tparam IsInt True if both source and destination types are integers.
/// \trapam ToNarrow True if th destination type is narrower that the source.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
template<typename DType, typename SType, bool IsInt, bool ToNarrow>
class Narrowing;

// No narrowing.
template<typename DType, typename SType, bool IsInt>
class Narrowing<DType, SType, IsInt, false> {
  static_assert(std::numeric_limits<DType>::is_integer ==
                std::numeric_limits<SType>::is_integer,
                "Must be both integers or both floats");
public:
  static constexpr Result<DType> convert(const SType &x) { return x; }
};

// Int narrowing.
template<typename DType, typename SType>
class Narrowing<DType, SType, true, true> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
           ? Result<DType>(std::numeric_limits<DType>::max(),
                           Status::IntOverflow)
           : (x < static_cast<SType>(std::numeric_limits<DType>::min())
              ? Result<DType>(std::numeric_limits<DType>::min(),
                              Status::IntOverflowNegative)
              : Result<DType>(static_cast<DType>(x)));
  }
};

// Float narrowing.
template<typename DType, typename SType>
class Narrowing<DType, SType, false, true> {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(),
                      Status::DoubleOverflow)
      : (x < static_cast<SType>(-std::numeric_limits<DType>::max())
         ? Result<DType>(-std::numeric_limits<DType>::max(),
                         Status::DoubleOverflowNegative)
         : Result<DType>(static_cast<DType>(x)));
  }
};

/// \brief Implements conversion float -> integer.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
template<typename DType, typename SType>
class ConvertToInt {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
public:
  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(),
                      Status::IntOverflow)
      : (x < static_cast<SType>(std::numeric_limits<DType>::min())
         ? Result<DType>(std::numeric_limits<DType>::min(),
                         Status::IntOverflow)
         : Result<DType>(static_cast<DType>(x)));
  }
};

/// \brief Conversion integer -> float.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
template<typename DType, typename SType>
class ConvertToFloat {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
public:
  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(),
                      Status::DoubleOverflow)
      : (x < static_cast<SType>(std::numeric_limits<DType>::min())
         ? Result<DType>(std::numeric_limits<DType>::min(),
                         Status::DoubleOverflow)
         : Result<DType>(static_cast<DType>(x)));
  }
};


/// \brief Helper class used to convert value of one numeric type to another.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
/// \tparam IntDest True if destination type is integer.
/// \trapam IntSrc True if source type is integer.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
/// This class dispatches call to \c convert to corresponding methods of classes
/// Narrowing, ConvertToInt or ConvertToFloat.
///
template<typename DType, typename SType, bool IntDest, bool IntSrc>
class ConvertImpl;

// Int to int conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, true, true> {
  static const bool ToNarrow =
    std::numeric_limits<DType>::digits < std::numeric_limits<SType>::digits;
public:
  static constexpr Result<DType> convert(const SType &x) {
    return Narrowing<DType, SType, true, ToNarrow>::convert(x);
  }
};

// Float to float conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, false, false> {
  static const bool ToNarrow =
    std::numeric_limits<DType>::digits < std::numeric_limits<SType>::digits;
public:
  static constexpr Result<DType> convert(const SType &x) {
    return Narrowing<DType, SType, false, ToNarrow>::convert(x);
  }
};

// Float to int conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, true, false> {
public:
  static constexpr Result<DType> convert(const SType &x) {
    return ConvertToInt<DType, SType>::convert(x);
  }
};

// Int to float conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, false, true> {
public:
  static constexpr Result<DType> convert(const SType &x) {
    return ConvertToFloat<DType, SType>::convert(x);
  }
};

}


//------------------------------------------------------------------------------
/// \brief Converts the specified value to the given type.
///
/// \tparam DestType Destination type.
/// \tparam SrcType Source type.
/// \param x Value to convert.
/// \returns Converted value with status of conversion.
//------------------------------------------------------------------------------
template<typename DestType, typename SrcType>
Result<DestType> convert_to(const SrcType &x) {
    return internal::ConvertImpl<DestType, SrcType,
                                 std::numeric_limits<DestType>::is_integer,
                                 std::numeric_limits<SrcType>::is_integer>
             ::convert(x);
}


}
#endif
