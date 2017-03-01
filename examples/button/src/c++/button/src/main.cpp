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
  static uint8_t state;

  // digitalRead() returns the current level of the pin,
  // either 1 for a high logic level or 0 for a low logic level.
  // Notice how the button is at a high level (value returns 1) when
  // it's not pressed. This is because the pull-up resistor keeps the pin at
  // a high level when it's not connected to ground through the button.
  // When the button is pressed then the input pin connects to ground
  // and reads a low level (value returns 0).
  state = digitalRead(D5);

  // Remember that the internal led turn on
  // when the pin is LOW
  digitalWrite(D0, state);

  delay(100);
}
