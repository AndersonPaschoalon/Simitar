#/bin/bash
interface=$1
ifconfig $interface up
ifconfig $interface promisc
