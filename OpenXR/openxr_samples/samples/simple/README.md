simple-xr-app Usage Notes
=========================

This example demonstrates a simple OpenXR application.

The graphics backend can run both in OpenGLES or Vulkan mode.

### Prerequisites

Refer to https://developer-docs.magicleap.cloud/docs/guides/native/getting-started/native-getting-started

### What to expect

* The left eye view will fade between transparent and red.
* The right eye view will fade between transparent and blue.
* After 5 seconds the application will terminate cleanly.

### Running on device

```
adb install ./app/build/outputs/apk/ml2/debug/com.magicleap.capi.xr.sample.simple-debug.apk
```

By default this uses the Vulkan backend.

To use the OpenGLES Graphics backend, run:

```
adb shell am start -a android.intent.action.MAIN -n com.magicleap.capi.xr.sample.simple/android.app.NativeActivity -e graphics opengles
```

To use the Vulkan Graphics backend, run:

```
adb shell am start -a android.intent.action.MAIN -n com.magicleap.capi.xr.sample.simple/android.app.NativeActivity -e graphics vulkan
```


### Removing from device

```
adb uninstall com.magicleap.capi.xr.sample.simple
```
