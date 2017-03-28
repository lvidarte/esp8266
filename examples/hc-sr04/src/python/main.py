from machine import Pin
from ultrasonic import HCSR04
import time

sensor = HCSR04(Pin(14), Pin(12))

def loop(secs=1):
    while True:
        print(sensor.distance())
        time.sleep(secs)

