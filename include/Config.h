#ifndef CONFIG_H
#define CONFIG_H

#include <WiFiMulti.h>


// microSD Card Reader connections
#define SD_CS 5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

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