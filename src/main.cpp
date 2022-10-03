#include <Arduino.h>
#include <motor.h>
#include "ros_init.h"
#include "encoder.h"
#include "task_monitor.h"

motor motor1;
motor motor2;
encoder motor1_enc;
int motor1_enc_pin = 12;

void TaskExecute(void *pvParam);
void TaskROS(void *pvParam);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  motor1_enc.attach(motor1_enc_pin);

  motor1.set_pins(17, 5);
  motor2.set_pins(19,18);

  xTaskCreatePinnedToCore(
    TaskMonitor,
    "Monitor",
    1024,
    NULL,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );

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
    3*1024, //Minimal 10kB for ROS
    NULL,
    1,
    NULL,
    ARDUINO_RUNNING_CORE
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}

void TaskExecute(void *pvParam){
  int test2;
  long last_millis;
  while (1)
  {
    if (millis() - last_millis > 1000)
    {
      last_millis = millis();
      Serial.println("Count :");
      Serial.println(motor1_enc.read());
    }
  }
}

void TaskROS(void *pvParam){
  int test;
  setupros();
  while (1)
  {
    uint64_t tmp = motor1_enc.read();
    sendAData(tmp);
    vTaskDelay(pdTICKS_TO_MS(100));
  }
}