#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <Arduino.h>
#include <IRremote.h>
#include "DFRobotDFPlayerMini.h"

#define DEFAULT_VOLUME 5

// IR remote button mappings
#define POWER         0xBA45FF00 // Power to the jukebox
#define FUNC_STOP     0xB847FF00 // Stop the jukebox
#define VOL_UP        0xB946FF00 // Volume up
#define FAST_BACK     0xBB44FF00 // Rewind
#define PAUSE_RESUME  0xBF40FF00 // Pause/Resume
#define FAST_FORWARD  0xBC43FF00 // Fast forward
#define DOWN          0xF807FF00 // Previous song
#define VOL_DOWN      0xEA15FF00 // Volume down
#define UP            0xF609FF00 // Next song
#define EQUALIZER     0xE619FF00 // Equalizer (Disabled)
#define ST_REPT       0xF20DFF00 // Repeat
#define ZERO          0xE916FF00 // Song 0
#define ONE           0xF30CFF00 // Song 1
#define TWO           0xE718FF00 // Song 2
#define THREE         0xA15EFF00 // Song 3
#define FOUR          0xF708FF00 // Song 4
#define FIVE          0xE31CFF00 // Song 5
#define SIX           0xA55AFF00 // Song 6
#define SEVEN         0xBD42FF00 // Song 7
#define EIGHT         0xAD52FF00 // Song 8
#define NINE          0xB54AFF00 // Song 9

static const int IR_RECEIVER_PIN = 11; // Signal pin of the IR receiver

class IR_Receiver {
public:

    // Singleton IR_Receiver
    static IR_Receiver& get_instance() {
      static IR_Receiver instance;
      return instance;
    }
    void begin();
    void translate_ir(DFRobotDFPlayerMini myDFPlayer);

private:
    IR_Receiver(int pin = IR_RECEIVER_PIN) : irrecv(new IRrecv(pin)), last_decodedRawData(0) {}
    IR_Receiver(const IR_Receiver&) = delete;
    IR_Receiver& operator=(const IR_Receiver&) = delete;

    // Destructor
    ~IR_Receiver() {
        delete irrecv;
        irrecv = nullptr;  // Avoid dangling pointer
    }

    IRrecv* irrecv;
    uint32_t last_decodedRawData;
    static const unsigned long DEBOUNCE_DELAY = 500;
};

static void handle_ir_codes(IRRawDataType decodedRawData, DFRobotDFPlayerMini myDFPlayer);
static void power_button(DFRobotDFPlayerMini myDFPlayer);
static void control_volume(uint32_t button, DFRobotDFPlayerMini myDFPlayer);
static void pause_resume_button();
static void repeat_button(DFRobotDFPlayerMini myDFPlayer, uint32_t song);
static void song_button(uint32_t button, DFRobotDFPlayerMini myDFPlayer);
static void stop_button(DFRobotDFPlayerMini myDFPlayer);
static void fast_forward_button(DFRobotDFPlayerMini myDFPlayer);
#endif
