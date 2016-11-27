#!/bin/bash

main()
{
	pcap_file="../pcap/live_background-traffic-1.pcap";
	tshark_pcapToFile ${pcap_file}

	name1="Abacate";
	coment1="Otavio-augusto";
	name2="Abacatepopo";
	coment2="Otavio augusto lima XD";
	name3="Abacaxi";


	store_fileToDatabase $name1 $coment1;
	#store_fileToDatabase $name2 $coment2;
	#store_fileToDatabase $name3 $coment3
	
	return 0;
}

###############################################################################
# Capture packets/traffic statistics from a interface and store in a temp text 
# file
###############################################################################
tshark_interfaceToFile()
{
	echo "to do";
}

###############################################################################
# Capture packet/traffic statistics from a pcap file, and store in a temp text 
# file
###############################################################################
tshark_pcapToFile()
{
	pcap_pathFile_name=$1;
	experiment_name=$1;

	n_lines=`awk 'END{print(NR)}' filters.list `

	awk_parser_out=`awk -v n_lines=$n_lines '
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
	' filters.list`

	fields=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[1]);}'`
	options=`echo $awk_parser_out |awk '{split($0,a,"@"); print(a[2]);}'`

	#read pcap file
	touch sniffer.txt.tmp
	echo $fields > sniffer.txt.tmp

	tshark -r ${pcap_pathFile_name}  -T fields -E separator="|" $options >> sniffer.txt.tmp
	
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
	echo "to do";
}



###############################################################################
# Convert the colected data into loadable data in matlab matrix
# The data is loadable in a matrix M with the command:
# M = dlmread('<filename>.txt', '' , 1, 0)
###############################################################################
parser_toMatlab()
{
	echo "to do";
}


###############################################################################
# Strore the file content information into a SQLite database
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
		experimentList_out=`sqlite3 trace.db "select experimentName from \
		ExperimentList where experimentName='$experiment_name';"`;

		if [[ $experimentList_out != "" ]]
			then

			printf "Name ${experiment_name} is already in use, please select "
			printf "another name'experimentID'...\n";
			return 2;

		else
			newExperimentId=`sqlite3 trace.db "select max(experimentID) from \
			ExperimentList"`;
			if [[ $newExperimentId = "" ]]
				then
				newExperimentId=0;
			else
				newExperimentId=$((newExperimentId + 1));
			fi
		fi
	fi

	sqlite3 trace.db "insert into ExperimentList(experimentID, experimentName, \
		experimentDate, Commentaries) \
	values('${newExperimentId}', '${experiment_name}', '${experiment_date}',
		'${experiment_comments}');";

	
	#Now, store the trace data on  its table

	sniffer_fields=`awk '{if(NR == 1) {printf($0)}}' sniffer.txt.tmp|sed "s/\./__/g"`;
	IFS=' ' read -r -a fields_array <<< $sniffer_fields;
	number_lines=`wc -l sniffer.txt.tmp |awk '{printf($1)}'`;
	number_columns=`${#fields_array[@]}`;
	traceCapture_fields=`echo $sniffer_fields |sed "s/ /', '/g"`;
	traceCapture_fields=`echo $"'experimentID', '"$traceCapture_fields$"'"`;

	touch save_trace.sql

	echo "begin transaction;" > save_trace.sql;




	for i in `seq 2 ${number_lines}`
	do
		traceCapture_values=`awk -v current_line=$i '{if(NR == current_line) {printf($0)} }' sniffer.txt.tmp |sed "s/|/', '/g"`;
		traceCapture_values=$"'"$newExperimentId$"', '"${traceCapture_values}$"'";
		echo "insert into TraceCapture($traceCapture_fields) values($traceCapture_values);" >> save_trace.sql;
		#printf "$i , "

	done
	#printf ". (done)"

	echo "commit transaction;" >> save_trace.sql;

	#values list
	#awk '{if(NR == 2) {printf($0)} }' sniffer.txt.tmp |sed "s/|/', '/g"
	#echo $sniffer_fields |sed "s/ /', '/g"


}

main;






