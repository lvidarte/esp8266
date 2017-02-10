#!/bin/bash

FIRMWARE_DIR=firmware


if [ ! -d $FIRMWARE_DIR ]
then
    mkdir $FIRMWARE_DIR
fi

VERSION=$((`ls -1tr $FIRMWARE_DIR | tail -1 | awk -F '.' '{print $2}'` + 1))

platformio run && \
    cp .pioenvs/nodemcuv2/firmware.bin $FIRMWARE_DIR/firmware-v0.${VERSION}.bin && \
    ls -1 $FIRMWARE_DIR/
