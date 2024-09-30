#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LEDController {
public:
    LEDController(int pin);
    void begin();
    void show(int state); // Mantener para compatibilidad con encendido/apagado simple
    void blink(int delayTime, int intensity); // Nueva función para parpadeo con intensidad

private:
    int ledPin;
};

#endif // LEDCONTROLLER_H


