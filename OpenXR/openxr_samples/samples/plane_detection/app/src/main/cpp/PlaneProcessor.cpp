#include "PlaneProcessor.h"

using namespace ml;

PlaneProcessor::PlaneProcessor(XrCore *xr_core, Scene::Node *root_node)
    : xr_core_(xr_core),
      root_node_(root_node),
      state_(ScanState::StartOfScan),
      detection_supported_(false),
      scanning_active_(false) {
  Init();
}

void PlaneProcessor::Process(const XrFrameState &state,
                             const PlaneFilters &plane_filters) {
  if (!detection_supported_) {
    return;
  }

  switch (state_) {
    case ScanState::StartOfScan:
      if (BeginScan(state, plane_filters)) {
        state_ = ScanState::Scanning;
      }
      break;
    case ScanState::Scanning:
      if (Retrieve(state, plane_filters)) {
        state_ = ScanState::Stopped;
      }
      break;
    case ScanState::Stopped:
      if (scanning_active_) {
        state_ = ScanState::StartOfScan;
      }
      break;
  }
}

bool PlaneProcessor::BeginScan(const XrFrameState &state,
                               const PlaneFilters &plane_filters) {
  XrPosef pose;
  Linear::XrCreateIdentity(pose);
  XrPlaneDetectorBeginInfoEXT filter_info{
      XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT};

  auto const orientations = plane_filters.GetOrientations();
  auto const semantic_types = plane_filters.GetSemanticTypes();

  filter_info.baseSpace = xr_core_->ViewSpace();
  filter_info.time = state.predictedDisplayTime;
  filter_info.orientationCount = (uint32_t)orientations.size();
  filter_info.orientations = orientations.data();
  filter_info.semanticTypeCount = (uint32_t)semantic_types.size();
  filter_info.semanticTypes = semantic_types.data();
  filter_info.maxPlanes = 100;
  filter_info.boundingBoxExtent = {10.0f, 10.0f, 10.0f};
  filter_info.boundingBoxPose = pose;
  filter_info.minArea = 0.1f;

  auto const result = plane_detection_->xrBeginPlaneDetectionEXT(&filter_info);
  if (result != XR_SUCCESS) {
    ALOGE("Error: %d", result);
    return false;
  }
  return true;
}

void PlaneProcessor::Init() {
  try {
    plane_detection_ =
        std::make_unique<ml::Extensions::ExtPlaneDetection>(xr_core_, true);
    detection_supported_ = plane_detection_->IsSupported(
        XR_PLANE_DETECTION_CAPABILITY_PLANE_DETECTION_BIT_EXT);

  } catch (std::exception &e) {
    ALOGE("Unable to create extension: %s", e.what());
  }
}

bool PlaneProcessor::Retrieve(const XrFrameState &state,
                              const PlaneFilters &plane_filters) {
  XrPlaneDetectionStateEXT detection_state = XR_PLANE_DETECTION_STATE_NONE_EXT;

  if (plane_detection_->xrGetPlaneDetectionStateEXT(&detection_state) !=
      XR_SUCCESS) {
    ALOGE("xrGetPlaneDetectionStateEXT failed");
    return false;
  }

  switch (detection_state) {
    case XR_PLANE_DETECTION_STATE_PENDING_EXT:
      return false;
    case XR_PLANE_DETECTION_STATE_DONE_EXT:
      // Alright!
      break;
    default:
      ALOGE("Invalid plane detection state");
      return false;
  }

  XrPlaneDetectorGetInfoEXT info{XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT, nullptr,
                                 xr_core_->WorldSpace(),
                                 state.predictedDisplayTime};

  XrPlaneDetectorLocationsEXT locations{XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT};

  auto result = plane_detection_->xrGetPlaneDetectionsEXT(&info, &locations);
  if (result != XR_SUCCESS) {
    ALOGE("Error: %d", result);
    return false;
  }

  std::vector<XrPlaneDetectorLocationEXT> location_store(
      locations.planeLocationCountOutput,
      {XR_TYPE_PLANE_DETECTOR_LOCATION_EXT});
  locations.planeLocationCapacityInput = location_store.size();
  locations.planeLocations = location_store.data();
  result = plane_detection_->xrGetPlaneDetectionsEXT(&info, &locations);

  if (result != XR_SUCCESS) {
    ALOGE("Error: %d", result);
    return false;
  } else {
    for (auto &[plane_id, plane_node] : planes_) {
      // tag all planes as invisible unless we see them in the current
      // results.
      // then a bit further down delete the invisible planes.
      plane_node.root->SetVisible(false);
    }

    for (auto &loc : location_store) {
      AddPlane(loc, plane_filters);
    }

    std::vector<uint64_t> plane_delete_list;
    for (auto &[plane_id, plane_node] : planes_) {
      if (!plane_node.root->Visible()) {
        plane_delete_list.push_back(plane_id);
      }
    }

    if (!plane_delete_list.empty()) {
      /*
        WaitForFrameRenderFinished is a blocking call but it should not take
        more time than is available before the next frame. Deleting planes below
        will remove Vulkan memory buffers as well which should not be done while
        rendering is still ongoing, hence the protection here.
      */
      xr_core_->GraphicsDevice()->WaitForFrameRenderFinished();
      for (uint64_t plane_id : plane_delete_list) {
        root_node_->RemoveChild(planes_[plane_id].root);
        planes_.erase(plane_id);
      }
    }
  }
  return true;
}

