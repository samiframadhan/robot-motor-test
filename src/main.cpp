#include <Arduino.h>
#include "task_ros.h"
#include "task_execute.h"

void TaskExecute(void *pvParam);
void TaskROS(void *pvParam);
QueueHandle_t cmd_vel_queue;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);

  cmd_vel_queue = xQueueCreate(10, sizeof(geometry_msgs__msg__Twist));

  xTaskCreatePinnedToCore(
    TaskExecute,
    "Execute",
    3*1024,
    (void *) cmd_vel_queue,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );

  xTaskCreatePinnedToCore(
    TaskROS,
    "ROS",
    5*1024, //Minimal 10kB for ROS
    (void *) cmd_vel_queue,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}