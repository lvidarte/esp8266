"""
RGBLamp
-------
HTTP daemon for Micropython running on NodeMCU.

@author Leo Vidarte <lvidarte@gmail.com>
@date   22-08-2016

PWM documentation: https://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/pwm.html
"""

import socket
import machine
import template

ADDR = ('0.0.0.0', 80)

PIN_R = 12
PIN_G = 13
PIN_B = 14


class RGBLed:
    def __init__(self, pin_r, pin_g, pin_b):
        self.pin_r = machine.PWM(machine.Pin(pin_r))
        self.pin_g = machine.PWM(machine.Pin(pin_g))
        self.pin_b = machine.PWM(machine.Pin(pin_b))
        self.set(0, 0, 0)

    def set(self, r, g, b):
        self.r = int(r)
        self.g = int(g)
        self.b = int(b)
        self.duty()

    def duty(self):
        self.pin_r.duty(self.duty_translate(self.r))
        self.pin_g.duty(self.duty_translate(self.g))
        self.pin_b.duty(self.duty_translate(self.b))

    def duty_translate(self, n):
        """translate values from 0-255 to 0-1023"""
        return int((float(n) / 255) * 1023)


def get_url(conn):
    conn_file = conn.makefile('rb', 0)
    method, url = None, None
    while True:
        line = conn_file.readline().decode()
        if not line or line == '\r\n':
            break
        if line.startswith('GET'):
            method, url, _ = line.split()
    return method, url

def parse_url(url):
    try:
        path, query = url.split('?', 2)
    except:
        return url, {}
    return path, {_.split('=')[0]: _.split('=')[1] for _ in query.split('&')}

def conn_send(conn, response):
    total_sent = 0
    while total_sent < len(response):
        sent = conn.send(response[total_sent:])
        if sent == 0:
            raise RuntimeError('Socket connection broken')
        total_sent = total_sent + sent


led = RGBLed(PIN_R, PIN_G, PIN_B)

s = socket.socket()
s.bind(ADDR)
s.listen(1)

print('RGBLamp daemon started on %s:%s' % ADDR)

while True:
    conn, addr = s.accept()
    method, url = get_url(conn)
    path, query = parse_url(url)
    print(addr[0], '-', method, url)
    if path == '/':
        if [_ for _ in list('rbg') if _ in query.keys()]:
            led.set(query.get('r', 0), query.get('g', 0), query.get('b', 0))
        response = template.html % (led.r, led.g, led.b)
        conn_send(conn, response)
    conn.close()
