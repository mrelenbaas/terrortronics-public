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

#include <memory>
#include <string>
#include <vector>

namespace ml {

class Application;
class SystemHelper;
namespace Scene {
class Node;
}

/*! \brief Helper class that requests Android Permissions for you.
 *
 * It also pops up a helpful dialog to let the user know not all permissions
 * were granted, if the first request failed.
 *
 */
class PermissionHelper {
 public:
  PermissionHelper(const std::vector<std::string>& permissions,
                   Application* application);

  /*! \brief Call before your code that creates restricted resources.
   *
   * @return true if all permissions were granted
   * @return false if there are ungranted permissions.
   *
   * This method will not invoke the OS permission request dialog.
   *
   * */
  bool PermissionGranted();

  /*! \brief Requests any permissions that were not yet granted.
   *
   * @return true if at the time of the call all permissions were already
   * granted.
   *
   * This is an asynchronous call, if it returns true all permissions are indeed
   * already granted, false means that a popup will appear for the user showing
   * them the OS permission request dialog. The application will loose focus.
   *
   * Call this when transitioning to VISIBLE.
   *
   */
  bool RequestPermissions();

 private:
  std::vector<std::string> GetUngrantedPermissions() const;
  Application* application_;
  bool first_request_;
  std::vector<std::string> permissions_;
  std::shared_ptr<ml::SystemHelper> system_helper_;
  Scene::Node* gui_;
};

}  // namespace ml
