// #include "Config.h"

// WiFiMulti wifiMulti;

// // WiFi Configuration
// const char* WIFI_SSID = "YOUR_WIFI_SSID";
// const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// bool setupWiFi() {
//   WiFi.mode(WIFI_STA);
//   wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
//   wifiMulti.run();
  
//   if (WiFi.status() != WL_CONNECTED) {
//     WiFi.disconnect(true);
//     wifiMulti.run();
//   }
  
//   return WiFi.status() == WL_CONNECTED;
// }

// void printWiFiStatus() {
//   Serial.print("WiFi Status: ");
//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("Connected");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());
//   } else {
//     Serial.println("Disconnected");
//   }
// } 