class WaterLevelSensor {
  private:
    const int pin_;
  public:
    WaterLevelSensor(int pin) : pin_(pin) {
    }

    int begin() {
      pinMode(pin_, INPUT);
      Serial.begin(9600);
      delay(1000); // Laisse une seconde au port pour se réveiller
      Serial.println("Système StarHack : Prêt !");
      return 1;
    }

    int readLevel() {
      long level = 0;

      for (int i = 0 ; i < 15 ; i++) {
        level += analogRead(pin_);
      }

      return level / 15;
    }
};
