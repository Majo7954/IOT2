#include <WiFiConnection.h>
#include <UltrasonicSensor.h>
#include <WiFi.h>

// Pines del sensor ultrasónico
int trigPin = 2;
int echoPin = 4;

// Definir credenciales WiFi
const char *ssid = "Mi 9T Pro";
const char *password = "boquitapapa";
WiFiConnection wifiConnection(ssid, password);

UltrasonicSensor sensor(trigPin, echoPin);

WiFiClient client;
const char* serverIP = "192.168.19.167";

int serverPort = 2020;

void setup() {
    Serial.begin(115200);
    wifiConnection.begin();
    sensor.begin();
}

void loop() {
    long distance = sensor.readDistance();
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    int estado = 0;

    // Determinar el estado según la distancia
    if (distance >= 200 && distance < 300) {
        estado = 3;  // Verde
    } else if (distance >= 50 && distance < 200) {
        estado = 2;  // Amarillo
    } else if (distance >= 2 && distance < 50) {
        estado = 1;  // Rojo
    } else {
        estado = 0;  // Ningún objeto
    }

    // Conectar al servidor y enviar el estado
    if (client.connect(serverIP, serverPort)) {
        client.print("distance=" + String(estado) + "\n");
        Serial.println("Estado enviado: " + String(estado));
        client.stop();
    }

    delay(1000);
}
