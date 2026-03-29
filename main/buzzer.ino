// #define NOTE_E5  659
// #define NOTE_DS5 622
// #define NOTE_B4  494
// #define NOTE_D5  587
// #define NOTE_C5  523
// #define NOTE_A4  440

// const int buzzerPin = 8;

// void setup() {
//   Serial.begin(9600);

//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   playFurElise();
// }

// void playFurElise() {
//       // Les premières notes célèbres
//       int melody[] = { NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4 };
//       int durations[] = { 200, 200, 200, 200, 200, 200, 200, 200, 400 };

//       for (int i = 0; i < 9; i++) {
//         tone(buzzerPin, melody[i]);
//         delay(durations[i]);
//         noTone(buzzerPin); // Pause entre les notes
//         delay(50); 
//       }
//     }
#include "buzzer.h"

int RobotVoice::calculateFrequency(String noteName) {
  noteName.toUpperCase();
  char letter = noteName[0];
  int octave = noteName.substring(noteName.length() - 1).toInt();
  bool isSharp = noteName.indexOf('S') != -1 || noteName.indexOf('#') != -1;

  // 1. Trouver le demi-ton de base dans l'octave
  int semitone;
  switch (letter) {
    case 'C': semitone = -9;  break;
    case 'D': semitone = -7;  break;
    case 'E': semitone = -5;  break;
    case 'F': semitone = -4;  break;
    case 'G': semitone = -2;  break;
    case 'A': semitone = 0;   break;
    case 'B': semitone = 2;   break;
    default: return 0;
  }

  if (isSharp) semitone++;

  // 2. Ajuster selon l'octave (A4 est la référence)
  int n = semitone + (octave - 4) * 12;

  // 3. Appliquer la formule : f = 440 * 2^(n/12)
  return (int)(440.0 * pow(2.0, (double)n / 12.0));
}

RobotVoice::RobotVoice(uint8_t pin) : pin_(pin) {}

void RobotVoice::begin() {
  pinMode(pin_, OUTPUT);
}

void RobotVoice::play(String noteName, int duration = 200) {
  int freq = calculateFrequency(noteName);
  if (freq > 0) {
    tone(pin_, freq, duration);
    delay(duration * 1.1);
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
