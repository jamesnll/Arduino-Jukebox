#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <Arduino.h>
#include <IRremote.h>

// IR remote button mappings
#define POWER         0xBA45FF00
#define FUNC_STOP     0xB847FF00
#define VOL_UP        0xB946FF00
#define FAST_BACK     0xBB44FF00
#define PAUSE_RESUME  0xBF40FF00
#define FAST_FORWARD  0xBC43FF00
#define DOWN          0xF807FF00
#define VOL_DOWN      0xEA15FF00
#define UP            0xF609FF00
#define EQ            0xE619FF00
#define ST_REPT       0xF20DFF00
#define ZERO          0xE916FF00
#define ONE           0xF30CFF00
#define TWO           0xE718FF00
#define THREE         0xA15EFF00
#define FOUR          0xF708FF00
#define FIVE          0xE31CFF00
#define SIX           0xA55AFF00
#define SEVEN         0xBD42FF00
#define EIGHT         0xAD52FF00
#define NINE          0xB54AFF00

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
