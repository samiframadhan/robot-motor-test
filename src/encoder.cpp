#include "encoder.h"

void IRAM_ATTR encoderAISR(void *arg){
    encoder* object = (encoder*)arg;
    long start = micros();
    long duration = start - object->micro_last;
    if (duration >= 10)
    {
        object->micro_last = start;
        object->micro_between_ticks = duration;
        if (object->direction == 0) {
            object->count--;
        } else {
            object->count++;
        }
    }
}

uint64_t encoder::read(){
    return count;
}

uint64_t encoder::read_and_clear(){
    uint64_t temp = count;
    count = 0;
    return temp;
}

void encoder::clear(){
    count = 0;
}

void encoder::attach(int &pinE){
    if (attached) return;
    pin = pinE;
    pinMode(pin, INPUT_PULLUP);
    attachInterruptArg(digitalPinToInterrupt(pin), encoderAISR, this, CHANGE);
}

void encoder::attach_direction(bool &dir){
    direction = dir;
}

encoder::encoder(/* args */)
{
}

encoder::~encoder()
{
    if (attached)
    {
        detachInterrupt(digitalPinToInterrupt(pin));
    }
    
}