#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigPin, int echoPin);
    void begin();
    long readDistance();

private:
    int trigPin;
    int echoPin;
};

#endif
