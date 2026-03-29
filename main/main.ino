#include "HorizontalDistanceSensor.h"
#include "VerticalDistanceSensor.h"
#include "Motor.h"

HorizontalDistanceSensor horizontalDistanceSensor(9, 10);
VerticalDistanceSensor verticalDistanceSensor(11, 12);
Motor motor(6);
int counter = 0;

void setup() {
  Serial.begin(9600);

  horizontalDistanceSensor.begin();
  verticalDistanceSensor.begin();
  motor.begin();
}

void loop() {
  // horizontalDistanceSensor.printReading();
  // verticalDistanceSensor.printReading();
  Serial.println(counter);

  if (counter < 40)
  {
  motor.slowVibration();
  counter++;
  }

  if (counter == 40)
  {
    delay(500);
    counter++;
  }

  if (counter  > 40 && counter < 80)
  {
  motor.normalVibration();
  counter++;
  }
  
  if (counter == 80)
  {
    delay(500);
    counter++;
  }

  if (counter > 80)
  {   
  motor.fastVibration();
  counter++;
  }
  // Serial.println("--------------------");
  // delay(500);
}
