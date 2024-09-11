#include <IRremote.h>

static const int IR_RECEIVER_PIN = 11; // Signal pin of the IR receiver

IRrecv irrecv(IR_RECEIVER_PIN); // Creeate irrecv object

uint32_t last_decodedRawData = 0; // Store the last decodedRawData

/**
 * Decodes IR signals from a remote, checks for repeat codes, and prints the IR code in 
 * hexadecimal. Maps the code to a corresponding button (e.g., "POWER", "VOL+") or prints 
 * "other button" if unrecognized. Stores the last decoded code and adds a delay to prevent 
 * immediate repeats.
 */
void translate_ir()
{
  // Check if it is a repeat IR code
  if (irrecv.decodedIRData.flags)
  {
    // Set the current decodedRawData to the last decodedRawData
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    Serial.println("Repeat IR code");
  }
  else
  {
    // Output the IR code to the Serial Monitor
    Serial.print("IR code:0x");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
  }

  // Map the IR code to the IR remote key
  switch (irrecv.decodedIRData.decodedRawData) {
    case 0xBA45FF00: Serial.println("POWER");         break;
    case 0xB847FF00: Serial.println("FUNC/STOP");     break;
    case 0xB946FF00: Serial.println("VOL+");          break;
    case 0xBB44FF00: Serial.println("FAST BACK");     break;
    case 0xBF40FF00: Serial.println("PAUSE");         break;
    case 0xBC43FF00: Serial.println("FAST FORWARD");  break;
    case 0xF807FF00: Serial.println("DOWN");          break;
    case 0xEA15FF00: Serial.println("VOL-");          break;
    case 0xF609FF00: Serial.println("UP");            break;
    case 0xE619FF00: Serial.println("EQ");            break;
    case 0xF20DFF00: Serial.println("ST/REPT");       break;
    case 0xE916FF00: Serial.println("0");             break;
    case 0xF30CFF00: Serial.println("1");             break;
    case 0xE718FF00: Serial.println("2");             break;
    case 0xA15EFF00: Serial.println("3");             break;
    case 0xF708FF00: Serial.println("4");             break;
    case 0xE31CFF00: Serial.println("5");             break;
    case 0xA55AFF00: Serial.println("6");             break;
    case 0xBD42FF00: Serial.println("7");             break;
    case 0xAD52FF00: Serial.println("8");             break;
    case 0xB54AFF00: Serial.println("9");             break;
    default:
      Serial.println(" other button");
  }

  // Store the last decodedRawData
  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
  // Delay to not get an immediate repeat
  delay(500);
}

void setup()
{

}


void loop()
{

}