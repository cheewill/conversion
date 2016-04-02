//===--- numbers.h ----------------------------------------------*- C++ -*-===//
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
/// Miscellaneous converion tools for numeric data.
///
//===----------------------------------------------------------------------===//
#ifndef EXTRA_NUMBERS_H_
#define EXTRA_NUMBERS_H_

//------ Dependencies ----------------------------------------------------------
#include <memory>
#include <limits>
#include <type_traits>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <wchar.h>
//------------------------------------------------------------------------------


namespace conversion {


//------------------------------------------------------------------------------
// Negation.
//------------------------------------------------------------------------------

namespace internal {

template<typename NumType, bool Signed>
class NegationImpl;

template<typename NumType>
class NegationImpl<NumType, true> {
public:
  static void apply(NumType &x) { x = -x; }
  static NumType get(const NumType &x) { return -x; }
};

}


//------------------------------------------------------------------------------
/// \brief Generic negation of number values.
///
/// Allows to change sign only if it has sense for given type. Negation of
/// unsigned values causes compile-time errors.
//------------------------------------------------------------------------------
template<typename NumType>
class Negation {
public:
  static void apply(NumType &x) {
    internal::NegationImpl<NumType,
                           std::numeric_limits<NumType>::is_signed>::apply(x);
  }
  static NumType get(const NumType &x) {
    return internal::NegationImpl<NumType,
                               std::numeric_limits<NumType>::is_signed>::get(x);
  }
};

}
#endif