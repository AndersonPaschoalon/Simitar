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
APP_NAME = "analysis-pkt-filter.py"
 
def print_help():
	print("Usage: ")
	print("\t" + APP_NAME + " <experiment-name> <pcap-file> : to filter packet info and store at " + DATA_DIR)
	print("\t" + APP_NAME + " --help/-h                     : displays this help menu")

def print_error(args):
	print("Error: invalid args " + args)
	print_help()
	exit(-1)

def main(args):
	exName = args[0]
	pcap_file = args[1]
	
	#print('@ main() ex:' + exName + ' pcap:' + pcap_file)
	#exit(0)	

	os.system('cd ' +  os.path.dirname(os.path.abspath(__file__)))
	os.system('mkdir -p ' + DATA_DIR)	

	# load pcap and output files
	pcap = pyshark.FileCapture(pcap_file, keep_packets=False)
	datafile = open(DATA_DIR + 'packetsinfo_' + exName + '.csv', 'w')
	datafile.write('#Experiment:' + exName + ' pcap: ' + pcap_file + '>\n')  
	datafile.write('#frameNumber, flowID, frameLen, InterPacketTime, frameTime\n')
	iptFile = open(DATA_DIR + 'interpackettime_' + exName + '.txt', 'w')
	iptFile.write('#Experiment:' + exName + ' pcap: ' + pcap_file + '>\n')
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
	if( len(sys.argv) >= 3 ):
		main(sys.argv[1:])
	elif( len(sys.argv) == 2):
		if( sys.argv[1] == '--help' or sys.argv[1] == '-h'):
			print_help()
			exit(0)
		else:
			print_error(sys.argv[1])
	else:
		print_error('`no args`')




