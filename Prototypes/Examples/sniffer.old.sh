#!/bin/bash

#files
SNIFFER_COLECTOR="./data/sniffer.txt.tmp";
TRACE_DATABASE="./data/trace.db";
MATLAB_PLOT_DATA="./data/plot_data_";
FILTER_LIST_FILE="filters.list";

EX_NUMBER=$1

main()
{
	local name1="exQualification";
	local coment1="Qualification";
	
	reset_traceDb
	create_traceDb

	#pcap_file="../pcap/live_background-traffic-1.pcap";
	pcap_file="../pcap/qualification1.pcap";
	tshark_pcapToFile ${pcap_file};
	store_fileToDatabase $name1 $coment1;
	parser_toMatlab $name1
	./plotData.m

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

	local n_lines=`awk 'END{print(NR)}' $FILTER_LIST_FILE `;
	local awk_parser_out=`awk -v n_lines=$n_lines '
	{
		if(NR == 0){
			fields = "";
			options = "";
		}
		#ignore comment lines and blank lines
		#ignore_flag = match($0, /(#.*)|^([:blank:]*$)|(^.*ignore_pcap.*$)/);
		ignore_flag = match($0, /(#.*)|^([:blank:]*$)/);
		
		#process data
		if(!ignore_flag){
			#printf("-e %s ", $1);
			#print($0)
			fields = fields " " $1;
			options = options "-e " $1 " ";	
		}

		if(NR == n_lines)
		{ 
			print(fields);
			print(" @ ");
			print(options);

		}
	}
	' $FILTER_LIST_FILE `;

	local fields=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[1]);}'`;
	local options=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[2]);}'`;

	#read pcap file
	touch ${SNIFFER_COLECTOR};
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

	local n_lines=`awk 'END{print(NR)}' $FILTER_LIST_FILE `

	local awk_parser_out=`awk -v n_lines=$n_lines '
	{
		if(NR == 0){
			fields = "";
			options = "";
		}
		#ignore comment lines and blank lines
		ignore_flag = match($0, /(#.*)|^([:blank:]*$)|(^.*ignore_pcap.*$)/);
		
		#process data
		if(!ignore_flag){
			#printf("-e %s ", $1);
			#print($0)
			fields = fields " " $1;
			options = options "-e " $1 " ";	
		}

		if(NR == n_lines)
		{ 
			print(fields);
			print(" @ ");
			print(options);

		}
	}
	' $FILTER_LIST_FILE`

	local fields=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[1]);}'`
	local options=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[2]);}'`

	#read pcap file
	touch ${SNIFFER_COLECTOR}
	echo $fields > ${SNIFFER_COLECTOR}

	tshark -r ${pcap_path_fileName}  -T fields -E separator="|" $options >> ${SNIFFER_COLECTOR}
	
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

	> setFlow.sql
	echo "begin transaction;" >> setFlow.sql 
	for i in `seq 0 $nIds`;                                                         
	do                     
		IFS='|' read -r -a flowTag_vector <<< ${flowTags[$i]}; 
		echo "update  TraceCapture set flowID=$i where eth__type='${flowTag_vector[0]}' and ip__src='${flowTag_vector[1]}' and ip__dst='${flowTag_vector[2]}' and ip__proto='${flowTag_vector[3]}' and tcp__srcport='${flowTag_vector[4]}' and udp__srcport='${flowTag_vector[5]}' and dccp__srcport='${flowTag_vector[6]}'  and sctp__srcport='${flowTag_vector[7]}'  and tcp__dstport='${flowTag_vector[8]}'    and udp__dstport='${flowTag_vector[9]}'  and dccp__dstport='${flowTag_vector[10]}'   and sctp__dstport='${flowTag_vector[11]}';" >> setFlow.sql;
	done 
	echo "commit transaction;" >> setFlow.sql

	#dysplay
	echo "Commit data"
	sleep 0.1
	sqlite3 ${TRACE_DATABASE} < setFlow.sql

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

	touch save_trace.sql
	echo "begin transaction;" > save_trace.sql;
	for i in `seq 2 ${number_lines}`
	do
		traceCapture_values=`awk -v current_line=$i '{if(NR == current_line) {printf($0)} }' ${SNIFFER_COLECTOR} |sed "s/|/', '/g"`;
		traceCapture_values=$"'"$newExperimentId$"', '"${traceCapture_values}$"'";
		echo "insert into TraceCapture($traceCapture_fields) values($traceCapture_values);" >> save_trace.sql;
		#printf "$i , "

	done
	echo "commit transaction;" >> save_trace.sql;
	

	#display
	echo "Commit data"
	sleep 0.1
	sqlite3 ${TRACE_DATABASE} < save_trace.sql

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
	 * More important features (there is some entries separated by comma)
	 *(alguns pacotes estao vindo com varios enderecos IP e protocolos. 
	 * Aparentemente sao pacotes sFlow 
	 * https://www.wireshark.org/docs/dfref/s/sflow.html)
	 * frame__number, frame__len, frame__time_delta, frame__time_relative
	 * ip__dst, ip__src, ip__ttl, ip__version, ipv6__addr, ipv6__dst, ipv6__flow, 
	 * eth__type, tcp__window_size, udp__dstport, udp__srcport, udp__stream,  
	 * icmp__address_mask, icmp__lifetime, icmp__int_info__ip, 
	 * icmp__int_info__ipv4, icm    p__int_info__ipv6, icmp__type, dccp__dstport, 
	 * dccp__type,  sctp__dstport, sc    tp__parameter_ipv4_address, 
	 * sctp__parameter_ipv6_address, sctp__srcport
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
		frame__cap_len       unsigned integer(4) not null, -- Frame length stored into the capture file Unsigned integer, 4 bytes
		frame__comment       varchar2(255)       not null, -- Comment Character string
		frame__len           unsigned integer(4) not null, -- Frame length on the wire 	Unsigned integer, 4 bytes
		frame__offset_shift  double              not null, -- Time shift for this packet Time offset
		frame__p2p_dir       integer             not null, -- Point-to-Point Direction  Signed integer, 1 byte
		frame__p_prot_data   unsigned integer(4) not null, -- Number of per-protocol-data Unsigned integer, 4 bytes
		frame__pkt_len       unsigned integer(4) , -- Frame length on the wire 	Unsigned integer, 4 bytes ignore_pcap
		frame__protocols     varchar2(255)       not null, -- Protocols in frame Character string
		frame__ref_time      varchar2(255)       not null, -- This is a Time Reference frame  Label
		frame__time          varchar2(255)        not null, -- Arrival Time  Date and time 
		frame__time_delta    double              not null, -- Time delta from previous captured frame Time offset 	
		frame__time_delta_displayed double       not null, -- displayed Time delta from previous displayed frame Time offset 	
		frame__time_epoch    varchar2(255)       not null, -- Epoch Time 	Time offset 	
		frame__time_invalid  varchar2(255)       not null, -- Expert Info 	Label 	
		frame__time_relative double              not null, -- Time since reference or first frame Time offset 	
		ip__dst              text                not null, -- Destination IPv4 address
		ip__dst_host 	     text                not null, -- Destination Host Character string
		ip__fragment         text                not null, -- IPv4 Fragment 	Frame number
		ip__fragment__count   text               not null, -- Fragment count 	Unsigned integer, 4 bytes
		ip__hdr_len          unsigned integer(1) not null, -- Header Length 	Unsigned integer, 1 byte
		ip__len              unsigned integer(2) not null, -- Total Length 	Unsigned integer, 2 bytes
		ip__proto 	     unsigned integer(1) not null, -- Protocol 	Unsigned integer, 1 byte
		ip__src              text                not null, -- Source  IPv4 address
		ip__src_host         text                not null, -- Source Host Character string
		ip__ttl              unsigned integer    not null, -- Time to live Unsigned integer, 1 byte
		ip__version          unsigned integer    not null, --
		ipv6__addr           text                not null, -- Source or Destination Address 	IPv6 address
		ipv6__dst            text                not null, -- Destination 	IPv6 address
		ipv6__flow           varchar2(255)       not null, -- Flowlabel
		ipv6__fragment       text                not null, -- IPv6 Fragment 	Frame number
		ipv6__fragment__count integer            not null, -- Fragment count 	Unsigned integer, 4 bytes
		ipv6__opt__jumbo      integer            not null, -- Payload Length 	Unsigned integer, 4 bytes
		ipv6__plen            integer            not null, -- Payload length 	Unsigned integer, 2 bytes
		ipv6__version        integer             not null, -- Version Unsigned integer, 1 byte
		eth__addr Address    varchar2(255)       not null, -- Ethernet or other MAC address
		eth__addr_resolved   varchar2(255)       not null, -- Address (resolved) 	Character string
		eth__dst             varchar2(255)       not null, -- Destination 	Ethernet or other MAC address
		eth__dst_resolved    varchar2(255)       not null, -- Destination (resolved) 	Character string
		eth__len             varchar2(255)       not null, -- Length 	Unsigned integer, 2 bytes
		eth__padding         varchar2(255)       not null, -- Padding 	Sequence of bytes
		eth__src             varchar2(255)       not null, -- Source 	Ethernet or other MAC address
		eth__src_resolved    varchar2(255)       not null, -- Source (resolved) 	Character string
		eth__type            unsigned integer    not null, -- Type 	Unsigned integer, 2 bytes (L3 protocol)
		tcp__ack             unsigned integer    not null, -- Acknowledgment number 	Unsigned integer, 4 bytes
		tcp__dstport         unsigned integer    not null, -- Destination Port 	Unsigned integer, 2 bytes
		tcp__hdr_len         unsigned integer    not null, -- Header Length 	Unsigned integer, 1 byte
		tcp__len             unsigned integer    not null, -- TCP Segment Len 	Unsigned integer, 4 bytes
		tcp__nxtseq          unsigned integer    not null, -- Next sequence number 	Unsigned integer, 4 bytes
		tcp__proc__dstcmd   varchar2(255)       not null, -- Destination process name 	Character string
		tcp__proc__dstpid    unsigned integer    not null, -- Destination process ID 	Unsigned integer, 4 bytes
		tcp__proc__dstuid    unsigned integer    not null, -- Destination process user ID 	Unsigned integer, 4 bytes
		tcp__proc__dstuname  varchar2(255)       not null, -- Destination process user name 	Character string
		tcp__proc__srccmd    varchar2(255)       not null, -- Source process name 	Character string
		tcp__proc__srcpid    unsigned integer    not null, -- Source process ID 	Unsigned integer, 4 bytes
		tcp__proc__srcuid    unsigned integer    not null, -- Source process user ID 	Unsigned integer, 4 bytes
		tcp__proc__srcuname  varchar2(255)       not null, --  Source process user name        Character string        
		tcp__reassembled_in  unsigned integer    not null, --  tcpReassembled PDU in frame        Frame number            
		tcp__seq             unsigned integer    not null, --  Sequence number         Unsigned integer, 4 bytes
		tcp__srcport         unsigned integer    not null, -- Source Port Unsigned integer, 2 bytes                
		tcp__time_delta      double              not null, --  Time since previous frame in this TCP stream    Time offset        
		tcp__time_relative   double              not null, --  Time since first frame in this TCP stream               
		tcp__window_size     unsigned integer    not null, --  Calculated window size  Unsigned integer, 4 bytes          
		tcp__window_size_scalefactor integer      not null, --  Window size scaling factor      Signed integer, 4 bytes
		tcp__window_size_value unsigned integer  not null, --  Window size value       Unsigned integer, 2 bytes          
		udp__dstport         unsigned integer    not null, --  Destination Port        Unsigned integer, 2 bytes               
		udp__length          unsigned integer    not null, --  Length  Unsigned integer, 2 bytes                               
		udp__proc__dstcmd    varchar2(255)       not null, --  Destination process name        Character string        
		udp__proc__dstpid    unsigned integer    not null, --  Destination process ID  Unsigned integer, 4 bytes       
		udp__proc__dstuid    unsigned integer    not null, --  Destination process user ID     Unsigned integer, 4 bytes
		udp__proc__dstuname  varchar2(255)       not null, --  Destination process user name   Character string           
		udp__proc__srccmd    varchar2(255)       not null, --  Source process name     Character string                   
		udp__proc__srcpid    unsigned integer    not null, --  Source process ID       Unsigned integer, 4 bytes       
		udp__proc__srcuid    unsigned integer    not null, --  Source process user ID  Unsigned integer, 4 bytes       
		udp__proc__srcuname  varchar2(255)       not null, --  Source process user name        Character string           
		udp__srcport         unsigned integer    not null, --  Source Port     Unsigned integer, 2 bytes                          
		udp__stream          unsigned integer    not null, --  Stream index    Unsigned integer, 4 bytes                       
		icmp__address_mask   text                , --  Address Mask    IPv4 address                       
		icmp__data_time      text                not null, --  Timestamp from icmp data        Date and time                      
		icmp__data_time_relative double          not null, --  Timestamp from icmp data (relative)     Time offset
		icmp__ext__version   unsigned integer    not null, --  Version         Unsigned integer, 1 byte                   
		icmp__int_info__ip   text                , --  Source  IPv4 address ignore_pcap                           
		icmp__int_info__ipaddr text              not null, --  IP Address      Boolean                                    
		icmp__int_info__ipunknown text           , --  Source  Sequence of bytes ignore_pcap              
		icmp__int_info__ipv4 text                not null, --  Source  IPv4 address                                    
		icmp__int_info__ipv6 text                not null, --  Source  IPv6 address                                    
		icmp__int_info__mtu  unsigned integer    not null, --  MTU     Boolean  (maximum transmission unit - https://en__wikipedia__org/wiki/Maximum_transmission_unit)
		icmp__length         unsigned integer    not null, --  Length  Unsigned integer, 1 byte                                   
		icmp__length__original_datagram unsigned integer , --  Length of original datagram     Unsigned integer, 1 byte ignore_pcap
		icmp__lifetime       unsigned integer    , --  Unsigned integer, 2 bytes       ignore_pcap        
		icmp__mpls__ttl      unsigned integer    not null, --  Time to live    Unsigned integer, 1 byte                           
		icmp__seq            unsigned integer    not null, --  Sequence number (BE)    Unsigned integer, 2 bytes                  
		icmp__type           unsigned integer    not null, --  Type    Unsigned integer, 1 byte                                   
		dccp__dstport        unsigned integer    not null, --  Destination Port        Unsigned integer, 2 bytes                  
		dccp__padding        text                , --  Padding         Sequence of bytes ignore_pcap                      
		dccp__port           unsigned integer    not null, --  Source or Destination Port      Unsigned integer, 2 bytes          
		dccp__seq            unsigned integer    not null, --  Sequence Number         Unsigned integer, 8 bytes  
		dccp__srcport        unsigned integer    not null, --  Source Port Unsigned integer, 2 bytes                
		dccp__timestamp      unsigned integer    not null, --  Timestamp       Unsigned integer, 4                                
		dccp__timestamp_echo unsigned integer    not null, --  Timestamp Echo  Unsigned integer, 4 bytes                  
		dccp__type           unsigned integer    not null, --  Type    Unsigned integer, 1 byte
		sctp__asconf_ack_seq_nr_number unsigned integer not null, --  Sequence number         Unsigned integer, 4 bytes
		sctp__dstport        unsigned integer    not null, --  Unsigned integer, 2 bytes               
		sctp__forward_tsn_sid unsigned integer   not null, --  Stream identifier       Unsigned integer, 2 bytes       
		sctp__forward_tsn_ssn unsigned integer   not null, --  Stream sequence number  Unsigned integer, 2 bytes       
		sctp__hmac           text                not null, --  HMAC    Sequence of bytes                                       
		sctp__hmac_id        unsigned integer    not null, --  HMAC identifier         Unsigned integer, 2 bytes               
		sctp__parameter_hostname varchar2(255)   not null, --  Hostname        Character string                
		sctp__parameter_ipv4_address text        not null, --  IP Version 4 address    IPv4 address            
		sctp__parameter_ipv6_address text        not null, --  IP Version 6 address    IPv6 address            
		sctp__rtt            unsigned integer    , --  The RTT to ACK the chunk was    Time offset ignore_pcap         
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

if [ "${1}" != "--source-only" ]; 
then
    main "${@}";
fi

#main;






