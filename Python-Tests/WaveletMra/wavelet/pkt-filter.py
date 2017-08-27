#!/usr/bin/python3.5
import sys
import time
import os.path
import logging
import pyshark
from optparse import OptionParser
from PacketInfo import PacketInfo
from FlowId import FlowId

DATA_DIR = './data/'
VERBOSITY = True
APP_NAME = "pkt-filter.py"
 
def print_help():
	print("Usage: ")
	print("\t" + APP_NAME + " <experiment-name> <pcap-file> : to filter packet info and store at " + DATA_DIR)
	print("\t" + APP_NAME + " --help/-h                     : displays this help menu")

def print_error(args):
	print("Error: invalid args " + args)
	print_help()
	exit(-1)

def main(args):
	try:
		exName = args[0]
		pcap_file = args[1]
	except:
		print_error(args)
	
	if (args[0] == "--help" or args[0] == "-h"):
		print_help()
		exit(0)	

	print ("oiiiiiii")
	exit(0)
	os.system('cd ' +  os.path.dirname(os.path.abspath(__file__)))
	os.system('mkdir -p ' + DATA_DIR)	

	# load pcap and output files
	pcap = pyshark.FileCapture(pcap_file, keep_packets=False)
	datafile = open(DATA_DIR + 'packetsinfo_' + exName + '.csv', 'w')
	datafile.write('#Experiment:' + exName + ' pcap: ' + filebasename + '>\n')  
	datafile.write('#frameNumber, flowID, frameLen, InterPacketTime, frameTime\n')
	iptFile = open(DATA_DIR + 'interpackettime_' + exName + '.txt', 'w')
	iptFile.write('#Experiment:' + exName + ' pcap: ' + filebasename + '>\n')
	iptFile.write('#InterPacketTime\n')

	# config loop
	initial_time = 0
	flow_calc = FlowId()  # calculate flow id
	for pkt in pcap:
		# capture packet data
		pktInfo = PacketInfo(pkt)  # get packets info
		pktInfo.setFlowId(flow_calc.getFlowId(pktInfo.flow_str()))  # calculate packet flows
		# write data
		data_list_str = ''
		data_list_str += str(pktInfo.number) + ', '
		data_list_str += str(pktInfo.flowID) + ', '
		data_list_str += str(pktInfo.length) + ', '
		data_list_str += str(pktInfo.time_delta) + ', '
		data_list_str += str(pktInfo.time)
		datafile.write(data_list_str + '\n')
		iptFile.write(str(pktInfo.time_delta) + '\n')

		if VERBOSITY is True:
		    print(pktInfo)
		# end loop

	datafile.close()
	iptFile.close()


if __name__ == '__main__':
	main(sys.argv[1:])
	#print_error("`no args`")

