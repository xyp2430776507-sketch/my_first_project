#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/point_field.hpp>

namespace {

const sensor_msgs::msg::PointField *FindField(
    const sensor_msgs::msg::PointCloud2 &cloud, const std::string &name) {
  for (const auto &field : cloud.fields) {
    if (field.name == name) return &field;
  }
  return nullptr;
}

float ReadFloat(const uint8_t *point, const sensor_msgs::msg::PointField *field,
                float fallback = 0.0F) {
  if (!field || field->datatype != sensor_msgs::msg::PointField::FLOAT32) {
    return fallback;
  }
  float value;
  std::memcpy(&value, point + field->offset, sizeof(value));
  return value;
}

void Write(void *destination, const void *source, std::size_t size) {
  std::memcpy(destination, source, size);
}

}  // namespace

class SimCloudAdapter final : public rclcpp::Node {
 public:
  SimCloudAdapter() : Node("sim_cloud_adapter") {
    auto input_qos = rclcpp::SensorDataQoS();
    auto output_qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
    publisher_ = create_publisher<sensor_msgs::msg::PointCloud2>(
        "/points_raw", output_qos);
    subscription_ = create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar", input_qos,
        [this](sensor_msgs::msg::PointCloud2::ConstSharedPtr input) {
          Convert(*input);
        });
  }

 private:
  void Convert(const sensor_msgs::msg::PointCloud2 &input) {
    const auto *x_field = FindField(input, "x");
    const auto *y_field = FindField(input, "y");
    const auto *z_field = FindField(input, "z");
    const auto *intensity_field = FindField(input, "intensity");
    if (!x_field || !y_field || !z_field || input.point_step == 0) {
      RCLCPP_ERROR_THROTTLE(get_logger(), *get_clock(), 5000,
                            "Input cloud lacks float32 x/y/z fields");
      return;
    }

    sensor_msgs::msg::PointCloud2 output;
    output.header = input.header;
    output.header.frame_id = "livox_frame";
    output.height = input.height;
    output.width = input.width;
    output.is_bigendian = false;
    output.is_dense = input.is_dense;
    output.fields.resize(6);
    const char *names[] = {"x", "y", "z", "intensity", "time", "ring"};
    const uint32_t offsets[] = {0, 4, 8, 16, 20, 24};
    const uint8_t types[] = {
        sensor_msgs::msg::PointField::FLOAT32,
        sensor_msgs::msg::PointField::FLOAT32,
        sensor_msgs::msg::PointField::FLOAT32,
        sensor_msgs::msg::PointField::FLOAT32,
        sensor_msgs::msg::PointField::FLOAT32,
        sensor_msgs::msg::PointField::UINT16};
    for (std::size_t i = 0; i < output.fields.size(); ++i) {
      output.fields[i].name = names[i];
      output.fields[i].offset = offsets[i];
      output.fields[i].datatype = types[i];
      output.fields[i].count = 1;
    }
    output.point_step = 32;
    output.row_step = output.point_step * output.width;
    output.data.assign(static_cast<std::size_t>(output.row_step) * output.height,
                       0U);

    const uint32_t rows = std::max(1U, input.height);
    const uint32_t columns = std::max(1U, input.width);
    for (uint32_t row = 0; row < rows; ++row) {
      for (uint32_t column = 0; column < columns; ++column) {
        const std::size_t input_offset =
            static_cast<std::size_t>(row) * input.row_step +
            static_cast<std::size_t>(column) * input.point_step;
        const std::size_t output_offset =
            static_cast<std::size_t>(row) * output.row_step +
            static_cast<std::size_t>(column) * output.point_step;
        if (input_offset + input.point_step > input.data.size()) continue;
        auto *destination = output.data.data() + output_offset;
        const auto *source = input.data.data() + input_offset;
        const float x = ReadFloat(source, x_field);
        const float y = ReadFloat(source, y_field);
        const float z = ReadFloat(source, z_field);
        const float intensity = ReadFloat(source, intensity_field);
        const float time = 0.1F * static_cast<float>(column) /
                           static_cast<float>(columns);
        const uint16_t ring = static_cast<uint16_t>(row);
        Write(destination + 0, &x, sizeof(x));
        Write(destination + 4, &y, sizeof(y));
        Write(destination + 8, &z, sizeof(z));
        Write(destination + 16, &intensity, sizeof(intensity));
        Write(destination + 20, &time, sizeof(time));
        Write(destination + 24, &ring, sizeof(ring));
      }
    }
    publisher_->publish(std::move(output));
  }

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimCloudAdapter>());
  rclcpp::shutdown();
  return 0;
}
