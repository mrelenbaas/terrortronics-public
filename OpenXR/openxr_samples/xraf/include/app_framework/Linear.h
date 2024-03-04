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

#include <math.h>
#include <openxr/openxr.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <ostream>
#include <string>

/*! \brief 4x4 float transform matrix.
 *
 * Column Major. This means that the first column appears as
 * first four floats in the array.
 */
typedef struct XrMatrix4x4f {
  float m[16];
  /*! \brief Element Accessor. */
  inline float &At(uint32_t column, uint32_t row) {
    const int offset = column | (row << 2);
    assert(offset < 16);
    return m[offset];
  }
} XrMatrix4x4f;

namespace ml {

/*! \brief Xr Linear Algebra functions.
 *
 * Typically the result output variable may also be one of the input variables.
 */
namespace Linear {

const float MATH_PI = 3.14159265358979323846f;

const float DEFAULT_NEAR_Z = 0.015625f;  // exact floating point representation
const float INFINITE_FAR_Z = 0.0f;

/*! \brief Convert Radians to degree. */
inline float RadToDegree(float rad) {
  return rad / MATH_PI * 180.0f;
}

/*! \brief Convert degree to Radians. */
inline float DegreeToRad(float degree) {
  return MATH_PI * degree / 180.0f;
}

/*! \brief Adds two values.
 * The result is not normalized.
 * result = a + b;
 */
template <typename T>
inline void XrAdd(T &result, const T &a, const T &b) {
  result = a + b;
}
template <>
void XrAdd(XrVector2f &result, const XrVector2f &a, const XrVector2f &b);
template <>
void XrAdd(XrVector3f &result, const XrVector3f &a, const XrVector3f &b);
template <>
void XrAdd(XrQuaternionf &result, const XrQuaternionf &a,
           const XrQuaternionf &b);
void XrAdd(XrPosef &result, const XrPosef &a, const XrVector3f &b);

/*! \brief Adds two values.
 * The result is not normalized.
 * result = result + a;
 */
template <typename T>
inline void XrAdd(T &result, const T &a) {
  XrAdd(result, result, a);
}

/*! \brief Subtracts two values.
 * The result is not normalized.
 * result = a - b;
 */
template <typename T>
inline void XrSub(T &result, const T &a, const T &b) {
  result = a - b;
}
template <>
void XrSub(XrVector2f &result, const XrVector2f &a, const XrVector2f &b);
template <>
void XrSub(XrVector3f &result, const XrVector3f &a, const XrVector3f &b);
template <>
void XrSub(XrQuaternionf &result, const XrQuaternionf &a,
           const XrQuaternionf &b);

/*! \brief Adds two values.
 * The result is not normalized.
 * result = result - a;
 */
template <typename T>
inline void XrSub(T &result, const T &a) {
  XrSub(result, result, a);
}

/*! \brief Adds two values, with operand b multiplied with scale.
 * The result is not normalized.
 * result = a + b * scale;
 */
template <typename T>
void XrAddScaled(T &result, const T &a, const T &b, float scale);

template <>
void XrAddScaled(XrVector2f &result, const XrVector2f &a, const XrVector2f &b,
                 float scale);
template <>
void XrAddScaled(XrVector3f &result, const XrVector3f &a, const XrVector3f &b,
                 float scale);
template <>
void XrAddScaled(XrQuaternionf &result, const XrQuaternionf &a,
                 const XrQuaternionf &b, float scale);

/*! \brief Scales a value.
 * The result is not normalized.
 * result = a * scale;
 */
template <typename T>
inline void XrScale(T &result, const T &a, float scale) {
  result = a * scale;
}

template <>
void XrScale(XrVector2f &result, const XrVector2f &a, float scale);
template <>
void XrScale(XrVector3f &result, const XrVector3f &a, float scale);
template <>
void XrScale(XrQuaternionf &result, const XrQuaternionf &a, float scale);

/*! \brief Calculate the magnitude.
 * result = || a ||;
 */
template <typename T>
inline float XrMagnitude(const T &a) {
  return fabs(a);
}

template <>
float XrMagnitude(const XrVector2f &a);
template <>
float XrMagnitude(const XrVector3f &a);
template <>
float XrMagnitude(const XrQuaternionf &a);

/*! \brief Calculate the square of the magnitude.
 * this avoid the costly square root operation
 * if it is not needed.
 */
template <typename T>
inline float XrSquareNorm(const T &a) {
  return a * a;
}
template <>
float XrSquareNorm(const XrVector2f &a);
template <>
float XrSquareNorm(const XrVector3f &a);
template <>
float XrSquareNorm(const XrQuaternionf &a);

/*! \brief Normalizes a value.
 * result = a / || a ||;
 */
template <typename T>
inline void XrNormalize(T &result, const T &a) {
  const float SMALLEST_NON_DENORMAL = 1.1754943508222875e-038f;  // ( 1U << 23 )
  const auto len = XrMagnitude(a);
  if (fabs(len) > SMALLEST_NON_DENORMAL) {
    XrScale(result, a, 1.0f / len);
  } else {
    result = a;
  }
}

/*! \brief In place Normalizes a value.
 * a = a / || a ||;
 */
template <typename T>
inline void XrNormalize(T &result) {
  XrNormalize(result, result);
}

/*! \brief Calculate the dot product.
 */
inline float XrDot(const XrVector2f &a, const XrVector2f &b) {
  return a.x * b.x + a.y * b.y;
}
/*! \brief Calculate the dot product.
 */
inline float XrDot(const XrVector3f &a, const XrVector3f &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
/*! \brief Calculate the dot product.
 */
inline float XrDot(const XrQuaternionf &a, const XrQuaternionf &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/*! \brief Linear Lerp between a and b. */
template <typename T>
inline void XrLerp(T &result, const T &a, const T &b, float fraction) {
  XrSub(result, b, a);
  XrAddScaled(result, a, result, fraction);
}
template <>
inline void XrLerp(XrQuaternionf &result, const XrQuaternionf &a,
                   const XrQuaternionf &b, float fraction) {
  const float s = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  const float fa = 1.0f - fraction;
  const float fb = (s < 0.0f) ? -fraction : fraction;
  const float x = a.x * fa + b.x * fb;
  const float y = a.y * fa + b.y * fb;
  const float z = a.z * fa + b.z * fb;
  const float w = a.w * fa + b.w * fb;
  result.x = x;
  result.y = y;
  result.z = z;
  result.w = w;
  XrNormalize(result, result);
}

/*! \brief Spherical Interpolation between and b. */
inline void XrSlerp(XrQuaternionf &result, const XrQuaternionf &a,
                    const XrQuaternionf &b, double fraction) {
  const float dp = XrDot(a, b);
  const float pa = acos(fabsf(std::clamp(dp, -1.0f, 1.0f)));
  int sign = (pa > 0.0f) - (pa < 0.0f);  // sign of a.

  // For low values of pa this becomes a linear interpolation.
  if (pa < 0.1f) {
    return XrLerp(result, a, b, fraction);
  }

  const float sina_rcp = 1.0f / sin(pa);
  const float p1 = sin(pa * (1 - fraction)) * sina_rcp;
  const float p2 = sign * sin(pa * fraction) * sina_rcp;

  XrScale(result, a, p1);
  XrAddScaled(result, result, b, p2);
  XrNormalize(result, result);
}

/*! \brief Rotates a vector "v" by q.
 *
 * vprime = v rotated by q.
 */
void XrRotate(XrVector3f &vprime, const XrQuaternionf &q, const XrVector3f &v);

/*! \brief Rotates a vector "v" by q. */
void XrRotate(XrVector3f &v, const XrQuaternionf &q);

/*! \brief Test for equality between floating point types.
 *  return = fabs(a-b) < eps;
 */
template <typename T>
inline bool XrEqual(const T &a, const T &b, float eps = 0.001f) {
  return fabs(a - b) < eps;
}

template <>
bool XrEqual(const XrVector2f &a, const XrVector2f &b, float eps);
template <>
bool XrEqual(const XrVector3f &a, const XrVector3f &b, float eps);
template <>
bool XrEqual(const XrColor4f &a, const XrColor4f &b, float eps);
template <>
bool XrEqual(const XrQuaternionf &a, const XrQuaternionf &b, float eps);
template <>
bool XrEqual(const XrMatrix4x4f &a, const XrMatrix4x4f &b, float eps);

/*! \brief Calculate the cross product.
 */
inline void XrCross(XrVector3f &result, const XrVector3f &a,
                    const XrVector3f &b) {
  const float x = a.y * b.z - a.z * b.y;
  const float y = a.z * b.x - a.x * b.z;
  const float z = a.x * b.y - a.y * b.x;
  result.x = x;
  result.y = y;
  result.z = z;
}

/*! \brief Calculate the intersection distance from ray_center, along
 * ray_normal.
 *
 * If return value is true, the distance will be available in "distance".
 *
 * distance = ( (Pc - Rc) dot Pn ) / ( Rn dot Pn )
 *
 */
inline bool XrIntersect(const XrVector3f &ray_center,
                        const XrVector3f &ray_normal,
                        const XrVector3f &plane_center,
                        const XrVector3f &plane_normal, float &distance) {
  float dot_product = XrDot(ray_normal, plane_normal);
  if (fabs(dot_product) < 0.0001f) {
    return false;
  }
  XrVector3f diff;
  XrSub(diff, plane_center, ray_center);
  distance = XrDot(diff, plane_normal) / dot_product;
  return distance > 0.0f;
}

/*! \brief Multiplies a with b and stores the result.
 *
 * Note that result may not be a or b.
 */
template <typename T>
inline void XrMultiply(T &result, const T &a, const T &b) {
  result = a * b;
}
template <>
void XrMultiply(XrQuaternionf &result, const XrQuaternionf &a,
                const XrQuaternionf &b);
template <>
void XrMultiply(XrMatrix4x4f &result, const XrMatrix4x4f &a,
                const XrMatrix4x4f &b);

/*! \brief Multiplies a with b and stores the result.
 *
 * a = a * b
 */
void XrMultiply(XrMatrix4x4f &a, const XrMatrix4x4f &b);

/*! \brief Multiplies a with b and stores the result in a.
 *
 * a = a * b
 */
inline void XrMultiply(XrVector3f &a, const float &b) {
  a.x = a.x * b;
  a.y = a.y * b;
  a.z = a.z * b;
}

/*! \brief Multiplies a with b and stores the result.
 *
 * a = a * b
 */
inline void XrMultiply(XrVector3f &result, const XrVector3f &a,
                       const float &b) {
  result.x = a.x * b;
  result.y = a.y * b;
  result.z = a.z * b;
}

/*! \brief Transposes matrix and stores the result.
 *
 * Note that result may not be a.
 */
void XrTranspose(XrMatrix4x4f &result, const XrMatrix4x4f &a);

/*! \brief Transposes matrix in place. */
void XrTranspose(XrMatrix4x4f &a);

/*! \brief Inverts the src matrix. */
void XrInvert(XrMatrix4x4f &result, const XrMatrix4x4f &src);

/*! \brief Inverts a rigid body matrix. */
void XrInvertRigidBody(XrMatrix4x4f &result, const XrMatrix4x4f &src);

/*! \brief Inverts the quaternion. */
void XrInvert(XrQuaternionf &quat);

/*! \brief Returns Identity quaternion. */
inline void XrCreateIdentity(XrQuaternionf &result) {
  result.x = 0.0f;
  result.y = 0.0f;
  result.z = 0.0f;
  result.w = 1.0f;
}

/*! \brief Returns Identity Pose. */
inline void XrCreateIdentity(XrPosef &result) {
  result.position = {0.0f, 0.0f, 0.0f};
  XrCreateIdentity(result.orientation);
}

/*! \brief Returns Identity transformation. */
inline void XrCreateIdentity(XrMatrix4x4f &result) {
  result.m[0] = 1.0f;
  result.m[1] = 0.0f;
  result.m[2] = 0.0f;
  result.m[3] = 0.0f;
  result.m[4] = 0.0f;
  result.m[5] = 1.0f;
  result.m[6] = 0.0f;
  result.m[7] = 0.0f;
  result.m[8] = 0.0f;
  result.m[9] = 0.0f;
  result.m[10] = 1.0f;
  result.m[11] = 0.0f;
  result.m[12] = 0.0f;
  result.m[13] = 0.0f;
  result.m[14] = 0.0f;
  result.m[15] = 1.0f;
}

/*! \brief Create a Translation matrix. */
void XrCreateTranslation(XrMatrix4x4f &result, const float x, const float y,
                         const float z);

/*! \brief Create a Rotation matrix. */
void XrCreateRotation(XrMatrix4x4f &result, const float degrees_x,
                      const float degrees_y, const float degrees_z);

/*! \brief Create a Rotation matrix. */
void XrCreateRotation(XrMatrix4x4f &result, const XrQuaternionf &quat);

/*! \brief Creates Quaternion from Axis and rotation angle. */
void XrCreateRotation(XrQuaternionf &result, const XrVector3f &axis,
                      float angle_in_radians);

/*! \brief Creates Quaternion from a source point looking at
    a destination point.

    unit_forward must be normalized.
    */
void XrLookAt(XrQuaternionf &result, const XrVector3f &source,
              const XrVector3f &dest, const XrVector3f &unit_forward);

/*! \brief Creates Quaternion from roll (X), pitch (Y) and yaw (Z). */
void XrCreateRotation(XrQuaternionf &result, double roll, double pitch,
                      double yaw);

/*! \brief Create a Scaling matrix. */
void XrCreateScale(XrMatrix4x4f &result, const float x, const float y,
                   const float z);

/*! \brief Create a combined Translation, Rotation and scaling matrix. */
void XrCreateTranslationRotationScale(XrMatrix4x4f &result,
                                      const XrVector3f &translation,
                                      const XrQuaternionf &rotation,
                                      const XrVector3f &scale);

/*! \brief Graphics API Enum for XrCreateProjectionFov. */
typedef enum GraphicsAPI {
  GRAPHICS_VULKAN,
  GRAPHICS_OPENGL,
  GRAPHICS_OPENGL_ES,
} GraphicsAPI;

/*! \brief Create a projection matrix. */
void XrCreateProjectionFov(XrMatrix4x4f &result, GraphicsAPI graphics_api,
                           const XrFovf fov, const float near_z,
                           const float far_z);

/*! \brief Transforms offset to the reference space. */
XrPosef XrCreatePose(const XrPosef &reference, const XrPosef &offset);

/*! \brief Transforms offset to the reference space. */
XrPosef XrCreatePose(const XrPosef &reference, const XrVector3f &offset);

/*! \brief Returns true if matrix is affine. */
bool XrIsAffine(const XrMatrix4x4f &matrix, const float epsilon);

/*! \brief Returns true if matrix is orthogonal. */
bool XrIsOrthogonal(const XrMatrix4x4f &matrix, const float epsilon);

/*! \brief Returns true if matrix is orthonormal. */
bool XrIsOrthonormal(const XrMatrix4x4f &matrix, const float epsilon);

/*! \brief Returns true if matrix is a rigid body transformation. */
bool XrIsRigidBody(const XrMatrix4x4f &matrix, const float epsilon);

/*! \brief Extracts the translation from a translation matrix.
 *
 * Matrix format: translation(rotation(scale(object)))
 */
void XrGetTranslation(XrVector3f &result, const XrMatrix4x4f &src);

/*! \brief Extracts the rotation from a translation matrix.
 *
 * Matrix format: translation(rotation(scale(object)))
 */
void XrGetRotation(XrQuaternionf &result, const XrMatrix4x4f &src);

/*! \brief Extracts the scalefrom a translation matrix.
 *
 * Matrix format: translation(rotation(scale(object)))
 */
void XrGetScale(XrVector3f &esult, const XrMatrix4x4f &src);

/*! \brief Transforms a vector. */
void XrTransform(XrVector3f &result, const XrMatrix4x4f &m,
                 const XrVector3f &v);
/*! \brief Transforms a vector. */
void XrTransform(XrVector4f &result, const XrMatrix4x4f &m,
                 const XrVector4f &v);

/*! \brief ToString for XrMatrix4x4f. */
std::string ToString(const XrMatrix4x4f &matrix);
/*! \brief ToString for XrVector3f. */
std::string ToString(const XrVector2f &vector);
/*! \brief ToString for XrVector3f. */
std::string ToString(const XrVector3f &vector);
/*! \brief ToString for XrQuaternionf. */
std::string ToString(const XrQuaternionf &vector);

/*! \brief convert floating point array of 4 elements to a XrColor4f. */
inline XrColor4f CreateColor(const double *elements) {
  return XrColor4f{(float)elements[0], (float)elements[1], (float)elements[2],
                   (float)elements[3]};
}

/*! \brief convert floating point array of 4 elements to a XrColor4f. */
inline XrColor4f CreateColor(const std::array<double, 4> &elements) {
  return XrColor4f{(float)elements[0], (float)elements[1], (float)elements[2],
                   (float)elements[3]};
}

/*! \brief convert floating point array of 4 elements to a XrColor4f. */
inline XrColor4f CreateColor(const float *elements) {
  return XrColor4f{elements[0], elements[1], elements[2], elements[3]};
}

/*! \brief convert floating point array of 4 elements to a XrColor4f. */
inline XrColor4f CreateColor(const std::array<float, 4> &elements) {
  return XrColor4f{elements[0], elements[1], elements[2], elements[3]};
}

}  // namespace Linear

}  // namespace ml

inline std::ostream &operator<<(std::ostream &out, const XrMatrix4x4f &matrix) {
  out << ml::Linear::ToString(matrix);
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const XrVector2f &vector) {
  out << ml::Linear::ToString(vector);
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const XrVector3f &vector) {
  out << ml::Linear::ToString(vector);
  return out;
}

inline std::ostream &operator<<(std::ostream &out, const XrQuaternionf &quat) {
  out << ml::Linear::ToString(quat);
  return out;
}

inline bool operator==(const XrMatrix4x4f &a, const XrMatrix4x4f &b) {
  return ml::Linear::XrEqual(a, b);
}

inline bool operator==(const XrVector2f &a, const XrVector2f &b) {
  return ml::Linear::XrEqual(a, b);
}

inline bool operator==(const XrVector3f &a, const XrVector3f &b) {
  return ml::Linear::XrEqual(a, b);
}

inline bool operator==(const XrQuaternionf &a, const XrQuaternionf &b) {
  return ml::Linear::XrEqual(a, b);
}
