//===--- number_recognizer.h ------------------------------------*- C++ -*-===//
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
/// \brief
/// Tools for converting strings to numbers.
///
//===----------------------------------------------------------------------===//
#ifndef CONVERSION_NUMBER_RECOGNIZER_H_
#define CONVERSION_NUMBER_RECOGNIZER_H_

//------ Dependencies ----------------------------------------------------------
#include "number_convert.h"
#include "number_properties.h"
#include "strto.h"
#include <assert.h>
#include <float.h>
#include <tuple>
#include <cctype>
//------------------------------------------------------------------------------


namespace conversion {

/// Recognizer options.
enum Option {
  Prefix0x  = 0x001,    ///< 0x specifies hexadecimal base
  Prefix0o  = 0x002,    ///< 0o specifies octal base
  Prefix0q  = 0x004,    ///< 0q specifies octal base
  Prefix0b  = 0x010,    ///< 0b specifies binary base
  Prefix0   = 0x020,    ///< leading 0 specifies octal base
  Floating  = 0x040,    ///< Parse floating point notation
  DefaultOptions = Floating    ///< Default option set
};


// Allowed bases.
const unsigned char MinBase = 2;    ///< Minimal allowed base
const unsigned char MaxBase = 36;   ///< Maximal allowed base


// Arrays of digits.
extern const char upper_digits[];   ///< Upper case digits: 0123456789ABCD...
extern const char lower_digits[];   ///< Lower case digits: 0123456789abcd...


/// \brief Converts sequence of digits into corresponding integer number.
///
/// \tparam NumType Target number type.
/// \tparam CharT Type of character data.
///
/// \param[out] value variable that gets converted number
/// \param[in]  str   start of the text to convert
/// \param[in]  len   length of the text to convert
/// \param[in]  base  radix to use
///
/// \returns status of conversion
///
/// This function is designed for internal use in other conversion functions, so
/// it makes little error handling.
///
template<typename NumType, typename CharT>
Status convert_int(NumType &value, const CharT *str, unsigned len,
                   unsigned char base = 10) {
  value = 0;
  if (len == 0)
    return NaN;

  assert(str);
  assert(base >= MinBase && base <= MaxBase);

  // Build result value.
  for (; len; --len, ++str) {
    // Get current digit
    CharT ch = *str;
    unsigned char digit;
    if (ch >= CharT('0') && ch <= CharT('9'))
      digit = ch - CharT('0');
    else if (ch >= CharT('A') && ch <= CharT('Z'))
      digit = 10 + (ch - CharT('A'));
    else if (ch >= CharT('a') && ch <= CharT('z'))
      digit = 10 + (ch - CharT('a'));
    else
      return NaN;
    if (digit >= base)
      return NaN;

    // Append the digit to result.
    NumType prev = value;
    value *= base;
    // TODO: there must be more effective way to detect overflow, for instance
    // by using compiler intrinsics.
    bool overflow = false;
    if (std::numeric_limits<NumType>::is_integer)
      overflow = (value / base != prev);
    if (!overflow) {
      value += digit;
      if (value < prev)
        overflow = true;
    }
    if (overflow) {
      if (std::numeric_limits<NumType>::is_integer &&
          std::numeric_limits<NumType>::is_signed && len == 1) {
        // Check particular case, if this is negation of negative limit.
        if (prev * base - 1 + digit == std::numeric_limits<NumType>::max())
          return NegativeLimit;
      }
      value = std::numeric_limits<NumType>::max();
      return IntOverflow;
    }
  }

  return OK;
}


/// \brief Variant of convert_int which gets text in the form of std::tuple.
///
template<typename NumType, typename CharT>
Status convert_int(NumType &value, std::tuple<const CharT *, unsigned> text,
                   unsigned char base = 10) {
  return convert_int(value, std::get<0>(text), std::get<1>(text), base);
}


class NumberRecognizerState {
public:

  // Recognizer options.

  unsigned char get_options() const { return options; }
  void set_options(unsigned char x) { options = x; }
  void add_options(unsigned char x) { options |= x; }
  void remove_options(unsigned char x) { options &= ~x; }

