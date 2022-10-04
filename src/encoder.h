#include <Arduino.h>

class encoder
{
private:
    bool attached = false;
public:
    bool direction = false;//0 forward 1 reverse
    int pin=0;
    volatile uint64_t count = 0;
    volatile uint64_t micro_last = 0;
    volatile uint64_t micro_between_ticks = 0;
    uint64_t read();
    uint64_t read_and_clear();
    void clear();
    void attach_direction(bool &dir);
    void attach(int &pinE);
    encoder(/* args */);
    virtual ~encoder();
};