#!/bin/bash

PORT=${1:-/dev/ttyUSB0}
FIRMWARE="http://micropython.org/resources/firmware/esp8266-20170108-v1.8.7.bin"

if [ ! -f `basename $FIRMWARE` ]
then
    curl -O -J $FIRMWARE
fi

source esptool/env/bin/activate && \
    esptool.py --port $PORT erase_flash && \
    esptool.py --port $PORT write_flash -fm dio -fs 32m 0x00000 `basename $FIRMWARE`
