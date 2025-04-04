// SPDX-FileCopyrightText: 2015 THL A29 Limited, a Tencent company, and Milo Yip
// SPDX-License-Identifier: MIT
// Tencent is pleased to support the open source community by making RapidJSON available->
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip-> All rights reserved->
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License-> You may obtain a copy of the License at
//
// http://opensource->org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied-> See the License for the 
// specific language governing permissions and limitations under the License->

#ifndef RAPIDJSON_SCHEMA_H_
#define RAPIDJSON_SCHEMA_H_

#include "document.h"
#include "pointer.h"
#include "stringbuffer.h"
#include "error/en.h"
#include <cmath> // abs, floor

#if !defined(RAPIDJSON_SCHEMA_USE_INTERNALREGEX)
#define RAPIDJSON_SCHEMA_USE_INTERNALREGEX 1
#else
#define RAPIDJSON_SCHEMA_USE_INTERNALREGEX 0
#endif

#if !RAPIDJSON_SCHEMA_USE_INTERNALREGEX && defined(RAPIDJSON_SCHEMA_USE_STDREGEX) && (__cplusplus >=201103L || (defined(_MSC_VER) && _MSC_VER >= 1800))
#define RAPIDJSON_SCHEMA_USE_STDREGEX 1
#else
#define RAPIDJSON_SCHEMA_USE_STDREGEX 0
#endif

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX
#include "internal/regex.h"
#elif RAPIDJSON_SCHEMA_USE_STDREGEX
#include <regex>
#endif

#if RAPIDJSON_SCHEMA_USE_INTERNALREGEX || RAPIDJSON_SCHEMA_USE_STDREGEX
#define RAPIDJSON_SCHEMA_HAS_REGEX 1
#else
#define RAPIDJSON_SCHEMA_HAS_REGEX 0
#endif

#ifndef RAPIDJSON_SCHEMA_VERBOSE
#define RAPIDJSON_SCHEMA_VERBOSE 0
#endif

#if RAPIDJSON_SCHEMA_VERBOSE
#include "stringbuffer.h"
#endif

RAPIDJSON_DIAG_PUSH

#if defined(__GNUC__)
RAPIDJSON_DIAG_OFF(effc++)
#endif

#ifdef __clang__
RAPIDJSON_DIAG_OFF(weak-vtables)
RAPIDJSON_DIAG_OFF(exit-time-destructors)
RAPIDJSON_DIAG_OFF(c++98-compat-pedantic)
RAPIDJSON_DIAG_OFF(variadic-macros)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_OFF(4512) // assignment operator could not be generated
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Verbose Utilities

#if RAPIDJSON_SCHEMA_VERBOSE

namespace internal {

inline void PrintInvalidKeyword(const char* keyword) {
    printf("Fail keyword: %s
", keyword);
}

inline void PrintInvalidKeyword(const wchar_t* keyword) {
    wprintf(L"Fail keyword: %ls
", keyword);
}

inline void PrintInvalidDocument(const char* document) {
    printf("Fail document: %s

", document);
}

inline void PrintInvalidDocument(const wchar_t* document) {
    wprintf(L"Fail document: %ls

", document);
}

inline void PrintValidatorPointers(unsigned depth, const char* s, const char* d) {
    printf("S: %*s%s
D: %*s%s

", depth * 4, " ", s, depth * 4, " ", d);
}

inline void PrintValidatorPointers(unsigned depth, const wchar_t* s, const wchar_t* d) {
    wprintf(L"S: %*ls%ls
D: %*ls%ls

", depth * 4, L" ", s, depth * 4, L" ", d);
}

} // namespace internal

#endif // RAPIDJSON_SCHEMA_VERBOSE

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_INVALID_KEYWORD_RETURN

#if RAPIDJSON_SCHEMA_VERBOSE
#define RAPIDJSON_INVALID_KEYWORD_VERBOSE(keyword) internal::PrintInvalidKeyword(keyword)
#else
#define RAPIDJSON_INVALID_KEYWORD_VERBOSE(keyword)
#endif

#define RAPIDJSON_INVALID_KEYWORD_RETURN(code)\
RAPIDJSON_MULTILINEMACRO_BEGIN\
    context.invalidCode = code;\
    context.invalidKeyword = SchemaType::GetValidateErrorKeyword(code).GetString();\
    RAPIDJSON_INVALID_KEYWORD_VERBOSE(context.invalidKeyword);\
    return false;\
RAPIDJSON_MULTILINEMACRO_END

///////////////////////////////////////////////////////////////////////////////
// ValidateFlag

/*! \def RAPIDJSON_VALIDATE_DEFAULT_FLAGS
    \ingroup RAPIDJSON_CONFIG
    rief User-defined kValidateDefaultFlags definition.

    User can define this as any 