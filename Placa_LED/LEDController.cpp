#include "LEDController.h"

LEDController::LEDController(int pin) : ledPin(pin) {}

void LEDController::begin() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void LEDController::show(int state) {
    digitalWrite(ledPin, state);
}

void LEDController::blink(int delayTime, int intensity) {
    analogWrite(ledPin, intensity);  
    delay(delayTime);                
    analogWrite(ledPin, 0);          
    delay(delayTime);                
}
