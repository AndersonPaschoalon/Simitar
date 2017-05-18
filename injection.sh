#!/bin/bash
interface=$1
sudo packit -i ${interface} -s 10.22.41.6 -d 172.16.1.3 -D 1-1024 -F S -v
#sudo packit -t TCP -c 0 -i ${interface} -z 1400  -d 172.1.4.5 -t 64 -s 44 -d 1223
