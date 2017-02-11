#!/bin/bash

cd bin && \
    mkdir -p envs && \
    cd envs && \
    virtualenv -p python2 esptool && \
    source esptool/bin/activate && \
    pip install esptool && \
    deactivate && \
    cd .. && \
    ln -s $(pwd)/envs/esptool/bin/esptool.py
