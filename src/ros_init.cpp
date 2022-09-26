#include "ros_init.h"

Ticker setIndicator;
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

void setupros(){
    IPAddress agent_ip(192, 168, 40, 103);
    pinMode(2, OUTPUT);

    set_microros_wifi_transports("Nintendo", "papahbaik", agent_ip, 8888);

    allocator = rcl_get_default_allocator();

    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    RCCHECK(rclc_node_init_default(&node, "micro_ros_wifi", "", &support));

    RCCHECK(rclc_publisher_init_best_effort(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "microros"));

    msg.data = 0;
}

void togglePin(){
    digitalWrite(2, !digitalRead(2));
    vTaskDelay(pdTICKS_TO_MS(100));
}

void errorHandle(){
    setIndicator.attach_ms(100, togglePin);
}