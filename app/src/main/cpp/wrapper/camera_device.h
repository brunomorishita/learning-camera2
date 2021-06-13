//
// Created by bruno on 12/06/2021.
//

#ifndef LEARNING_CAMERA2_CAMERA_DEVICE_H
#define LEARNING_CAMERA2_CAMERA_DEVICE_H

#include <string>

struct ACameraDevice_StateCallbacks;
struct ACameraDevice;
struct ACameraManager;

namespace devices {

    class CameraDevice {
    public:
        CameraDevice() = delete;
        CameraDevice(ACameraManager *cameraManager, std::string id);
        ~CameraDevice();

    private:
        ACameraDevice* m_cameraDevice = nullptr;
        std::unique_ptr<ACameraDevice_StateCallbacks> m_deviceStateCallbacks = nullptr;
        std::string m_id;
    };
}

#endif //LEARNING_CAMERA2_CAMERA_DEVICE_H
