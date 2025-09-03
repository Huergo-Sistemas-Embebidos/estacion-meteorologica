#include "wifi-manager.h"

bool WiFiManager::begin(const char *ssid, const char *password) {
    WiFi.begin(ssid, password);
    Serial.print("[Wifi] Conectando a la red...");
    int maxAttempts = 20;  // 20 x 500ms = 10 seconds timeout
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
        delay(1000);
        Serial.print(".");
        attempt++;
    }
    Serial.println();
    wl_status_t status = WiFi.status();
    if (status != WL_CONNECTED) {
        Serial.print("[Wifi] Error: WiFi connection failed with status code ");
        Serial.println(status);

        return false;
    } else {
        Serial.println("[Wifi] Conectado a la red");

        Serial.print("[Wifi] IP address: ");
        Serial.println(WiFi.localIP());

        Serial.print("[Wifi] MAC address: ");
        Serial.println(WiFi.macAddress());

        Serial.print("[Wifi] RSSI: ");
        Serial.println(WiFi.RSSI());

        Serial.print("[Wifi] Gateway: ");
        Serial.println(WiFi.gatewayIP());

        Serial.print("[Wifi] Subnet: ");
        Serial.println(WiFi.subnetMask());

        return true;
    }
}
