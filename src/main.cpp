#include <Arduino.h>
#include <motor.h>



int motor::count = 0;

motor motor1;

void printPins(){
  Serial.print("Pin1 : ");
  Serial.println(motor1.getpin1());
  Serial.print("Pin 2: ");
  Serial.println(motor1.getpin2());
}

void test_pwm(){
  for (int i = 0; i < 20; i++)
  {
    if (i > 10)
    {
      int temp = (i-20)*-20;
      int temp2 = motor1.set_pwm(temp);
      Serial.print("Forward in: ");
      Serial.println(temp2);
      Serial.println(temp);
      vTaskDelay(200 / portTICK_RATE_MS);
    } else
    {
      int temp = i*20;
      int temp2 = motor1.set_pwm(temp);
      Serial.print("Forward in: ");
      Serial.println(temp2);
      Serial.println(temp);
      vTaskDelay(200 / portTICK_RATE_MS);
    }
  }
  for (int i = 0; i < 20; i++)
  {
    if (i > 10)
    {
      int temp = (20-i)*-20;
      int temp2 = motor1.set_pwm(temp);
      Serial.print("Reverse in: ");
      Serial.println(temp2);
      Serial.println(temp);
      vTaskDelay(200 / portTICK_RATE_MS); 
    } else
    {
      int temp = -i * 20;
      int temp2 = motor1.set_pwm(temp);
      Serial.print("Reverse in: ");
      Serial.println(temp2);
      Serial.println(temp);
      vTaskDelay(200 / portTICK_RATE_MS);
    }
  }
}

void test_pin_pwm(int pwm_pin){
  for (int i = 0; i < 20; i++)
  {
    if (i > 10)
    {
      int temp = (i-20)*-20;
      motor1.pwm.write(pwm_pin, temp);
      Serial.print("PWM in: ");
      Serial.println(pwm_pin);
      vTaskDelay(200 / portTICK_RATE_MS);
    } else
    {
      int temp = i*20;
      motor1.pwm.write(pwm_pin, temp);
      Serial.print("PWM in: ");
      Serial.println(pwm_pin);
      vTaskDelay(200 / portTICK_RATE_MS);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  motor1.set_pins(17, 5);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // // test_pwm();
  if(Serial.available() > 0){
    int tmp = Serial.parseInt();
    int tmp2 = motor1.set_pwm(tmp);
    Serial.println(tmp2);
  } else{
    // motor1.set_pwm(0);
    motor1.pwm.write(motor1.motorpins[0], 0);
    motor1.pwm.write(motor1.motorpins[1], 0);
  }
}