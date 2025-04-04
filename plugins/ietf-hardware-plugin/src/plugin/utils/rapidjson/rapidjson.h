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

#ifndef RAPIDJSON_RAPIDJSON_H_
#define RAPIDJSON_RAPIDJSON_H_

/*!ile rapidjson.h
    rief common definitions and configuration
    
    \see RAPIDJSON_CONFIG
 */

/*! \defgroup RAPIDJSON_CONFIG RapidJSON configuration
    rief Configuration macros for library features

    Some RapidJSON features are configurable to adapt the library to a wide
    variety of platforms, environments and usage scenarios.  Most of the
    features can be configured in terms of overridden or predefined
    preprocessor macros at compile-time.

    Some additional customization is available in the ef RAPIDJSON_ERRORS APIs.

    
ote These macros should be given on the compiler command-line
          (where applicable)  to avoid inconsistent values when compiling
          different translation units of a single application.
 */

#include <cstdlib>  // malloc(), realloc(), free(), size_t
#include <cstring>  // memset(), memcpy(), memmove(), memcmp()

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_VERSION_STRING
//
// ALWAYS synchronize the following 3 macros with corresponding variables in /CMakeLists.txt.
//

//!@cond RAPIDJSON_HIDDEN_FROM_DOXYGEN
// token stringification
#define RAPIDJSON_STRINGIFY(x) RAPIDJSON_DO_STRINGIFY(x)
#define RAPIDJSON_DO_STRINGIFY(x) #x

// token concatenation
#define RAPIDJSON_JOIN(X, Y) RAPIDJSON_DO_JOIN(X, Y)
#define RAPIDJSON_DO_JOIN(X, Y) RAPIDJSON_DO_JOIN2(X, Y)
#define RAPIDJSON_DO_JOIN2(X, Y) X##Y
//!@endcond

/*! \def RAPIDJSON_MAJOR_VERSION
    \ingroup RAPIDJSON_CONFIG
    rief Major version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_MINOR_VERSION
    \ingroup RAPIDJSON_CONFIG
    rief Minor version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_PATCH_VERSION
    \ingroup RAPIDJSON_CONFIG
    rief Patch version of RapidJSON in integer.
*/
/*! \def RAPIDJSON_VERSION_STRING
    \ingroup RAPIDJSON_CONFIG
    rief Version of RapidJSON in "<major>.<minor>.<patch>" string format.
*/
#define RAPIDJSON_MAJOR_VERSION 1
#define RAPIDJSON_MINOR_VERSION 1
#define RAPIDJSON_PATCH_VERSION 0
#define RAPIDJSON_VERSION_STRING \
    RAPIDJSON_STRINGIFY(RAPIDJSON_MAJOR_VERSION.RAPIDJSON_MINOR_VERSION.RAPIDJSON_PATCH_VERSION)

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_NAMESPACE_(BEGIN|END)
/*! \def RAPIDJSON_NAMESPACE
    \ingroup RAPIDJSON_CONFIG
    rief   provide custom rapidjson namespace

    In order to avoid symbol clashes and/or "One Definition Rule" errors
    between multiple inclusions of (different versions of) RapidJSON in
    a single binary, users can customize the name of the main RapidJSON
    namespace.

    In case of a single nesting level, defining 