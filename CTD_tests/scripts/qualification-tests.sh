#/!/bin/bash

###############################################################################
#includes
###############################################################################
#configurations(env vars)
source options.cfg 
#TODO exclude this
source ${PROJECT_ROOT_DIR}/CompactTraceDescriptor/src/sniffer.sh --source-only 

###############################################################################
#defines 
###############################################################################
#TODO: exclude this
#external defines overwrite
FILTER_LIST_FILE="${PROJECT_ROOT_DIR}/CompactTraceDescriptor/src/filters.list";


main()
{
	opt=$1
	if [[ $opt == "--sim" ]]
	then
			
		generate_traces;	

	elif [[ $opt == "--collect" ]] 
	then

		collect_data;

	elif [[ $opt == "--help" ]]
	then

		help_menu
	
	else
		echo "Invalid option: " $opt
		help_menu;	
	fi
 	

}

help_menu()
{
	echo "Simulation opts:"
	echo "    --sim        Generate traces";
	echo "    --collect    Collect data from generated traffic traces";
	echo "    --help       display this help menu";
}

generate_traces()
{
	echo "+---------------------------------------------------------------+";
	echo "|Test - init                                                    |";
	echo "+---------------------------------------------------------------+";

	cd $SOFTWARE_DIR;
	
	for i in `seq 1 30`;
	do
		echo "+-----------------------------------------------------+";
		echo "|Run#$i                                               | ";
		echo "+-----------------------------------------------------+";

		local tcpdump_pid;
		local sender_pid;
		local receiver_pid;


		$RECEIVER_BIN & receiver_pid=$!;
		$SENDER_BIN -Q & sender_pid=$!;

		sleep $SLEEP;

		local pcap_file=$PCAP_DIR$PCAP_NAME$i".pcap";
		sudo tcpdump -i ${ETHERNET_INTERFACE} -s 65535 -w $pcap_file & tcpdump_pid=$!;
		$SOFTWARE_BIN;

		echo "Capturing pcap " $pcap_name;

		sleep $SLEEP;

		killall tcpdump;
		kill $sender_pid;
		kill $receiver_pid;
	done

	echo "+---------------------------------------------------------------+"
	echo "|Done                                                           |"
	echo "+---------------------------------------------------------------+"

	return;
}

#TODO: Implement this function not using external fuctions
collect_data()
{
	local pcap_file="";	
	local name_prefix="qualification";
	local comment1="qualification-exam-data";
	local name_experiment="";

	for i in `seq 1 30`
	do

		reset_traceDb;
		create_traceDb;
		
		name_experiment=$name_prefix$i;
		pcap_file=$PCAP_DIR$PCAP_NAME$i".pcap";
		tshark_pcapToFile ${pcap_file};                                         
		store_fileToDatabase $name_experiment $coment1;                                   
		parser_toMatlab $name_experiment                                                  
	done	

	return;
}

if [ "${1}" != "--source-only" ];                                               
then                                                                            
    main "${@}";                                                                
fi  


