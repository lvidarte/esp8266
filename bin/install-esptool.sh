#!/bin/bash

mkdir esptool && \
    cd esptool && \
    virtualenv -p python2 env && \
    source env/bin/activate && \
    pip install esptool
