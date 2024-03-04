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

#include <stb_easy_font.h>

#include <tuple>

#include "../Scene/Node.h"
#include "Component.h"

namespace ml {

namespace Components {

class Text;
/*! Shared Pointer type of the Text Component. */
using TextPtr = std::shared_ptr<Components::Text>;

class Text : public IComponent {
 public:
  enum Align { Left, Right, Center };
  Text() = default;

  static std::tuple<TextPtr, Scene::Node *> Factory(
      const std::string &text, float text_height = 0.2f,
      const XrColor4f &color = {1.0f, 1.0f, 1.0f, 1.0f}, Align align = Left) {
    auto align_node = new Scene::Node();
    auto node = new Scene::Node();
    align_node->AddChild(node);
    std::shared_ptr<Text> component = std::make_shared<Text>();
    component->node_ = node;
    node->AddComponent(component);
    component->SetAlign(align);
    component->SetText(text, text_height, color);
    return std::make_tuple(component, align_node);
  }

  void SetAlign(Align align) {
    align_ = align;
    UpdatePos();
  }

  void SetText(const std::string &text) {
    SetText(text, text_height_, color_);
  }

  void SetText(const std::string &text, float text_height,
               const XrColor4f &color) {
    if (text_height == text_height_ && Linear::XrEqual(color, color_) &&
        text == text_) {
      return;
    }

    text_ = text;
    text_height_ = text_height;
    color_ = color;
    stb_easy_font_spacing(0.0f);
    int height = stb_easy_font_height((char *)text.c_str());
    text_width_ = stb_easy_font_width((char *)text.c_str());
    scale_ = text_height / height;

    struct FontData {
      XrVector3f pos;
      unsigned char color[4];
    };

    std::vector<FontData> font_data;
    font_data.resize(g_max_vertices_per_char * text.size());

    int num_quads = stb_easy_font_print(0, 0, (char *)text.c_str(), nullptr,
                                        font_data.data(),
                                        sizeof(FontData) * font_data.size());

    auto mesh = node_->GetSharedComponent<Mesh>();
    if (!mesh) {
      mesh = std::make_shared<Mesh>();
      node_->AddComponent(mesh);
    }
    const size_t vertex_count = num_quads * 4;
    mesh->vertices.resize(vertex_count);

    for (size_t i = 0; i < vertex_count; ++i) {
      Linear::XrScale(mesh->vertices[i].pos, font_data[i].pos, scale_);
      mesh->vertices[i].pos.y = -mesh->vertices[i].pos.y;
      mesh->vertices[i].color = color;
    }

    size_t num_indices = 6 * num_quads;
    mesh->indices.resize(num_indices);
    for (size_t i = 0; 6 * i < num_indices; ++i) {
      mesh->indices[6 * i + 5] = 4 * i + 0;
      mesh->indices[6 * i + 4] = 4 * i + 1;
      mesh->indices[6 * i + 3] = 4 * i + 2;
      mesh->indices[6 * i + 2] = 4 * i + 0;
      mesh->indices[6 * i + 1] = 4 * i + 2;
      mesh->indices[6 * i + 0] = 4 * i + 3;
    }
    mesh->material->use_material = false;
    mesh->type = ml::Components::Mesh::TRIANGLE;
    UpdatePos();
    node_->BroadcastChange(Scene::Node::MESH_UPDATED);
  }

 protected:
  static const constexpr size_t g_max_vertices_per_char = 4 * 11;
  float text_height_;
  int text_width_;
  XrColor4f color_;
  float scale_;
  Align align_;
  std::string text_;

  void UpdatePos() {
    switch (align_) {
      case Left:
        break;
      case Center:
        node_->SetTranslation(-text_width_ * scale_ / 2.0, 0.0f, 0.0f);
        break;
      case Right:
        node_->SetTranslation(-text_width_ * scale_, 0.0f, 0.0f);
        break;
    }
  }

 private:
  Scene::Node *node_;
};
}  // namespace Components
}  // namespace ml
