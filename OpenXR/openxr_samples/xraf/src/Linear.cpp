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

// Parts of this code is based upon xr_linear,
// available from https://github.com/KhronosGroup/OpenXR-SDK
//
// Modifications Copyright(c) 2022 Magic Leap, Inc.
//
// Original Copyright:
//
// Copyright (c) 2017 The Khronos Group Inc.
// Copyright (c) 2016 Oculus VR, LLC.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: J.M.P. van Waveren
//

#include "../include/app_framework/Linear.h"

// this is a bit of an odd duck. It returns 1.0f for the square root
// of anything smaller than SMALLEST_NON_DENORMAL. This is used when
// the length of a vector is smaller than SMALLEST_NON_DENORMAL and
// thus would cause a division by 0/nan error. In that case, no scaling
// will be applied.
static float XrSqrtOrOne(const float x) {
  const float SMALLEST_NON_DENORMAL = 1.1754943508222875e-038f;  // ( 1U << 23 )
  if (x >= SMALLEST_NON_DENORMAL) {
    return sqrtf(x);
  } else {
    return 1.0f;
  }
}

std::string ml::Linear::ToString(const XrMatrix4x4f &matrix) {
  std::string s;
  s.resize(200);

#define FMT "\n\t%1.3f, %1.3f, %1.3f, %1.3f,"
#define FMTL "\n\t%1.3f, %1.3f, %1.3f, %1.3f"
  size_t len = std::snprintf(
      s.data(), s.size(), "[" FMT FMT FMT FMTL " ]", matrix.m[0], matrix.m[4],
      matrix.m[8], matrix.m[12], matrix.m[1], matrix.m[5], matrix.m[9],
      matrix.m[13], matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
      matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15]);

  s.resize(len);
  return s;
}

std::string ml::Linear::ToString(const XrVector2f &vector) {
  std::string s;
  s.resize(200);

  size_t len =
      std::snprintf(s.data(), s.size(), "[%1.3f, %1.3f]", vector.x, vector.y);

  s.resize(len);
  return s;
}

std::string ml::Linear::ToString(const XrVector3f &vector) {
  std::string s;
  s.resize(200);

  size_t len = std::snprintf(s.data(), s.size(), "[%1.3f, %1.3f, %1.3f]",
                             vector.x, vector.y, vector.z);

  s.resize(len);
  return s;
}

std::string ml::Linear::ToString(const XrQuaternionf &quat) {
  std::string s;
  s.resize(200);

  size_t len = std::snprintf(s.data(), s.size(), "[%1.3f, %1.3f, %1.3f, %1.3f]",
                             quat.x, quat.y, quat.z, quat.w);

  s.resize(len);
  return s;
}

// result = a + b
template <>
void ml::Linear::XrAdd(XrVector2f &result, const XrVector2f &a,
                       const XrVector2f &b) {
  result.x = a.x + b.x;
  result.y = a.y + b.y;
}

// result = a + b
template <>
void ml::Linear::XrAdd(XrVector3f &result, const XrVector3f &a,
                       const XrVector3f &b) {
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
}

// result = a + b
template <>
void ml::Linear::XrAdd(XrQuaternionf &result, const XrQuaternionf &a,
                       const XrQuaternionf &b) {
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  result.w = a.w + b.w;
}

// result = a - b
template <>
void ml::Linear::XrSub(XrVector2f &result, const XrVector2f &a,
                       const XrVector2f &b) {
  result.x = a.x - b.x;
  result.y = a.y - b.y;
}

// result = a - b
template <>
void ml::Linear::XrSub(XrVector3f &result, const XrVector3f &a,
                       const XrVector3f &b) {
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
}

// result = a - b
template <>
void ml::Linear::XrSub(XrQuaternionf &result, const XrQuaternionf &a,
                       const XrQuaternionf &b) {
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  result.w = a.w - b.w;
}

// result = a + b * scale
template <>
void ml::Linear::XrAddScaled(XrVector2f &result, const XrVector2f &a,
                             const XrVector2f &b, float scale) {
  result.x = a.x + b.x * scale;
  result.y = a.y + b.y * scale;
}

// result = a + b * scale
template <>
void ml::Linear::XrAddScaled(XrVector3f &result, const XrVector3f &a,
                             const XrVector3f &b, float scale) {
  result.x = a.x + b.x * scale;
  result.y = a.y + b.y * scale;
  result.z = a.z + b.z * scale;
}

// result = a + b * scale
template <>
void ml::Linear::XrAddScaled(XrQuaternionf &result, const XrQuaternionf &a,
                             const XrQuaternionf &b, float scale) {
  result.x = a.x + b.x * scale;
  result.y = a.y + b.y * scale;
  result.z = a.z + b.z * scale;
  result.w = a.w + b.w * scale;
}

// result = a * scale;
template <>
void ml::Linear::XrScale(XrVector2f &result, const XrVector2f &a, float scale) {
  result.x = a.x * scale;
  result.y = a.y * scale;
}

