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


/// \brief Represents both the converted value and the conversion status.
///
/// \tparam NumType Type of the value stored in this class.
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

/// \brief Helper class used to convert value of an integer type to another
/// integer type.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
/// \tparam SignD True if destination type is signed.
/// \tparam SignS True if source type is signed.
/// \tparam Narrowing True if destination type has more bits in representation
///                   than the source type.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
template<typename DType, typename SType, bool SignD, bool SignS, bool Narrowing>
class ConvertInts;

// Narrowing conversion between signed.
template<typename DType, typename SType>
class ConvertInts<DType, SType, true, true, true> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::is_signed, "Must be signed");
  static_assert(std::numeric_limits<SType>::is_signed, "Must be signed");
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

// Non narrowing conversion between signed.
template<typename DType, typename SType>
class ConvertInts<DType, SType, true, true, false> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::is_signed, "Must be signed");
  static_assert(std::numeric_limits<SType>::is_signed, "Must be signed");
  static_assert(std::numeric_limits<DType>::digits
                >= std::numeric_limits<SType>::digits, "Must not be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return static_cast<DType>(x);
  }
};

// Narrowing conversion from signed to unsigned.
template<typename DType, typename SType>
class ConvertInts<DType, SType, false, true, true> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<DType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<SType>::is_signed, "Must be signed");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x < 0
      ? Result<DType>(0, Status::IntOverflowNegative)
      : (x > static_cast<SType>(std::numeric_limits<DType>::max()))
        ? Result<DType>(std::numeric_limits<DType>::max(), Status::IntOverflow)
        : Result<DType>(static_cast<DType>(x));
  }
};

// Non-narrowing conversion from signed to unsigned.
template<typename DType, typename SType>
class ConvertInts<DType, SType, false, true, false> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<DType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<SType>::is_signed, "Must be signed");
  static_assert(std::numeric_limits<DType>::digits
                >= std::numeric_limits<SType>::digits, "Must not be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x < 0
      ? Result<DType>(0, Status::IntOverflowNegative)
      : Result<DType>(static_cast<DType>(x));
  }
};

// Narrowing conversion between unsigned.
template<typename DType, typename SType>
class ConvertInts<DType, SType, false, false, true> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<DType>::is_signed, "Must be unsigned");
  static_assert(!std::numeric_limits<SType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(),
                      Status::IntOverflow)
      : Result<DType>(static_cast<DType>(x));
  }
};

// Non narrowing conversion between unsigned.
template<typename DType, typename SType>
class ConvertInts<DType, SType, false, false, false> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(!std::numeric_limits<DType>::is_signed, "Must be unsigned");
  static_assert(!std::numeric_limits<SType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<DType>::digits
                >= std::numeric_limits<SType>::digits, "Must not be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return static_cast<DType>(x);
  }
};

// Narrowing conversion from unsigned to signed.
template<typename DType, typename SType>
class ConvertInts<DType, SType, true, false, true> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::is_signed, "Must be signed");
  static_assert(!std::numeric_limits<SType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<DType>::digits
                < std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(), Status::IntOverflow)
      : Result<DType>(static_cast<DType>(x));
  }
};

// Non-narrowing conversion from unsigned to signed.
template<typename DType, typename SType>
class ConvertInts<DType, SType, true, false, false> {
  static_assert(std::numeric_limits<DType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
  static_assert(std::numeric_limits<DType>::is_signed, "Must be signed");
  static_assert(!std::numeric_limits<SType>::is_signed, "Must be unsigned");
  static_assert(std::numeric_limits<DType>::digits
                >= std::numeric_limits<SType>::digits, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(0, Status::IntOverflow)
      : Result<DType>(static_cast<DType>(x));
  }
};


/// \brief Helper class used to convert value of an float type to another
/// float type.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
/// \tparam Narrowing True if destination type cannot represent all values of
///                   the source type.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
template<typename DType, typename SType, bool Narrowing>
class ConvertFloats;

template<typename DType, typename SType>
class ConvertFloats<DType, SType, true> {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<DType>::max_exponent
               < std::numeric_limits<SType>::max_exponent, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    // TODO: check precision loss?
    return x > static_cast<SType>(std::numeric_limits<DType>::max())
      ? Result<DType>(std::numeric_limits<DType>::max(),
                      Status::DoubleOverflow)
      : (x < static_cast<SType>(-std::numeric_limits<DType>::max())
         ? Result<DType>(-std::numeric_limits<DType>::max(),
                         Status::DoubleOverflowNegative)
         : Result<DType>(static_cast<DType>(x)));
  }
};

template<typename DType, typename SType>
class ConvertFloats<DType, SType, false> {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(!std::numeric_limits<SType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<DType>::max_exponent
                >= std::numeric_limits<SType>::max_exponent, "Must be narrowing");
public:

  static constexpr Result<DType> convert(const SType &x) {
    // TODO: check precision loss?
    return static_cast<DType>(x);
  }
};


/// \brief Implements conversion float value to integer.
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
                         Status::IntOverflowNegative)
         : Result<DType>(static_cast<DType>(x), Status::DoubleToInt));
  }
};

/// \brief Conversion integer value to float.
///
/// \tparam DType Destination type.
/// \tparam SType Source type.
///
/// The class contains static method <tt>convert(const SType &x)</tt>, which
/// converts value of \c x to the value of the destination type and returns it
/// with the status of conversion.
///
/// We assume that absolute value of the integer is withing range of the
/// float type.
///
template<typename DType, typename SType>
class ConvertToFloat {
  static_assert(!std::numeric_limits<DType>::is_integer, "Must be float");
  static_assert(std::numeric_limits<SType>::is_integer, "Must be integer");
public:
  static constexpr Result<DType> convert(const SType &x) {
   // TODO: check precision loss?
    return Result<DType>(static_cast<DType>(x));
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
/// ConvertInts, ConvertFloats, ConvertToInt or ConvertToFloat.
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
    return ConvertInts<DType, SType,
                       std::numeric_limits<DType>::is_signed,
                       std::numeric_limits<SType>::is_signed,
                       ToNarrow>::convert(x);
  }
};

// Float to float conversion.
template<typename DType, typename SType>
class ConvertImpl<DType, SType, false, false> {
  static const bool ToNarrow =
    std::numeric_limits<DType>::digits < std::numeric_limits<SType>::digits;
public:
  static constexpr Result<DType> convert(const SType &x) {
    return ConvertFloats<DType, SType, ToNarrow>::convert(x);
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
/// \tparam SrcType  Type of converted value.
/// \tparam DestType Type of resulting value.
///
/// \param x      Converted value.
///
/// \returns Pair of converted value and the status of conversion.
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
