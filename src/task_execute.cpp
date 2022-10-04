#include "task_execute.h"

motor motor1;
motor motor2;
motor motor3;
motor motor4;

void TaskExecute(void *pv_param){
  motor1.set_pins(19,18);
  motor2.set_pins(17, 5);
  motor3.set_pins(26, 27);
  motor4.set_pins(32, 33);
  motor1.set_encoder_pin(35);
  motor2.set_encoder_pin(34);
  motor3.set_encoder_pin(14);
  motor4.set_encoder_pin(12);
  int forward_pwm = 100;
  int backward_pwm = -100;
  bool forward = false;

  while (1)
  {
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            motor1.set_pwm(forward == 1 ? forward_pwm : backward_pwm);
            break;
        
        case 1:
            motor2.set_pwm(forward == 1 ? forward_pwm : backward_pwm);
            break;

        case 2:
            motor3.set_pwm(forward == 1 ? forward_pwm : backward_pwm);
            break;

        case 3:
            motor4.set_pwm(forward == 1 ? forward_pwm : backward_pwm);
            break;
        
        default:
            break;
        }
        vTaskDelay(pdTICKS_TO_MS(1000));
    }
    forward = !forward; 
  } 
}