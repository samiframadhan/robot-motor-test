#include "ros_init.h"

Ticker setIndicator;
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
std_msgs__msg__UInt64 newmsg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
rclc_executor_t executor;

//TODO: If not connected, don't restart ESP32. Report using serial
//TODO: data not published
void setupros(){ 
    IPAddress agent_ip(192, 168, 40, 103);
    pinMode(2, OUTPUT);
    const unsigned int pub_freq = 100;

    set_microros_wifi_transports("Nintendo", "papahbaik", agent_ip, 8888);

    allocator = rcl_get_default_allocator();

    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    RCCHECK(rclc_node_init_default(&node, "micro_ros_wifi", "", &support));

    RCCHECK(rclc_publisher_init_best_effort(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "microros"));
    
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(pub_freq),
        timerCb
    ));

    RCCHECK(rclc_executor_init(
        &executor,
        &support.context,
        1,
        &allocator
    ));

    RCCHECK(rclc_executor_add_timer(&executor, &timer));
    // RCCHECK(rclc_executor_spin_period(&executor, RCL_MS_TO_NS(100)));

    msg.data = 0;
}

void togglePin(){
    digitalWrite(2, !digitalRead(2));
    // vTaskDelay(pdTICKS_TO_MS(100));
}

void errorHandle(){
    setIndicator.attach_ms(100, togglePin);
}

void timerCb(rcl_timer_t *timer, int64_t last_timer_call){
    RCLC_UNUSED(last_timer_call);
    if (timer != NULL)
    {
        RCCHECK(rcl_publish(&publisher, &msg, NULL));
        msg.data++;
    }
}

void sendAData(uint64_t &data){
    newmsg.data = data;
    RCCHECK(rcl_publish(&publisher, &newmsg, NULL));
}