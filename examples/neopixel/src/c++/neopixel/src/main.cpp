#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 10
#define PIN_PIXELS 14

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

void setup ()
{
  pixels.begin();
}

void loop ()
{
  int i;
  for (i = 0; i < NUM_PIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(127, 0, 0));
    pixels.show();
    delay(500);
  }

  for (i = NUM_PIXELS - 1; i >= 0; i--)
  {
    pixels.setPixelColor(i, pixels.Color(0, 127, 0));
    pixels.show();
    delay(500);
  }
}
