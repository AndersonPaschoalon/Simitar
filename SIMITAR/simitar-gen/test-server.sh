#!/bin/bash

#tool_name="tins"
tool_name="iperf"
#tool_name="ditg"
#tool_name="dummy"
ether_interface="enp3s0"
ctd_xml="../data/xml/http-chunked-gzip.xml"
#sudo -E ./simitar-gen --tool tins --mode client --ether enp3s0 --xml ../data/xml/http-chunked-gzip.xml

function help_display()
{
	echo "Just run some tests of simitar"
	echo "sudo -E ./tests-client.sh"
	echo "toll_name values: dummy, iperf, tins, ditg"
}

source ../data/config/simitar-workspace-config.sh

if [[ $tool_name == "dummy" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml} 

elif [[ $tool_name == "iperf" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode  server --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml} 

elif [[ $tool_name == "tins"  ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml} 

elif [[ $tool_name == "ditg"  ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode server --ether ${ether_interface} --xml ${ctd_xml} 

elif [[ $tool_name == "--help"  ]]
then
	help_display;

elif [[ $tool_name == "-h"  ]]
then
	help_display;

else
	echo "Error: Invalid arg:" $tool_name;
	help_display;

fi