  bool is_allowed_0x() const { return (options & Prefix0x) != 0; }
  bool is_allowed_0o() const { return (options & Prefix0o) != 0; }
  bool is_allowed_0q() const { return (options & Prefix0q) != 0; }
  bool is_allowed_0b() const { return (options & Prefix0b) != 0; }
  bool is_allowed_0() const { return (options & Prefix0) != 0; }
  bool is_allowed_float() const { return (options & Floating) != 0; }

  void set_base(unsigned char x) { base = x; }

  unsigned size() const { return length; }

  // Recognition results.

  bool has_sign() const { return sign != NoSign; }
  bool has_plus() const { return sign == Positive; }
  bool has_minus() const { return sign == Negative; }
  bool is_positive() const { return sign <= Positive; }
  bool is_negative() const { return sign == Negative; }

  bool has_exp_sign() const { return exp_sign != NoSign; }
  bool has_exp_plus() const { return exp_sign == Positive; }
  bool has_exp_minus() const { return exp_sign == Negative; }
  bool is_exp_positive() const { return exp_sign <= Positive; }
  bool is_exp_negative() const { return exp_sign == Negative; }

  // Recognition results.

  bool recognized() const { return result != Unrecognized; }
  bool success() const { return result == Success; }
  bool failure() const { return result == Failure; }
  bool partial() const { return result == Partial; }

  unsigned get_base() const { return base; }

  bool is_float() const { return has_dot || exp_length; }
  bool is_empty() const { return leading_ws == length; }

  // Number parts.

  unsigned get_leading_ws() const { return leading_ws; }
  unsigned get_leading_zeros() const {
    if (int_length == 0)
      return 0;
    return int_start - leading_ws - get_prefix_length() - has_sign();
  }
  unsigned get_prefix_length() const { return has_prefix ? has_sign() + 2 : 0; }
  unsigned get_trailing_zeros() const {
    if (exp_length)
      return (exp_start - (1 + has_exp_sign() + exp_leading_zeros))
           - (frac_start + frac_length);
    return exp_start - (frac_start + frac_length);
  }
  unsigned get_trailing_ws() const { return trailing_ws; }

  unsigned get_int_length() const { return int_length; }
  unsigned get_frac_length() const { return frac_length; }
  unsigned get_exp_length() const { return exp_length; }
  unsigned get_rest_length() const { return length - rest_start; }
  unsigned get_mantissa_length() const {
    return int_length + frac_length + (has_dot && frac_length);
  }
  unsigned get_number_length() const {
    return rest_start - leading_ws - trailing_ws;
  }

  unsigned get_prefix_start() const { return leading_ws + has_sign(); }
  unsigned get_int_start() const { return int_start; }
  unsigned get_frac_start() const { return frac_start; }
  unsigned get_exp_start() const { return exp_start; }
  unsigned get_rest_start() const { return rest_start; }
  unsigned get_mantissa_start() const { return int_start; }
  unsigned get_number_start() const { return leading_ws; }

  // Conversion results.
  Status get_status() const { return static_cast<Status>(status); }

protected:

  /// Recognition result.
  enum Result {
    Unrecognized = 0, ///< Recognition is not made yet.
    Success = 1,      ///< Entire string is a number
    Partial = 2,      ///< Only start of the string is a number
    Failure = 3       ///< Not a number at all
  };

  /// Sing recognition status.
  enum Sign {
    NoSign = 0,       ///< No sign was specified
    Positive = 1,     ///< '+' was explicitly specified
    Negative = 2      ///< '-' was specified
  };

  unsigned length;
  unsigned leading_ws;
  unsigned int_start, int_length;
  unsigned frac_start, frac_length;
  unsigned exp_start, exp_leading_zeros, exp_length;
  unsigned trailing_ws;
  unsigned rest_start;
  unsigned char options;
  bool has_dot : 1;
  bool has_prefix : 1;
  unsigned sign : 2;
  unsigned exp_sign : 2;
  unsigned base : 8;
  unsigned int result : 2;
  unsigned int status : 4;

  NumberRecognizerState(unsigned char opts = DefaultOptions) { init(opts); }

