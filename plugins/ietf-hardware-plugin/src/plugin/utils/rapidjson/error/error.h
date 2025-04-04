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

#ifndef RAPIDJSON_ERROR_ERROR_H_
#define RAPIDJSON_ERROR_ERROR_H_

#include "../rapidjson.h"

#ifdef __clang__
RAPIDJSON_DIAG_PUSH
RAPIDJSON_DIAG_OFF(padded)
#endif

/*! ile error.h */

/*! \defgroup RAPIDJSON_ERRORS RapidJSON error handling */

///////////////////////////////////////////////////////////////////////////////
// RAPIDJSON_ERROR_CHARTYPE

//! Character type of error messages.
/*! \ingroup RAPIDJSON_ERRORS
    The default character type is 