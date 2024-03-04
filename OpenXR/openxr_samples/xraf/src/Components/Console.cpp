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

#include "../../include/app_framework/Components/Console.h"

#include "../../include/app_framework/Application.h"
#include "../../include/app_framework/Components/Gui.h"

using namespace ml::Components;

std::tuple<ConsolePtr, ml::Scene::Node *> Console::Factory(
    ml::Application *application, uint16_t max_lines, uint32_t flags) {
  Scene::Node *node = nullptr;
  auto console = std::make_shared<Console>(application, max_lines, flags, node);
  return std::tie(console, node);
}

Console::Console(ml::Application *application, uint16_t max_lines,
                 uint32_t flags, Scene::Node *&node)
    : max_lines_(max_lines), flags_(flags) {
  uint32_t height = std::min(60 + max_lines * 17, 500);

  node = application->CreateGui(
      500, height, 500, Gui::DefaultGuiFlags,
      [this, application](IGui &gui, const XrFrameState &frame_state) {
        bool is_running = true;
        bool *is_running_ptr =
            (flags_ & Console::CLOSE_APP_ON_CLOSE_CONSOLE) != 0 ? &is_running
                                                                : nullptr;

        if (gui.BeginDialog("Console", is_running_ptr)) {
          if (ImGui::Button("Clear")) {
            std::scoped_lock lock_(mutex_);
            lines_.clear();
          }

          ImGui::BeginChild("Output");
          {
            std::scoped_lock lock_(mutex_);
            for (const std::string &line : lines_) {
              ImGui::Text("%s", line.c_str());
            }
          }
          ImGui::EndChild();
        }
        gui.EndDialog();

        if (!is_running) {
          application->FinishActivity();
        }
      });
}

void Console::Print(const char *format, ...) {
  va_list arguments;
  va_start(arguments, format);
  VPrint(format, arguments);
  va_end(arguments);
}

void Console::VPrint(const char *format, va_list args) {
  va_list arguments;

  // calculate the length of the string to allocate.
  va_copy(arguments, args);
  const int length = vsnprintf(nullptr, 0, format, arguments) + 1;
  va_end(arguments);

  // allocate the string
  std::string s;
  s.resize(length);

  // 'print' to the string.
  va_copy(arguments, args);
  vsnprintf(s.data(), (size_t)length, format, arguments);
  va_end(arguments);

  {
    std::scoped_lock lock_(mutex_);
    // put in the string list buffer.
    lines_.push_back(s);
    while (lines_.size() > max_lines_) {
      lines_.pop_front();
    }
  }
}
void Console::Clear() {
  lines_.clear();
}
