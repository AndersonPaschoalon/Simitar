#!/bin/bash

arg1=$1

main()
{
	if [[ $arg1 == ""  ]]
		then
		help_menu;
	elif [[ $arg1 == "--help" ]]
		then
		help_menu;
	else
		./pcap-sniffer.sh --time-delta  $arg2 $arg1
		./dataProcessor.m  $arg1;
		./modelFittingEvaluation-plots.sh  $arg1;
		./plotCostFunction.sh  $arg1;

	fi

	return 0;

}

help_menu()
{
	echo "To run:";
	echo "./run <experiment-name> <pcap-file-name>"

}


if [ "${1}" != "--source-only" ];                                               
then                                                                            
    main "${@}";                                                                
fi 
