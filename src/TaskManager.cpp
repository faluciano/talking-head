#include "TaskManager.h"
#include "IRHandler.h"

void TaskManager::run() {
    uint32_t currentMillis = millis();
    
    // Handle IR with 1-second interval
    if (currentMillis - lastIRCheck >= IR_TASK_DELAY) {
        lastIRCheck = currentMillis;
        if (irrecv.decode(&results)) {
            handleIRCommand(&results);
            irrecv.resume();
        }
    }
    
    // Handle Audio with 10ms interval
    if (currentMillis - lastAudioCheck >= AUDIO_TASK_DELAY) {
        lastAudioCheck = currentMillis;
        audio.loop();
    }
    
    // Handle Server with improved management
    serverManager.run();
} 