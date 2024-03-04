hand-tracking Usage Notes
=========================

XR_EXT_hand_tracking sample application


### Prerequisites

Refer to https://developer-docs.magicleap.cloud/docs/guides/native/getting-started/native-getting-started

### What to expect

When looking at your hands you should see cubes at your finger joints. Bubbles
will be floating up around you which you can pop using your hands.

Caveats:

1. Cubes do not have orientation information.
2. Palm is not tracked.

### Running on device

```
adb install ./app/build/outputs/apk/ml2/debug/com.magicleap.capi.xr.sample.hand_tracking-debug.apk
adb shell am start -a android.intent.action.MAIN -n com.magicleap.capi.xr.sample.hand_tracking/android.app.NativeActivity
```

### Removing from device

```
adb uninstall com.magicleap.capi.xr.sample.hand_tracking
```
