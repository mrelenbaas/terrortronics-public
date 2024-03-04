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

#include "../../include/app_framework/Components/Mesh.h"

#include <mikktspace.h>

using namespace ml::Components;

bool Mesh::GenerateTangents() {
  struct TangentContext {
    std::vector<Geometry::Vertex> vertices;
    std::vector<uint16_t> indices;
    Mesh *mesh;
    int next_index;
    int next_vertex;
  };

  const int VERTEX_COUNT = 3;
  SMikkTSpaceInterface interface = {
      .m_getNumFaces = [](const SMikkTSpaceContext *pContext) -> int {
        auto *ctx = reinterpret_cast<TangentContext *>(pContext->m_pUserData);
        auto &mesh = ctx->mesh;
        return mesh->indices.size() / VERTEX_COUNT;
      },
      .m_getNumVerticesOfFace = [](const SMikkTSpaceContext *pContext,
                                   const int iFace) -> int {
        return VERTEX_COUNT;
      },
      .m_getPosition =
          [](const SMikkTSpaceContext *pContext, float fvPosOut[],
             const int iFace, const int iVert) {
            auto *ctx =
                reinterpret_cast<TangentContext *>(pContext->m_pUserData);
            auto &mesh = ctx->mesh;
            size_t index = (iFace * VERTEX_COUNT) + iVert;
            assert(index < mesh->indices.size());
            auto vertex_index = mesh->indices[index];
            const auto &vertex = mesh->vertices[vertex_index];
            fvPosOut[0] = vertex.pos.x;
            fvPosOut[1] = vertex.pos.y;
            fvPosOut[2] = vertex.pos.z;
          },
      .m_getNormal =
          [](const SMikkTSpaceContext *pContext, float fvNormOut[],
             const int iFace, const int iVert) {
            auto *ctx =
                reinterpret_cast<TangentContext *>(pContext->m_pUserData);
            auto &mesh = ctx->mesh;
            size_t index = (iFace * VERTEX_COUNT) + iVert;
            assert(index < mesh->indices.size());
            auto vertex_index = mesh->indices[index];
            const auto &vertex = mesh->vertices[vertex_index];
            fvNormOut[0] = vertex.normal.x;
            fvNormOut[1] = vertex.normal.y;
            fvNormOut[2] = vertex.normal.z;
          },
      .m_getTexCoord =
          [](const SMikkTSpaceContext *pContext, float fvTexcOut[],
             const int iFace, const int iVert) {
            auto *ctx =
                reinterpret_cast<TangentContext *>(pContext->m_pUserData);
            auto &mesh = ctx->mesh;
            size_t index = (iFace * VERTEX_COUNT) + iVert;
            assert(index < mesh->indices.size());
            auto vertex_index = mesh->indices[index];
            const auto &vertex = mesh->vertices[vertex_index];
            fvTexcOut[0] = vertex.uv.x;
            fvTexcOut[1] = -vertex.uv.y;
          },
      .m_setTSpaceBasic =
          [](const SMikkTSpaceContext *pContext, const float fvTangent[],
             const float fSign, const int iFace, const int iVert) {
            auto *ctx =
                reinterpret_cast<TangentContext *>(pContext->m_pUserData);
            auto &mesh = ctx->mesh;
            if (iFace == 0 && iVert == 0) {
              // resize as we have to reindex this array.
              ctx->vertices.resize(mesh->indices.size());
              ctx->indices.resize(mesh->indices.size());
              // first naive approach
            }

            size_t index = (iFace * VERTEX_COUNT) + iVert;
            assert(index < mesh->indices.size());
            auto vertex_index = mesh->indices[index];
            const auto &source_vertex = mesh->vertices[vertex_index];

            // really check if we can merge by looking for similar vertices.
            ctx->vertices[ctx->next_vertex] = source_vertex;
            ctx->indices[ctx->next_index] = ctx->next_vertex;
            auto &new_vertex = ctx->vertices[ctx->next_vertex];

            ctx->next_vertex++;
            ctx->next_index++;

            new_vertex.tangent.x = fvTangent[0];
            new_vertex.tangent.y = fvTangent[1];
            new_vertex.tangent.z = fvTangent[2];
            new_vertex.tangent.w = fSign;
          }};

  TangentContext ctx;
  ctx.mesh = this;
  ctx.next_index = 0;
  ctx.next_vertex = 0;

  SMikkTSpaceContext context{.m_pInterface = &interface, .m_pUserData = &ctx};

  if (genTangSpaceDefault(&context) != 0) {
    vertices = std::move(ctx.vertices);
    indices = std::move(ctx.indices);
    return true;
  }
  return false;
}
