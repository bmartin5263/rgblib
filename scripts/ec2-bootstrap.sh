#!/bin/sh -e

echo "Creating SSH Key"
ssh-keygen -f .ssh/id_rsa -t rsa -N ''
echo "Copy the following key and add it to the git repository's deploy keys then press any key to continue setup:"
cat .ssh/id_rsa.pub
read -r -n 1 -s

echo "Installing Git"
yes | sudo yum install git
ssh-keyscan -H github.com >> ~/.ssh/known_hosts

echo "Cloning rgblib"
yes yes | git clone git@github.com:bmartin5263/rgblib.git