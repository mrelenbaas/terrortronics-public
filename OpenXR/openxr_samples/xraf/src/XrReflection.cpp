// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#include "../include/app_framework/XrReflection.h"

#include <openxr/openxr_reflection.h>

#define XR_ENUM_CASE_STR(name, val) \
  case name:                        \
    return #name;
#define XR_ENUM_STR(enumType)                                               \
  const char* ml::XrEnumStr(enumType e) {                                   \
    switch (e) {                                                            \
      XR_LIST_ENUM_##enumType(XR_ENUM_CASE_STR) default : return "Unknown"; \
    }                                                                       \
  }

XR_ENUM_STR(XrResult);
XR_ENUM_STR(XrReferenceSpaceType);
XR_ENUM_STR(XrSessionState);
