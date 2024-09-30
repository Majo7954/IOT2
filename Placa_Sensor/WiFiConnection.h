#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <WiFi.h>

class WiFiConnection {
public:
    WiFiConnection(const char *ssid, const char *password);
    void begin();

private:
    const char *ssid;
    const char *password;
};

#endif // WIFICONNECTION_H
