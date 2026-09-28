#!/bin/sh -e

docker compose -f cicd/docker-compose-concourse-ec2.yml up -d
echo "Waiting for Concourse to startup..."

sleep 10 # wait for concourse to spin up

if ! command -v fly >/dev/null 2>&1; then
    curl 'http://localhost:8080/api/v1/cli?arch=amd64&platform=linux' -o fly \
        && chmod +x ./fly \
        && sudo mv ./fly /usr/local/bin/
fi

fly -t rgblib login -c http://localhost:8080 -u rgblib -p "$PASSWORD"