#include "WiFiConnection.h"

WiFiConnection::WiFiConnection(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

void WiFiConnection::begin() {
    Serial.print("Conectando a WiFi: ");
    Serial.println(ssid);  // Imprime el nombre de la red WiFi para verificar

    WiFi.begin(ssid, password);
    int intentos = 0;  // Contador de intentos de conexión
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");  // Imprime un punto cada 500ms mientras intenta conectarse
        
        intentos++;
        if (intentos > 40) {  // Después de 20 segundos (40 * 500ms)
            Serial.println("\nError: No se pudo conectar al WiFi.");
            return;  // Salir del intento de conexión
        }
    }

    // Si la conexión fue exitosa, muestra la IP asignada
    Serial.println("\nConectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}


