#include <Arduino.h>

// D0 - Internal LED (GPIO16)

void setup ()
{
  pinMode(D0, OUTPUT);
}

void loop ()
{
  digitalWrite(D0, HIGH);
  delay(1000);
  digitalWrite(D0, LOW);
  delay(1000);
}
