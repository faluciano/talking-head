#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <WebServer.h>
#include <Arduino.h>

class ServerManager {
private:
    static const uint32_t SERVER_TIMEOUT = 5000;  // 5 second timeout
    static const uint32_t SERVER_CHECK_INTERVAL = 100;  // Check every 100ms
    
    WebServer& server;
    uint32_t lastClientTime = 0;
    uint32_t lastCheckTime = 0;
    bool isClientConnected = false;
    
    void handleTimeout();
    void handleConnection();

public:
    ServerManager(WebServer& serv) : server(serv) {}
    void run();
    bool isConnected() const { return isClientConnected; }
    void resetConnection() { isClientConnected = false; }
};

#endif 