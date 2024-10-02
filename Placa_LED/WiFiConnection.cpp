#include "WiFiConnection.h"

WiFiConnection::WiFiConnection(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

void WiFiConnection::begin() {
    Serial.print("Conectando a WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int intentos = 0;
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        
        intentos++;
        if (intentos > 40) {
            Serial.println("\nError: No se pudo conectar al WiFi.");
            return;
        }
    }

    Serial.println("\nConectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

