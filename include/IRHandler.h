#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include <IRrecv.h>
#include "Audio.h"

extern Audio audio;
extern IRrecv irrecv;

void setupIR();
void handleIRCommand(decode_results *results);

#endif // IR_HANDLER_H 