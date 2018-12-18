#!/bin/bash

source data/config/simitar-workspace-config.sh
sudo -E ./bin/simitar-gen --tool iperf --mode client --ether lo --xml ./data/xml/skype.sec.xml --dst-ip 127.0.0.1
sudo -E ./bin/simitar-gen --tool iperf --mode server --ether eth0 --xml ./data/xml/skype.sec.xml
sudo -E ./bin/simitar-gen --tool tins --mode server --ether eth0 --xml ./data/xml/skype.sec.xml


