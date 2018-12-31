#!/usr/bin/python3

import subprocess
import time
import os
import sys
from config import config
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/..')
from SimulationMininet.Config import Config


operation_mode = "server"

def print_header(title):
	print('')
	print('###############################################################################')
	print('# ' + title)
	print('###############################################################################')


def main():
	# capture pcap
	tcpdump_command = 'tcpdump -i ' + config.ether_interface_server  + ' -s 65535 -w ' + config.capture_dir + config.pcap_name + "_" + config.ether_interface_server  +'.server.pcap'
	os.system('mkdir -p ' + config.capture_dir)
	print_header("Tcpdump")
	print("> interface: " + config.ether_interface_server)
	print("> pcap file: " + config.pcap_name)
	print("> tcpdump command: " + tcpdump_command)
	os.system(tcpdump_command + " &")
	#proc_tcpdump = subprocess.Popen(tcpdump_command, shell=True)

	# server execution
	print_header("simitar-gen, mode:server")
	cd_dir = " cd " + config.simitargen_app_dir + "; "
	script_server = cd_dir + " sudo -E ./simitar-gen --tool " + config.tool_name + " --mode server --ether " + config.ether_interface_server + " --xml " + config.ctd_xml_file;
	print("> script server: " + script_server)
	if( config.tool_name != "iperf" and config.tool_name != "ditg" and config.tool_name != "tins"):
		print("> Invalid tool name: " + config.tool_name)
		exit()
	if(config.toplology_type != "tree" and config.toplology_type != "simple"):
		print("> Invalid topology: " + config.toplology_type)
		exit()
	print("\nPress ctrl-C to finish")
	os.system(script_server + ' &')


if __name__ == "__main__":
	main()
