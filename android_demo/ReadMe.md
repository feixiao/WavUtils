### Build:
#### Linux && OSX
```shell
mkdir build
cd build && cmake ../
make -j 4
```

#### Android
```shell
# android-ndk-r23
# android-ndk-r21e
export ANDROID_NDK=~/Android/ndk/android-ndk-r23
mkdir android_build && cd android_build

cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
	-DANDROID_ABI="arm64-v8a" \
	-DANDROID_PLATFORM=android-29 \
	-DCMAKE_SYSTEM_NAME=Android \
	-DCMAKE_BUILD_TYPE=RELEASE \
	../
```