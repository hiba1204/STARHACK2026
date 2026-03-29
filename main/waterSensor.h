#pragma once

class WaterLevelSensor {
  private:
    const int pin_;
    const int threshold_;

  public:
    WaterLevelSensor(int pin, int threshold = 250);
    int begin();
    int readLevel();
    int isSubmerged();
};