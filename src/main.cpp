#include <Arduino.h>
#include <motor.h>
#include "ros_init.h"
#include "encoder.h"

QueueHandle_t buffer;
motor motor1;
motor motor2;
encoder motor1_enc;
int motor1_enc_pin = 12;

void TaskMonitor(void *pvParam);
void TaskExecute(void *pvParam);
void TaskROS(void *pvParam);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  motor1_enc.attach(motor1_enc_pin);

  buffer = xQueueCreate(100, sizeof(int));

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

void TaskMonitor(void *pvParam){
  int test1;
  
  while (1)
  {
    if (Serial.available() > 0)
    {
      test1 = Serial.parseInt();
      Serial.println(test1);
      if (xQueueSend(buffer, &test1, 10) != pdTRUE)
      {
        Serial.printf("Queue full");
      }
    }
  }
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
    
    if (xQueueReceive(buffer, &test2, 0) == pdTRUE)
    {
      Serial.println("Queue received!");
      Serial.println(test2);
      motor1.set_pwm(test2);
      motor2.set_pwm(test2);
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