#!/bin/bash

arg1=$1;
arg2=$2;
arg3=$3;
arg4=$4;

main()
{
	if [[ $arg1 == "veth" ]]
		then
		veth_test;

	elif [[ $arg1 == "" ]]
		then
		help_menu;

	elif [[ $arg1 == "prototype" ]]
		then
		prototype_pcap $arg2 $arg3;

	elif [[ $arg1 == "prototype-flow" ]]
		then
		prototype_flow $arg2 $arg3 $arg4;

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

prototype_pcap()
{
	#pcap_name="qualification1.pcap";
	#exName="kkk";

	pcap_name=$1;
	exName=$2;

	#sniffer
	cd scripts/; exec;
	./pcap-sniffer.sh --time-delta ${pcap_name} ${exName};
	#dataProcessor
	cd prototype-dataProcessor/; exec;
	./dataProcessor.m ${exName}
	#plot
	./modelFittingEvaluation-plots.sh ${exName};
	cd ../..; exec;

}

prototype_flow()
{
	pcap_name=$1;
	exName=$2;
	filter=$3;

	#sniffer
	cd scripts/; exec;
	./pcap-sniffer.sh --flow-time-delta ${pcap_name} ${exName} ${filter};
	./timerelative2timedelta.m ${exName};
	#dataProcessor
	cd prototype-dataProcessor/; exec;
	./dataProcessor.m ${exName}
	#plot
	./modelFittingEvaluation-plots.sh ${exName};
	cd ../..; exec;


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
