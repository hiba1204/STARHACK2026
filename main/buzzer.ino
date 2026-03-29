#include "buzzer.h"
#include <math.h>

RobotVoice::RobotVoice(uint8_t pin) : pin_(pin) {}

void RobotVoice::begin() {
  pinMode(pin_, OUTPUT);
  noTone(pin_);
}

int RobotVoice::calculateFrequency(String noteName) {
  noteName.trim();
  noteName.toUpperCase();

  if (noteName.length() < 2) return 0;

  char letter = noteName[0];
  int octave = noteName.substring(noteName.length() - 1).toInt();
  bool isSharp = noteName.indexOf('S') != -1 || noteName.indexOf('#') != -1;

  int semitone;
  switch (letter) {
    case 'C': semitone = -9; break;
    case 'D': semitone = -7; break;
    case 'E': semitone = -5; break;
    case 'F': semitone = -4; break;
    case 'G': semitone = -2; break;
    case 'A': semitone = 0;  break;
    case 'B': semitone = 2;  break;
    default: return 0;
  }

  if (isSharp) semitone++;
  int n = semitone + (octave - 4) * 12;

  return (int)(440.0 * pow(2.0, (double)n / 12.0));
}

void RobotVoice::play(String noteName, int duration) {
  int freq = calculateFrequency(noteName);
  if (freq > 0) {
    tone(pin_, freq, duration);
    delay(duration + 20);
    noTone(pin_);
  }
}

void RobotVoice::playSequence(String sequence) {
  int start = 0;
  int space = sequence.indexOf(' ');

  while (space != -1) {
    play(sequence.substring(start, space));
    start = space + 1;
    space = sequence.indexOf(' ', start);
  }

  play(sequence.substring(start));
}

void RobotVoice::alertGroundChange() {
  tone(pin_, 900, 120);
  delay(150);
  tone(pin_, 650, 220);
  delay(250);
  noTone(pin_);
}

void RobotVoice::alertWater() {
  // Lower and longer so it is easy to hear
  tone(pin_, 700, 250);
  delay(300);
  tone(pin_, 950, 250);
  delay(300);
  tone(pin_, 700, 350);
  delay(400);
  noTone(pin_);
}