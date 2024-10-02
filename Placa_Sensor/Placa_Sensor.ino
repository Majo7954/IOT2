#include <WiFiConnection.h>
#include <UltrasonicSensor.h>
#include <WiFi.h>

int trigPin = 2;
int echoPin = 4;

const char *ssid = "Mi 9T Pro";
const char *password = "boquitapapa";
WiFiConnection wifiConnection(ssid, password);

UltrasonicSensor sensor(trigPin, echoPin);

WiFiClient client;
const char* serverIP = "192.168.82.167";

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

    int condition = 0;

    if (distance >= 100 && distance < 200) {
        condition = 3;
    } else if (distance >= 50 && distance < 100) {
        condition = 2;
    } else if (distance >= 2 && distance < 50) {
        condition = 1;
    } else {
        condition = 0;
    }

    if (client.connect(serverIP, serverPort)) {
        client.print("distance=" + String(condition) + "\n");
        Serial.println("Estado enviado: " + String(condition));
        client.stop();
    }

    delay(1000);
}
