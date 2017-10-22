#!/bin/bash

#tool_name="tins"
tool_name="iperf1"
#tool_name="iperf2"
#tool_name="ditg1"
#tool_name="ditg2"
#tool_name="dummy"
#ether_interface="enp3s0"
ether_interface="h1-eth0"
ctd_xml="../data/xml/http-chunked-gzip.xml"
dst_ip="10.0.0.5"
csv_file="../data/csv/ip-addrs-list1.csv"
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
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} 

elif [[ $tool_name == "iperf1" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-ip ${dst_ip}"
	sudo -E ./simitar-gen --tool iperf --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-ip ${dst_ip}

elif [[ $tool_name == "iperf2" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-list-ip ${csv_file}"
	sudo -E ./simitar-gen --tool iperf --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-list-ip ${csv_file}

elif [[ $tool_name == "ditg1" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-ip ${dst_ip}"
	sudo -E ./simitar-gen --tool ditg --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-ip ${dst_ip}

elif [[ $tool_name == "ditg2" ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-list-ip ${csv_file}"
	sudo -E ./simitar-gen --tool ditg --mode client --ether ${ether_interface} --xml ${ctd_xml} --dst-list-ip ${csv_file}

elif [[ $tool_name == "tins"  ]]
then
	echo "###########################################################################################"
	echo "./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml}"
	sudo -E ./simitar-gen --tool ${tool_name} --mode client --ether ${ether_interface} --xml ${ctd_xml} 

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

