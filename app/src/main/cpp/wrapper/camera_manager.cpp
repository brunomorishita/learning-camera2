//
// Created by bruno on 12/06/2021.
//

#include "camera_manager.h"
#include "log_internal.h"
#include "camera_device.h"

#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>

namespace devices {

    CameraManager::CameraManager() {
        camera_status_t camera_status = ACAMERA_OK;

        m_cameraManager = ACameraManager_create();

        camera_status = ACameraManager_getCameraIdList(m_cameraManager, &m_cameraIdList);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to get camera id list (reason: %d)\n", camera_status);
            return;
        }
    }

    CameraManager::~CameraManager() {
        if (m_cameraManager)
            ACameraManager_delete(m_cameraManager);

        if (m_cameraIdList)
            ACameraManager_deleteCameraIdList(m_cameraIdList);
    }

    std::vector<std::string> CameraManager::getCameraIds() {
        std::vector<std::string> ret;

        for (int i = 0; i < m_cameraIdList->numCameras; ++i) {
            const char* selectedCameraId = m_cameraIdList->cameraIds[i];
            ret.push_back(std::string(selectedCameraId));
        }

        return ret;
    }

    CameraMetadata CameraManager::getCameraCharacteristics(std::string id) {
        camera_status_t camera_status = ACAMERA_OK;
        ACameraMetadata *cameraMetadata = nullptr;

        CameraMetadata metadata;

        camera_status = ACameraManager_getCameraCharacteristics(m_cameraManager, id.c_str(),
                                                                &cameraMetadata);
        if (camera_status != ACAMERA_OK) {
            ACameraMetadata_free(cameraMetadata);
            LOGE("Failed to get camera meta data of ID:%s\n", id.c_str());
            return metadata;
        }

        ACameraMetadata_const_entry entry;
        if(ACameraMetadata_getConstEntry(cameraMetadata, ACAMERA_LENS_FACING, &entry) == ACAMERA_OK)
        {
            auto facing = static_cast<acamera_metadata_enum_android_lens_facing_t>(entry.data.u8[0]);
            if(facing == ACAMERA_LENS_FACING_BACK)
                metadata.camera_lens_facing = CAMERA_LENS_FACING::BACK;
            else if (facing == ACAMERA_LENS_FACING_FRONT)
                metadata.camera_lens_facing = CAMERA_LENS_FACING::FRONT;
            else
                metadata.camera_lens_facing = CAMERA_LENS_FACING::EXTERNAL;
        }

        ACameraMetadata_free(cameraMetadata);

        return metadata;
    }

    std::shared_ptr<devices::CameraDevice> CameraManager::getCameraDevice(std::string id) {
        if (auto dev{m_devices.find(id ) }; dev != std::end(m_devices ) ) {
            auto[ key, value ] { *dev };
            return value;
        }

        auto cameraDevice = std::make_shared<devices::CameraDevice>(m_cameraManager, id);
        m_devices.emplace(id, cameraDevice);

        return cameraDevice;
    }
}  // namespace devices