from time import sleep_ms
from machine import Pin, I2C
from ssd1306 import SSD1306_I2C
from dht import DHT11

OLED_WIDTH = 128
OLED_HEIGHT = 64

i2c = I2C(scl=Pin(5), sda=Pin(4))
oled = SSD1306_I2C(OLED_WIDTH, OLED_HEIGHT, i2c)

sensor = DHT11(Pin(14))

def show_weather():
    t, h = sensor_read()
    oled.fill(0)
    oled.text("Temperature: %dC" % t, 0, 0)
    oled.text("Humidity:    %d%%" % h, 0, 10)
    oled.show()

def sensor_read():
    sensor.measure()
    t = sensor.temperature()
    h = sensor.humidity()
    return t, h

def weather(sec=10):
    intervals = int(OLED_WIDTH / 16 + 1)
    ms = int(sec / intervals * 1000)
    y = OLED_HEIGHT - 1
    while True:
        show_weather()
        sleep_ms(ms)
        for x in range(OLED_WIDTH):
            oled.pixel(x, y, 1)
            if (x + 1) % 16 == 0:
                oled.show()
                sleep_ms(ms)
