#!/bin/bash

cd bin && \
    mkdir -p envs && \
    cd envs && \
    virtualenv -p python3 ampy && \
    source ampy/bin/activate && \
    pip3 install adafruit-ampy && \
    deactivate && \
    cd .. && \
    ln -fs $(pwd)/envs/ampy/bin/ampy && \
    ln -fs $(pwd)/envs/ampy/bin/ampy ../examples/rgb-lamp/src/python/bin/ampy && \
    ln -fs $(pwd)/envs/ampy/bin/ampy ../examples/dht11/src/python/bin/ampy && \
    ln -fs $(pwd)/envs/ampy/bin/ampy ../examples/ap/src/python/bin/ampy && \
    cd ..