void PlaneProcessor::AddPlane(const XrPlaneDetectorLocationEXT &plane,
                              const PlaneFilters &filters) {
  if (planes_.find(plane.planeId) == planes_.end()) {
    PlaneNode plane_node(plane);
    root_node_->AddChild(plane_node.root);
    planes_[plane.planeId] = plane_node;
  }

  PlaneNode &plane_node = planes_[plane.planeId];
  plane_node.UpdateCaption(plane);
  plane_node.root->SetPose(plane.pose);
  plane_node.root->SetVisible(true);

  XrColor4f color = PlaneNode::SemanticTypeToColor(plane.semanticType);

  if (filters.show_bounding_boxes) {
    plane_node.bounding_box->SetScale(plane.extents.width, plane.extents.height,
                                      1.0);
  }
  plane_node.bounding_box->SetVisible(filters.show_bounding_boxes);

  if (filters.show_vertices) {
    std::vector<XrVector2f> vertices;
    // Buffer index 0 is plane itself
    if (!GetVertices(plane, 0, vertices)) {
      return;
    }
    PlaneNode::SetPolygon(plane_node.boundary, vertices, color);
  }
  plane_node.boundary->SetVisible(filters.show_vertices);

  if (filters.show_holes) {
    // hide the existing holes and only show the holes as needed.
    plane_node.HideHoles();
    // add/show the holes as needed.
    // Buffer indices greater than 0 are holes
    std::vector<XrVector2f> vertices;
    for (uint32_t i = 1; i < plane.polygonBufferCount; i++) {
      if (!GetVertices(plane, i, vertices)) {
        return;
      }
      plane_node.AddHole(vertices, XrColor4f{1.0f, 0.0f, 0.0f, 1.0f});
    }
  }
  plane_node.holes->SetVisible(filters.show_holes);
}

bool PlaneProcessor::GetVertices(const XrPlaneDetectorLocationEXT &plane,
                                 uint32_t polygon_buffer_index,
                                 std::vector<XrVector2f> &vertices) {
  XrPlaneDetectorPolygonBufferEXT polygon_buffer_info{
      XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT};
  auto result = plane_detection_->xrGetPlanePolygonBufferEXT(
      plane.planeId, polygon_buffer_index, &polygon_buffer_info);
  if (result != XR_SUCCESS) {
    ALOGE("Unable to get vertex count. Error: %d", result);
    return false;
  }

  vertices.resize(polygon_buffer_info.vertexCountOutput);
  polygon_buffer_info.vertices = vertices.data();
  polygon_buffer_info.vertexCapacityInput = vertices.size();
  result = plane_detection_->xrGetPlanePolygonBufferEXT(
      plane.planeId, polygon_buffer_index, &polygon_buffer_info);
  if (result != XR_SUCCESS) {
    ALOGE("Unable to get vertex buffer data. Error: %d", result);
    return false;
  }
  return true;
}
