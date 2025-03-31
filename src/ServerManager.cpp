#include "ServerManager.h"

void ServerManager::handleTimeout() {
    if (isClientConnected && (millis() - lastClientTime > SERVER_TIMEOUT)) {
        Serial.println("Client connection timeout");
        isClientConnected = false;
        server.client().stop();
    }
}

void ServerManager::handleConnection() {
    if (server.client()) {
        lastClientTime = millis();
        isClientConnected = true;
    }
}

void ServerManager::run() {
    uint32_t currentMillis = millis();
    
    // Check server status at regular intervals
    if (currentMillis - lastCheckTime >= SERVER_CHECK_INTERVAL) {
        lastCheckTime = currentMillis;
        handleTimeout();
        handleConnection();
    }
    
    // Handle client requests
    server.handleClient();
} 