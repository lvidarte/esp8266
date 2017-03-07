from machine import Pin
from time import sleep

# GPIO16 (D0) is the internal LED for NodeMCU
led = Pin(16, Pin.OUT)

# The internal LED turn on when the pin is LOW
while True:
    led.high()
    sleep(1)
    led.low()
    sleep(1)
