#include "ir_receiver.h"

bool power_button_status = false; // off = false, on = true
bool pause_status = false; // pause = false, resume = true
int volume = DEFAULT_VOLUME;
uint32_t current_song; // Current song being played

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
 * @param decodedRawData the decoded raw IR data.
 * @param myDFPlayer the object of the MP3 player module.
 */
static void handle_ir_codes(IRRawDataType decodedRawData, DFRobotDFPlayerMini myDFPlayer)
{
  switch (decodedRawData) 
  {
    case POWER:
      power_button(myDFPlayer);
      break;
    case FUNC_STOP: 
      stop_button(myDFPlayer);
      break;
    case VOL_UP: 
      control_volume(VOL_UP, myDFPlayer);
      break;
    case FAST_BACK:
      Serial.println("FAST BACK");
      break;
    case PAUSE_RESUME: 
      pause_resume_button(); 
      break;
    case FAST_FORWARD: 
      fast_forward_button(myDFPlayer, current_song);
      break;
    case DOWN: 
      Serial.println("DOWN");
      break;
    case VOL_DOWN: 
      control_volume(VOL_DOWN, myDFPlayer); 
      break;
    case UP: 
      Serial.println("UP"); 
      break;
    case EQUALIZER: 
      Serial.println("EQUALIZER"); 
      break;
    case ST_REPT: 
      repeat_button(myDFPlayer, current_song);
      break;
    case ZERO: 
      song_button(ZERO, myDFPlayer);
      current_song = 1;
      break;
    case ONE: 
      song_button(ONE, myDFPlayer);
      current_song = 2;
      break;
    case TWO: 
      song_button(TWO, myDFPlayer);
      current_song = 3;
      break;
    case THREE: 
      song_button(THREE, myDFPlayer);
      current_song = 4;
      break;
    case FOUR: 
      song_button(FOUR, myDFPlayer);
      current_song = 5;
      break;
    case FIVE: 
      song_button(FIVE, myDFPlayer);
      current_song = 6;
      break;
    case SIX: 
      song_button(SIX, myDFPlayer);
      current_song = 7;
      break;
    case SEVEN: 
      song_button(SEVEN, myDFPlayer);
      current_song = 8;
      break;
    case EIGHT: 
      song_button(EIGHT, myDFPlayer);
      current_song = 9;
      break;
    case NINE: 
      song_button(NINE, myDFPlayer);
      current_song = 10;
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
 *
 * @param myDFPlayer the object of the MP3 player module.
 */
static void power_button(DFRobotDFPlayerMini myDFPlayer)
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
    myDFPlayer.stop();
  }
}

/**
 * Handles the functionality of volume up/down.
 * If power_button_status is true, turn the volume up/down depending on the button.
 * If power_button_status is false, return.
 *
 * @param button Hex address for volume up/down.
 * @param myDFPlayer the object of the MP3 player module.
 */
static void control_volume(uint32_t button, DFRobotDFPlayerMini myDFPlayer)
{
  if (power_button_status)
  {
    if (button == VOL_UP)
    {
      myDFPlayer.volumeUp();
      volume++;
      if (volume > 30)
      {
        volume = 30;
      }
    }
    else if (button == VOL_DOWN)
    {
      myDFPlayer.volumeDown();
      volume--;
      if (volume < 0)
      {
        volume = 0;
      }
    }

    Serial.print("Volume: ");
    Serial.println(volume);
  }
}

/**
 * Handles the functionality of the pause/resume button.
 * If pause_status is false (paused), it will resume the song and set pause_status to true.
 * If pause_status is true (resumed), it will pause the song and set pause_status to false.
 */
static void pause_resume_button()
{
  if (power_button_status)
  {
    if (pause_status)
    {
      myDFPlayer.start();
      Serial.println("Resuming song");
      pause_status = false;
    }
    else
    {
      myDFPlayer.pause();
      Serial.println("Pausing song");
      pause_status = true;
    }
  }
}

/**
 * Handles the functionality of the repeat button.
 * If power_button_status is true, repeat the current song being played.
 * If power_button_status is false, return.
 *
 * The DFPlayer Mini's first file starts at 001 instead of 000. To keep the "correct" track of songs
 * we subtract 1 when printing out which number track is being played. This way it stays aligned with
 * the buttons on the IR remote.
 *
 * @param myDFPlayer the object of the MP3 player module.
 * @param song the int of the current song being played.
 */
static void repeat_button(DFRobotDFPlayerMini myDFPlayer, uint32_t song)
{
  if (power_button_status)
  {

    Serial.print("Repeating song: ");
    Serial.println(song - 1);

    myDFPlayer.play(song);
  }
}

/**
 * Handles the functionality for the buttons 0 - 9 for songs.
 * If power_button_status is true, play the song corresponding to button.
 * If power_button_status is false, return.
 *
 * @param button Hex address representing which song to play.
 * @param myDFPlayer the object of the MP3 player module.
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
        myDFPlayer.play(2);
        break;      
      case TWO:
        Serial.println("Playing song 2");
        myDFPlayer.play(3);
        break;      
      case THREE:
        Serial.println("Playing song 3");
        myDFPlayer.play(4);
        break;      
      case FOUR:
        Serial.println("Playing song 4");
        myDFPlayer.play(5);
        break;      
      case FIVE:
        Serial.println("Playing song 5");
        myDFPlayer.play(6);
        break;      
      case SIX:
        Serial.println("Playing song 6");
        myDFPlayer.play(7);
        break;      
      case SEVEN:
        Serial.println("Playing song 7");
        myDFPlayer.play(8);
        break;      
      case EIGHT:
        Serial.println("Playing song 8");
        myDFPlayer.play(9);
        break;      
      case NINE:
        Serial.println("Playing song 9");
        myDFPlayer.play(10);
        break;      
      default:
        break;
    }
  }

}

/**
 * Handles the FUNC/STOP button on the IR Remote.
 * Stops the DFPlayer Mini Module from playing the current song.
 *
 * @param myDFPlayer the object of the MP3 player module.
 */
static void stop_button(DFRobotDFPlayerMini myDFPlayer)
{
  if (power_button_status)
  {
    Serial.println("Stopping song");
    myDFPlayer.stop();
  }
}

/**
 * Handles the fast forward button on the IR Remote.
 * Skips to the next song. 
 *
 * @param myDFPlayer the object of the MP3 player module.
 * @param song the int of the current song being played.
 */
static void fast_forward_button(DFRobotDFPlayerMini myDFPlayer, uint32_t song)
{
  if (power_button_status)
  {
    uint32_t new_song;
    Serial.println("Playing next song");
    new_song = song + 1;

    if (new_song > 10)
    {
      new_song = 0;
    }
    myDFPlayer.play(new_song);

    current_song = new_song;
  }
}
