#!/usr/bin/env bash

sudo apt-get update --yes
sudo apt-get install --yes cmake
sudo apt-get install --yes libgtest-dev
sudo apt-get install --yes valgrind
sudo apt-get install --yes cppcheck
sudo apt-get install --yes curl
sudo apt-get install --yes wget
sudo apt-get install --yes unzip
export CODECOV_TOKEN="26c004a8-b488-43b9-b095-62632b2b38f1"
cd /usr/src/gtest && sudo mkdir build && cd build 
sudo cmake .. && sudo make && sudo cp *.a /usr/lib
