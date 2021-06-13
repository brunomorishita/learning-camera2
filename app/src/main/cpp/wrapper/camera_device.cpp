//
// Created by bruno on 12/06/2021.
//

#include "camera_device.h"
#include "log_internal.h"

#include <android/native_window_jni.h>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>

namespace devices {

    CameraDevice::CameraDevice(ACameraManager *cameraManager, std::string id) {
        m_id = id;
        m_deviceStateCallbacks = std::make_unique<ACameraDevice_StateCallbacks>();
        m_deviceStateCallbacks->context = this;

        camera_status_t camera_status = ACAMERA_OK;
        camera_status = ACameraManager_openCamera(cameraManager, m_id.c_str(),
                                                  m_deviceStateCallbacks.get(), &m_cameraDevice);

        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to open camera device (id: %s)\n", m_id.c_str());
        }
    }

    CameraDevice::~CameraDevice() {
        ACameraDevice_close(m_cameraDevice);
    }
}