// result = a * scale;
template <>
void ml::Linear::XrScale(XrVector3f &result, const XrVector3f &a, float scale) {
  result.x = a.x * scale;
  result.y = a.y * scale;
  result.z = a.z * scale;
}

// result = a * scale;
template <>
void ml::Linear::XrScale(XrQuaternionf &result, const XrQuaternionf &a,
                         float scale) {
  result.x = a.x * scale;
  result.y = a.y * scale;
  result.z = a.z * scale;
  result.w = a.w * scale;
}

// result = ||a||
template <>
float ml::Linear::XrMagnitude(const XrVector2f &a) {
  return sqrtf(a.x * a.x + a.y * a.y);
}

// result = ||a||
template <>
float ml::Linear::XrMagnitude(const XrVector3f &a) {
  return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

// result = ||a||
template <>
float ml::Linear::XrMagnitude(const XrQuaternionf &a) {
  return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

// result = ||a||^2
template <>
float ml::Linear::XrSquareNorm(const XrVector2f &a) {
  return (a.x * a.x + a.y * a.y);
}
// result = ||a||^2
template <>
float ml::Linear::XrSquareNorm(const XrVector3f &a) {
  return (a.x * a.x + a.y * a.y + a.z * a.z);
}
// result = ||a||^2
template <>
float ml::Linear::XrSquareNorm(const XrQuaternionf &a) {
  return (a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

template <>
bool ml::Linear::XrEqual(const XrVector2f &a, const XrVector2f &b, float eps) {
  return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps;
}

template <>
bool ml::Linear::XrEqual(const XrVector3f &a, const XrVector3f &b, float eps) {
  return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps &&
         fabs(a.z - b.z) < eps;
}

template <>
bool ml::Linear::XrEqual(const XrColor4f &a, const XrColor4f &b, float eps) {
  return fabs(a.r - b.r) < eps && fabs(a.g - b.g) < eps &&
         fabs(a.b - b.b) < eps && fabs(a.a - b.a) < eps;
}

template <>
bool ml::Linear::XrEqual(const XrQuaternionf &a, const XrQuaternionf &b,
                         float eps) {
  return fabs(a.x - b.x) < eps && fabs(a.y - b.y) < eps &&
         fabs(a.z - b.z) < eps && fabs(a.w - b.w) < eps;
}

template <>
bool ml::Linear::XrEqual(const XrMatrix4x4f &a, const XrMatrix4x4f &b,
                         float eps) {
  for (size_t i = 0; i < 16; i++) {
    if (fabs(a.m[i] - b.m[i]) > eps) {
      return false;
    }
  }
  return true;
}

void ml::Linear::XrRotate(XrVector3f &vprime, const XrQuaternionf &q,
                          const XrVector3f &v) {
  // TODO optimize
  // Extract the vector part of the quaternion
  XrVector3f u{q.x, q.y, q.z};

  // Extract the scalar part of the quaternion
  float s = q.w;

  double u_dot_v = XrDot(u, v);
  double u_dot_u = XrDot(u, u);
  XrVector3f cross;
  XrCross(cross, u, v);

  XrVector3f t1, t2, t3;
  XrScale(t1, u, 2.0f * u_dot_v);
  XrScale(t2, v, (s * s - u_dot_u));
  XrScale(t3, cross, 2.0f * s);

  XrAdd(vprime, t1, t2);
  XrAdd(vprime, vprime, t3);
}
void ml::Linear::XrRotate(XrVector3f &v, const XrQuaternionf &q) {
  XrVector3f result;
  XrRotate(result, q, v);
  v = result;
}

template <>
void ml::Linear::XrMultiply(XrQuaternionf &result, const XrQuaternionf &q,
                            const XrQuaternionf &p) {
  const float w = q.w;
  const float wp = p.w;
  result.w = w * wp - q.x * p.x - q.y * p.y - q.z * p.z;  // (wx′+xw′+yz′−zy′)
  result.x = (w * p.x + q.x * wp + q.y * p.z - q.z * p.y);
  result.y = (w * p.y - q.x * p.z + q.y * wp + q.z * p.x);
  result.z = (w * p.z + q.x * p.y - q.y * p.x + q.z * wp);

  //  const float x = (b.w * a.x) + (b.x * a.w) + (b.y * a.z) - (b.z * a.y);
  //  const float y = (b.w * a.y) - (b.x * a.z) + (b.y * a.w) + (b.z * a.x);
  //  const float z = (b.w * a.z) + (b.x * a.y) - (b.y * a.x) + (b.z * a.w);
  //  const float w = (b.w * a.w) - (b.x * a.x) - (b.y * a.y) - (b.z * a.z);
  //  result.x = x;
  //  result.y = y;
  //  result.z = z;
  //  result.w = w;
}

template <>
void ml::Linear::XrMultiply(XrMatrix4x4f &result, const XrMatrix4x4f &a,
                            const XrMatrix4x4f &b) {
  result.m[0] =
      a.m[0] * b.m[0] + a.m[4] * b.m[1] + a.m[8] * b.m[2] + a.m[12] * b.m[3];
  result.m[1] =
      a.m[1] * b.m[0] + a.m[5] * b.m[1] + a.m[9] * b.m[2] + a.m[13] * b.m[3];
  result.m[2] =
      a.m[2] * b.m[0] + a.m[6] * b.m[1] + a.m[10] * b.m[2] + a.m[14] * b.m[3];
  result.m[3] =
      a.m[3] * b.m[0] + a.m[7] * b.m[1] + a.m[11] * b.m[2] + a.m[15] * b.m[3];

  result.m[4] =
      a.m[0] * b.m[4] + a.m[4] * b.m[5] + a.m[8] * b.m[6] + a.m[12] * b.m[7];
  result.m[5] =
      a.m[1] * b.m[4] + a.m[5] * b.m[5] + a.m[9] * b.m[6] + a.m[13] * b.m[7];
  result.m[6] =
      a.m[2] * b.m[4] + a.m[6] * b.m[5] + a.m[10] * b.m[6] + a.m[14] * b.m[7];
  result.m[7] =
      a.m[3] * b.m[4] + a.m[7] * b.m[5] + a.m[11] * b.m[6] + a.m[15] * b.m[7];

  result.m[8] =
      a.m[0] * b.m[8] + a.m[4] * b.m[9] + a.m[8] * b.m[10] + a.m[12] * b.m[11];
  result.m[9] =
      a.m[1] * b.m[8] + a.m[5] * b.m[9] + a.m[9] * b.m[10] + a.m[13] * b.m[11];
  result.m[10] =
      a.m[2] * b.m[8] + a.m[6] * b.m[9] + a.m[10] * b.m[10] + a.m[14] * b.m[11];
  result.m[11] =
      a.m[3] * b.m[8] + a.m[7] * b.m[9] + a.m[11] * b.m[10] + a.m[15] * b.m[11];

  result.m[12] = a.m[0] * b.m[12] + a.m[4] * b.m[13] + a.m[8] * b.m[14] +
                 a.m[12] * b.m[15];
  result.m[13] = a.m[1] * b.m[12] + a.m[5] * b.m[13] + a.m[9] * b.m[14] +
                 a.m[13] * b.m[15];
  result.m[14] = a.m[2] * b.m[12] + a.m[6] * b.m[13] + a.m[10] * b.m[14] +
                 a.m[14] * b.m[15];
  result.m[15] = a.m[3] * b.m[12] + a.m[7] * b.m[13] + a.m[11] * b.m[14] +
                 a.m[15] * b.m[15];
}

void ml::Linear::XrMultiply(XrMatrix4x4f &a, const XrMatrix4x4f &b) {
  XrMatrix4x4f temp;
  temp.m[0] =
      a.m[0] * b.m[0] + a.m[4] * b.m[1] + a.m[8] * b.m[2] + a.m[12] * b.m[3];
  temp.m[1] =
      a.m[1] * b.m[0] + a.m[5] * b.m[1] + a.m[9] * b.m[2] + a.m[13] * b.m[3];
  temp.m[2] =
      a.m[2] * b.m[0] + a.m[6] * b.m[1] + a.m[10] * b.m[2] + a.m[14] * b.m[3];
  temp.m[3] =
      a.m[3] * b.m[0] + a.m[7] * b.m[1] + a.m[11] * b.m[2] + a.m[15] * b.m[3];

  temp.m[4] =
      a.m[0] * b.m[4] + a.m[4] * b.m[5] + a.m[8] * b.m[6] + a.m[12] * b.m[7];
  temp.m[5] =
      a.m[1] * b.m[4] + a.m[5] * b.m[5] + a.m[9] * b.m[6] + a.m[13] * b.m[7];
  temp.m[6] =
      a.m[2] * b.m[4] + a.m[6] * b.m[5] + a.m[10] * b.m[6] + a.m[14] * b.m[7];
  temp.m[7] =
      a.m[3] * b.m[4] + a.m[7] * b.m[5] + a.m[11] * b.m[6] + a.m[15] * b.m[7];

  temp.m[8] =
      a.m[0] * b.m[8] + a.m[4] * b.m[9] + a.m[8] * b.m[10] + a.m[12] * b.m[11];
  temp.m[9] =
      a.m[1] * b.m[8] + a.m[5] * b.m[9] + a.m[9] * b.m[10] + a.m[13] * b.m[11];
  temp.m[10] =
      a.m[2] * b.m[8] + a.m[6] * b.m[9] + a.m[10] * b.m[10] + a.m[14] * b.m[11];
  temp.m[11] =
      a.m[3] * b.m[8] + a.m[7] * b.m[9] + a.m[11] * b.m[10] + a.m[15] * b.m[11];

  temp.m[12] = a.m[0] * b.m[12] + a.m[4] * b.m[13] + a.m[8] * b.m[14] +
               a.m[12] * b.m[15];
  temp.m[13] = a.m[1] * b.m[12] + a.m[5] * b.m[13] + a.m[9] * b.m[14] +
               a.m[13] * b.m[15];
  temp.m[14] = a.m[2] * b.m[12] + a.m[6] * b.m[13] + a.m[10] * b.m[14] +
               a.m[14] * b.m[15];
  temp.m[15] = a.m[3] * b.m[12] + a.m[7] * b.m[13] + a.m[11] * b.m[14] +
               a.m[15] * b.m[15];
  a = std::move(temp);
}

// Creates the transpose of the given matrix.
void ml::Linear::XrTranspose(XrMatrix4x4f &result, const XrMatrix4x4f &src) {
  result.m[0] = src.m[0];
  result.m[1] = src.m[4];
  result.m[2] = src.m[8];
  result.m[3] = src.m[12];

  result.m[4] = src.m[1];
  result.m[5] = src.m[5];
  result.m[6] = src.m[9];
  result.m[7] = src.m[13];

  result.m[8] = src.m[2];
  result.m[9] = src.m[6];
  result.m[10] = src.m[10];
  result.m[11] = src.m[14];

  result.m[12] = src.m[3];
  result.m[13] = src.m[7];
  result.m[14] = src.m[11];
  result.m[15] = src.m[15];
}

void ml::Linear::XrTranspose(XrMatrix4x4f &a) {
  std::swap(a.m[1], a.m[4]);
  std::swap(a.m[2], a.m[8]);
  std::swap(a.m[3], a.m[12]);
  std::swap(a.m[4], a.m[1]);
  std::swap(a.m[6], a.m[9]);
  std::swap(a.m[7], a.m[13]);
  std::swap(a.m[11], a.m[14]);
}

static float XrMatrix4x4f_Minor(const XrMatrix4x4f &matrix, int r0, int r1,
                                int r2, int c0, int c1, int c2) {
  return matrix.m[4 * r0 + c0] *
             (matrix.m[4 * r1 + c1] * matrix.m[4 * r2 + c2] -
              matrix.m[4 * r2 + c1] * matrix.m[4 * r1 + c2]) -
         matrix.m[4 * r0 + c1] *
             (matrix.m[4 * r1 + c0] * matrix.m[4 * r2 + c2] -
              matrix.m[4 * r2 + c0] * matrix.m[4 * r1 + c2]) +
         matrix.m[4 * r0 + c2] *
             (matrix.m[4 * r1 + c0] * matrix.m[4 * r2 + c1] -
              matrix.m[4 * r2 + c0] * matrix.m[4 * r1 + c1]);
}

void ml::Linear::XrInvert(XrMatrix4x4f &result, const XrMatrix4x4f &src) {
  const float rcp_det =
      1.0f / (src.m[0] * XrMatrix4x4f_Minor(src, 1, 2, 3, 1, 2, 3) -
              src.m[1] * XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 2, 3) +
              src.m[2] * XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 1, 3) -
              src.m[3] * XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 1, 2));

  result.m[0] = XrMatrix4x4f_Minor(src, 1, 2, 3, 1, 2, 3) * rcp_det;
  result.m[1] = -XrMatrix4x4f_Minor(src, 0, 2, 3, 1, 2, 3) * rcp_det;
  result.m[2] = XrMatrix4x4f_Minor(src, 0, 1, 3, 1, 2, 3) * rcp_det;
  result.m[3] = -XrMatrix4x4f_Minor(src, 0, 1, 2, 1, 2, 3) * rcp_det;
  result.m[4] = -XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 2, 3) * rcp_det;
  result.m[5] = XrMatrix4x4f_Minor(src, 0, 2, 3, 0, 2, 3) * rcp_det;
  result.m[6] = -XrMatrix4x4f_Minor(src, 0, 1, 3, 0, 2, 3) * rcp_det;
  result.m[7] = XrMatrix4x4f_Minor(src, 0, 1, 2, 0, 2, 3) * rcp_det;
  result.m[8] = XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 1, 3) * rcp_det;
  result.m[9] = -XrMatrix4x4f_Minor(src, 0, 2, 3, 0, 1, 3) * rcp_det;
  result.m[10] = XrMatrix4x4f_Minor(src, 0, 1, 3, 0, 1, 3) * rcp_det;
  result.m[11] = -XrMatrix4x4f_Minor(src, 0, 1, 2, 0, 1, 3) * rcp_det;
  result.m[12] = -XrMatrix4x4f_Minor(src, 1, 2, 3, 0, 1, 2) * rcp_det;
  result.m[13] = XrMatrix4x4f_Minor(src, 0, 2, 3, 0, 1, 2) * rcp_det;
  result.m[14] = -XrMatrix4x4f_Minor(src, 0, 1, 3, 0, 1, 2) * rcp_det;
  result.m[15] = XrMatrix4x4f_Minor(src, 0, 1, 2, 0, 1, 2) * rcp_det;
}

