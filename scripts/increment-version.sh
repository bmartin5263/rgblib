#!/bin/bash

# Check for input argument
if [ $# -ne 1 ]; then
  echo "Usage: $0 <json-file>"
  exit 1
fi

JSON_FILE="$1"

# Ensure the file exists
if [ ! -f "$JSON_FILE" ]; then
  echo "File not found: $JSON_FILE"
  exit 1
fi

# Use sed and awk to increment the PATCH version
# This assumes the version string is in the format: "version": "x.y.z"
UPDATED=$(awk '
  BEGIN { done=0 }
  {
    if (!done && match($0, /"version"[[:space:]]*:[[:space:]]*"[0-9]+\.[0-9]+\.[0-9]+"/)) {
      version = substr($0, RSTART, RLENGTH)
      split(version, parts, /[": ]+/)
      split(parts[3], nums, ".")
      nums[3] += 1
      new_version = "\"version\": \"" nums[1] "." nums[2] "." nums[3] "\""
      sub(/"version"[[:space:]]*:[[:space:]]*"[0-9]+\.[0-9]+\.[0-9]+"/, new_version)
      done=1
    }
    print
  }
' "$JSON_FILE")

# Overwrite the file with the updated contents
echo "$UPDATED" > "$JSON_FILE"

echo "Version updated in $JSON_FILE"