#ifndef CONFIG_H
#define CONFIG_H

#include <WiFiMulti.h>

// I2S Connections
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_LRC 25

// IR Receiver Pin
#define IR_PIN 15

// WiFi Configuration
extern WiFiMulti wifiMulti;
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Function declarations
void setupPins();
bool setupWiFi();
void printWiFiStatus();

#endif