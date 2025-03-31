#include "WebHandlers.h"
#include "Config.h"

extern WebServer server;
extern Audio audio;

void handleSpeak() {
  String text;
  String language = "en";
  int volume = -1;  // -1 indicates no volume change requested
  
  if (server.method() == HTTP_POST) {
    if (server.hasArg("plain")) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, server.arg("plain"));
      if (!error && doc.containsKey("text")) {
        text = doc["text"].as<String>();
        if (doc.containsKey("language")) {
          language = doc["language"].as<String>();
        }
        if (doc.containsKey("volume")) {
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
    StaticJsonDocument<200> respDoc;
    respDoc["status"] = "speaking";
    respDoc["text"] = text;
    respDoc["language"] = language;
    if (volume >= 0) {
      respDoc["volume"] = volume;
    }
    serializeJson(respDoc, response);
    server.send(200, "application/json", response);
  } else {
    server.send(400, "application/json", "{\"error\": \"Missing 'text' parameter\"}");
  }
}

void handleAudioFile() {
  String url;
  
  if (server.method() == HTTP_POST) {
    if (server.hasArg("plain")) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, server.arg("plain"));
      if (!error && doc.containsKey("url")) {
        url = doc["url"].as<String>();
      }
    }
  } else if (server.method() == HTTP_GET) {
    url = server.arg("url");
  }
  
  if (url.length() > 0) {
    audio.connecttohost(url.c_str());
    
    String response;
    StaticJsonDocument<200> respDoc;
    respDoc["status"] = "playing";
    respDoc["url"] = url;
    serializeJson(respDoc, response);
    server.send(200, "application/json", response);
  } else {
    server.send(400, "application/json", "{\"error\": \"Missing 'url' parameter\"}");
  }
} 