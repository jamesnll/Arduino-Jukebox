#include "ir_receiver.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Create an object for the IR receiver
IR_Receiver& ir_receiver = IR_Receiver::get_instance();

// Initialize software serial on pins 5 and 6
SoftwareSerial mySoftwareSerial(5, 6);  // RX, TX
// Declare an object for the DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;

/**
 * Setup the IR receiver, Serial Monitor to the Arduino board
 */
void setup()
{
  // Serial communication with the module
  mySoftwareSerial.begin(9600);
  // Initialize Arduino serial
  Serial.begin(115200);
  // Check if the module is responding and if the SD card is found
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer module ... Wait!"));

  // Check for DFPlayer Mini initialization errors
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true)
      ;
  }

  delay(1000); // Short delay before initializing settings

  // Initial settings
  myDFPlayer.volume(DEFAULT_VOLUME);  // Volume 5

  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!"));

  delay(1000); // Short delay before starting the IR receiver

  // Start the receiver
  ir_receiver.begin();
  Serial.println();
  Serial.println(F("IR receiver initialized!"));
}

/**
 * Continuously checks for received IR signals, decodes them, and processes the input.
 */
void loop()
{
  ir_receiver.translate_ir(myDFPlayer);  // Check for IR signals and handle them
}