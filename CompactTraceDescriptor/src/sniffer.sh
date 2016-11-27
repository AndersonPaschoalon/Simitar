#!/bin/bash

#files
SNIFFER_COLECTOR="./data/sniffer.txt.tmp";
SQL_DATA_QUERIES="./data/save_trace.sql";
SQL_FLOW_QUERIES="./data/setFlow.sql";
TRACE_DATABASE="./data/trace.db";
MATLAB_PLOT_DATA="./data/plot_data_";
FILTER_LIST_FILE="filters.list";

EX_NUMBER=$1

main()
{
	local name1="exQualification";
	local coment1="Qualification";
	local pcap_file="../pcap/live_background-traffic-1.pcap";
	create_tempFiles;

	reset_traceDb;
	create_traceDb;

	pcap_file="../pcap/qualification1.pcap";
	tshark_pcapToFile ${pcap_file};
	store_fileToDatabase $name1 $coment1;
	parser_toMatlab $name1
	./plotTraceData.m ${MATLAB_PLOT_DATA}$name1".txt" ${name1};
	
	remove_tempFiles;
	return 0;
}




###############################################################################
# Print a list of filters used by tshark, to collect data from pacekts.  
###############################################################################
tshark_filterFields()
{
        local fields=" 
frame.number
frame.len
frame.protocols
frame.time
frame.time_delta
frame.time_relative
ip.dst
ip.proto
ip.src
ip.ttl
ipv6.addr
ipv6.dst
eth.dst
eth.src
eth.type
tcp.dstport
tcp.srcport
udp.dstport
udp.srcport
dccp.dstport
dccp.srcport
sctp.dstport
sctp.srcport ";

	echo $fields;
	
	return 0;	
}


###############################################################################
# Capture packets/traffic statistics from a interface and store in a temp text 
# file
###############################################################################
tshark_interfaceToFile()
{
	#name of the interface
	local interface_name=$1;
	#tshark fields
	local  fields=`tshark_filterFields`;
	#tshark fields options
	local options=`echo " "$fields |sed "s/\ /\ -e\ /g"`;

	echo $fields > ${SNIFFER_COLECTOR};
	tshark -i ${interface_name}  -T fields -E separator="|" $options >> ${SNIFFER_COLECTOR};
}

###############################################################################
# Capture packet/traffic statistics from a pcap file, and store in a temp text 
# file
###############################################################################
tshark_pcapToFile()
{
	# path and filename to of pcap
	local pcap_path_fileName=$1;
	#tshark fields
	local  fields=`tshark_filterFields`;
	#tshark fields options
	local options=`echo " "$fields |sed "s/\ /\ -e\ /g"`;

	echo $fields > ${SNIFFER_COLECTOR};
	tshark -r ${pcap_path_fileName}  -T fields -E separator="|"  $options  >> ${SNIFFER_COLECTOR};

	return 0;
}

