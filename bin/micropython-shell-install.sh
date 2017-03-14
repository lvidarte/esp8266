#!/bin/bash

for DIR in `ls -1 examples`
do
    if [ -d "examples/$DIR/src/python" ]
    then
        if [ ! -d "examples/$DIR/src/python/bin" ]
        then
            mkdir "examples/$DIR/src/python/bin"
        fi
        ln -fs $(pwd)/bin/micropython-shell.sh examples/$DIR/src/python/bin/shell
    fi
done
