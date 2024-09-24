#include "songs.h"

void play_song_zero()
{
  int eighth_beat_tempo = EIGHTH_BEAT / 2.273;
  int sixteenth_beat_tempo = SIXTEENTH_BEAT / 2.273;
  const int NUM_NOTES = 10;

  int melody[NUM_NOTES] = {
    NOTE_B4, NOTE_B4, NOTE_GS4, NOTE_B4,
    NOTE_B4, NOTE_AS4, NOTE_FS4, NOTE_FS5,
    NOTE_FS5, NOTE_DS5
  };

  int rests[NUM_NOTES] = {
    eighth_beat_tempo * 2,
    eighth_beat_tempo + 50,
    eighth_beat_tempo * 2,
    eighth_beat_tempo * 2,
    eighth_beat_tempo * 2,
    eighth_beat_tempo * 2,
    eighth_beat_tempo + 50,
    eighth_beat_tempo + sixteenth_beat_tempo,
    eighth_beat_tempo + sixteenth_beat_tempo,
    eighth_beat_tempo
  };

  // Small delay before starting the song
  delay(2000);

  // Play the song chorus
  for (int i = 0; i < 4; i++)
  {

    // Different high note on the 2nd & 4th time
    if (i % 2 != 0)
    {
      melody[7] = NOTE_E5;
      melody[8] = NOTE_E5;
    }
    else
    {
      melody[7] = NOTE_FS5;
      melody[8] = NOTE_FS5;
    }
    for (int curr_note = 0; curr_note < NUM_NOTES; curr_note++)
    {
      tone(8, melody[curr_note], eighth_beat_tempo);
      delay(rests[curr_note]);
    }
  }
}