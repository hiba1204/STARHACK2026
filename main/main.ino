#include "HorizontalDistanceSensor.h"
#include "VerticalDistanceSensor.h"
#include "Motor.h"

// HorizontalDistanceSensor horizontalDistanceSensor(9, 10);
// VerticalDistanceSensor verticalDistanceSensor(11, 12);
// pinMode(9, OUTPUT);
Motor motor(9);
int counter = 0;

void setup() {
  Serial.begin(9600);
  // horizontalDistanceSensor.begin();
  // verticalDistanceSensor.begin();
  motor.begin();
}

void loop() {
  // horizontalDistanceSensor.printReading();
  // verticalDistanceSensor.printReading();
  Serial.println(counter);
  if (counter < 100)
  {
  motor.slow();
  counter++;
  delay(100);
  }
  if (counter == 100)
  {
  // delay(200);
  counter++;  
  // delay(50);
  }
  if (counter > 100 && counter < 200)
  {
  motor.medium();
  counter++;
  delay(20);
  // delay(50);
  }
  
  if (counter == 200)
  {
  // delay(200);
  counter++;
  delay(500);
  // delay(50);
  }
  
  if (counter > 200)
  {
  motor.fast();
  counter++;
  delay(10);
  }
  if (counter > 300) 
  {
    counter =0;
   }
  // delay(20);
  // Serial.println("--------------------");
  // delay(500);
}
