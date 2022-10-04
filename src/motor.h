#include <Arduino.h>
#include <pwmWrite.h>
#include "encoder.h"

//PWM Limits:
//Freq: 800 Hz
//Min duty: 70/255 * 100%
//Freq: 1000 Hz
//Min duty: 77/255 * 100%

class motor
{
private:
    
public:

    Pwm pwm = Pwm();
    encoder motor_enc;
    float freq = 800;
    uint8_t res = 8;
    int motorpins[2]= {0,0};
    int encoder_pin = 0;
    bool direction = 0; //0 forward, 1 backward
    void set_pins(int (&pins)[2]);
    void set_pins(int pin1, int pin2);
    void set_pins(int pin1, int pin2, int pin_enc);
    void set_encoder_pin(int pin);
    
    int set_pwm(int &pwm_val);
    int getpin1();
    int getpin2();
    int absolute(int value);
    motor(/* args */);
};