#pragma once
#include <Arduino.h>

class RobotVoice {
  private:
    uint8_t pin_;
    // Calcule la fréquence de n'importe quelle note (ex: "C4", "DS5")
    int calculateFrequency(String noteName);

  public:
    RobotVoice(uint8_t pin);
    void begin();
    void playSequence(String sequence);
    void play(String noteName, int duration = 200);
    //void speak(String sequence);
};