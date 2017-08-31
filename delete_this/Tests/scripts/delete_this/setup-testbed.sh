#!/bin/bash

arg1=$1


main()
{
	if [[ $arg1 == "setup-veth1" ]]
		then
		setup_veth1;

	elif [[ $arg1 == "delete-veth1" ]]
		then
		delete_veth1;

	elif [[ $arg1 == "" ]]
		then
		help_menu;

	else
		help_menu;
	fi

	return 0;

}

###############################################################################
# The fucnctions setup_veth1() and delete_veth1() build and delete a simple 
# setup of a sender and a destination virtual interfaces, with uses a virtual
# bridge.
# veth11======veth12->[br0]<-veht21======veth22
###############################################################################
setup_veth1()
{
	brctl addbr br0
	ip link add dev veth11 type veth peer name veth12
	ip link add dev veth21 type veth peer name veth22
	brctl addif br0 veth12
	brctl addif br0 veth22
	ip link set br0 up
	ip link set veth11 up
	ip link set veth12 up
	ip link set veth21 up
	ip link set veth22 up
	ip addr add 172.16.0.1/24 dev veth11
	ip addr add 172.16.0.2/24 dev veth21
	echo "Topology:"
	echo "veth11======veth12->[br0]<-veth21======veth22";
	echo "";
	echo "Text connectivity using ping:";
	ping -I 172.16.0.2  -c1 172.16.0.1

}

delete_veth1()
{
	sudo ip link delete veth11
	sudo ip link delete veth21
	sudo ip link delete veth12
	sudo ip link delete veth22
}

help_menu()
{
	echo "Automatize testbed creation";
	echo "Usage: ./testbed-shell <opt>";
	echo "    setup-veth1    : set up small virtual network, of two pairs, and one bridge."
	echo "                     veth11======veth12->[br0]<-veth21======veth22";
	echo "                     execute as a superuser";
	echo "    delete-veth1   : delete setup created by setup-veth1 option";
	echo "                     execute as a superuser";
	echo "    help           : display this help menu";
}

if [ "${1}" != "--source-only" ];                                               
then                                                                            
    main "${@}";                                                                
fi 



