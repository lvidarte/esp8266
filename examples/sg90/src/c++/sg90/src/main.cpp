#include <Arduino.h>
#include <Servo.h>

Servo servo;

void setup ()
{
  servo.attach(14);
}

void loop ()
{
  // To 0°
  servo.write(0);
  delay(1000);

  // To 90°
  servo.write(90);
  delay(1000);

  // To 180°
  servo.write(180);
  delay(1000);
}
