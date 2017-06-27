from enum import Enum
import string
import time
import sys
import os.path
import logging
import pyshark

from traffic import PacketInfo
from traffic import Trace
from traffic import Flow
from traffic import Packet
from FlowId import FlowId

##############
# Command-line opts
verbose = True
capture_method = "--live"
liveTimeout = 10 # timeout in seconds
# capture_method = "--test"
#capture_method = "--file"
# capture_method = "--live"
# capture_method = "--live-rb"
# capture_method = "--remote"
internetIf = 'enp3s0'
#file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
#file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/live_background-traffic-1.pcap'
#file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/lan_diurnalFirewallCapture.pcap'
#file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/equinix-chicago.dirA.20160121-130500.UTC.anon.pcap.gz'
file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/equinix-chicago.dirA.20160121-130500.UTC.anon.pcap'
##############
# Inner configuration

database = '' #database path and name

# main

# INFO
flow_calc = FlowId() #calculate flow id
info_progInitTime = time.time()
i = 0
if capture_method == '--live':
    file_log_name = 'liveCapture_' + internetIf + '.log'
    logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s', level=logging.INFO)
    capture = pyshark.LiveCapture(interface=internetIf)
    capture.sniff(timeout=0)

    pcapList = []
    for pkt in capture.sniff_continuously():
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        # DEBUG
        debug_pktInitTime = time.time() * 1000

        pktInfo = PacketInfo(pkt, initial_time)
        pktInfo.setFlowId(flow_calc.getFlowId(pktInfo.flow_str()))
        i += 1

        # DEBUG
        debug_pktEndTime = time.time() * 1000
        logging.debug("Max execution time of PacketInfo(): %fus", float(debug_pktEndTime) - float(debug_pktInitTime))

        pcapList.append(pktInfo)
        if (verbose == True):
            print(pktInfo)

        if (pktInfo.time > liveTimeout):
            break

    # INFO
    info_progEndTime = time.time()
    logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))

elif (capture_method == '--file'):
    filebasename = os.path.basename(file_name)
    file_log_name = 'fileCapture_' + filebasename + '.log'
    logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                        level=logging.INFO)
    pcap = pyshark.FileCapture(file_name)

    pcapList = []
    i = 0
    for pkt in pcap:
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        # DEBUG
        #debug_pktInitTime = time.time() * 1000

        pktInfo = PacketInfo(pkt, initial_time)
        i += 1

        # DEBUG
        #debug_pktEndTime = time.time() * 1000
        #logging.debug("Max execution time of PacketInfo(): %fus ", float(debug_pktEndTime) - float(debug_pktInitTime))

        #pcapList.append(pktInfo)
        if (verbose == True):
            print(pktInfo)
            #print(i)

    # INFO
    info_progEndTime = time.time()
    logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))

elif capture_method == '--live-rb':
    logging.debug("TODO: capture --live-rb")

elif capture_method == '--remote':
    logging.debug("TODO: capture --remote")

else:
    # ERROR
    logging.error("Invalid command line option: %s", capture_method)


print("Sniffer execution has finished")