  void init(unsigned char opts = DefaultOptions) {
    length = 0;
    leading_ws = trailing_ws = 0;
    int_start = int_length = 0;
    frac_start = frac_length = 0;
    exp_start = exp_leading_zeros = exp_length = 0;
    rest_start = 0;
    options = opts;
    has_dot = has_prefix = false;
    sign = exp_sign = NoSign;
    base = 0;
    result = static_cast<unsigned>(Unrecognized);
    status = static_cast<unsigned>(OK);
  }

  Result get_result() const { return static_cast<Result>(result); }
};


namespace internal {

template<typename NumberType, bool IsInt, bool Signed>
class SetSign;


template<typename NumberType>
class SetSign<NumberType, true, true> {
public:
  static void set(NumberType &value, bool is_negative, Status &status) {
    if (is_negative) {
      if (status == NegativeLimit) {
        value = std::numeric_limits<NumberType>::min();
        status = OK;
      } else {
        value = -value;
      }
    }
    else if (status == NegativeLimit) {
      value = std::numeric_limits<NumberType>::max();
    }
  }
};


template<typename NumberType>
class SetSign<NumberType, true, false> {
public:
  static void set(NumberType &value, bool is_negative, Status &status) {
    assert(status != NegativeLimit);
    if (is_negative)
      value = 0;
  }
};


template<typename NumberType>
class SetSign<NumberType, false, true> {
public:
  static void set(NumberType &value, bool is_negative, Status &status) {
    if (is_negative)
      value = -value;
  }
};

}

template<typename CharT = char, typename TraitT = std::char_traits<CharT> >
class NumberRecognizer : public NumberRecognizerState {
  const CharT *start;
public:

  // Constructors.

  NumberRecognizer() { start = nullptr; }
  NumberRecognizer(unsigned opts) : NumberRecognizerState(opts) {
    start = nullptr;
  }
  NumberRecognizer(const CharT *str) : NumberRecognizerState(), start(str) {
    length = TraitT::length(str);
  }
  NumberRecognizer(const CharT *str, unsigned len)
    : NumberRecognizerState(), start(str) {
    length = len;
  }
  NumberRecognizer(const CharT *str, unsigned len, unsigned opts)
    : NumberRecognizerState(opts), start(str) {
    length = len;
  }

  // Initialization.

  NumberRecognizer &init(unsigned opts = DefaultOptions) {
    NumberRecognizerState::init(opts);
    start = nullptr;
    return *this;
  }

  NumberRecognizer &init(const CharT *str) {
    NumberRecognizerState::init(get_options());
    start = str;
    length = TraitT::length(str);
    return *this;
  }

  NumberRecognizer &init(const CharT *str, unsigned len) {
    NumberRecognizerState::init(get_options());
    start = str;
    length = len;
    return *this;
  }

  NumberRecognizer &init(const CharT *str, unsigned len, unsigned opts) {
    NumberRecognizerState::init(opts);
    start = str;
    length = TraitT::length(str);
    return *this;
  }

  NumberRecognizer &init(const CharT *str, unsigned len,
                         unsigned opts, unsigned b) {
    NumberRecognizerState::init(opts);
    start = str;
    length = TraitT::length(str);
    set_base(b);
    return *this;
  }

  // Get pointers to different parts of recognized number.

  const CharT *begin() const { return start; }
  const CharT *end() const { return start + length; }
  const CharT *begin_prefix() const { return start + get_prefix_start(); }
  const CharT *end_prefix() const { return begin_prefix() + get_prefix_length(); }
  const CharT *begin_int() const { return start + get_int_start(); }
  const CharT *end_int() const { return begin_int() + get_int_length(); }
  const CharT *begin_frac() const { return start + get_frac_start(); }
  const CharT *end_frac() const { return begin_frac() + get_frac_length(); }
  const CharT *begin_exp() const { return start + get_exp_start(); }
  const CharT *end_exp() const { return begin_exp() + get_exp_length(); }
  const CharT *begin_rest() const { return start + get_rest_start(); }
  const CharT *end_rest() const { return begin_rest() + get_rest_length(); }
  const CharT *begin_mantissa() const {
    if (int_length)
      return begin_int();
    if (is_empty())
      return end();
    assert(has_dot);
    return start + frac_start - 1;
  }
  const CharT *end_mantissa() const {
    if (frac_length)
      return end_frac();
    return end_int();
  }
  const CharT *begin_number() const {
    return start + leading_ws;
  }
  const CharT *end_number() const {
    return begin_rest() - trailing_ws;
  }