void ml::Linear::XrInvertRigidBody(XrMatrix4x4f &result,
                                   const XrMatrix4x4f &src) {
  result.m[0] = src.m[0];
  result.m[1] = src.m[4];
  result.m[2] = src.m[8];
  result.m[3] = 0.0f;
  result.m[4] = src.m[1];
  result.m[5] = src.m[5];
  result.m[6] = src.m[9];
  result.m[7] = 0.0f;
  result.m[8] = src.m[2];
  result.m[9] = src.m[6];
  result.m[10] = src.m[10];
  result.m[11] = 0.0f;
  result.m[12] =
      -(src.m[0] * src.m[12] + src.m[1] * src.m[13] + src.m[2] * src.m[14]);
  result.m[13] =
      -(src.m[4] * src.m[12] + src.m[5] * src.m[13] + src.m[6] * src.m[14]);
  result.m[14] =
      -(src.m[8] * src.m[12] + src.m[9] * src.m[13] + src.m[10] * src.m[14]);
  result.m[15] = 1.0f;
}

void ml::Linear::XrCreateTranslation(XrMatrix4x4f &result, const float x,
                                     const float y, const float z) {
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
  result.m[12] = x;
  result.m[13] = y;
  result.m[14] = z;
  result.m[15] = 1.0f;
}

