import time
from machine import Pin, I2C
from ssd1306 import SSD1306_I2C


width = 128
height = 64

i2c = I2C(scl=Pin(5), sda=Pin(4))
oled = SSD1306_I2C(width, height, i2c)

oled.fill(1)
oled.show()

time.sleep(2)

oled.fill(0)
oled.show()

time.sleep(2)

oled.pixel(0, 0, 1)
oled.show()

time.sleep(2)

oled.pixel(127, 63, 1)
oled.show()

time.sleep(2)

oled.text('Hello', 0, 0)
oled.text('World', 0, 10)
oled.show()

time.sleep(2)

oled.invert(True)

time.sleep(2)

oled.invert(False)
