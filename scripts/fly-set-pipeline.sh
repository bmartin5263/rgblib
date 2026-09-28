#!/bin/sh -e

yes | fly -t rgblib set-pipeline -c cicd/deploy-pipeline.yml -p rgblib -l cicd/secrets.yml