#include "task_execute.h"

uint8_t motor::channel = 0;
motor motor1;
motor motor2;
motor motor3;
motor motor4;
QueueHandle_t q_handle_2;
geometry_msgs__msg__Twist cmd_vel_execute_msg;
static const char* TAG = "Execute";

void TaskExecute(void *pv_param){
  q_handle_2 = (QueueHandle_t) pv_param;

  motor1.set_pins(19,18);
  motor2.set_pins(17, 5);
  motor3.set_pins(33, 32);
  motor4.set_pins(27, 26);
//   motor1.set_encoder_pin(35);
//   motor2.set_encoder_pin(34);
//   motor3.set_encoder_pin(14);
//   motor4.set_encoder_pin(12);
  bool forward = false;
  int temp_data_x = 0;
  int temp_data_y = 0;
  int temp_data_xy = 0;

  while (1)
  {
    if (xQueueReceive(q_handle_2, &cmd_vel_execute_msg, portMAX_DELAY) != pdPASS)
    {
        log_i("Failed to get queue data");
    } else
    {
        cmd_vel_execute_msg.linear.x = cmd_vel_execute_msg.linear.x * 255;
        cmd_vel_execute_msg.linear.y = cmd_vel_execute_msg.linear.y * 255;
        cmd_vel_execute_msg.angular.z = cmd_vel_execute_msg.angular.z * 255;
        temp_data_x = (int) cmd_vel_execute_msg.linear.x;
        temp_data_y = (int) cmd_vel_execute_msg.linear.y;
        temp_data_xy = (int) cmd_vel_execute_msg.angular.z;
        log_i("Queue received!");
    }

    motor1.set_pwm(temp_data_x - temp_data_y - temp_data_xy);
    motor2.set_pwm(temp_data_x + temp_data_y + temp_data_xy);
    motor3.set_pwm(temp_data_x + temp_data_y - temp_data_xy);
    motor4.set_pwm(temp_data_x - temp_data_y + temp_data_xy);
  } 
}