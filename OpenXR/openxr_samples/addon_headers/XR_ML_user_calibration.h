#ifndef ML_USER_CALIBRATION_H_
#define ML_USER_CALIBRATION_H_ 1

/*
** Copyright 2017-2023 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/


#ifdef __cplusplus
extern "C" {
#endif


#ifndef XR_ML_user_calibration

#define XR_ML_user_calibration 1
#define XR_ML_user_calibration_SPEC_VERSION 1
#define XR_ML_USER_CALIBRATION_EXTENSION_NAME "XR_ML_user_calibration"
#define XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML ((XrStructureType) 1000472000U)
#define XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML ((XrStructureType) 1000472001U)
#define XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML ((XrStructureType) 1000472002U)

typedef enum XrHeadsetFitStatusML {
    XR_HEADSET_FIT_STATUS_UNKNOWN_ML = 0,
    XR_HEADSET_FIT_STATUS_NOT_WORN_ML = 1,
    XR_HEADSET_FIT_STATUS_GOOD_FIT_ML = 2,
    XR_HEADSET_FIT_STATUS_BAD_FIT_ML = 3,
    XR_HEADSET_FIT_STATUS_MAX_ENUM_ML = 0x7FFFFFFF
} XrHeadsetFitStatusML;

typedef enum XrEyeCalibrationStatusML {
    XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML = 0,
    XR_EYE_CALIBRATION_STATUS_NONE_ML = 1,
    XR_EYE_CALIBRATION_STATUS_COARSE_ML = 2,
    XR_EYE_CALIBRATION_STATUS_FINE_ML = 3,
    XR_EYE_CALIBRATION_STATUS_MAX_ENUM_ML = 0x7FFFFFFF
} XrEyeCalibrationStatusML;
typedef struct XrEventDataHeadsetFitChangedML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrHeadsetFitStatusML        status;
    XrTime                      time;
} XrEventDataHeadsetFitChangedML;

typedef struct XrEventDataEyeCalibrationChangedML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrEyeCalibrationStatusML    status;
} XrEventDataEyeCalibrationChangedML;

typedef struct XrUserCalibrationEnableEventsInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrBool32                    enabled;
} XrUserCalibrationEnableEventsInfoML;

typedef XrResult (XRAPI_PTR *PFN_xrEnableUserCalibrationEventsML)(XrInstance                                       instance, const XrUserCalibrationEnableEventsInfoML*            enableInfo);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrEnableUserCalibrationEventsML(
    XrInstance                                  instance,
    const XrUserCalibrationEnableEventsInfoML*  enableInfo);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_ML_user_calibration */

#ifdef __cplusplus
}
#endif

#endif
