from machine import Pin
from time import sleep

pin = Pin(14, Pin.OUT)

while True:
    pin.high()
    sleep(1)
    pin.low()
    sleep(1)
