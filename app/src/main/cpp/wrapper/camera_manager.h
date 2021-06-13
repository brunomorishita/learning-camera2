//
// Created by bruno on 12/06/2021.
//

#ifndef LEARNING_CAMERA2_CAMERA_MANAGER_H
#define LEARNING_CAMERA2_CAMERA_MANAGER_H

#include <memory>
#include <vector>
#include <string>
#include <map>

struct ACameraManager;
struct ACameraIdList;

namespace devices {
    class CameraDevice;

    enum class CAMERA_LENS_FACING {
        FRONT                                        = 0,
        BACK                                         = 1,
        EXTERNAL                                     = 2,
    };

    struct CameraMetadata {
        CAMERA_LENS_FACING camera_lens_facing = CAMERA_LENS_FACING::BACK;
    };

    class CameraManager {
    public:
        CameraManager();
        ~CameraManager();

        std::vector<std::string> getCameraIds();
        CameraMetadata getCameraCharacteristics(std::string id);
        std::shared_ptr<devices::CameraDevice> getCameraDevice(std::string id);

    private:
        ACameraManager *m_cameraManager = nullptr;
        ACameraIdList *m_cameraIdList = nullptr;
        std::map<std::string, std::shared_ptr<devices::CameraDevice>> m_devices;
    };
}

#endif //LEARNING_CAMERA2_CAMERA_MANAGER_H