###############################################################################
# Insert two column in the temp text file:
# flowID: "srcIP,dstIP,NetProtocol,tranportProtocol,srcPort,dstPort". In case 
#	the field do not exist, "x" is inserted
# FlowNumber: number of aparence of the flow, in crecente order (1, 2, 3, ...)
# This data is necessary to classify all flows.
# Also, it convert the extention of the file fom ".txt.tmp" to ".txt" (avoid
# incomplete data)
###############################################################################
parser_FlowData()
{
	local flowTag_vector="";

	local flowVet=`sqlite3 ${TRACE_DATABASE} "select distinct eth__type, ip__src, ip__dst, ip__proto, tcp__srcport, udp__srcport, dccp__srcport, sctp__srcport, tcp__dstport, udp__dstport, dccp__dstport, sctp__dstport from TraceCapture"`;

	IFS=' ' read -r -a flowTags <<< $flowVet;
	nIds=${#flowTags[@]};
	nIds=$((nIds-1));

	#dysplay
	echo "Creating flow queries...";

	echo "begin transaction;" >> ${SQL_FLOW_QUERIES};
	for i in `seq 0 $nIds`;                                                         
	do                     
		IFS='|' read -r -a flowTag_vector <<< ${flowTags[$i]}; 
		echo "update  TraceCapture set flowID=$i where eth__type='${flowTag_vector[0]}' and ip__src='${flowTag_vector[1]}' and ip__dst='${flowTag_vector[2]}' and ip__proto='${flowTag_vector[3]}' and tcp__srcport='${flowTag_vector[4]}' and udp__srcport='${flowTag_vector[5]}' and dccp__srcport='${flowTag_vector[6]}'  and sctp__srcport='${flowTag_vector[7]}'  and tcp__dstport='${flowTag_vector[8]}'    and udp__dstport='${flowTag_vector[9]}'  and dccp__dstport='${flowTag_vector[10]}'   and sctp__dstport='${flowTag_vector[11]}';" >>  ${SQL_FLOW_QUERIES};
	done 
	echo "commit transaction;" >> ${SQL_FLOW_QUERIES};

	#display
	echo "Commit data"
	sleep 0.1
	sqlite3 ${TRACE_DATABASE} < ${SQL_FLOW_QUERIES};

}



###############################################################################
# Convert the colected data into loadable data in matlab matrix
# The data is loadable in a matrix M with the command:
# M = dlmread('<filename>.txt', '' , 1, 0)
###############################################################################
parser_toMatlab()
{
	local experiment_name=$1;
	local experimentID="";

	experimentID=`sqlite3 ${TRACE_DATABASE} "select experimentID from ExperimentList where experimentName='${experiment_name}'"` ;

	if [[ $experimentID == "" ]]
		then

		echo "Error loading data. Invalid experiment name $experiment_name."

		return 1;

	else

		echo "${experiment_name} ${experimentID}"  > ${MATLAB_PLOT_DATA}${experiment_name}.txt;
		echo "frame__number flowID frame__len frame__time_delta frame__time_relative" >> ${MATLAB_PLOT_DATA}${experiment_name}.txt;

		sqlite3  -separator ' ' ${TRACE_DATABASE} "select frame__number, flowID, frame__len, frame__time_delta, frame__time_relative from TraceCapture where experimentID='${experimentID}'" >>  ${MATLAB_PLOT_DATA}${experiment_name}.txt;

	fi

	return 0;
}


###############################################################################
# Strore the file content information into a SQLite database, remove
# the temporary file sniffer.txt.tmp, and create an SQL script to store all
# data
###############################################################################
store_fileToDatabase()
{
	local experiment_name=$1;
	local experiment_comments=$2;

	local experiment_date=`date`;
	local experimentList_out="";
	local newExperimentId="";
	local sniffer_fields="";
	local number_lines="";
	local conter="";


	#Create the ExperimentList table

	if [[ $experiment_name == "" ]]
		then
		#no experiment name specified
		echo "Please, specify a valid experiment name"
		return 1;

	else
		experimentList_out=`sqlite3 ${TRACE_DATABASE} "select experimentName from \
		ExperimentList where experimentName='$experiment_name';"`;

		if [[ $experimentList_out != "" ]]
			then

			printf "Name ${experiment_name} is already in use, please select "
			printf "another name'experimentID'...\n";
			return 2;

		else
			newExperimentId=`sqlite3 ${TRACE_DATABASE} "select max(experimentID) from \
			ExperimentList"`;
			if [[ $newExperimentId = "" ]]
				then
				newExperimentId=0;
			else
				newExperimentId=$((newExperimentId + 1));
			fi
		fi
	fi

	sqlite3 ${TRACE_DATABASE} "insert into ExperimentList(experimentID, experimentName, \
		experimentDate, Commentaries) \
	values('${newExperimentId}', '${experiment_name}', '${experiment_date}',
		'${experiment_comments}');";

	
	#Now, store the trace data on  its table
	sniffer_fields=`awk '{if(NR == 1) {printf($0)}}' ${SNIFFER_COLECTOR}|sed "s/\./__/g"`;
	number_lines=`wc -l ${SNIFFER_COLECTOR} |awk '{printf($1)}'`;
	traceCapture_fields=`echo $sniffer_fields |sed "s/ /', '/g"`;
	traceCapture_fields=`echo $"'experimentID', '"$traceCapture_fields$"'"`;

	#display
	echo "Creating queries..."

	echo "begin transaction;" > ${SQL_DATA_QUERIES};
	for i in `seq 2 ${number_lines}`
	do
		traceCapture_values=`awk -v current_line=$i '{if(NR == current_line) {printf($0)} }' ${SNIFFER_COLECTOR} |sed "s/|/', '/g"`;
		traceCapture_values=$"'"$newExperimentId$"', '"${traceCapture_values}$"'";
		echo "insert into TraceCapture($traceCapture_fields) values($traceCapture_values);" >> ${SQL_DATA_QUERIES};
		#printf "$i , "

	done
	echo "commit transaction;" >> ${SQL_DATA_QUERIES};
	

	#display
	echo "Commit data"
	sleep 0.1
	sqlite3 ${TRACE_DATABASE} < ${SQL_DATA_QUERIES};

	#give flows label
	parser_FlowData;
}

