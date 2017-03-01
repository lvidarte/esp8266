#include <Arduino.h>

// D0 - Internal LED (GPIO16)
// D5 - Button (GPIO14)

void setup ()
{
  pinMode(D0, OUTPUT);
  pinMode(D5, INPUT_PULLUP);
}

void loop ()
{
  static int state = 0;

  state = digitalRead(D5);

  digitalWrite(D0, state);
  delay(100);
}
