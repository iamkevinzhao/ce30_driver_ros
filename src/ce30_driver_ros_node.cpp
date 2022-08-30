// Ported to ROS2-Foxy by José-L @ SDLE (jlmvalbuena@sdle.es)

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud.hpp>
#include <geometry_msgs/msg/point32.hpp>
#include <ce30_driver/ce30_driver.h>

using namespace std;
using namespace ce30_driver;

class CE30D : public rclcpp::Node{
public:
  CE30D(const std::string & name):Node(name){
    declare_parameter("frame_id", frame_id_);
    get_parameter("frame_id",frame_id_);

    pc_pub_ = create_publisher<sensor_msgs::msg::PointCloud>("ce30_cloud",10);
  }
  
  ~CE30D(){
    RCLCPP_INFO(get_logger(), "Closing CE30 driver node");
  }

  void dataCallback(shared_ptr<PointCloud> cloud){
    sensor_msgs::msg::PointCloud pointcloud;
    pointcloud.header.stamp = get_clock().get()->now();
    pointcloud.header.frame_id = frame_id_;
    static int point_num = 320 * 20;
    pointcloud.points.reserve(point_num);
    for (auto& point : cloud->points) {
      static geometry_msgs::msg::Point32 ros_point;
      ros_point.x = point.x;
      ros_point.y = point.y;
      ros_point.z = point.z;
      pointcloud.points.push_back(ros_point);
    }
    if (pc_pub_->get_subscription_count()) {
      pc_pub_->publish(pointcloud);
    }
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr pc_pub_;
  std::string frame_id_ = "ce30";
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<CE30D>("ce30_node");
  UDPServer server;
  if (!server.Start()) {
    RCLCPP_ERROR(node->get_logger(), "Could not initialize CE30-D");
    return -1;
  }else{
    RCLCPP_INFO(node->get_logger(), "Starting CE30-D Pointcloud");
  }
  server.RegisterCallback(std::bind(&CE30D::dataCallback, node, std::placeholders::_1));

  while(rclcpp::ok()){
    server.SpinOnce();
  }

  rclcpp::shutdown();
  return 0;
}
