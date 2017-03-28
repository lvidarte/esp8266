##
# Ultrasonic library for esp8266.
# Compatible with HC-SR04 and SRF04.
#
# Copyright 2014 - Sergio Conde Gómez <skgsergio@gmail.com>
#
# esp8266 port by Leo Vidarte <lvidarte@gmail.com> on May 2017
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

import machine
import time


# Pin configuration.
# WARNING: Do not use PA4-X5 or PA5-X6 as the echo pin without a 1k resistor.

class HCSR04:

    MAX_TICKS = 20300 # 350m * 29 * 2

    def __init__(self, trigger_pin, echo_pin):
        self._debug = False

        # Init trigger pin (out)
        if type(trigger_pin) is machine.Pin:
            self.trigger = trigger_pin
        elif type(trigger_pin) is int:
            self.trigger = machine.Pin(trigger_pin)
        else:
            raise Exception("trigger_pin must be the type machine.Pin or int")
        self.trigger.init(machine.Pin.OUT, pull=None, value=0)
        self.trigger.low()

        # Init echo pin (in)
        if type(echo_pin) is machine.Pin:
            self.echo = echo_pin
        elif type(echo_pin) is int:
            self.echo = machine.Pin(echo_pin)
        else:
            raise Exception("echo_pin must be the type machine.Pin or int")
        self.echo.init(machine.Pin.IN, pull=None)

    def debug(self, enabled=True):
        self._debug = enabled 

    def distance(self, cm=True):
        if cm:
            return self.distance_in_cm()
        else:
            return self.distance_in_inches()

    def distance_in_inches(self):
        return (self.distance_in_cm() * 0.3937)

    def distance_in_cm(self):
        # Send a 10us pulse.
        self.trigger.high()
        time.sleep_us(10)
        self.trigger.low()

        # Wait 'till whe pulse starts.
        #while self.echo.value() == 0:
        while self.echo.value() == 0:
            start = time.ticks_us()

        # Wait 'till the pulse is gone.
        end = start
        while self.echo.value() == 1:
            end = time.ticks_us()

        delta = time.ticks_diff(end, start)
        if self._debug:
            print(start, end, delta)
        if delta == 0 or delta > self.MAX_TICKS:
            return None # out of range

        # Divide the delta by 2 (round-trip) and divide it by 29
        # (the speed of sound is 340 m/s and that is 29 us/cm).
        return (delta / 2) / 29
