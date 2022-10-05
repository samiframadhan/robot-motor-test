#include "motor.h"

void motor::set_pins(int (&pins)[2]){
    motorpins[0] = pins[0];
    motorpins[1] = pins[1];
    ledcAttachPin(motorpins[0], motor_pins_channel[0]);
    ledcAttachPin(motorpins[1], motor_pins_channel[1]);
    ledcSetup(motor_pins_channel[0], freq, res);
    ledcSetup(motor_pins_channel[1], freq, res);
}

void motor::set_pins(int pin1, int pin2){
    motorpins[0] = pin1;
    motorpins[1] = pin2;
    ledcAttachPin(motorpins[0], motor_pins_channel[0]);
    ledcAttachPin(motorpins[1], motor_pins_channel[1]);
    ledcSetup(motor_pins_channel[0], freq, res);
    ledcSetup(motor_pins_channel[1], freq, res);
}

// void motor::set_pins(int pin1, int pin2, int pin_enc){
//     pwm.setPinsStatusDefaults(0, freq, res);
//     motorpins[0] = pin1;
//     motorpins[1] = pin2;
//     pwm.write(motorpins[0], 0);
//     pwm.write(motorpins[1], 0);
//     motor_enc.attach(pin_enc);
//     motor_enc.attach_direction(direction);
//     encoder_pin = pin_enc;
// }

int motor::absolute(int value){
    if (value < 0)
    {
        value = -value;
    }
    return value;
}

uint8_t motor::getpin1_channel(){
    return motor_pins_channel[0];
}

uint8_t motor::getpin2_channel(){
    return motor_pins_channel[1];
}

int motor::set_pwm(int pwm_val){
    if(pwm_val > 0){
        ledcWrite(motor_pins_channel[0], (uint32_t)pwm_val);
        ledcWrite(motor_pins_channel[1], 0);
        direction = 0;
    } else {
        ledcWrite(motor_pins_channel[1], (uint32_t)absolute(pwm_val));
        ledcWrite(motor_pins_channel[0], 0);
        direction = 1;
    }
    return pwm_val;
}

// void motor::set_encoder_pin(int pin){
//     motor_enc.attach(pin);
//     motor_enc.attach_direction(direction);
//     encoder_pin = pin;
// }

int motor::getpin1(){
    return motorpins[0];
}

int motor::getpin2(){
    return motorpins[1];
}

motor::motor(){
    uint8_t temp = channel;
    motor_pins_channel[0] = temp;
    motor_pins_channel[1] = temp;
    motor_pins_channel[1]++;
    channel += 2;
}