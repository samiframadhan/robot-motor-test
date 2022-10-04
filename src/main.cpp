#include <Arduino.h>
#include "task_ros.h"
#include "task_execute.h"

void TaskExecute(void *pvParam);
void TaskROS(void *pvParam);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    TaskExecute,
    "Execute",
    1024,
    NULL,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );

  xTaskCreatePinnedToCore(
    TaskROS,
    "ROS",
    5*1024, //Minimal 10kB for ROS
    NULL,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}