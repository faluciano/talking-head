#include "WebHandlers.h"
#include "Config.h"

extern WebServer server;
extern Audio audio;

void handleSpeak() {
  String text;
  String language = "en";
  
  if (server.method() == HTTP_POST) {
    if (server.hasArg("plain")) {
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, server.arg("plain"));
      if (!error && doc.containsKey("text")) {
        text = doc["text"].as<String>();
        if (doc.containsKey("language")) {
          language = doc["language"].as<String>();
        }
      }
    }
  } else if (server.method() == HTTP_GET) {
    text = server.arg("text");
    if (server.hasArg("language")) {
      language = server.arg("language");
    }
  }
  
  if (text.length() > 0) {
    audio.connecttospeech(text.c_str(), language.c_str());
    
    String response;
    StaticJsonDocument<200> respDoc;
    respDoc["status"] = "speaking";
    respDoc["text"] = text;
    respDoc["language"] = language;
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