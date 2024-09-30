#include "LEDController.h"

LEDController::LEDController(int pin) : ledPin(pin) {}

void LEDController::begin() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
}

// Función para encender/apagar el LED de forma tradicional
void LEDController::show(int state) {
    digitalWrite(ledPin, state);
}

// Nueva función para hacer parpadear el LED con diferentes intensidades
void LEDController::blink(int delayTime, int intensity) {
    analogWrite(ledPin, intensity);  // Ajustar la intensidad (PWM: 0-255)
    delay(delayTime);                // Tiempo encendido
    analogWrite(ledPin, 0);          // Apagar LED
    delay(delayTime);                // Tiempo apagado
}
