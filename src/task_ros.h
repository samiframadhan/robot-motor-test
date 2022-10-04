#include <Arduino.h>
#include <stdio.h>
#include <IPAddress.h>

#if defined(MICRO_ROS_TRANSPORT_ARDUINO_WIFI)
#include <WiFi.h>
#endif

#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/u_int64.h>
#include <geometry_msgs/msg/twist.h>
#include <Ticker.h>

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){errorHandle();}}

void TaskROS(void *pvParam);
void errorHandle();
void cmd_vel_cb(const void *received_msg);