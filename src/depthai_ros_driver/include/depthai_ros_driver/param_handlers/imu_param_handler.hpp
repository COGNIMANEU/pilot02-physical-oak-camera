#pragma once

#include <memory>
#include <string>
#include <vector>

#include "depthai-shared/properties/IMUProperties.hpp"
#include "depthai/pipeline/datatype/CameraControl.hpp"
#include "depthai_bridge/ImuConverter.hpp"
#include "depthai_ros_driver/param_handlers/base_param_handler.hpp"

namespace dai {
namespace node {
class IMU;
}
}  // namespace dai

namespace rclcpp {
class Node;
class Parameter;
}  // namespace rclcpp

namespace depthai_ros_driver {
namespace param_handlers {
namespace imu {
enum class ImuMsgType { IMU, IMU_WITH_MAG, IMU_WITH_MAG_SPLIT };
}
class ImuParamHandler : public BaseParamHandler {
   public:
    explicit ImuParamHandler(std::shared_ptr<rclcpp::Node> node, const std::string& name);
    ~ImuParamHandler();
    void declareParams(std::shared_ptr<dai::node::IMU> imu, const std::string& imuType);
    dai::CameraControl setRuntimeParams(const std::vector<rclcpp::Parameter>& params) override;
    std::unordered_map<std::string, dai::ros::ImuSyncMethod> syncMethodMap;
    std::unordered_map<std::string, imu::ImuMsgType> messagetTypeMap;
    std::unordered_map<std::string, dai::IMUSensor> rotationVectorTypeMap;
    std::unordered_map<std::string, dai::IMUSensor> accelerometerModeMap;
    std::unordered_map<std::string, dai::IMUSensor> gyroscopeModeMap;
    std::unordered_map<std::string, dai::IMUSensor> magnetometerModeMap;
    imu::ImuMsgType getMsgType();
    dai::ros::ImuSyncMethod getSyncMethod();
};
}  // namespace param_handlers
}  // namespace depthai_ros_driver
