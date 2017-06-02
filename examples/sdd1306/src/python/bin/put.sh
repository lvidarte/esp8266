#!/bin/bash

if [ ! -f bin/ampy ]; then
    echo "ampy is not installed! installing..."
    cd ../../../.. && bin/ampy-install.sh && cd -
fi

PORT=${1:-/dev/ttyUSB0}

for FILE in ssd1306.py weather.py; do
    bin/ampy -p $PORT put $FILE
done

