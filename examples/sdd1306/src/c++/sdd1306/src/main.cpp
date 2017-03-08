#include <Arduino.h>
#include <SSD1306.h>

#define SDA 4
#define SCL 5

SSD1306 display(0x3c, SDA, SCL);

void setup ()
{
  display.init();
  display.flipScreenVertically();

  display.clear();
  display.drawString(0, 0, "Hello");
  display.drawString(0, 10, "World");

  display.drawCircle(50, 30, 10);
  display.drawRect(10, 30, 10, 10);
  display.display();
}

void loop ()
{
}
