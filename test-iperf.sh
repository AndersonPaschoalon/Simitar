#!/bin/bash
#iperf -c 10.0.0.2 --bandwidth 0k --time 0.100000 --format k  --udp  --bind 10.0.0.1:35990 --realtime  --nodelay  --ttl 64 --nodelay
iperf -c 10.0.0.2 --bandwidth 0k --time 0.100000 --format k  --udp  --bind 10.0.0.1:35990 --realtime  --nodelay  --ttl 64 --nodelay

