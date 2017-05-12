import time
import pyshark
import string
import sys
import logging
from PacketInfo import PacketInfo

##############
# Command-line opts
verbose = False
# capture_method = "--test"
capture_method = "--file"
# capture_method = "--live"
# capture_method = "--live-rb"
# capture_method = "--remote"
internetIf = 'enp3s0'
file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
##############
# Inner configuration
logging.basicConfig(format='[%(levelname)s] (%(threadName)-10s) %(message)s', level=logging.INFO)
database = '' #database path and name
# TODO Ctrl^C handling http://effbot.org/zone/stupid-exceptions-keyboardinterrupt.htm
# main


# INFO
info_progInitTime = time.time()

if capture_method == '--live':
    capture = pyshark.LiveCapture(interface=internetIf)
    capture.sniff(timeout=0)

    pcapList = []
    i = 0
    for pkt in capture.sniff_continuously():
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        # DEBUG
        debug_pktInitTime = time.time() * 1000

        pktInfo = PacketInfo(pkt, initial_time)
        i += 1

        # DEBUG
        debug_pktEndTime = time.time() * 1000
        logging.debug("Max execution time of PacketInfo(): %fus", float(debug_pktEndTime) - float(debug_pktInitTime))

        pcapList.append(pktInfo)
        if (verbose == True):
            print(pktInfo)


elif (capture_method == '--file'):
    pcap = pyshark.FileCapture(file_name)

    pcapList = []
    i = 0
    for pkt in pcap:
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        # DEBUG
        debug_pktInitTime = time.time() * 1000

        pktInfo = PacketInfo(pkt, initial_time)
        i += 1

        # DEBUG
        debug_pktEndTime = time.time() * 1000
        logging.debug("Max execution time of PacketInfo(): %fus ", float(debug_pktEndTime) - float(debug_pktInitTime))

        pcapList.append(pktInfo)
        if (verbose == True):
            print(pktInfo)

elif capture_method == '--live-rb':
    logging.debug("TODO: capture --live-rb")

elif capture_method == '--remote':
    logging.debug("TODO: capture --remote")

else:
    # ERROR
    logging.error("Invalid command line option: %s", capture_method)

# INFO
info_progEndTime = time.time()
logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))
