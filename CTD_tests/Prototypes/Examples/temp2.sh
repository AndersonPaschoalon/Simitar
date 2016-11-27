#!/bin/bash
awk '
	{
		#ignore comment lines and blank lines
		ignore_flag = match($0, /(#.*)|^([:blank:]*$)|(^.*ignore_pcap.*$)/);
		
		if(ignore_flag){
			printf("%s \n", $0);
			#printf("-e %s ", $1);	
		}
		else{}
	}
' filters.list





