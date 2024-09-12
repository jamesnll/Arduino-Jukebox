#include "ir_receiver.h"

IR_Receiver ir_receiver;

/**
 * Setup the IR receiver, Serial Monitor to the Arduino board
 */
void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  // Start the receiver
  ir_receiver.begin();
}

/**
 * Continuously checks for received IR signals, decodes them, and processes the input.
 */
void loop()
{
  ir_receiver.translate_ir();  // Check for IR signals and handle them
}