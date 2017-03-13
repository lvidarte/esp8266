from machine import Pin
from dht import DHT11
import urequests
import time


PHANT_HOST  = "192.168.43.217:8080"
PUBLIC_KEY  = "4YkYvXgMBPFlE1DZZPKJhdVm9W4"
PRIVATE_KEY = "qOaO3mXpgZUl372VVqpRhxaLmBe"


d = DHT11(Pin(14))


def read_sensor():
    d.measure()
    return {
        "temperature": d.temperature(),
        "humidity": d.humidity()
    }

def get_query(data):
    return "&".join(["%s=%.1f" % (k, v) for k, v in data.items()])

def phant_log(data):
    url = "http://%s/input/%s?%s" % (PHANT_HOST, PUBLIC_KEY, get_query(data))
    headers = {"Phant-Private-Key": PRIVATE_KEY}
    response = urequests.post(url, headers=headers)
    print(url, response.status_code, response.reason)
    response.close()

def run():
    while True:
        data = read_sensor()
        print("Sending data", data)
        phant_log(data)
        time.sleep(60)


