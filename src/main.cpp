#include <IRrecv.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"
#include "Config.h"
#include "WebHandlers.h"
#include "IRHandler.h"
#include "TaskManager.h"

Audio audio;
IRrecv irrecv(IR_PIN);
decode_results results;
WebServer server(80);
TaskManager taskManager(irrecv, results, audio, server);

void setup()
{
  Serial.begin(115200);

  // Setup WiFi
  if (!setupWiFi()) {
    Serial.println("Failed to connect to WiFi!");
    while (true) delay(1000);
  }
  printWiFiStatus();

  // Setup I2S
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(80);

  // Setup IR
  setupIR();

  // Setup web server routes
  server.on("/speak", HTTP_GET, handleSpeak);
  server.on("/speak", HTTP_POST, handleSpeak);
  server.on("/audio", HTTP_GET, handleAudioFile);
  server.on("/audio", HTTP_POST, handleAudioFile);
  server.begin();
}

void loop()
{
  taskManager.run();
}