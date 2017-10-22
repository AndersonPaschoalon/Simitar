#!/usr/bin/python3

import subprocess
import time
import os
from config import *

def print_header(title):
	print('')
	print('###############################################################################')
	print('# ' + title)
	print('###############################################################################')


def main():
	tcpdump_command = 'tcpdump -i ' + ether_interface_client + '-s 65535 -w ' + CAPTURE_DIR + capture_name + '.client.pcap'
	os.system('mkdir -p ' + CAPTURE_DIR)

	# capture pcap
	print_header(' Tcpdump interface:' + ether_interface_client + ', pcap:' + capture_name)
	#proc_tcpdump = subprocess.Popen(tcpdump_command, shell=True)
	os.system(tcpdump_command + " &")

	# client execution
	print_header('Simitar-app command:' + binary_command_client + ", Mode:server")
	os.system(binary_command_client + " &")	

	# sleep until finishes
	time.sleep(exec_time + 1)  # <-- There's no time.wait, but time.sleep.

	# kill tcpdump
	print_header('killing Tcpdump')
	#proc_tcpdump.kill()
	os.system("killall tcpdump -9")


if __name__ == "__main__":
    main()
