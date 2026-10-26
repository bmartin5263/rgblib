#!/bin/sh -e

root="$(cd "$(dirname "$0")/.." && pwd)"

pio run -d "$root" -e ci

# build each example
for example in "$root"/examples/*/; do
  pio run -d "$example" -e nano_esp32
done
