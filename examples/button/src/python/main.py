from machine import Pin
from time import sleep

led = Pin(16, Pin.OUT)
button = Pin(14, Pin.IN, Pin.PULL_UP)

while True:
    if not button.value():
        led.high()
    else:
        led.low()
    sleep(1)
