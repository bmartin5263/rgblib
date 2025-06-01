#!/bin/sh -e

if [ $# -ne 1 ]; then
  echo "Usage: $0 <variables.yml>"
  exit 1
fi

VARIABLES_YML="$1"


yes | fly -t rgblib set-pipeline -c cicd/deploy-pipeline.yml -p rgblib-deploy -l "${VARIABLES_YML}"