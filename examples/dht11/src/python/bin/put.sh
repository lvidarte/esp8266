#!/bin/bash

if [ ! -f bin/ampy ]; then
    echo "ampy is not installed! installing..."
    cd ../../../.. && bin/ampy-install.sh && cd -
fi

PORT=${1:-/dev/ttyUSB0}

bin/ampy -p $PORT put boot.py main.py requests.py