  /// \brief Range specified by pair of iterators.
  struct CharRange {
    typedef const CharT *iterator;
    typedef const CharT *const_iterator;

    const CharT *start;
    const CharT *finish;

    CharRange() : start(nullptr), finish(nullptr) {}
    CharRange(const CharT *s, const CharT *f) : start(s), finish(f) {}

    bool empty() const { return start == finish; }
    unsigned size() const { return finish - start; }
    iterator begin() const { return start; }
    iterator end() const { return finish; }
  };

  // Get ranges corresponding to different parts of recognized number.

  CharRange prefix_part() const { return CharRange(begin_prefix(), end_prefix()); }
  CharRange int_part() const { return CharRange(begin_int(), end_int()); }
  CharRange frac_part() const { return CharRange(begin_frac(), end_frac()); }
  CharRange exp_part() const { return CharRange(begin_exp(), end_exp()); }
  CharRange rest_part() const { return CharRange(begin_rest(), end_rest()); }
  CharRange mantissa_part() const {
    return CharRange(begin_mantissa(), end_mantissa());
  }
  CharRange number_text() const {
    return CharRange(begin_number(), end_number());
  }

  std::tuple<const CharT*, unsigned> get_prefix() const {
    return std::tuple<const CharT*, unsigned>(begin_prefix(), get_prefix_length());
  }
  std::tuple<const CharT*, unsigned> get_int() const {
    return std::tuple<const CharT*, unsigned>(begin_int(), int_length);
  }
  std::tuple<const CharT*, unsigned> get_frac() const {
    return std::tuple<const CharT*, unsigned>(begin_frac(), frac_length);
  }
  std::tuple<const CharT*, unsigned> get_exp() const {
    return std::tuple<const CharT*, unsigned>(begin_exp(), exp_length);
  }
  std::tuple<const CharT*, unsigned> get_rest() const {
    return std::tuple<const CharT*, unsigned>(begin_rest(), get_rest_length());
  }
  std::tuple<const CharT*, unsigned> get_mantissa() const {
    return std::tuple<const CharT*, unsigned>(begin_mantissa(),
                                              get_mantissa_length());
  }
  std::tuple<const CharT*, unsigned> get_number() const {
    return std::tuple<const CharT*, unsigned>(begin_number(),
                                              get_number_length());
  }

  NumberRecognizer &recognize(const CharT *str) {
    init(str);
    return recognize();
  }

  NumberRecognizer &recognize(const CharT *str, unsigned len) {
    init(str, len);
    return recognize();
  }

  NumberRecognizer &recognize(const CharT *str, unsigned len, unsigned b) {
    init(str, len);
    set_base(b);
    return recognize();
  }

