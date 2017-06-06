#/bin/bash
interface=$1
sudo ifconfig $interface up
sudo ifconfig $interface promisc
