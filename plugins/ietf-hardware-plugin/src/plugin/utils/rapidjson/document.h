// SPDX-FileCopyrightText: 2015 THL A29 Limited, a Tencent company, and Milo Yip
// SPDX-License-Identifier: MIT
// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#ifndef RAPIDJSON_DOCUMENT_H_
#define RAPIDJSON_DOCUMENT_H_

/*! ile document.h */

#include "reader.h"
#include "internal/meta.h"
#include "internal/strfunc.h"
#include "memorystream.h"
#include "encodedstream.h"
#include <new>      // placement new
#include <limits>
#ifdef __cpp_lib_three_way_comparison
#include <compare>
#endif

RAPIDJSON_DIAG_PUSH
#ifdef __clang__
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(switch-enum)
RAPIDJSON_DIAG_OFF(c++98-compat)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_OFF(4127) // conditional expression is constant
RAPIDJSON_DIAG_OFF(4244) // conversion from kXxxFlags to 'uint16_t', possible loss of data
#endif

#ifdef __GNUC__
RAPIDJSON_DIAG_OFF(effc++)
#endif // __GNUC__

#ifndef RAPIDJSON_NOMEMBERITERATORCLASS
#include <iterator> // std::random_access_iterator_tag
#endif

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
#include <utility> // std::move
#endif

RAPIDJSON_NAMESPACE_BEGIN

// Forward declaration.
template <typename Encoding, typename Allocator>
class GenericValue;

template <typename Encoding, typename Allocator, typename StackAllocator>
class GenericDocument;

/*! \def RAPIDJSON_DEFAULT_ALLOCATOR
    \ingroup RAPIDJSON_CONFIG
    rief Allows to choose default allocator.

    User can define this to use CrtAllocator or MemoryPoolAllocator.
*/
#ifndef RAPIDJSON_DEFAULT_ALLOCATOR
#define RAPIDJSON_DEFAULT_ALLOCATOR MemoryPoolAllocator<CrtAllocator>
#endif

/*! \def RAPIDJSON_DEFAULT_STACK_ALLOCATOR
    \ingroup RAPIDJSON_CONFIG
    rief Allows to choose default stack allocator for Document.

    User can define this to use CrtAllocator or MemoryPoolAllocator.
*/
#ifndef RAPIDJSON_DEFAULT_STACK_ALLOCATOR
#define RAPIDJSON_DEFAULT_STACK_ALLOCATOR CrtAllocator
#endif

/*! \def RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY
    \ingroup RAPIDJSON_CONFIG
    rief User defined kDefaultObjectCapacity value.

    User can define this as any natural number.
*/
#ifndef RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY
// number of objects that rapidjson::Value allocates memory for by default
#define RAPIDJSON_VALUE_DEFAULT_OBJECT_CAPACITY 16
#endif

/*! \def RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY
    \ingroup RAPIDJSON_CONFIG
    rief User defined kDefaultArrayCapacity value.

    User can define this as any natural number.
*/
#ifndef RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY
// number of array elements that rapidjson::Value allocates memory for by default
#define RAPIDJSON_VALUE_DEFAULT_ARRAY_CAPACITY 16
#endif

//! Name-value pair in a JSON object value.
/*!
    This class was internal to GenericValue. It used to be a inner struct.
    But a compiler (IBM XL C/C++ for AIX) have reported to have problem with that so it moved as a namespace scope struct.
    https://code.google.com/p/rapidjson/issues/detail?id=64
*/
template <typename Encoding, typename Allocator> 
class GenericMember {
public:
    GenericValue<Encoding, Allocator> name;     //!< name of member (must be a string)
    GenericValue<Encoding, Allocator> value;    //!< value of member.

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
    //! Move constructor in C++11
    GenericMember(GenericMember&& rhs) RAPIDJSON_NOEXCEPT
        : name(std::move(rhs.name)),
          value(std::move(rhs.value))
    {
    }

    //! Move assignment in C++11
    GenericMember& operator=(GenericMember&& rhs) RAPIDJSON_NOEXCEPT {
        return *this = static_cast<GenericMember&>(rhs);
    }
#endif

    //! Assignment with move semantics.
    /*! \param rhs Source of the assignment. Its name and value will become a null value after assignment.
    */
    GenericMember& operator=(GenericMember& rhs) RAPIDJSON_NOEXCEPT {
        if (RAPIDJSON_LIKELY(this != &rhs)) {
            name = rhs.name;
            value = rhs.value;
        }
        return *this;
    }

    // swap() for std::sort() and other potential use in STL.
    friend inline void swap(GenericMember& a, GenericMember& b) RAPIDJSON_NOEXCEPT {
        a.name.Swap(b.name);
        a.value.Swap(b.value);
    }

private:
    //! Copy constructor is not permitted.
    GenericMember(const GenericMember& rhs);
};

///////////////////////////////////////////////////////////////////////////////
// GenericMemberIterator

#ifndef RAPIDJSON_NOMEMBERITERATORCLASS

//! (Constant) member iterator for a JSON object value
/*!
    	param Const Is this a constant iterator?
    	param Encoding    Encoding of the value. (Even non-string values need to have the same encoding in a document)
    	param Allocator   Allocator type for allocating memory of object, array and string.

    This class implements a Random Access Iterator for GenericMember elements
    of a GenericValue, see ISO/IEC 14882:2003(E) C++ standard, 24.1 [lib.iterator.requirements].

    
ote This iterator implementation is mainly intended to avoid implicit
        conversions from iterator values to 