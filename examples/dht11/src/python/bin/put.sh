#!/bin/bash

if [ ! -f bin/ampy ]; then
    echo "ampy is not installed! installing..."
    cd ../../../.. && bin/ampy-install.sh && cd -
fi

PORT=${1:-/dev/ttyUSB0}
echo "Using $PORT"

for FILE in boot.py main.py; do
    bin/ampy -p $PORT put $FILE
done
