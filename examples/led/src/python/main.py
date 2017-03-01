from machine import Pin
from time import sleep

led = Pin(16, Pin.OUT)

while True:
    led.high()
    sleep(1)
    led.low()
    sleep(1)
