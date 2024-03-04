Plane Detection Sample Usage Notes
======================

### Prerequisites

Refer to https://developer-docs.magicleap.cloud/docs/guides/native/getting-started/native-getting-started

### What to expect
An spatial dialog will be visible showing the capabilities of the
plane detection system. It will also show a few checkboxes controlling
the operating mode of the detection.

There are two detection modes.

1. Bounding box, in this mode the plane 2D bounding boxes are visible including
   plane ID and type.

2. Polygon Mode, in this mode the polygons of the planes are shown including the holes
   if the appropriate checkbox is checked.


### Running on device

```
adb install ./app/build/outputs/apk/ml2/debug/com.magicleap.capi.xr.sample.plane_detection-debug.apk
adb shell am start -a android.intent.action.MAIN -n com.magicleap.capi.xr.sample.plane_detection/android.app.NativeActivity
```

### Removing from device

```
adb uninstall com.magicleap.capi.xr.sample.plane_detection
```
