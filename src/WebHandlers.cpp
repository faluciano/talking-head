#include "WebHandlers.h"
#include "Config.h"

extern WebServer server;
extern Audio audio;

// Reuse JsonDocument to save memory
JsonDocument doc;
JsonDocument respDoc;

void handleSpeak() {
  String text;
  String language = "en";
  int volume = -1;  // -1 indicates no volume change requested
  
  if (server.method() == HTTP_POST) {
    if (server.hasArg("plain")) {
      DeserializationError error = deserializeJson(doc, server.arg("plain"));
      if (!error && doc["text"].is<String>()) {
        text = doc["text"].as<String>();
        if (doc["language"].is<String>()) {
          language = doc["language"].as<String>();
        }
        if (doc["volume"].is<int>()) {
          volume = doc["volume"].as<int>();
        }
      }
    }
  } else if (server.method() == HTTP_GET) {
    text = server.arg("text");
    if (server.hasArg("language")) {
      language = server.arg("language");
    }
    if (server.hasArg("volume")) {
      volume = server.arg("volume").toInt();
    }
  }
  
  if (text.length() > 0) {
    if (volume >= 0 && volume <= 10) {
      audio.setVolume(volume);
    }
    audio.connecttospeech(text.c_str(), language.c_str());
    
    String response;
    respDoc.clear();  // Clear previous data
    respDoc[F("status")] = F("speaking");
    respDoc[F("text")] = text;
    respDoc[F("language")] = language;
    if (volume >= 0) {
      respDoc[F("volume")] = volume;
    }
    serializeJson(respDoc, response);
    server.send(200, F("application/json"), response);
  } else {
    server.send(400, F("application/json"), F("{\"error\": \"Missing 'text' parameter\"}"));
  }
}

void handleAudioFile() {
  String url;
  
  if (server.method() == HTTP_POST) {
    if (server.hasArg("plain")) {
      DeserializationError error = deserializeJson(doc, server.arg("plain"));
      if (!error && doc["url"].is<String>()) {
        url = doc["url"].as<String>();
      }
    }
  } else if (server.method() == HTTP_GET) {
    url = server.arg("url");
  }
  
  if (url.length() > 0) {
    audio.connecttohost(url.c_str());
    
    String response;
    respDoc.clear();  // Clear previous data
    respDoc[F("status")] = F("playing");
    respDoc[F("url")] = url;
    serializeJson(respDoc, response);
    server.send(200, F("application/json"), response);
  } else {
    server.send(400, F("application/json"), F("{\"error\": \"Missing 'url' parameter\"}"));
  }
} 