void ml::Linear::XrCreateRotation(XrMatrix4x4f &result, const float degrees_x,
                                  const float degrees_y,
                                  const float degrees_z) {
  const float sin_x = sinf(degrees_x * (MATH_PI / 180.0f));
  const float cos_x = cosf(degrees_x * (MATH_PI / 180.0f));
  const XrMatrix4x4f rotation_x = {
      {1, 0, 0, 0, 0, cos_x, sin_x, 0, 0, -sin_x, cos_x, 0, 0, 0, 0, 1}};
  const float sin_y = sinf(degrees_y * (MATH_PI / 180.0f));
  const float cos_y = cosf(degrees_y * (MATH_PI / 180.0f));
  const XrMatrix4x4f rotation_y = {
      {cos_y, 0, -sin_y, 0, 0, 1, 0, 0, sin_y, 0, cos_y, 0, 0, 0, 0, 1}};
  const float sin_z = sinf(degrees_z * (MATH_PI / 180.0f));
  const float cos_z = cosf(degrees_z * (MATH_PI / 180.0f));
  const XrMatrix4x4f rotation_z = {
      {cos_z, sin_z, 0, 0, -sin_z, cos_z, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
  XrMatrix4x4f rotation_xy;
  XrMultiply(rotation_xy, rotation_y, rotation_x);
  XrMultiply(result, rotation_z, rotation_xy);
}

void ml::Linear::XrCreateRotation(XrMatrix4x4f &result,
                                  const XrQuaternionf &quat) {
  const float x2 = quat.x + quat.x;
  const float y2 = quat.y + quat.y;
  const float z2 = quat.z + quat.z;

  const float xx2 = quat.x * x2;
  const float yy2 = quat.y * y2;
  const float zz2 = quat.z * z2;

  const float yz2 = quat.y * z2;
  const float wx2 = quat.w * x2;
  const float xy2 = quat.x * y2;
  const float wz2 = quat.w * z2;
  const float xz2 = quat.x * z2;
  const float wy2 = quat.w * y2;

  result.m[0] = 1.0f - yy2 - zz2;
  result.m[1] = xy2 + wz2;
  result.m[2] = xz2 - wy2;
  result.m[3] = 0.0f;

  result.m[4] = xy2 - wz2;
  result.m[5] = 1.0f - xx2 - zz2;
  result.m[6] = yz2 + wx2;
  result.m[7] = 0.0f;

  result.m[8] = xz2 + wy2;
  result.m[9] = yz2 - wx2;
  result.m[10] = 1.0f - xx2 - yy2;
  result.m[11] = 0.0f;

  result.m[12] = 0.0f;
  result.m[13] = 0.0f;
  result.m[14] = 0.0f;
  result.m[15] = 1.0f;
}

void ml::Linear::XrCreateRotation(XrQuaternionf &result, const XrVector3f &axis,
                                  float angle_in_radians) {
  const float half_angle = angle_in_radians / 2.0f;
  const float s = sinf(half_angle);
  const float length_rcp = 1.0f / XrMagnitude(axis);
  result.x = s * axis.x * length_rcp;
  result.y = s * axis.y * length_rcp;
  result.z = s * axis.z * length_rcp;
  result.w = cosf(half_angle);
}

// yaw (Z), pitch (Y), roll (X)
void ml::Linear::XrCreateRotation(XrQuaternionf &result, double roll,
                                  double pitch, double yaw) {
  float cy = cos(yaw * 0.5);
  float sy = sin(yaw * 0.5);
  float cp = cos(pitch * 0.5);
  float sp = sin(pitch * 0.5);
  float cr = cos(roll * 0.5);
  float sr = sin(roll * 0.5);

  result.w = cr * cp * cy + sr * sp * sy;
  result.x = sr * cp * cy - cr * sp * sy;
  result.y = cr * sp * cy + sr * cp * sy;
  result.z = cr * cp * sy - sr * sp * cy;
}

void ml::Linear::XrCreateScale(XrMatrix4x4f &result, const float x,
                               const float y, const float z) {
  result.m[0] = x;
  result.m[1] = 0.0f;
  result.m[2] = 0.0f;
  result.m[3] = 0.0f;
  result.m[4] = 0.0f;
  result.m[5] = y;
  result.m[6] = 0.0f;
  result.m[7] = 0.0f;
  result.m[8] = 0.0f;
  result.m[9] = 0.0f;
  result.m[10] = z;
  result.m[11] = 0.0f;
  result.m[12] = 0.0f;
  result.m[13] = 0.0f;
  result.m[14] = 0.0f;
  result.m[15] = 1.0f;
}

void ml::Linear::XrCreateTranslationRotationScale(XrMatrix4x4f &result,
                                                  const XrVector3f &translation,
                                                  const XrQuaternionf &rotation,
                                                  const XrVector3f &scale) {
  XrMatrix4x4f scale_matrix;
  XrCreateScale(scale_matrix, scale.x, scale.y, scale.z);

  XrMatrix4x4f rotation_matrix;
  XrCreateRotation(rotation_matrix, rotation);

  XrMatrix4x4f translation_matrix;
  XrCreateTranslation(translation_matrix, translation.x, translation.y,
                      translation.z);

  XrMatrix4x4f combined_matrix;
  XrMultiply(combined_matrix, rotation_matrix, scale_matrix);
  XrMultiply(result, translation_matrix, combined_matrix);
}

// Creates a projection matrix based on the specified dimensions.
// The projection matrix transforms -Z=forward, +Y=up, +X=right to the
// appropriate clip space for the graphics API. The far plane is placed at
// infinity if farZ <= nearZ. An infinite projection matrix is preferred for
// rasterization because, except for things *right* up against the near plane,
// it always provides better precision:
//              "Tightening the Precision of Perspective Rendering"
//              Paul Upchurch, Mathieu Desbrun
//              Journal of Graphics Tools, Volume 16, Issue 1, 2012
static void XrCreateProjection(XrMatrix4x4f &result,
                               ml::Linear::GraphicsAPI graphicsApi,
                               const float tanAngleLeft,
                               const float tanAngleRight,
                               const float tanAngleUp, float const tanAngleDown,
                               const float nearZ, const float farZ) {
  const float tanAngleWidth = tanAngleRight - tanAngleLeft;

  // Set to tanAngleDown - tanAngleUp for a clip space with positive Y down
  // (Vulkan). Set to tanAngleUp - tanAngleDown for a clip space with positive Y
  // up (OpenGL / D3D / Metal).
  const float tanAngleHeight = graphicsApi == ml::Linear::GRAPHICS_VULKAN
                                   ? (tanAngleDown - tanAngleUp)
                                   : (tanAngleUp - tanAngleDown);

  // Set to nearZ for a [-1,1] Z clip space (OpenGL / OpenGL ES).
  // Set to zero for a [0,1] Z clip space (Vulkan / D3D / Metal).
  const float offsetZ = (graphicsApi == ml::Linear::GRAPHICS_OPENGL ||
                         graphicsApi == ml::Linear::GRAPHICS_OPENGL_ES)
                            ? nearZ
                            : 0;

  if (farZ <= nearZ) {
    // place the far plane at infinity
    result.m[0] = 2.0f / tanAngleWidth;
    result.m[4] = 0.0f;
    result.m[8] = (tanAngleRight + tanAngleLeft) / tanAngleWidth;
    result.m[12] = 0.0f;

    result.m[1] = 0.0f;
    result.m[5] = 2.0f / tanAngleHeight;
    result.m[9] = (tanAngleUp + tanAngleDown) / tanAngleHeight;
    result.m[13] = 0.0f;

    result.m[2] = 0.0f;
    result.m[6] = 0.0f;
    result.m[10] = -1.0f;
    result.m[14] = -(nearZ + offsetZ);

    result.m[3] = 0.0f;
    result.m[7] = 0.0f;
    result.m[11] = -1.0f;
    result.m[15] = 0.0f;
  } else {
    // normal projection
    result.m[0] = 2.0f / tanAngleWidth;
    result.m[4] = 0.0f;
    result.m[8] = (tanAngleRight + tanAngleLeft) / tanAngleWidth;
    result.m[12] = 0.0f;

    result.m[1] = 0.0f;
    result.m[5] = 2.0f / tanAngleHeight;
    result.m[9] = (tanAngleUp + tanAngleDown) / tanAngleHeight;
    result.m[13] = 0.0f;

    result.m[2] = 0.0f;
    result.m[6] = 0.0f;
    result.m[10] = -(farZ + offsetZ) / (farZ - nearZ);
    result.m[14] = -(farZ * (nearZ + offsetZ)) / (farZ - nearZ);

    result.m[3] = 0.0f;
    result.m[7] = 0.0f;
    result.m[11] = -1.0f;
    result.m[15] = 0.0f;
  }
}

void ml::Linear::XrCreateProjectionFov(XrMatrix4x4f &result,
                                       GraphicsAPI graphics_api,
                                       const XrFovf fov, const float near_z,
                                       const float far_z) {
  const float tan_left = tanf(fov.angleLeft);
  const float tan_right = tanf(fov.angleRight);

  const float tan_down = tanf(fov.angleDown);
  const float tan_up = tanf(fov.angleUp);

  XrCreateProjection(result, graphics_api, tan_left, tan_right, tan_up,
                     tan_down, near_z, far_z);
}

XrPosef ml::Linear::XrCreatePose(const XrPosef &reference,
                                 const XrPosef &offset) {
  XrPosef new_pose = reference;

  XrVector3f rotated_offset;
  XrRotate(rotated_offset, new_pose.orientation, offset.position);

  XrAdd(new_pose, new_pose, rotated_offset);

  XrQuaternionf result;
  XrMultiply(result, new_pose.orientation, offset.orientation);
  new_pose.orientation = result;
  return new_pose;
}

XrPosef ml::Linear::XrCreatePose(const XrPosef &reference,
                                 const XrVector3f &offset) {
  return XrCreatePose(reference,
                      XrPosef{XrQuaternionf{0.0f, 0.0f, 0.0f, 1.0f}, offset});
}

bool ml::Linear::XrIsAffine(const XrMatrix4x4f &matrix, const float epsilon) {
  return fabsf(matrix.m[3]) <= epsilon && fabsf(matrix.m[7]) <= epsilon &&
         fabsf(matrix.m[11]) <= epsilon &&
         fabsf(matrix.m[15] - 1.0f) <= epsilon;
}

bool ml::Linear::XrIsOrthogonal(const XrMatrix4x4f &matrix,
                                const float epsilon) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i != j) {
        if (fabsf(matrix.m[4 * i + 0] * matrix.m[4 * j + 0] +
                  matrix.m[4 * i + 1] * matrix.m[4 * j + 1] +
                  matrix.m[4 * i + 2] * matrix.m[4 * j + 2]) > epsilon) {
          return false;
        }
        if (fabsf(matrix.m[4 * 0 + i] * matrix.m[4 * 0 + j] +
                  matrix.m[4 * 1 + i] * matrix.m[4 * 1 + j] +
                  matrix.m[4 * 2 + i] * matrix.m[4 * 2 + j]) > epsilon) {
          return false;
        }
      }
    }
  }
  return true;
}

