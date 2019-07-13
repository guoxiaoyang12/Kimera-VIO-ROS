/**
 * @file   stereo-image-buffer.h
 * @brief  Stereo Image Buffer for ROS wrapper
 * @author Yun Chang
 */

#pragma once

#include <cstdio>
#include <vector>

#include <common/vio_types.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include "datasource/DataSource.h"

namespace VIO {

struct StereoPacket {
  Timestamp timestamp;
  sensor_msgs::ImageConstPtr left_ros_img;
  sensor_msgs::ImageConstPtr right_ros_img;
};

class StereoBuffer {
  std::vector<StereoPacket> stereo_buffer_;
  // Latest timestamp
  Timestamp latest_timestamp_;
  // Earliest timestamp
  Timestamp earliest_timestamp_;

 public:
  // Get timestamp of latest frame
  Timestamp getLatestTimestamp() const;
  Timestamp getEarliestTimestamp() const;
  size_t size() const;

  // Get the images of the latest frame
  // and also delete from buffer
  bool extractLatestImages(sensor_msgs::ImageConstPtr& left_img,
                           sensor_msgs::ImageConstPtr& right_img);

  // add images to buffer
  // and update latest timestamp
  void addStereoFrame(sensor_msgs::ImageConstPtr left_img,
                      sensor_msgs::ImageConstPtr right_img);

  void removeNext();
  // discard next frame
};

}  // namespace VIO
