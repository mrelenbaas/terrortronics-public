#ifndef ML_SYSTEM_NOTIFICATIONS_H_
#define ML_SYSTEM_NOTIFICATIONS_H_ 1

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


#ifndef XR_ML_system_notifications

#define XR_ML_system_notifications 1
#define XR_ML_system_notifications_SPEC_VERSION 1
#define XR_ML_SYSTEM_NOTIFICATIONS_EXTENSION_NAME "XR_ML_system_notifications"
#define XR_TYPE_SYSTEM_NOTIFICATIONS_SET_INFO_ML ((XrStructureType) 1000473000U)
#define XR_TYPE_SYSTEM_NOTIFICATIONS_PROPERTIES_ML ((XrStructureType) 1000473001U)
#define XR_ERROR_SYSTEM_NOTIFICATION_PERMISSION_DENIED_ML ((XrResult) -1000473000U)
#define XR_ERROR_SYSTEM_NOTIFICATION_INCOMPATIBLE_SKU_ML ((XrResult) -1000473001U)
typedef XrFlags64 XrSystemNotificationsCapabilityFlagsML;

// Flag bits for XrSystemNotificationsCapabilityFlagsML
static const XrSystemNotificationsCapabilityFlagsML XR_SYSTEM_NOTIFICATIONS_CAPABILITY_SUPPRESSION_BIT_ML = 0x00000001;

typedef struct XrSystemNotificationsSetInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrBool32                    suppressNotifications;
} XrSystemNotificationsSetInfoML;

typedef struct XrSystemNotificationsPropertiesML {
    XrStructureType                           type;
    void* XR_MAY_ALIAS                        next;
    XrSystemNotificationsCapabilityFlagsML    supportedFeatures;
} XrSystemNotificationsPropertiesML;

typedef XrResult                              (XRAPI_PTR *PFN_xrSetSystemNotificationsML)(XrInstance                            instance, const XrSystemNotificationsSetInfoML* info);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult                              XRAPI_CALL xrSetSystemNotificationsML(
    XrInstance                                  instance,
    const XrSystemNotificationsSetInfoML*       info);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_ML_system_notifications */

#ifdef __cplusplus
}
#endif

#endif
