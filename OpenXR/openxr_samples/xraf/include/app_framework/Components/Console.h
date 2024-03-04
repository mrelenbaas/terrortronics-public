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

#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <tuple>

#include "../Scene/Node.h"
#include "Component.h"

namespace ml {

class Application;

namespace Components {

class Console;
using ConsolePtr = std::shared_ptr<Console>;

/*! \brief A simple Virtual "Console", outputing text. */
class Console : public Components::IComponent {
 public:
  /*! \brief Console Constructor  */
  Console(ml::Application *application, uint16_t max_lines, uint32_t flags,
          Scene::Node *&node);

  enum Flags { NONE = 0, CLOSE_APP_ON_CLOSE_CONSOLE };
  /*! \brief Console Factory
   *
   * @param application the main application object.
   * @param max_lines  number of lines to show at maximum, old lines are removed
   * when the number is exceeded.
   * @param flags Flags to use for the console.
   * @return tuple of the console component and the node.
   */
  static std::tuple<ConsolePtr, Scene::Node *> Factory(
      ml::Application *application, uint16_t max_lines, uint32_t flags = NONE);

  /*! \brief Prints into the Gui console.
   *
   *  Uses same syntax as vprintf.
   *  Note: thread-safe.
   */
  void Print(const char *format, ...);

  /*! \brief Prints into the Gui console.
   *
   *  Uses same syntax as vprintf.
   *  Note: thread-safe.
   */
  void VPrint(const char *format, va_list args);

  /*! \brief Clears the Gui console.
   *  Note: thread-safe.
   */
  void Clear();

 private:
  std::mutex mutex_;
  uint16_t max_lines_;
  uint32_t flags_;
  std::list<std::string> lines_;
};

}  // namespace Components
}  // namespace ml
