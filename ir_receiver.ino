#include "ir_receiver.h"

IR_Receiver::IR_Receiver(int pin) : irrecv(new IRrecv(pin)), last_decodedRawData(0) {}

void IR_Receiver::begin() 
{
  irrecv->enableIRIn();  // Start the receiver
}

void IR_Receiver::translate_ir() 
{
  if (irrecv->decode()) 
  {
    // Check if the signal is a repeat IR code
    if (irrecv->decodedIRData.flags)
    {
      // Set the current decodedRawData to the last decodedRawData
      irrecv->decodedIRData.decodedRawData = last_decodedRawData;
      Serial.println("Repeat code");
    }
    else
    {
      // Output the IR code onto the Serial Monitor in hex
      Serial.print("IR code: 0x");
      Serial.println(irrecv->decodedIRData.decodedRawData, HEX);
    }

    // Mapping IR codes to button names
    switch (irrecv->decodedIRData.decodedRawData) 
    {
      case POWER: Serial.println("POWER"); break;
      case FUNC_STOP: Serial.println("FUNC/STOP"); break;
      case VOL_UP: Serial.println("VOL+"); break;
      case FAST_BACK: Serial.println("FAST BACK"); break;
      case PAUSE_RESUME: Serial.println("PAUSE"); break;
      case FAST_FORWARD: Serial.println("FAST FORWARD"); break;
      case DOWN: Serial.println("DOWN"); break;
      case VOL_DOWN: Serial.println("VOL-"); break;
      case UP: Serial.println("UP"); break;
      case EQ: Serial.println("EQ"); break;
      case ST_REPT: Serial.println("ST/REPT"); break;
      case ZERO: Serial.println("0"); break;
      case ONE: Serial.println("1"); break;
      case TWO: Serial.println("2"); break;
      case THREE: Serial.println("3"); break;
      case FOUR: Serial.println("4"); break;
      case FIVE: Serial.println("5"); break;
      case SIX: Serial.println("6"); break;
      case SEVEN: Serial.println("7"); break;
      case EIGHT: Serial.println("8"); break;
      case NINE: Serial.println("9"); break;
      default:
        Serial.println("Other button");
        break;
    }

    // Store the last decodedRawData
    last_decodedRawData = irrecv->decodedIRData.decodedRawData;
    delay(DEBOUNCE_DELAY);
    irrecv->resume();  // Receive the next value
  }
}
