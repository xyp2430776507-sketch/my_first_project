#include <cmath>
#include <cstdint>
#include <memory>
#include <string>

#include <livox_ros_driver2/msg/custom_msg.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>

class LivoxCustomToPointCloud2 : public rclcpp::Node {
public:
  LivoxCustomToPointCloud2() : Node("livox_custom_to_pointcloud2") {
    input_topic_ = declare_parameter<std::string>("input_topic", "/livox/lidar");
    output_topic_ = declare_parameter<std::string>("output_topic", "/livox/points");
    frame_override_ = declare_parameter<std::string>("frame_override", "");
    use_current_time_ = declare_parameter<bool>("use_current_time", false);
    min_range_ = declare_parameter<double>("min_range", 0.05);
    max_range_ = declare_parameter<double>("max_range", 200.0);

    publisher_ = create_publisher<sensor_msgs::msg::PointCloud2>(
        output_topic_, rclcpp::SensorDataQoS());
    subscription_ = create_subscription<livox_ros_driver2::msg::CustomMsg>(
        input_topic_, rclcpp::SensorDataQoS(),
        std::bind(&LivoxCustomToPointCloud2::convert, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "Converting %s -> %s", input_topic_.c_str(), output_topic_.c_str());
  }

private:
  bool validPoint(const livox_ros_driver2::msg::CustomPoint &point) const {
    if (!std::isfinite(point.x) || !std::isfinite(point.y) || !std::isfinite(point.z)) {
      return false;
    }
    const double squared_range = static_cast<double>(point.x) * point.x +
                                 static_cast<double>(point.y) * point.y +
                                 static_cast<double>(point.z) * point.z;
    return squared_range >= min_range_ * min_range_ &&
           squared_range <= max_range_ * max_range_;
  }

  void convert(const livox_ros_driver2::msg::CustomMsg::SharedPtr message) {
    std::size_t valid_count = 0;
    for (const auto &point : message->points) {
      valid_count += validPoint(point) ? 1U : 0U;
    }

    sensor_msgs::msg::PointCloud2 cloud;
    cloud.header = message->header;
    if (use_current_time_) {
      cloud.header.stamp = now();
    }
    if (!frame_override_.empty()) {
      cloud.header.frame_id = frame_override_;
    }
    cloud.height = 1;
    cloud.is_dense = true;
    cloud.is_bigendian = false;

    sensor_msgs::PointCloud2Modifier modifier(cloud);
    // Keep the RViz display topic in the conventional 16-byte XYZI layout.
    // The original CustomMsg retains offset_time, tag, and line for SLAM use.
    modifier.setPointCloud2Fields(
        4,
        "x", 1, sensor_msgs::msg::PointField::FLOAT32,
        "y", 1, sensor_msgs::msg::PointField::FLOAT32,
        "z", 1, sensor_msgs::msg::PointField::FLOAT32,
        "intensity", 1, sensor_msgs::msg::PointField::FLOAT32);
    modifier.resize(valid_count);

    sensor_msgs::PointCloud2Iterator<float> x(cloud, "x");
    sensor_msgs::PointCloud2Iterator<float> y(cloud, "y");
    sensor_msgs::PointCloud2Iterator<float> z(cloud, "z");
    sensor_msgs::PointCloud2Iterator<float> intensity(cloud, "intensity");

    for (const auto &point : message->points) {
      if (!validPoint(point)) {
        continue;
      }
      *x = point.x;
      *y = point.y;
      *z = point.z;
      *intensity = static_cast<float>(point.reflectivity);
      ++x;
      ++y;
      ++z;
      ++intensity;
    }

    publisher_->publish(std::move(cloud));
  }

  std::string input_topic_;
  std::string output_topic_;
  std::string frame_override_;
  bool use_current_time_;
  double min_range_;
  double max_range_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::Subscription<livox_ros_driver2::msg::CustomMsg>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LivoxCustomToPointCloud2>());
  rclcpp::shutdown();
  return 0;
}