bool ml::Linear::XrIsOrthonormal(const XrMatrix4x4f &matrix,
                                 const float epsilon) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      const float kd = (i == j) ? 1.0f : 0.0f;  // Kronecker delta
      if (fabsf(kd - (matrix.m[4 * i + 0] * matrix.m[4 * j + 0] +
                      matrix.m[4 * i + 1] * matrix.m[4 * j + 1] +
                      matrix.m[4 * i + 2] * matrix.m[4 * j + 2])) > epsilon) {
        return false;
      }
      if (fabsf(kd - (matrix.m[4 * 0 + i] * matrix.m[4 * 0 + j] +
                      matrix.m[4 * 1 + i] * matrix.m[4 * 1 + j] +
                      matrix.m[4 * 2 + i] * matrix.m[4 * 2 + j])) > epsilon) {
        return false;
      }
    }
  }
  return true;
}

bool ml::Linear::XrIsRigidBody(const XrMatrix4x4f &matrix,
                               const float epsilon) {
  return XrIsAffine(matrix, epsilon) && XrIsOrthonormal(matrix, epsilon);
}

void ml::Linear::XrGetTranslation(XrVector3f &result, const XrMatrix4x4f &src) {
  assert(XrIsAffine(src, 1e-4f));
  assert(XrIsOrthogonal(src, 1e-4f));
  result.x = src.m[12];
  result.y = src.m[13];
  result.z = src.m[14];
}

