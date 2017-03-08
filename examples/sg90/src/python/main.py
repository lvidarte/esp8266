from machine import Pin, PWM

servo = PWM(Pin(14), freq=50, duty=77)

servo.duty(30)
servo.duty(122)
