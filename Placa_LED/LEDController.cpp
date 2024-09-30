#include "LEDController.h"

LEDController::LEDController(int pin) : ledPin(pin) {}

void LEDController::begin() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

void LEDController::show(int state) {
    digitalWrite(ledPin, state);
}
