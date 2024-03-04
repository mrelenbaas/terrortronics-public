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

#pragma once

#include <app_framework/Components/Text.h>
#include <app_framework/Extensions/ExtPlaneDetection.h>
#include <app_framework/Geometry/Quad.h>
#include <app_framework/Scene/Node.h>

namespace ml {
struct PlaneNode {
  static XrColor4f SemanticTypeToColor(
      XrPlaneDetectorSemanticTypeEXT semanticType, float brightness = 1.0) {
    brightness = std::clamp(brightness, 0.0f, 1.0f);
    switch (semanticType) {
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT:
        return {brightness, 0.0f, 0.0f, 1.0f};
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT:
        return {0.0f, brightness, 0.0f, 1.0f};
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT:
        return {0.0f, 0.0f, brightness, 1.0f};
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT:
        return {brightness, 0.0f, brightness, 1.0f};
      default:
        return {brightness, brightness, 0.0f, 1.0f};
    }
  }

  static std::string PlaneString(const XrPlaneDetectorLocationEXT &plane) {
    std::string idstr = std::to_string(plane.planeId);
    switch (plane.semanticType) {
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT:
        idstr += " ceiling";
        break;
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT:
        idstr += " floor";
        break;
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT:
        idstr += " wall";
        break;
      case XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT:
        idstr += " platform";
        break;
      default:
        break;
    }
    switch (plane.orientation) {
      case XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT:
        idstr += " [H-U]";
        break;
      case XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT:
        idstr += " [H-D]";
        break;
      case XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT:
        idstr += " [V]";
        break;
      case XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT:
        idstr += " [A]";
        break;
      default:
        break;
    }
    return idstr;
  }

  PlaneNode()
      : root(nullptr),
        bounding_box(nullptr),
        boundary(nullptr),
        holes(nullptr),
        id_label(nullptr) {
  }

  PlaneNode(const XrPlaneDetectorLocationEXT &plane)
      : root(nullptr),
        bounding_box(nullptr),
        boundary(nullptr),
        holes(nullptr),
        id_label(nullptr) {
    Init(plane);
  }

  void Init(const XrPlaneDetectorLocationEXT &plane) {
    root = new Scene::Node();

    // setup bounding box node.
    bounding_box = new Scene::Node();
    auto quad = ml::Geometry::Quad::LineFactory();
    quad->material->use_material = true;
    quad->material->base_color = SemanticTypeToColor(plane.semanticType, 1.0f);

    bounding_box->AddComponent(quad);
    root->AddChild(bounding_box);

    // setup boundary node.
    boundary = new Scene::Node();
    root->AddChild(boundary);

    // setup holes node
    holes = new Scene::Node();
    root->AddChild(holes);
    holes->SetVisible(true);

    auto idstr = PlaneString(plane);
    std::tie(std::ignore, id_label) = Components::Text::Factory(
        idstr, 0.1f, {1.0f, 1.0f, 1.0f, 1.0f}, Components::Text::Center);
    id_label->SetTranslation(0.0f, 0.0f, 0.01f);
    root->AddChild(id_label);
  }

  void UpdateCaption(const XrPlaneDetectorLocationEXT &plane) const {
    auto c = id_label->Child(0)->GetComponent<Components::Text>();
    if (c) {
      c->SetText(PlaneString(plane));
    }
  }

  void HideHoles() const {
    auto children = holes->Children();
    for (auto child : children) {
      child->SetVisible(false);
    }
  }

  /* AddHole will create a new hole node if needed, or reused hole nodes
   * that have previously been hidden. */
  void AddHole(const std::vector<XrVector2f> &vertices, XrColor4f color) const {
    Scene::Node *hole = nullptr;
    for (auto child : holes->Children()) {
      if (!child->Visible()) {
        hole = child;
        break;
      }
    }
    if (!hole) {
      hole = new Scene::Node();
      holes->AddChild(hole);
    }
    SetPolygon(hole, vertices, color);
  }

  static void SetPolygon(Scene::Node *node,
                         const std::vector<XrVector2f> &vertices,
                         XrColor4f color) {
    std::shared_ptr<Components::Mesh> mesh =
        node->GetSharedComponent<Components::Mesh>();

    if (!mesh) {
      mesh = std::make_shared<Components::Mesh>();
      node->AddComponent(mesh);
    }

    mesh->vertices.resize(vertices.size());
    mesh->indices.resize(vertices.size() + 1);
    auto &verts = mesh->vertices;
    auto &indices = mesh->indices;
    for (size_t i = 0; i < vertices.size(); i++) {
      verts[i].pos = XrVector3f{vertices[i].x, vertices[i].y, 0.0f};
      verts[i].color = color;
      indices[i] = i;
    }
    indices[indices.size() - 1] = 0;

    mesh->type = ml::Components::Mesh::LINE_STRIP;
    mesh->material->use_material = false;
    node->BroadcastChange(Scene::Node::MESH_UPDATED);
  }

  Scene::Node *root;
  Scene::Node *bounding_box;
  Scene::Node *boundary;
  Scene::Node *holes;
  Scene::Node *id_label;
};
}  // namespace ml
