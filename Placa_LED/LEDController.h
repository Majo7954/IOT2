#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LEDController {
public:
    LEDController(int pin);
    void begin();
    void show(int state);

private:
    int ledPin;
};

#endif // LEDCONTROLLER_H

