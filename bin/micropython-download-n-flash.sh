#!/bin/bash

PORT=${1:-/dev/ttyUSB0}
FIRMWARE="http://micropython.org/resources/firmware/esp8266-20170108-v1.8.7.bin"

source esptool/env/bin/activate && \
    curl -O -J $FIRMWARE && \
    esptool.py --port $PORT erase_flash && \
    esptool.py --port $PORT write_flash -fm dio -fs 32m 0x00000 `basename $FIRMWARE`