void ml::Linear::XrGetRotation(XrQuaternionf &result, const XrMatrix4x4f &src) {
  assert(XrIsAffine(src, 1e-4f));
  assert(XrIsOrthogonal(src, 1e-4f));

  const float rcp_scale_x =
      1.0f / XrSqrtOrOne(src.m[0] * src.m[0] + src.m[1] * src.m[1] +
                         src.m[2] * src.m[2]);
  const float rcp_scale_y =
      1.0f / XrSqrtOrOne(src.m[4] * src.m[4] + src.m[5] * src.m[5] +
                         src.m[6] * src.m[6]);
  const float rcp_scale_z =
      1.0f / XrSqrtOrOne(src.m[8] * src.m[8] + src.m[9] * src.m[9] +
                         src.m[10] * src.m[10]);
  const float m[9] = {
      src.m[0] * rcp_scale_x, src.m[1] * rcp_scale_x, src.m[2] * rcp_scale_x,
      src.m[4] * rcp_scale_y, src.m[5] * rcp_scale_y, src.m[6] * rcp_scale_y,
      src.m[8] * rcp_scale_z, src.m[9] * rcp_scale_z, src.m[10] * rcp_scale_z};
  if (m[0 * 3 + 0] + m[1 * 3 + 1] + m[2 * 3 + 2] > 0.0f) {
    float t = +m[0 * 3 + 0] + m[1 * 3 + 1] + m[2 * 3 + 2] + 1.0f;
    float s = 0.5f / XrSqrtOrOne(t);
    result.w = s * t;
    result.z = (m[0 * 3 + 1] - m[1 * 3 + 0]) * s;
    result.y = (m[2 * 3 + 0] - m[0 * 3 + 2]) * s;
    result.x = (m[1 * 3 + 2] - m[2 * 3 + 1]) * s;
  } else if (m[0 * 3 + 0] > m[1 * 3 + 1] && m[0 * 3 + 0] > m[2 * 3 + 2]) {
    float t = +m[0 * 3 + 0] - m[1 * 3 + 1] - m[2 * 3 + 2] + 1.0f;
    float s = 0.5f / XrSqrtOrOne(t);
    result.x = s * t;
    result.y = (m[0 * 3 + 1] + m[1 * 3 + 0]) * s;
    result.z = (m[2 * 3 + 0] + m[0 * 3 + 2]) * s;
    result.w = (m[1 * 3 + 2] - m[2 * 3 + 1]) * s;
  } else if (m[1 * 3 + 1] > m[2 * 3 + 2]) {
    float t = -m[0 * 3 + 0] + m[1 * 3 + 1] - m[2 * 3 + 2] + 1.0f;
    float s = 0.5f / XrSqrtOrOne(t);
    result.y = s * t;
    result.x = (m[0 * 3 + 1] + m[1 * 3 + 0]) * s;
    result.w = (m[2 * 3 + 0] - m[0 * 3 + 2]) * s;
    result.z = (m[1 * 3 + 2] + m[2 * 3 + 1]) * s;
  } else {
    float t = -m[0 * 3 + 0] - m[1 * 3 + 1] + m[2 * 3 + 2] + 1.0f;
    float s = 0.5f / XrSqrtOrOne(t);
    result.z = s * t;
    result.w = (m[0 * 3 + 1] - m[1 * 3 + 0]) * s;
    result.x = (m[2 * 3 + 0] + m[0 * 3 + 2]) * s;
    result.y = (m[1 * 3 + 2] + m[2 * 3 + 1]) * s;
  }
}

