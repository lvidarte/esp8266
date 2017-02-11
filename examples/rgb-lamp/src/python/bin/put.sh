#!/bin/bash

if [ ! -f bin/ampy ]; then
    echo "ampy is not installed! installing..."
    cd ../../../.. && bin/ampy-install.sh && cd -
fi

PORT=${1:-/dev/ttyUSB0}

if [ ! -f template.py ]; then
    echo "template doesn't exist! creating..."
    bin/minify.py > template.py
fi

for FILE in boot.py main.py template.py; do
    bin/ampy -p $PORT put $FILE
done

