#!/bin/bash -e

yes | fly -t rgblib set-pipeline -c cicd/deploy-pipeline.yml -p rgblib-deploy -l cicd/deploy-variables.yml