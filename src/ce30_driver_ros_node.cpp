#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <ce30_driver/ce30_driver.h>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>

using namespace std;
using namespace ce30_driver;

mutex gPacketMutex;
Packet gPacket;
mutex gSignalMutex;
bool gKillSignal = false;

void DataReceiveThread(shared_ptr<UDPSocket> socket) {
  while (true) {
    gSignalMutex.lock();
    auto kill_signal = gKillSignal;
    gSignalMutex.unlock();
    if (kill_signal) {
      return;
    }

    static Packet packet;
    if (GetPacket(packet, *socket, true)) {
      gPacketMutex.lock();
      gPacket = packet;
      gPacketMutex.unlock();
    }
  }
}

void PublishCloud(const Scan& scan, ros::Publisher& pub) {
  sensor_msgs::PointCloud pointcloud;
  pointcloud.header.stamp = ros::Time::now();
  pointcloud.header.frame_id = "map";

  static int scan_width = scan.Width();
  static int scan_height = scan.Height();
  static int point_num = scan_width * scan_height;
  pointcloud.points.reserve(point_num);

  for (int x = 0; x < scan_width; ++x) {
    for (int y = 0; y < scan_height; ++y) {
      ce30_driver::Point p = scan.at(x, y).point();
      if (sqrt(p.x * p.x + p.y * p.y) < 0.1f) {
        continue;
      }
      geometry_msgs::Point32 point;
      point.x = p.x;
      point.y = p.y;
      point.z = p.z;
      pointcloud.points.push_back(point);
    }
  }
  pub.publish(pointcloud);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "ce30_node");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud>("ce30_points", 1);
  shared_ptr<UDPSocket> socket(new UDPSocket);
  Scan scan;
  
  if (!Connect(*socket)) {
    cerr << "Unable to Connect Device!" << endl;
    return -1;
  }

  if (!StartRunning(*socket)) {
    cerr << "Unable to Start CE30!" << endl;
    return -1;
  }

  string device_version;
  if (!GetVersion(device_version, *socket)) {
    cerr << "Unable to Retrieve CE30 Device Version" << endl;
    return -1;
  }
  
  thread thread(bind(DataReceiveThread, socket));
  while (ros::ok()) {
    static Packet packet;
    gPacketMutex.lock();
    packet = gPacket;
    gPacketMutex.unlock();

    auto parsed = packet.Parse();
    if (parsed) {
      scan.AddColumnsFromPacket(*parsed);
      if (scan.Ready()) {
        PublishCloud(scan, pub);
        scan.Reset();
      }
    }
  }
  if (thread.joinable()) {
    thread.join();
  }
  StopRunning(*socket);
}
