#pragma once

#include <app_framework/Extensions/ExtPlaneDetection.h>
#include <app_framework/Scene/Node.h>
#include <app_framework/XrCore.h>

#include "PlaneFilters.h"
#include "PlaneNode.h"

namespace ml {

class PlaneProcessor {
 public:
  PlaneProcessor(XrCore *xr_core, Scene::Node *root_node);

  bool IsPlaneDetectionSupported() const {
    return detection_supported_;
  }

  bool IsPlaneDetectionCapSupported(uint64_t capability) const {
    return plane_detection_->IsSupported(capability);
  }

  bool IsScanInProgress() const {
    return scanning_active_;
  }

  void Process(const XrFrameState &state, const PlaneFilters &plane_filters);

  void Start() {
    scanning_active_ = true;
  }

  void Stop() {
    scanning_active_ = false;
  }

 private:
  enum class ScanState { StartOfScan, Scanning, Stopped };

  XrCore *xr_core_;
  Scene::Node *root_node_;
  std::unique_ptr<ml::Extensions::ExtPlaneDetection> plane_detection_;
  std::unordered_map<uint64_t, PlaneNode> planes_;
  ScanState state_;
  bool detection_supported_;
  bool scanning_active_;

  void Init();
  bool BeginScan(const XrFrameState &state, const PlaneFilters &plane_filters);
  bool Retrieve(const XrFrameState &state, const PlaneFilters &plane_filters);
  void AddPlane(const XrPlaneDetectorLocationEXT &plane,
                const PlaneFilters &filters);
  bool GetVertices(const XrPlaneDetectorLocationEXT &plane,
                   uint32_t polygon_buffer_index,
                   std::vector<XrVector2f> &vertices);
};

}  // namespace ml