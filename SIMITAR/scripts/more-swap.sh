#!/bin/bash

swapoff -a
sudo fallocate -l 30G /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
swapon -a
