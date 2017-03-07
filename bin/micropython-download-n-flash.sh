#!/bin/bash

PORT=${1:-/dev/ttyUSB0}
FIRMWARE="http://micropython.org/resources/firmware/esp8266-20170108-v1.8.7.bin"

echo "Using $PORT"

if [ ! -f `basename $FIRMWARE` ]
then
    curl -O -J $FIRMWARE
fi

bin/esptool.py --port $PORT erase_flash && \
bin/esptool.py --port $PORT write_flash -fm dio -fs 32m 0x00000 `basename $FIRMWARE`
