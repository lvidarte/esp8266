from machine import Pin
from dht import DHT11
import requests

aio_url = 'https://io.adafruit.com/api/feeds/%s/data'
aio_key = 'b9f5ba0712f91deb9eefdc1faf5dee06415d380f'

d = DHT11(Pin(14))


def log_data():
    d.measure()
    send_data('temperature', d.temperature())
    send_data('humidity', d.humidity())


def send_data(key, value):
    url = aio_url % key
    json = {'value': value}
    headers = {'x-aio-key': aio_key}
    r = requests.post(url, json=json, headers=headers)
    print(key, value, r.status_code)

def run():
    import time
    while True:
        log_data()
        time.sleep(60)