  NumberRecognizer &recognize() {
    if (recognized())
      return *this;

    const CharT *end = start + length;
    const CharT *cursor = start;

    // Skip leading spaces.
    while (cursor != end && std::isspace(TraitT::to_int_type(*cursor)))
      ++cursor;
    leading_ws = cursor - start;
    int_start = frac_start = exp_start = rest_start = leading_ws;
    if (cursor == end) {
      status = NaN;
      result = Failure;
      return *this;
    }

    // Recognize sign.
    if (*cursor == '+') {
      sign = Positive;
      ++cursor;
    } else if (*cursor == '-') {
      sign = Negative;
      ++cursor;
    } else
      sign = NoSign;
    if (sign != NoSign && cursor == end) {
      status = NaN;
      result = Failure;
      return *this;
    }

    // Recognize prefix.
    if (*cursor == '0') {
      if (base == 0) {
        // Possible radix indicator
        if (end - cursor > 2) {
          if (cursor[1] == 'x' || cursor[1] == 'X') {
            if (is_allowed_0x() && std::isxdigit(TraitT::to_int_type(cursor[2]))) {
              base = 16;
              cursor += 2;
              has_prefix = true;
            }
          } else if (cursor[1] == 'o' || cursor[1] == 'O') {
            if (is_allowed_0o() && std::isdigit(TraitT::to_int_type(cursor[2])) &&
                cursor[2] != '8' && cursor[2] != '9') {
              base = 8;
              cursor += 2;
              has_prefix = true;
            }
          } else if (cursor[1] == 'q' || cursor[1] == 'Q') {
            if (is_allowed_0q() && std::isdigit(TraitT::to_int_type(cursor[2])) &&
                cursor[2] != '8' && cursor[2] != '9') {
              base = 8;
              cursor += 2;
              has_prefix = true;
            }
          } else if ((cursor[1] == 'b' || cursor[1] == 'B')) {
            if (is_allowed_0b() && (cursor[2] == '0' || cursor[2] == '1')) {
              base = 2;
              cursor += 2;
              has_prefix = true;
            }
          }
        }
        if (base == 0 && is_allowed_0())
          base = 8;
      }

      // Skip leading zeros of integer part.
      while (*cursor == '0' && cursor + 1 != end &&
             std::isdigit(TraitT::to_int_type(cursor[1]))) ++cursor;
    }
    if (base == 0)
      base = 10;

    // Collect digits of integer part.
    int_start = frac_start = exp_start = rest_start = (cursor - start);
    const CharT *int_begin = cursor;
    while (cursor != end) {
      typename TraitT::int_type ch = TraitT::to_int_type(*cursor);
      if (!check_digit(ch))
        break;
      ++cursor;
    }
    if (cursor != int_begin) {
      int_length = cursor - int_begin;
      frac_start = exp_start = rest_start = cursor - start;
    }

    if (cursor == end) {
      result = Success;
      return *this;
    }

    // If base is no 10, no other parts may present.
    if (base != 10 || !is_allowed_float()) {
      if (int_length)
        result = Partial;
      else {
        result = Failure;
        status = NaN;
      }
      return *this;
    }

    // if radix was not specified, we may see decimal point here.
    if (*cursor == '.') {
      has_dot = true;
      ++cursor;
      frac_start = exp_start = rest_start = cursor - start;
    }

    // Collect fractional part.
    if (has_dot) {
      const CharT *frac_begin = cursor;
      while (cursor != end) {
        typename TraitT::int_type ch = TraitT::to_int_type(*cursor);
        if (!std::isdigit(ch))
          break;
        ++cursor;
      }

      // Skip trailing zeros.
      const CharT *frac_end = cursor;
      while (frac_end != frac_begin && frac_end[-1] == CharT('0'))
        --frac_end;
      if (frac_end == frac_begin && int_length == 0 && cursor != frac_end)
        frac_length = 1;
      else
        frac_length = frac_end - frac_begin;
    }

    // If both integer and fractional parts absent, this is not a number.
    if (int_length == 0 && frac_length == 0) {
      rest_start = 0;
      result = Failure;
      status = NaN;
      return *this;
    }

    exp_start = rest_start = cursor - start;
    if (cursor == end) {
      result = Success;
      return *this;
    }

    // Exponential part.
    if (end - cursor < 2) {
      result = Partial;
      return *this;
    }
    if (*cursor == CharT('e') || *cursor == CharT('E')) {
      // Optional sign.
      typename TraitT::int_type ch = TraitT::to_int_type(cursor[1]);
      if ((ch == CharT('+') || ch == CharT('-')) && (end - cursor >= 2)) {
        if (std::isdigit(TraitT::to_int_type(cursor[2]))) {
          if (ch == CharT('+'))
            exp_sign = Positive;
          else if (ch == CharT('-'))
            exp_sign = Negative;
          else
            exp_sign = NoSign;
          cursor += 2;
        } else {
          result = Partial;
          return *this;
        }
      } else {
        // At least one digit must present.
        if (!std::isdigit(TraitT::to_int_type(cursor[1]))) {
          result = Partial;
          return *this;
        }
        ++cursor;
      }
      // Skip leading zeros.
      while (cursor != end && *cursor == CharT('0')) {
        ++exp_leading_zeros;
        ++cursor;
      }
      if (cursor == end) {
        exp_start = (cursor - start) - 1;
        --exp_leading_zeros;
        exp_length = 1;
        rest_start = length;
        result = Success;
        return *this;
      }
      if (!std::isdigit(TraitT::to_int_type(*cursor))) {
        --cursor;
        --exp_leading_zeros;
      }
      exp_start = cursor - start;
      // Collect digits of exponent.
      while (cursor != end) {
        if (!std::isdigit(TraitT::to_int_type(*cursor)))
          break;
        ++cursor;
      }
      exp_length = cursor - start - exp_start;
    }

    // Skip trailing spaces.
    while (cursor != end && std::isspace(TraitT::to_int_type(*cursor))) {
      ++trailing_ws;
      ++cursor;
    }
    rest_start = cursor - start;

    // Recognition is finished.
    if (cursor == end) {
      result = Success;
    } else {
      rest_start = cursor - start;
      result = Partial;
    }
    return *this;
  }

