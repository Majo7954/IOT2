#include <WiFiConnection.h>
#include <LEDController.h>
#include <WiFi.h>

int ledPinRed = 5;
int ledPinYellow = 18;
int ledPinGreen = 19;

const char *ssid = "Mi 9T Pro";
const char *password = "boquitapapa";
WiFiConnection wifiConnection(ssid, password);

const char* serverIP = "192.168.23.167";
int serverPort = 2020;

LEDController redLED(ledPinRed);
LEDController yellowLED(ledPinYellow);
LEDController greenLED(ledPinGreen);

int estado = -1;

void setup() {
    Serial.begin(115200);
    wifiConnection.begin();

    redLED.begin();
    yellowLED.begin();
    greenLED.begin();
}

void loop() {
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
        client.println("GET");

        String response = client.readStringUntil('\n');
        estado = response.toInt();
        Serial.println("Estado recibido: " + String(estado));

        redLED.show(LOW);
        yellowLED.show(LOW);
        greenLED.show(LOW);

        switch (estado) {
            case 0:
                Serial.println("Estado 0: Todos los LEDs apagados.");
                break;
            case 1:
                Serial.println("Estado 1: LED Rojo parpadea rápido.");
                redLED.blink(100, 255);
                yellowLED.show(LOW);
                greenLED.show(LOW);
                break;
            case 2:
                Serial.println("Estado 2: LED Amarillo parpadea normal.");
                yellowLED.blink(500, 255);
                redLED.show(LOW);
                greenLED.show(LOW);
                break;
            case 3:
                Serial.println("Estado 3: LED Verde parpadea lento.");
                greenLED.blink(1000, 255);
                redLED.show(LOW);
                yellowLED.show(LOW);
                break;
            default:
                Serial.println("Estado no reconocido.");
                break;
        }

        client.stop();
    } else {
        Serial.println("Conexión fallida al servidor.");
    }

    delay(1000); 
}
