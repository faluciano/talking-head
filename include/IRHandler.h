#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include "Audio.h"

extern IRrecv irrecv;

void handleIRCommand(decode_results *results);
void setupIR();

#endif 