#include <WiFiConnection.h>
#include <LEDController.h>
#include <WiFi.h>

// Pines de los LEDs
int ledPinRed = 5;
int ledPinYellow = 18;
int ledPinGreen = 19;

// Definir credenciales WiFi
const char *ssid = "Mi 9T Pro";
const char *password = "boquitapapa";
WiFiConnection wifiConnection(ssid, password);

// Dirección IP y puerto del servidor
const char* serverIP = "192.168.19.167";
int serverPort = 2020;

// Instancias para cada LED
LEDController redLED(ledPinRed);
LEDController yellowLED(ledPinYellow);
LEDController greenLED(ledPinGreen);

int estado = -1;

void setup() {
    Serial.begin(115200);
    wifiConnection.begin();

    // Inicializar LEDs
    redLED.begin();
    yellowLED.begin();
    greenLED.begin();
}

void loop() {
    // Conectar al servidor
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
        client.println("GET");  // Solicitar el estado al servidor

        // Leer la respuesta del servidor
        String response = client.readStringUntil('\n');
        estado = response.toInt();
        Serial.println("Estado recibido: " + String(estado));

        // Apagar todos los LEDs
        redLED.show(LOW);
        yellowLED.show(LOW);
        greenLED.show(LOW);

        // Encender LED según el estado
        switch (estado) {
            case 0:  // Estado 0: Todos los LEDs apagados
                break;
            case 1:  // Estado 1: LED Rojo
                redLED.show(HIGH);
                break;
            case 2:  // Estado 2: LED Amarillo
                yellowLED.show(HIGH);
                break;
            case 3:  // Estado 3: LED Verde
                greenLED.show(HIGH);
                break;
        }

        client.stop();  // Cerrar la conexión con el servidor
    } else {
        Serial.println("Conexión fallida al servidor.");
    }

    delay(2000);  // Esperar 2 segundos antes de la próxima solicitud
}
