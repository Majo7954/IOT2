#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LEDController {
public:
    LEDController(int pin);
    void begin();
    void show(int state);
    void blink(int delayTime, int intensity);

private:
    int ledPin;
};

#endif


