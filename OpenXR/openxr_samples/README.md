Samples
=======

Prerequisites

1. NDK 25.0.8775105
2. CMake 3.22.1
3. Android Studio
4. Magic Leap SDK (MLSDK)

Refer to https://developer-docs.magicleap.cloud/docs/guides/native/getting-started/native-getting-started for more details.

Commandline Building
====================

To build individual samples simply change directory to the toplevel of the sample and run

```sh
./gradlew build -Proot_path=<absolute path to directory containing the signing artifacts ending with />
```

Or to build all samples change directory to the samples directory and type:

```sh
python build.py
```


NOTE: Currently the Application Simulator does not yet support OpenXR samples.


