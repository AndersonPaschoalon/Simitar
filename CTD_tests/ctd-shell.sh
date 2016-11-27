#!/bin/bash

arg1=$1

main()
{
	if [[ $arg1 == "veth" ]]
		then
		veth_test;

	elif [[ $arg1 == "" ]]
		then
		help_menu;

	else
		help_menu;
	fi

}

veth_test()
{
	./scripts/setup-testbed.sh setup-veth1
	./scripts/qualification-tests.sh --sim 
	./scripts/qualification-tests.sh --collect
	./scripts/testbed-shell.sh delete-veth1
	./scripts/plotData.m
	#clean_data;
}

clean_data()
{
	rm -f ./scripts/data/*
}

help_menu()
{
	echo "Usage: ./cdt-shell <opt>";
	echo "    veth  : tests the behavior unther a simple veth configuration"
	echo "    help  : display this help menu";
}

if [ "${1}" != "--source-only" ];                                               
then                                                                            
    main "${@}";                                                                
fi  
