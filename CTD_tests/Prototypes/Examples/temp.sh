#!/bin/bash

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
			print(" @ " );
			print(options);

		}
	}
' filters.list`

echo $awk_parser_out;

options=`echo $awk_parser_out |awk '{split($0,options,"@"); print(a[2])}'`;
fields=`echo $awk_parser_out |awk '{split($0,options,"@"); print(a[1])}'`;

echo $options
echo "--------------"
echo $fields



