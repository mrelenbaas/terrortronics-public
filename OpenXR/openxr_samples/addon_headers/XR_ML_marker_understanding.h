#ifndef ML_MARKER_UNDERSTANDING_H_
#define ML_MARKER_UNDERSTANDING_H_ 1

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


#ifndef XR_ML_marker_understanding

#define XR_ML_marker_understanding 1
XR_DEFINE_ATOM(XrMarkerML)
XR_DEFINE_HANDLE(XrMarkerDetectorML)
#define XR_ML_marker_understanding_SPEC_VERSION 1
#define XR_ML_MARKER_UNDERSTANDING_EXTENSION_NAME "XR_ML_marker_understanding"
#define XR_OBJECT_TYPE_MARKER_DETECTOR_ML ((XrObjectType) 1000138000U)
#define XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML ((XrStructureType) 1000138000U)
#define XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML ((XrStructureType) 1000138001U)
#define XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML ((XrStructureType) 1000138002U)
#define XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML ((XrStructureType) 1000138003U)
#define XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML ((XrStructureType) 1000138004U)
#define XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML ((XrStructureType) 1000138005U)
#define XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML ((XrStructureType) 1000138006U)
#define XR_TYPE_MARKER_DETECTOR_STATE_ML  ((XrStructureType) 1000138007U)
#define XR_TYPE_MARKER_SPACE_CREATE_INFO_ML ((XrStructureType) 1000138008U)
#define XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML ((XrResult) -1000138000U)
#define XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML ((XrResult) -1000138001U)
#define XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML ((XrResult) -1000138002U)
#define XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML ((XrResult) -1000138003U)
#define XR_ERROR_MARKER_INVALID_ML        ((XrResult) -1000138004U)

