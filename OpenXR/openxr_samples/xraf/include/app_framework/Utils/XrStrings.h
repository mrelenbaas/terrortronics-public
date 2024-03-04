// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include <openxr/openxr.h>

namespace ml {
/*! \brief returns a string value for the given state. */
inline const char *GetStateStr(XrSessionState state) {
  switch (state) {
    case XR_SESSION_STATE_UNKNOWN:
      return "Unknown";
    case XR_SESSION_STATE_IDLE:
      return "Idle";
    case XR_SESSION_STATE_READY:
      return "Ready";
    case XR_SESSION_STATE_SYNCHRONIZED:
      return "Synchronized";
    case XR_SESSION_STATE_VISIBLE:
      return "Visible";
    case XR_SESSION_STATE_FOCUSED:
      return "Focused";
    case XR_SESSION_STATE_STOPPING:
      return "Stoping";
    case XR_SESSION_STATE_LOSS_PENDING:
      return "LossPending";
    case XR_SESSION_STATE_EXITING:
      return "Exiting";
    default:
      return "Unknown XR_SESSION_STATE";
  }
}

}  // namespace ml