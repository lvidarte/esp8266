from machine import Pin
from time import sleep

pin = Pin(16, Pin.OUT)

while True:
    pin.high()
    sleep(1)
    pin.low()
    sleep(1)
