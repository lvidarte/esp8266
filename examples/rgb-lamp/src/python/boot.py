# This file is executed on every boot (including wake-boot from deepsleep)

import gc
gc.collect()

import network

ap_if = network.WLAN(network.AP_IF)
ap_if.config(essid="RGBLamp", password="12345678")

while not ap_if.active():
    pass
