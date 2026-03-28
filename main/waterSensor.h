#pragma once

class WaterLevelSensor {
  private:
    const int pin_;
  public:
    WaterLevelSensor(int pin);
    int begin();
    int readLevel();
    int isSubmerged();
};
