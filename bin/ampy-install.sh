#!/bin/bash

function create_ampy_link
{
    local DIR=$1

    if [ -d ../examples/$DIR/src/python ]
    then
        if [ ! -d ../examples/$DIR/src/python/bin ]
        then
            mkdir ../examples/$DIR/src/python/bin
        fi
        ln -fs $(pwd)/envs/ampy/bin/ampy ../examples/$DIR/src/python/bin/ampy
    fi
}

cd bin && \
    mkdir -p envs && \
    cd envs && \
    virtualenv -p python3 ampy && \
    source ampy/bin/activate && \
    pip3 install adafruit-ampy && \
    deactivate && \
    cd .. && \
    ln -fs $(pwd)/envs/ampy/bin/ampy && \
    for DIR in `ls -1 ../examples`; do create_ampy_link $DIR; done && \
    cd ..