typedef enum XrMarkerDetectorProfileML {
    XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML = 0,
    XR_MARKER_DETECTOR_PROFILE_SPEED_ML = 1,
    XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML = 2,
    XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML = 3,
    XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML = 4,
    XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML = 5,
    XR_MARKER_DETECTOR_PROFILE_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorProfileML;

typedef enum XrMarkerTypeML {
    XR_MARKER_TYPE_ARUCO_ML = 0,
    XR_MARKER_TYPE_APRIL_TAG_ML = 1,
    XR_MARKER_TYPE_QR_ML = 2,
    XR_MARKER_TYPE_EAN_13_ML = 3,
    XR_MARKER_TYPE_UPC_A_ML = 4,
    XR_MARKER_TYPE_CODE_128_ML = 5,
    XR_MARKER_TYPE_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerTypeML;

typedef enum XrMarkerArucoDictML {
    XR_MARKER_ARUCO_DICT_4X4_50_ML = 0,
    XR_MARKER_ARUCO_DICT_4X4_100_ML = 1,
    XR_MARKER_ARUCO_DICT_4X4_250_ML = 2,
    XR_MARKER_ARUCO_DICT_4X4_1000_ML = 3,
    XR_MARKER_ARUCO_DICT_5X5_50_ML = 4,
    XR_MARKER_ARUCO_DICT_5X5_100_ML = 5,
    XR_MARKER_ARUCO_DICT_5X5_250_ML = 6,
    XR_MARKER_ARUCO_DICT_5X5_1000_ML = 7,
    XR_MARKER_ARUCO_DICT_6X6_50_ML = 8,
    XR_MARKER_ARUCO_DICT_6X6_100_ML = 9,
    XR_MARKER_ARUCO_DICT_6X6_250_ML = 10,
    XR_MARKER_ARUCO_DICT_6X6_1000_ML = 11,
    XR_MARKER_ARUCO_DICT_7X7_50_ML = 12,
    XR_MARKER_ARUCO_DICT_7X7_100_ML = 13,
    XR_MARKER_ARUCO_DICT_7X7_250_ML = 14,
    XR_MARKER_ARUCO_DICT_7X7_1000_ML = 15,
    XR_MARKER_ARUCO_DICT_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerArucoDictML;

typedef enum XrMarkerAprilTagDictML {
    XR_MARKER_APRIL_TAG_DICT_16H5_ML = 0,
    XR_MARKER_APRIL_TAG_DICT_25H9_ML = 1,
    XR_MARKER_APRIL_TAG_DICT_36H10_ML = 2,
    XR_MARKER_APRIL_TAG_DICT_36H11_ML = 3,
    XR_MARKER_APRIL_TAG_DICT_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerAprilTagDictML;

typedef enum XrMarkerDetectorFpsML {
    XR_MARKER_DETECTOR_FPS_LOW_ML = 0,
    XR_MARKER_DETECTOR_FPS_MEDIUM_ML = 1,
    XR_MARKER_DETECTOR_FPS_HIGH_ML = 2,
    XR_MARKER_DETECTOR_FPS_MAX_ML = 3,
    XR_MARKER_DETECTOR_FPS_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorFpsML;

typedef enum XrMarkerDetectorResolutionML {
    XR_MARKER_DETECTOR_RESOLUTION_LOW_ML = 0,
    XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML = 1,
    XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML = 2,
    XR_MARKER_DETECTOR_RESOLUTION_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorResolutionML;

typedef enum XrMarkerDetectorCameraML {
    XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML = 0,
    XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML = 1,
    XR_MARKER_DETECTOR_CAMERA_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorCameraML;

typedef enum XrMarkerDetectorCornerRefineMethodML {
    XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML = 0,
    XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML = 1,
    XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML = 2,
    XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML = 3,
    XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorCornerRefineMethodML;

typedef enum XrMarkerDetectorFullAnalysisIntervalML {
    XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML = 0,
    XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML = 1,
    XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML = 2,
    XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML = 3,
    XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorFullAnalysisIntervalML;

typedef enum XrMarkerDetectorStatusML {
    XR_MARKER_DETECTOR_STATUS_PENDING_ML = 0,
    XR_MARKER_DETECTOR_STATUS_READY_ML = 1,
    XR_MARKER_DETECTOR_STATUS_ERROR_ML = 2,
    XR_MARKER_DETECTOR_STATUS_MAX_ENUM_ML = 0x7FFFFFFF
} XrMarkerDetectorStatusML;
typedef struct XrSystemMarkerUnderstandingPropertiesML {
    XrStructureType       type;
    void* XR_MAY_ALIAS    next;
    XrBool32              supportsMarkerUnderstanding;
} XrSystemMarkerUnderstandingPropertiesML;

typedef struct XrMarkerDetectorCreateInfoML {
    XrStructureType              type;
    const void* XR_MAY_ALIAS     next;
    XrMarkerDetectorProfileML    profile;
    XrMarkerTypeML               markerType;
} XrMarkerDetectorCreateInfoML;

// XrMarkerDetectorArucoInfoML extends XrMarkerDetectorCreateInfoML
typedef struct XrMarkerDetectorArucoInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrMarkerArucoDictML         arucoDict;
} XrMarkerDetectorArucoInfoML;

// XrMarkerDetectorSizeInfoML extends XrMarkerDetectorCreateInfoML
typedef struct XrMarkerDetectorSizeInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    float                       markerLength;
} XrMarkerDetectorSizeInfoML;

// XrMarkerDetectorAprilTagInfoML extends XrMarkerDetectorCreateInfoML
typedef struct XrMarkerDetectorAprilTagInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrMarkerAprilTagDictML      aprilTagDict;
} XrMarkerDetectorAprilTagInfoML;

// XrMarkerDetectorCustomProfileInfoML extends XrMarkerDetectorCreateInfoML
typedef struct XrMarkerDetectorCustomProfileInfoML {
    XrStructureType                           type;
    const void* XR_MAY_ALIAS                  next;
    XrMarkerDetectorFpsML                     fpsHint;
    XrMarkerDetectorResolutionML              resolutionHint;
    XrMarkerDetectorCameraML                  cameraHint;
    XrMarkerDetectorCornerRefineMethodML      cornerRefineMethod;
    XrBool32                                  useEdgeRefinement;
    XrMarkerDetectorFullAnalysisIntervalML    fullAnalysisIntervalHint;
} XrMarkerDetectorCustomProfileInfoML;

typedef struct XrMarkerDetectorSnapshotInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
} XrMarkerDetectorSnapshotInfoML;

typedef struct XrMarkerDetectorStateML {
    XrStructureType             type;
    void* XR_MAY_ALIAS          next;
    XrMarkerDetectorStatusML    state;
} XrMarkerDetectorStateML;

typedef struct XrMarkerSpaceCreateInfoML {
    XrStructureType             type;
    const void* XR_MAY_ALIAS    next;
    XrMarkerDetectorML          markerDetector;
    XrMarkerML                  marker;
    XrPosef                     poseInMarkerSpace;
} XrMarkerSpaceCreateInfoML;

typedef XrResult (XRAPI_PTR *PFN_xrCreateMarkerDetectorML)(XrSession session, const XrMarkerDetectorCreateInfoML* createInfo, XrMarkerDetectorML* markerDetector);
typedef XrResult (XRAPI_PTR *PFN_xrDestroyMarkerDetectorML)(XrMarkerDetectorML markerDetector);
typedef XrResult (XRAPI_PTR *PFN_xrSnapshotMarkerDetectorML)(XrMarkerDetectorML markerDetector, XrMarkerDetectorSnapshotInfoML* snapshotInfo);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkerDetectorStateML)(XrMarkerDetectorML markerDetector, XrMarkerDetectorStateML* state);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkersML)(XrMarkerDetectorML markerDetector, uint32_t markerCapacityInput, uint32_t* markerCountOutput, XrMarkerML* markers);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkerReprojectionErrorML)(XrMarkerDetectorML markerDetector, XrMarkerML marker, float* reprojectionErrorMeters);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkerLengthML)(XrMarkerDetectorML markerDetector, XrMarkerML marker, float* meters);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkerNumberML)(XrMarkerDetectorML markerDetector, XrMarkerML marker, uint64_t* number);
typedef XrResult (XRAPI_PTR *PFN_xrGetMarkerStringML)(XrMarkerDetectorML markerDetector, XrMarkerML marker, uint32_t bufferCapacityInput, uint32_t* bufferCountOutput, char* buffer);
typedef XrResult (XRAPI_PTR *PFN_xrCreateMarkerSpaceML)(XrSession session, const XrMarkerSpaceCreateInfoML* createInfo, XrSpace* space);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateMarkerDetectorML(
    XrSession                                   session,
    const XrMarkerDetectorCreateInfoML*         createInfo,
    XrMarkerDetectorML*                         markerDetector);