################################################################################
# Create SQLite database if it do not exist
################################################################################
create_traceDb ()
{
	sqlite3 ${TRACE_DATABASE} "create table if not exists ExperimentList(
		-- Primary key
		experimentID    unsigned smallint not null,
		-- Data
		experimentName  varchar2(20)      not null,
		experimentDate  date              not null,
		Commentaries    text,
		-- Constraints
		constraint ExperimentList_experimentID_pk primary key (experimentID)
	);

	/**
	 *(alguns pacotes estao vindo com varios enderecos IP e protocolos. 
	 * Aparentemente sao pacotes sFlow 
	 * https://www.wireshark.org/docs/dfref/s/sflow.html)
	 */
	create table if not exists TraceCapture(
		-----------------------------------------------------------------------
		-- Primary keys
		-----------------------------------------------------------------------
		experimentID         unsigned  smallint  not null, -- Reference to the parent table
		frame__number        unsigned integer(4) not null, -- Frame Number Unsigned integer, 4 bytes
		-----------------------------------------------------------------------
		-- Flow Identifiers
		-----------------------------------------------------------------------
		--flowTag              text                not null, -- concatenation of the fields, separated by a slash
		--	-- /eth__type/ip__src/ip__dst/ip.proto/(tcp__srcport|udp__srcport|.|dccp__dstport|sctp__srcport)/(tcp__dstport|udp___dstport|.|dccp__dstport|sctp__dstport)
		--	-- /<Network Protocol>/<IP dst>/<IP src>/<Transport Protocol>/<Port src or .>/<Port dst or .>		
		--flowID               unsigned integer    not null, -- Flow identifier number, in order of occurence
		flowID               unsigned integer    , -- Flow identifier number, in order of occurence
		-----------------------------------------------------------------------
		-- Trace Data
		-----------------------------------------------------------------------
		frame__len           unsigned integer(4) not null, -- Frame length on the wire 	Unsigned integer, 4 bytes
		frame__protocols     varchar2(255)       not null, -- Protocols in frame Character string
		frame__time          varchar2(255)        not null, -- Arrival Time  Date and time 
		frame__time_delta    double              not null, -- Time delta from previous captured frame Time offset 	
		frame__time_relative double              not null, -- Time since reference or first frame Time offset 	
		ip__dst              text                not null, -- Destination IPv4 address
		ip__proto 	     unsigned integer(1) not null, -- Protocol 	Unsigned integer, 1 byte
		ip__src              text                not null, -- Source  IPv4 address
		ip__ttl              unsigned integer    not null, -- Time to live Unsigned integer, 1 byte
		ipv6__addr           text                not null, -- Source or Destination Address 	IPv6 address
		ipv6__dst            text                not null, -- Destination 	IPv6 address
		eth__dst             varchar2(255)       not null, -- Destination 	Ethernet or other MAC address
		eth__src             varchar2(255)       not null, -- Source 	Ethernet or other MAC address
		eth__type            unsigned integer    not null, -- Type 	Unsigned integer, 2 bytes (L3 protocol)
		--tcp__ack             unsigned integer    not null, -- Acknowledgment number 	Unsigned integer, 4 bytes
		tcp__dstport         unsigned integer    not null, -- Destination Port 	Unsigned integer, 2 bytes
		tcp__srcport         unsigned integer    not null, -- Source Port Unsigned integer, 2 bytes                
		udp__dstport         unsigned integer    not null, --  Destination Port        Unsigned integer, 2 bytes               
		udp__srcport         unsigned integer    not null, --  Source Port     Unsigned integer, 2 bytes                          
		dccp__dstport        unsigned integer    not null, --  Destination Port        Unsigned integer, 2 bytes                  
		dccp__srcport        unsigned integer    not null, --  Source Port Unsigned integer, 2 bytes                
		sctp__dstport        unsigned integer    not null, --  Unsigned integer, 2 bytes               
		sctp__srcport        unsigned integer    not null, --  Source port     Unsigned integer, 2 bytes 
		-----------------------------------------------------------------------
		-- Constraints
		-----------------------------------------------------------------------
		constraint TraceCapture_experimentID_fk foreign key (experimentID) references ExperimentList(experimentID), 
		constraint TraceCapture_experimentIDframenumber_pk primary key (experimentID, frame__number)
	);";

}


################################################################################
# Reset SQLite database
################################################################################
reset_traceDb() 
{
	rm ${TRACE_DATABASE};
	create_traceDb;
}

################################################################################
# Create temp files to be used in the script
################################################################################
create_tempFiles()
{
	touch ${SNIFFER_COLECTOR}
	touch ${SQL_DATA_QUERIES}
	touch ${SQL_FLOW_QUERIES}
}

################################################################################
# Remove temp files. Execute this at the end of the script
################################################################################
remove_tempFiles()
{
	rm -f ${SNIFFER_COLECTOR}
	rm -f ${SQL_DATA_QUERIES}
	rm -f ${SQL_FLOW_QUERIES}
}

################################################################################
# Main function
################################################################################
if [ "${1}" != "--source-only" ]; 
then
    main "${@}";
fi







