#include "motor.h"

void motor::set_pins(int (&pins)[2]){
    pwm.setPinsStatusDefaults(0, freq, res);
    motorpins[0] = pins[0];
    motorpins[1] = pins[1];
    pwm.write(motorpins[0], 0);
    pwm.write(motorpins[1], 0);
}

void motor::set_pins(int pin1, int pin2){
    pwm.setPinsStatusDefaults(0, freq, res);
    motorpins[0] = pin1;
    motorpins[1] = pin2;
    pwm.write(motorpins[0], 0);
    pwm.write(motorpins[1], 0);
}

int motor::absolute(int value){
    if (value < 0)
    {
        value = -value;
    }
    return value;
}

int motor::set_pwm(int &pwm_val){
    if(pwm_val > 0){
        pwm.write(motorpins[0], pwm_val);
    } else {
        pwm.write(motorpins[1], absolute(pwm_val));
    }
    return pwm_val;
}

int motor::getpin1(){
    return motorpins[0];
}

int motor::getpin2(){
    return motorpins[1];
}

motor::motor(){
}