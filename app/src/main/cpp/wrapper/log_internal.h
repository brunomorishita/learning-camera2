//
// Created by bruno on 13/06/2021.
//

#ifndef LEARNING_CAMERA2_LOG_INTERNAL_H
#define LEARNING_CAMERA2_LOG_INTERNAL_H

#include <android/log.h>

#define  LOG_TAG    "learning-camera2-native"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //LEARNING_CAMERA2_LOG_INTERNAL_H
