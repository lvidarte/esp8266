from machine import Pin
from time import sleep

led = Pin(16, Pin.OUT)
button = Pin(14, Pin.IN, Pin.PULL_UP)

while True:

    # The value function returns the current level of the pin,
    # either 1 for a high logic level or 0 for a low logic level.
    # Notice how the button is at a high level (value returns 1) when
    # it's not pressed. This is because the pull-up resistor keeps the pin at
    # a high level when it's not connected to ground through the button.
    # When the button is pressed then the input pin connects to ground
    # and reads a low level (value returns 0).
    if not button.value():
        # Remember that the internal led turn on
        # when the pin is LOW
        led.low()
    else:
        led.high()

    sleep(.1)
