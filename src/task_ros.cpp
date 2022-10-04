#include "task_ros.h"

rcl_subscription_t subscriber;
geometry_msgs__msg__Twist cmd_vel_msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rclc_executor_t executor;

void cmd_vel_cb(const void *received_msg){
    const geometry_msgs__msg__Twist *msg = (const geometry_msgs__msg__Twist *) received_msg;
    // cmd_vel_msg = *msg;
    Serial.println("Angular Z:");
    Serial.println(msg->angular.z);
    Serial.println("Linear X:");
    Serial.println(msg->linear.x);
    // Serial.println("Angular Z Saved:");
    // Serial.println(cmd_vel_msg.angular.z);
    // Serial.println("Linear X Saved:");
    // Serial.println(cmd_vel_msg.linear.x);
}

void errorHandle(){
    while (1)
    {
        digitalWrite(2, !digitalRead(2));
        vTaskDelay(pdTICKS_TO_MS(100));
    }
}

void TaskROS(void *pvParam){
    IPAddress agent_ip(192, 168, 40, 103);
    set_microros_wifi_transports("Nintendo", "papahbaik", agent_ip, 8888);
    allocator = rcl_get_default_allocator();
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, "micro_ros_wifi", "", &support));
    RCCHECK(rclc_subscription_init_best_effort(
        &subscriber, 
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "cmd_vel" ));
    RCCHECK(rclc_executor_init(
        &executor,
        &support.context,
        1,
        &allocator
    ));
    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &cmd_vel_msg, &cmd_vel_cb, ON_NEW_DATA));
    pinMode(2, OUTPUT);
    while (1)
    {
        RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
    }
    
}