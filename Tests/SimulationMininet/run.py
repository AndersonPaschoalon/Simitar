import subprocess
import time
import os

# execution options
operation_mode = "client" # client, server
capture_name = "capture-name"
ether_interface = "enp3s0"
binary_command_client = "iperf -c 10.0.0.2" 
binary_command_server = "iperf -s " 
exec_time = 10

# constants
CAPTURE_DIR = './pcaps/'


def print_header(title):
    print('')
    print('###############################################################################')
    print('# ' + title)
    print('###############################################################################')


def main():
    tcpdump_command = 'tcpdump -i ' + ether_interface + '-s 65535 -w ' + CAPTURE_DIR + capture_name + '.pcap'
    os.system('mkdir -p ' + CAPTURE_DIR)

    # capture pcap
    print_header(' Tcpdump interface:' + ether_interface + ', pcap:' + capture_name)
    proc_tcpdump = subprocess.Popen(tcpdump_command, shell=True)
    # execute simitar app
	if(operation_mode == "client"):
    	print_header('Simitar-app command:' + binary_command_client)
    	os.system(binary_command_client + ' &')	
	else:
		print_header('Simitar-app command:' + binary_command_server)
		os.system(binary_command_server + ' &')
    # sleep until finishes
    time.sleep(exec_time + 1)  # <-- There's no time.wait, but time.sleep.
    # kill tcpdump
    print_header('killing Tcpdump')
    proc_tcpdump.kill()


if __name__ == "__main__":
    main()