  template<typename NumType>
  Status read(NumType &value) {
    if (!recognized())
      recognize();

    // Process recognition failure.
    if (get_result() == Failure) {
      value = 0;
      return static_cast<Status>(status = NaN);
    }

    // If the recognized number contains only integer part, convert
    // corresponding sequence of digits. It works if NumType is a float type
    // as well.
    if (!is_float()) {
      Status st = convert_int(value, get_int(), get_base());
      set_sign(value, is_negative(), st);
      return st;
    }

    // We have recognized a floating number. Check exponent first, it must not
    // be too large.
    if (get_exp_length() > 3) {
      // Strictly speaking, it is not true. Adding digits to integer of
      // fractional part, it is possible to compensate exponent. It is however
      // unlikely that a user would write several dozens of digits.
      if (is_exp_negative()) {
        value = 0;
        return static_cast<Status>(status = DoubleUnderflow);
      } else {
        if (is_negative())
          value = extra::number_property<NumType>::lowest();
        else
          value = std::numeric_limits<NumType>::max();
        return static_cast<Status>(status = DoubleOverflow);
      }
    }

    int expval;
    if (exp_length) {
      Status st = convert_int(expval, get_exp());
      assert(st == OK); (void)st;
    } else {
      expval = 0;
    }

    // If NumType is an integer type, make conversion to integer.
    if (std::numeric_limits<NumType>::is_integer) {
      // Exponent can move digits from fractional part to integer and back.
      // TODO: make conversion to integer here, without call to strtod.
      if (is_exp_negative()) {
        if (get_int_length() < (unsigned)expval) {
          value = 0;
          return static_cast<Status>(status = DoubleToInt);
        }
        status = convert_int(value, begin_int(), get_int_length());
        return static_cast<Status>(status);
      }
    }

    // Textual representation of a float value is converted to float data type.

    // Filter out some cases based on exponent value.
    if (is_exp_negative())
      expval = -expval;
    if (!std::numeric_limits<NumType>::is_integer) {
      if (expval > std::numeric_limits<NumType>::max_exponent10) {
        value = std::numeric_limits<NumType>::max();
        return static_cast<Status>(status = DoubleOverflow);
      } else if (expval < std::numeric_limits<NumType>::min_exponent10) {
        if (!std::numeric_limits<NumType>::has_denorm)
          return static_cast<Status>(status = DoubleUnderflow);
        if (expval < extra::number_property<NumType>::denorm_min_exponent10) {
          value = 0;
          return static_cast<Status>(status = DoubleUnderflow);
        }
      }
    }

    // Convert text to number.
    double dvalue = strto<double>(begin_number(), get_number_length());
    auto res = convert_to<NumType>(dvalue);
    value = res.value();
    return static_cast<Status>(status = res.status());
  }

  template<typename NumType>
  NumType to() {
    NumType value;
    read(value);
    return value;
  }

  private:

  bool check_digit(typename TraitT::int_type ch) {
    if (base == 2) {
      if (ch == CharT('0') || ch == CharT('1'))
        return true;
    } else if (base == 8) {
      if (ch >= CharT('0') && ch <= CharT('7'))
        return true;
    } else if (base == 10) {
      if (std::isdigit(ch))
        return true;
    } else if (base == 16) {
      if (std::isxdigit(ch))
        return true;
    } else {
      assert(base == 0);
      if (std::isdigit(ch))
        return true;
    }
    return false;
  }

  template<typename NumType>
  void set_sign(NumType &value, bool is_neg, Status &st) {
    internal::SetSign<
      NumType,
      std::numeric_limits<NumType>::is_integer,
      std::numeric_limits<NumType>::is_signed
    >::set(value, is_neg, st);
    status = st;
  }
};

}
#endif
