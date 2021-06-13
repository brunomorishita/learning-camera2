# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("learning_camera2")

set(Project_SOURCES learning-camera2-jni.cpp
        wrapper/camera_device.cpp
        wrapper/camera_manager.cpp)

add_library( native-lib SHARED ${Project_SOURCES})

target_link_libraries( native-lib
        android
        dl
        log
        camera2ndk)