#!/bin/bash

#files
MATLAB_DATA="../data/matlab_data_";
OPT_TIME_CAP="--time-delta";
OPT_TIME_FLOW="--flow-time-delta"


#EX_NUMBER=$1
arg1=$1
arg2=$2;
arg3=$3;
arg4=$4

main()
{
	local pcap_file=${arg2};
	local exName=${arg3};


	if [[ $arg1 == ${OPT_TIME_CAP} ]]
		then
		tshark_frameTimeDelta $pcap_file $exName

	elif [[ $arg1 == ${OPT_TIME_FLOW} ]]
		then

		local flow_filter=$arg4
		#flow_filter="'(ip.src==69.12.209.118)&&(ip.dst==153.193.117.110)&&(tcp.srcport==80)&&(tcp.dstport==58902)'";
		tshark_flowTimeDelta $pcap_file $exName ${flow_filter}
		./timerelative2timedelta.m $exName

	else
		help_menu;
	fi

	return 0;
}

###############################################################################
#
###############################################################################
help_menu()
{

	echo "./pcap-sniffer.sh --time-delta/--flow-time-delta  <pcap_file> <exName>";
}

###############################################################################
#
###############################################################################
tshark_frameTimeDelta()
{
	# path and filename to of pcap
	local pcap_path_fileName=$1;
	local experiment_name=$2

	touch ${MATLAB_DATA}${experiment_name}".txt";
	tshark -r ${pcap_path_fileName} -T fields -e frame.time_delta >> ${MATLAB_DATA}${experiment_name}".txt";

	echo "time delta stored at " ${MATLAB_DATA}${experiment_name}".txt";

}

###############################################################################
#
###############################################################################
tshark_flowTimeDelta()
{
	# path and filename to of pcap
	local pcap_path_fileName=$1;
	local experiment_name=$2
	local flow_filter=$3 #'(ip.src==43.252.226.5)&&(ip.dst==125.6.107.157)&&(tcp.srcport==80)&&(tcp.dstport==64834)'
	#./pcap-sniffer.sh --flow-time-delta ../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz "kkkk" '(ip.src==43.252.226.5)&&(ip.dst==125.6.107.157)&&(tcp.srcport==80)&&(tcp.dstport==64834)'

	touch ${MATLAB_DATA}${experiment_name}".txt";
	tshark -r ${pcap_path_fileName} -T fields -e frame.time_relative  -Y ${flow_filter} >> ${MATLAB_DATA}${experiment_name}".txt";

	echo "time delta stored at " ${MATLAB_DATA}${experiment_name}".txt";

}


################################################################################
# Main function
################################################################################
if [ "${1}" != "--source-only" ]; 
then
    main "${@}";
fi







