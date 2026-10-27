#!/bin/sh -e

export PLATFORMIO_CORE_DIR="$PWD/.platformio"

apk add curl
apk add python3
apk add gcompat
apk add build-base

if [ ! -x "$PLATFORMIO_CORE_DIR/penv/bin/platformio" ]; then
    curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
    python3 get-platformio.py
fi

mkdir -p /usr/local/bin
ln -sf "$PLATFORMIO_CORE_DIR/penv/bin/platformio" /usr/local/bin/platformio
ln -sf "$PLATFORMIO_CORE_DIR/penv/bin/pio" /usr/local/bin/pio
ln -sf "$PLATFORMIO_CORE_DIR/penv/bin/piodebuggdb" /usr/local/bin/piodebuggdb

cd rgblib

./scripts/build.sh
./scripts/test.sh