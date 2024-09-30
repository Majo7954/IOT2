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

        // Apagar todos los LEDs antes de cualquier acción
        redLED.show(LOW);
        yellowLED.show(LOW);
        greenLED.show(LOW);

        // Controlar LEDs según el estado recibido
        switch (estado) {
            case 0:  // Estado 0: Apagar todos los LEDs
                Serial.println("Estado 0: Todos los LEDs apagados.");
                // Todos los LEDs se mantendrán apagados
                break;
            case 1:  // Estado 1: LED Rojo parpadea rápidamente
                Serial.println("Estado 1: LED Rojo parpadea rápido.");
                redLED.blink(100, 255);  // Parpadeo rápido, intensidad máxima
                yellowLED.show(LOW);     // Asegurarse de que los otros LEDs estén apagados
                greenLED.show(LOW);
                break;
            case 2:  // Estado 2: LED Amarillo parpadea normal
                Serial.println("Estado 2: LED Amarillo parpadea normal.");
                yellowLED.blink(500, 255);  // Parpadeo normal, intensidad máxima
                redLED.show(LOW);            // Asegurarse de que los otros LEDs estén apagados
                greenLED.show(LOW);
                break;
            case 3:  // Estado 3: LED Verde parpadea lentamente
                Serial.println("Estado 3: LED Verde parpadea lento.");
                greenLED.blink(1000, 255);  // Parpadeo lento, intensidad máxima
                redLED.show(LOW);           // Asegurarse de que los otros LEDs estén apagados
                yellowLED.show(LOW);
                break;
            default:
                Serial.println("Estado no reconocido.");
                break;
        }

        client.stop();  // Cerrar la conexión con el servidor
    } else {
        Serial.println("Conexión fallida al servidor.");
    }

    delay(1000);  // Esperar 1 segundo antes de la próxima solicitud
}
