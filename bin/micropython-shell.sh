#!/bin/bash

PORT=${1:-/dev/ttyUSB0}

echo "Using $PORT"

screen $PORT 115200
