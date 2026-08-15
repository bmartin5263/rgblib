#!/bin/sh -e

if [ -z "$1" ]; then
  echo "Error: no IP address provided." >&2
  echo "Usage: $0 <ip-address>" >&2
  exit 1
fi

pio run -t upload -e debug --upload-port "$1"