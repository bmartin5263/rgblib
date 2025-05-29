#!/bin/sh -e

apk add --no-cache curl
apk add --no-cache python3
apk add --no-cache gcompat

curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
export PATH=$PATH:$HOME/.local/bin

mkdir -p /usr/local/bin
ln -s ~/.platformio/penv/bin/platformio /usr/local/bin/platformio
ln -s ~/.platformio/penv/bin/pio /usr/local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb /usr/local/bin/piodebuggdb

cd repo

pio account login -u "${PIO_USERNAME}" -p "${PIO_PASSWORD}"

./scripts/build-library.sh
pio pkg publish ".libbuild/rgblib.tar.gz" --type library --no-interactive

./scripts/increment-version.sh

git add ./library.json
git commit -m "[Version]"