// Get the scale from a combined translation(rotation(scale(object))) matrix.
void ml::Linear::XrGetScale(XrVector3f &result, const XrMatrix4x4f &src) {
  assert(XrIsAffine(src, 1e-4f));
  assert(XrIsOrthogonal(src, 1e-4f));
  result.x =
      sqrtf(src.m[0] * src.m[0] + src.m[1] * src.m[1] + src.m[2] * src.m[2]);
  result.y =
      sqrtf(src.m[4] * src.m[4] + src.m[5] * src.m[5] + src.m[6] * src.m[6]);
  result.z =
      sqrtf(src.m[8] * src.m[8] + src.m[9] * src.m[9] + src.m[10] * src.m[10]);
}

void ml::Linear::XrTransform(XrVector3f &result, const XrMatrix4x4f &m,
                             const XrVector3f &v) {
  const float w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15];
  const float rcp_w = 1.0f / w;
  result.x = (m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12]) * rcp_w;
  result.y = (m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13]) * rcp_w;
  result.z = (m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14]) * rcp_w;
}

void ml::Linear::XrTransform(XrVector4f &result, const XrMatrix4x4f &m,
                             const XrVector4f &v) {
  result.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12] * v.w;
  result.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13] * v.w;
  result.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w;
  result.w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w;
}

void ml::Linear::XrInvert(XrQuaternionf &quat) {
  quat.x = -quat.x;
  quat.y = -quat.y;
  quat.z = -quat.z;
  quat.w = quat.w;
  // XrNormalize(quat); //if it was normal before, it's normal after.
}

void ml::Linear::XrAdd(XrPosef &result, const XrPosef &a, const XrVector3f &b) {
  XrAdd(result.position, a.position, b);
}

void ml::Linear::XrLookAt(XrQuaternionf &result, const XrVector3f &source,
                          const XrVector3f &dest,
                          const XrVector3f &unit_forward) {
  XrVector3f to_vector, rot_axis;
  ml::Linear::XrSub(to_vector, dest, source);
  ml::Linear::XrNormalize(to_vector);
  ml::Linear::XrCross(rot_axis, unit_forward, to_vector);
  if (ml::Linear::XrSquareNorm(rot_axis) < 0.00001f) {
    rot_axis = {0.0f, 1.0f, 0.0f};
  }
  ml::Linear::XrNormalize(rot_axis);
  float dot = ml::Linear::XrDot(unit_forward, to_vector);
  float angle = acosf(dot);
  ml::Linear::XrCreateRotation(result, rot_axis, angle);
}
