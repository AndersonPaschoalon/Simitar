#!/usr/bin/python3.5
import time
import os.path
import logging
import pyshark
from optparse import OptionParser
from PacketInfo import PacketInfo
from FlowId import FlowId

# Constants
PLOT_DIR = '../../plots/'
PCAP_DIR = '../../pcaps/'
DATA_DIR = '../data/'

parser = OptionParser()
parser.add_option("-s", "--simulation", dest="simulation",
                  help="simulation name, the name you give for this simulation, stored at ./data/ with the prefix name packetsinfo_",
                  metavar="STRING")
parser.add_option("-p", "--pcap", dest="pcapfile",
                  help="pcap file name, without directory, stored at ../../pcaps/", metavar="FILE")
parser.add_option("-v", "--verbose",
                  action="store_true", dest="verbose", default=False,
                  help="print status messages to stdout")
parser.add_option("-i", "--inter-packet-time",
                  action="store_true", dest="interPacketTime", default=False,
                  help="store inter packet times in a separate file, with the prefix name interpackettime_")
parser.add_option("-b", "--bandwidth",
                  action="store_true", dest="interPacketTime", default=False,
                  help=" interpackettime_")
(options, args) = parser.parse_args()

file_name = PCAP_DIR + options.pcapfile
exName = options.simulation
verbose = options.verbose
interPacketTime = options.interPacketTime

# log configuration
info_progInitTime = time.time()
filebasename = os.path.basename(file_name)
file_log_name = DATA_DIR + 'fileCapture_' + filebasename + '.log'
logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                    level=logging.INFO)

# pcap and output file
pcap = pyshark.FileCapture(file_name, keep_packets=False)
datafile = open(DATA_DIR + 'packetsinfo_' + exName + '.txt', 'w')
datafile.write('# ' + exName + ' <pcap: ' + filebasename + '>\n')  # write title
datafile.write('# frame__number flowID frame__len frame__time_delta frame__time_relative\n')
if interPacketTime is True:
    iptFile = open(DATA_DIR + 'interpackettime_' + exName + '.txt', 'w')

# config loop
last_packet_time = 0
initial_time = 0
flow_calc = FlowId()  # calculate flow id
i = 0
for pkt in pcap:
    # Evaluate initial time
    #if i is 0:
    #    initial_time = pkt.sniff_timestamp

    # capture packet data
    pktInfo = PacketInfo(pkt)  # get packets info
    pktInfo.setFlowId(flow_calc.getFlowId(pktInfo.flow_str()))  # calculate packet flows

    # inter packet time
    #time_delta = pktInfo.time - last_packet_time
    #last_packet_time = pktInfo.time

    # write data
    data_list_str = ''
    #data_list_str += str(i) + ' '
    data_list_str += str(pktInfo.number) + ' '
    data_list_str += str(pktInfo.flowID) + ' '
    data_list_str += str(pktInfo.length) + ' '
    #data_list_str += str(time_delta) + ' '
    data_list_str += str(pktInfo.time_delta) + ' '
    data_list_str += str(pktInfo.time)
    datafile.write(data_list_str + '\n')
    if interPacketTime is True:
        #iptFile.write(str(time_delta) + '\n')
        iptFile.write(str(pktInfo.time_delta) + '\n')


    #print(pktInfo)
    # pcapList.append(pktInfo)
    if verbose is True:
        #print(data_list_str)
        # print(i)
        print(pktInfo)

    # end loop
    i += 1

datafile.close()
iptFile.close()

# INFO
info_progEndTime = time.time()
logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))
