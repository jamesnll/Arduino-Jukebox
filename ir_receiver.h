#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <Arduino.h>
#include <IRremote.h>

static const int IR_RECEIVER_PIN = 11; // Signal pin of the IR receiver

class IR_Receiver {
public:
    IR_Receiver(int pin = IR_RECEIVER_PIN);
    void begin();
    void translate_ir();

private:
    IRrecv* irrecv;
    uint32_t last_decodedRawData;
    static const unsigned long DEBOUNCE_DELAY = 500;
};

#endif
