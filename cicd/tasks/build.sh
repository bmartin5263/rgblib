#!/bin/sh -e

apk add --no-cache curl
apk add --no-cache python3

curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
export PATH=$PATH:$HOME/.local/bin

cd repo

./scripts/build-library.sh