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
#include <std_msgs/msg/int32.h>
#include <Ticker.h>

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){errorHandle();}}

void setupros();
void errorHandle();
void timerCb(rcl_timer_t *timer, int64_t last_call_time);