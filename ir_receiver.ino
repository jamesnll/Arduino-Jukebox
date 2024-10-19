#include "ir_receiver.h"

bool power_button_status = false;
bool pause_resume_status = false; // pause = false, resume = true
uint32_t current_song;

void IR_Receiver::begin() 
{
  irrecv->enableIRIn();  // Start the receiver
}

void IR_Receiver::translate_ir(DFRobotDFPlayerMini myDFPlayer) 
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
    handle_ir_codes(irrecv->decodedIRData.decodedRawData, myDFPlayer);

    // Store the last decodedRawData
    last_decodedRawData = irrecv->decodedIRData.decodedRawData;
    delay(DEBOUNCE_DELAY); // Add a delay to not get an immediate response
    irrecv->resume();  // Receive the next value
  }
}

/**
 * Handles the raw IR data and maps it to the corresponding hex address.
 *
 * @param decodedRawData the decoded raw IR data
 */
static void handle_ir_codes(IRRawDataType decodedRawData, DFRobotDFPlayerMini myDFPlayer)
{
  switch (decodedRawData) 
  {
    case POWER:
      power_button();
      break;
    case FUNC_STOP: 
      Serial.println("FUNC/STOP");
      break;
    case VOL_UP: 
      control_volume(VOL_UP);
      break;
    case FAST_BACK:
      Serial.println("FAST BACK");
      break;
    case PAUSE_RESUME: 
      pause_resume_button(); 
      break;
    case FAST_FORWARD: 
      Serial.println("FAST FORWARD"); 
      break;
    case DOWN: 
      Serial.println("DOWN");
      break;
    case VOL_DOWN: 
      control_volume(VOL_DOWN); 
      break;
    case UP: 
      Serial.println("UP"); 
      break;
    case EQUALIZER: 
      Serial.println("EQUALIZER"); 
      break;
    case ST_REPT: 
      repeat_button(current_song);
      break;
    case ZERO: 
      song_button(ZERO, myDFPlayer);
      break;
    case ONE: 
      song_button(ONE, myDFPlayer);
      break;
    case TWO: 
      song_button(TWO, myDFPlayer);
      break;
    case THREE: 
      song_button(THREE, myDFPlayer);
      break;
    case FOUR: 
      song_button(FOUR, myDFPlayer);
      break;
    case FIVE: 
      song_button(FIVE, myDFPlayer);
      break;
    case SIX: 
      song_button(SIX, myDFPlayer);
      break;
    case SEVEN: 
      song_button(SEVEN, myDFPlayer);
      break;
    case EIGHT: 
      song_button(EIGHT, myDFPlayer);
      break;
    case NINE: 
      song_button(NINE, myDFPlayer);
      break;
    default:
      Serial.println("Other button");
      break;
  }
}

/**
 * Handles the functionality of the power button.
 * If power_button_status is true, enable functionality for all other buttons on the remote.
 * If power_button_status is false, disable functionality for all other buttons.
 */
static void power_button()
{
  if (!power_button_status)
  {
    Serial.println("POWER ON");
    power_button_status = true;
  }
  else
  {
    Serial.println("POWER OFF");
    power_button_status = false;
  }
}

/**
 * Handles the functionality of volume up/down.
 * If power_button_status is true, turn the volume up/down depending on the button.
 * If power_button_status is false, return.
 *
 * @param button Hex address for volume up/down.
 */
static void control_volume(uint32_t button)
{
  if (power_button_status)
  {
    if (button == VOL_UP)
    {
      Serial.println("VOLUME UP");
    }
    else if (button == VOL_DOWN)
    {
      Serial.println("VOLUME DOWN");
    }
  }
}

/**
 * Handles the functionality of the pause/resume button.
 * If pause_resume_status is false (paused), it will resume the song and set pause_resume_status to true.
 * If pause_resume_status is true (resumed), it will pause the song and set pause_resume_status to false.
 */
static void pause_resume_button()
{
  if (power_button_status)
  {
    if (!pause_resume_status)
    {
      Serial.println("Resuming song");
      pause_resume_status = true;
    }
    else
    {
      Serial.println("Pausing song");
      pause_resume_status = false;
    }
  }
}

/**
 * Handles the functionality of the repeat button.
 * If power_button_status is true, repeat the current song being played.
 * If power_button_status is false, return.
 *
 * @param current_song the hex address of the current song being played.
 */
static void repeat_button(uint32_t song)
{
  if (power_button_status)
  {
    Serial.println("Repeating song");
    Serial.println(song);
  }
}

/**
 * Handles the functionality for the buttons 0 - 9 for songs.
 * If power_button_status is true, play the song corresponding to button.
 * If power_button_status is false, return.
 *
 * @param button Hex address representing which song to play.
 */
static void song_button(uint32_t button, DFRobotDFPlayerMini myDFPlayer)
{
  if (power_button_status)
  {
    // TODO: add functions to each case to play each respective song
    switch (button)
    {
      case ZERO:
        Serial.println("Playing song 0");
        myDFPlayer.play(1);
        break;
      case ONE:
        Serial.println("Playing song 1");
        break;      
      case TWO:
        Serial.println("Playing song 2");
        break;      
      case THREE:
        Serial.println("Playing song 3");
        break;      
      case FOUR:
        Serial.println("Playing song 4");
        break;      
      case FIVE:
        Serial.println("Playing song 5");
        break;      
      case SIX:
        Serial.println("Playing song 6");
        break;      
      case SEVEN:
        Serial.println("Playing song 7");
        break;      
      case EIGHT:
        Serial.println("Playing song 8");
        break;      
      case NINE:
        Serial.println("Playing song 9");
        break;      
      default:
        break;
    }
  }
  
  // Update the current song
  current_song = button;
}
