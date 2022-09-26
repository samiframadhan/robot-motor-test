#include <Arduino.h>

class encoder
{
private:
    bool attached = false;
public:
    int pin=0;
    volatile uint64_t count = 0;
    volatile uint64_t micro_last = 0;
    volatile uint64_t micro_between_ticks = 0;
    uint64_t read();
    void clear();
    void attach(int &pinE);
    encoder(/* args */);
    virtual ~encoder();
};