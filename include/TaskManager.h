#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include "Audio.h"
#include "WebServer.h"
#include "IRrecv.h"
#include "ServerManager.h"

class TaskManager {
private:
    static const uint32_t IR_TASK_DELAY = 1000;  // 1 second delay for IR processing
    static const uint32_t AUDIO_TASK_DELAY = 10;  // 10ms delay for audio processing
    
    uint32_t lastIRCheck = 0;
    uint32_t lastAudioCheck = 0;

    IRrecv& irrecv;
    decode_results& results;
    Audio& audio;
    ServerManager serverManager;

public:
    TaskManager(IRrecv& ir, decode_results& res, Audio& aud, WebServer& serv)
        : irrecv(ir), results(res), audio(aud), serverManager(serv) {}
    
    void run();
};

#endif 