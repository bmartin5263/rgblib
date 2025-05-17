#!/bin/bash -e

echo "Setting up Docker"
yes | sudo yum install docker
sudo usermod -a -G docker ec2-user
id ec2-user # Reload a Linux user's group assignments to docker w/o logout
newgrp docker

echo "Setting up Docker Compose"
DOCKER_CONFIG=${DOCKER_CONFIG:-$HOME/.docker}
mkdir -p "$DOCKER_CONFIG"/cli-plugins
curl -SL https://github.com/docker/compose/releases/download/v2.18.1/docker-compose-linux-x86_64 -o $DOCKER_CONFIG/cli-plugins/docker-compose
chmod +x $DOCKER_CONFIG/cli-plugins/docker-compose

echo "Starting Docker"
sudo systemctl enable docker.service
sudo systemctl start docker.service

echo "Setting up Concourse"

TOKEN=$(curl -X PUT "http://169.254.169.254/latest/api/token" -H "X-aws-ec2-metadata-token-ttl-seconds: 21600")
EC2_DNS=$(curl -H "X-aws-ec2-metadata-token: $TOKEN" -s http://169.254.169.254/latest/meta-data/public-hostname)
export EC2_DNS

./Scripts/concourse-up.sh
./Scripts/set-pipeline.sh