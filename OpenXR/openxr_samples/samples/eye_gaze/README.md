eye_gaze Usage Notes
====================

XR_EXT_eye_gaze_interaction sample application


### Prerequisites

Refer to https://developer-docs.magicleap.cloud/docs/guides/native/getting-started/native-getting-started

### What to expect

When looking around you should see where you're looking (a cube should float in air in the direction
of Your gaze!). Bubbles will be floating up around you, which you can pop using your gaze!

### Running on device

```
adb install ./app/build/outputs/apk/ml2/debug/com.magicleap.capi.xr.sample.eye_gaze-debug.apk
adb shell am start -a android.intent.action.MAIN -n com.magicleap.capi.xr.sample.eye_gaze/android.app.NativeActivity
```

### Removing from device

```
adb uninstall com.magicleap.capi.xr.sample.eye_gaze
```
