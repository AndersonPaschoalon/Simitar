#!/usr/bin/python3

import subprocess
import time
import os
from config import *

operation_mode = "server"

def print_header(title):
	print('')
	print('###############################################################################')
	print('# ' + title)
	print('###############################################################################')


def main():
	tcpdump_command = 'tcpdump -i ' + ether_interface_server + '-s 65535 -w ' + CAPTURE_DIR + capture_name + '.server.pcap'
	os.system('mkdir -p ' + CAPTURE_DIR)

	# capture pcap
	print_header(' Tcpdump interface:' + ether_interface_server + ', pcap:' + capture_name)
	proc_tcpdump = subprocess.Popen(tcpdump_command, shell=True)
	# execute simitar app
	print_header('Simitar-app command:' + binary_command_server + ", Mode:server")
	print("Press ctrl-C to finish")
	os.system(binary_command_server + ' &')
	

if __name__ == "__main__":
	main()
