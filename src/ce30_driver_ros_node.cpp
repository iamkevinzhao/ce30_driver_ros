#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <ce30_driver/ce30_driver.h>

using namespace std;
using namespace ce30_driver;

ros::Publisher gPub;

void DataReceiveCB(shared_ptr<PointCloud> cloud) {
  sensor_msgs::PointCloud pointcloud;
  pointcloud.header.stamp = ros::Time::now();
  pointcloud.header.frame_id = "map";
  static int point_num = 320 * 20;
  pointcloud.points.reserve(point_num);
  for (auto& point : cloud->points) {
    static geometry_msgs::Point32 ros_point;
    ros_point.x = point.x;
    ros_point.y = point.y;
    ros_point.z = point.z;
    pointcloud.points.push_back(ros_point);
  }
  gPub.publish(pointcloud);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "ce30_node");
  ros::NodeHandle nh;
  gPub = nh.advertise<sensor_msgs::PointCloud>("ce30_points", 1);
  UDPServer server;
  server.RegisterCallback(DataReceiveCB);
  if (!server.Start()) {
    return -1;
  }
  while (ros::ok()) {
   	server.SpinOnce();
  }
}