XRAPI_ATTR XrResult XRAPI_CALL xrDestroyMarkerDetectorML(
    XrMarkerDetectorML                          markerDetector);

XRAPI_ATTR XrResult XRAPI_CALL xrSnapshotMarkerDetectorML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerDetectorSnapshotInfoML*             snapshotInfo);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkerDetectorStateML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerDetectorStateML*                    state);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkersML(
    XrMarkerDetectorML                          markerDetector,
    uint32_t                                    markerCapacityInput,
    uint32_t*                                   markerCountOutput,
    XrMarkerML*                                 markers);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkerReprojectionErrorML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerML                                  marker,
    float*                                      reprojectionErrorMeters);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkerLengthML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerML                                  marker,
    float*                                      meters);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkerNumberML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerML                                  marker,
    uint64_t*                                   number);

XRAPI_ATTR XrResult XRAPI_CALL xrGetMarkerStringML(
    XrMarkerDetectorML                          markerDetector,
    XrMarkerML                                  marker,
    uint32_t                                    bufferCapacityInput,
    uint32_t*                                   bufferCountOutput,
    char*                                       buffer);

XRAPI_ATTR XrResult XRAPI_CALL xrCreateMarkerSpaceML(
    XrSession                                   session,
    const XrMarkerSpaceCreateInfoML*            createInfo,
    XrSpace*                                    space);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */
#endif /* XR_ML_marker_understanding */

#ifdef __cplusplus
}
#endif

#endif
