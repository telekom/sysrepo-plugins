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

#ifndef RAPIDJSON_WRITER_H_
#define RAPIDJSON_WRITER_H_

#include "stream.h"
#include "internal/clzll.h"
#include "internal/meta.h"
#include "internal/stack.h"
#include "internal/strfunc.h"
#include "internal/dtoa.h"
#include "internal/itoa.h"
#include "stringbuffer.h"
#include <new>      // placement new

#if defined(RAPIDJSON_SIMD) && defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(_BitScanForward)
#endif
#ifdef RAPIDJSON_SSE42
#include <nmmintrin.h>
#elif defined(RAPIDJSON_SSE2)
#include <emmintrin.h>
#elif defined(RAPIDJSON_NEON)
#include <arm_neon.h>
#endif

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
RAPIDJSON_DIAG_OFF(unreachable-code)
RAPIDJSON_DIAG_OFF(c++98-compat)
#elif defined(_MSC_VER)
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(4127) // conditional expression is constant
#endif

RAPIDJSON_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// WriteFlag

/*! \def RAPIDJSON_WRITE_DEFAULT_FLAGS 
    \ingroup RAPIDJSON_CONFIG
    rief User-defined kWriteDefaultFlags definition.

    User can define this as any 