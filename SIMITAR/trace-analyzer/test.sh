#!/bin/bash
cd ..
source data/config/simitar-workspace-config.sh
cd trace-analyzer/; 
./trace-analyzer --trace "live_background-traffic-1"
