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

#include <imgui.h>

namespace ml {

class IAsset;

class IGui {
 public:
  /*! \brief BeginDialog used to start an ImGui dialog.

   Use this in place of ImGui::Begin to allow for extra functionality like 3d
   dragging.

   Must be called in the same order of the Gui Node creation!

   Don't use "Dialog #" (#=number) as the name as this will confuse the ImGui
   system.
  */
  virtual bool BeginDialog(
      const char* name, bool* open = nullptr,
      ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove |
                               ImGuiWindowFlags_NoResize |
                               ImGuiWindowFlags_NoCollapse) = 0;

  /*! \brief EndDialog used to finish building an ImGui dialog. */
  virtual void EndDialog() = 0;

  /*! \brief Adds provided font into the ImGui's FontAtlas.

  Provided *font_buffer* should be valid for as long as the font is used.
  *is_owned* can be used to let ImGui take care of memory deallocation. ImGui
  uses free(). *merge* can be used to merge provided *glyph_ranges* of given
  font into the currently loaded font.

  Note that ImGui DOES NOT support neither RTL, nor BiDi font rendering. Even if
  Arabic font is loaded it will still be displayed LTR. A quick hack is to
  reverse the unicode text before displaying it (so it will look like it was
  displayed in RTL).

  Returns pointer to the loaded font. Nullptr if loading failed.

  Example usage:

  \code{.cpp}
  AAsset* font_jpn_asset = LoadSomeAssetFile(); // E.x. "NotoSansJP-Medium.otf"
  loaded as an asset. AAsset* font_ara_asset = LoadSomeAssetFile(); // E.x.
  "NotoSansArabic-Medium.ttf" loaded as an asset. ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontDefault(); // Add default font to merge the rest later into
  it

  auto font_jpn_len = AAsset_getLength(font_jpn_asset);
  void* font_buffer_jpn = malloc(font_jpn_len);
  AAsset_read(font_jpn_asset, font_buffer_jpn, font_jpn_len);

  auto font_ara_len = AAsset_getLength(font_ara_asset);
  void* font_buffer_ara = malloc(font_ara_len);
  AAsset_read(font_ara_asset, font_buffer_ara, font_ara_len);

  // We pass is_owned=true to let ImGuiFontAtlas deallocate font memory for us
  LoadFont(font_buffer_jpn, font_jpn_len, io.Fonts->GetGlyphRangesJapanese(),
  true, 20.f, true); LoadFont(font_buffer_ara, font_ara_len,
  GetGlyphRangesArabic(), true, 30.f, true); \endcode
  */
  virtual ImFont* LoadFont(void* font_buffer, size_t font_buffer_len,
                           const ImWchar* glyph_ranges = nullptr,
                           bool is_owned = false, float font_size = 20.f,
                           bool merge = true) = 0;

  /*! \brief Loads font from provided asset and adds loaded font into the
    ImGui's FontAtlas.

    Returns pointer to the loaded font. Nullptr if loading failed.
  */
  virtual ImFont* LoadFont(std::shared_ptr<IAsset> font_asset,
                           const ImWchar* glyph_ranges = nullptr,
                           float font_size = 20.f, bool merge = true) = 0;
};

}  // namespace ml