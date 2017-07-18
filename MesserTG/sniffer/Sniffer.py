#!/usr/bin/python3

import string
import time
import sys
import os.path
import logging
import pyshark

from TrafficRepr import PacketInfo
from TrafficRepr import Trace
from TrafficRepr import Flow
from TrafficRepr import Packet
from FlowId import FlowId

##############
# Command-line opts
# verbose = True
# capture_method = "--live"
# liveTimeout = 10 # timeout in seconds
# capture_method = "--test"
# capture_method = "--file"
# capture_method = "--live"
# internetIf = 'enp3s0'
# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/live_background-traffic-1.pcap'
# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/lan_diurnalFirewallCapture.pcap'
# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/equinix-chicago.dirA.20160121-130500.UTC.anon.pcap.gz'
# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/equinix-chicago.dirA.20160121-130500.UTC.anon.pcap'
##############
# Inner configuration


class Sniffer:
    def __init__(self, captureMethod='none', captureTarget='none', liveTimeout=10, traceID=0):
        """
        This constructor configure the sniffer, setting  the capture type (pcap or live), the capture target (pcap file
        name for pcap or interface name for live capture), and the live capture timeout.
        :param captureType: live or pcap
        :param captureTarget: pcap file name, or interface name
        :param liveTimeout: live capture timeout. 10s as default
        :param traceID: trace ID (optional, default 0)
        """
        self.captureMethod = captureMethod
        self.captureTarget = captureTarget
        self.liveTimeout = liveTimeout
        self.logfile_path_prefix = '../data/log/sniffer-'
        self.traceID = traceID
        self.flowList = []
        self.packetList = []

    def listFlowsProperties(self):
        """
        Returns a list of properties of all Flows
        :return: list of properties of all flows
        """
        thelist = []
        for element in self.flowList:
            thelist.append(element.list())
        return thelist

    def listPacketsProperties(self):
        """
        Returns a list of properties of all Packets
        :return:
        """
        thelist = []
        for element in self.packetList:
            thelist.append(element.list())
        return thelist

    @staticmethod
    def flows_properties_names():
        """
        Returns a string  with the properties names of flowList
        :return: first of properties of all packets
        """
        return Flow.list_repr()

    @staticmethod
    def packets_properties_names():
        """
        Returns a string  with the properties names of flowList
        :return: ist of properties of all flows
        """
        return Packet.list_repr()

    def start(self, verbose=True):
        """
        Collect data using the constructor configuration
        :param verbose: prints the output for each packet
        :return:
        """
        # set local variables
        capture_method = self.captureMethod
        internetIf = self.captureTarget
        file_name = self.captureTarget
        liveTimeout = self.liveTimeout
        # init
        flow_calc = FlowId()  # calculate flow id
        info_progInitTime = time.time()
        i = 0
        if capture_method == 'live':
            # promisc mode
            os.system('sudo ifconfig ' + self.captureTarget + ' up')
            os.system('sudo ifconfig ' + self.captureTarget + ' promisc')
            # logs
            file_log_name = self.logfile_path_prefix + 'liveCapture_' + internetIf + '.log'
            logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                                level=logging.INFO)
            # capture
            capture = pyshark.LiveCapture(interface=internetIf)
            capture.sniff(timeout=0)

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
                logging.debug("Max execution time of PacketInfo(): %fus",
                              float(debug_pktEndTime) - float(debug_pktInitTime))

                # add to flow list, jusf it has a larger flow ID
                if pktInfo.flowID > (len(self.flowList) - 1):
                    self.flowList.append(Flow(pktInfo, self.traceID))
                # add new packet to list
                self.packetList.append(Packet(pktInfo, self.traceID))

                # pcapList.append(pktInfo)
                if (verbose == True):
                    print(pktInfo)

                if (pktInfo.time > liveTimeout):
                    break
            if (verbose == True):
                print(self.flowList)
                print(self.packetList)
            info_progEndTime = time.time()
            logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))

        elif (capture_method == 'pcap'):
            filebasename = os.path.basename(file_name)
            file_log_name = self.logfile_path_prefix + 'fileCapture_' + filebasename + '.log'
            logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                                level=logging.INFO)
            pcap = pyshark.FileCapture(file_name)

            i = 0
            for pkt in pcap:
                # Evaluate initial time
                if (i == 0):
                    initial_time = pkt.sniff_timestamp

                # DEBUG
                # debug_pktInitTime = time.time() * 1000

                pktInfo = PacketInfo(pkt, initial_time)
                pktInfo.setFlowId(flow_calc.getFlowId(pktInfo.flow_str()))
                i += 1

                # add to flow list, jusf it has a larger flow ID
                if pktInfo.flowID > (len(self.flowList) - 1):
                    self.flowList.append(Flow(pktInfo, self.traceID))
                # add new packet to list
                self.packetList.append(Packet(pktInfo, self.traceID))

                # DEBUG
                # debug_pktEndTime = time.time() * 1000
                # logging.debug("Max execution time of PacketInfo(): %fus ", float(debug_pktEndTime) - float(debug_pktInitTime))

                if (verbose == True):
                    print(pktInfo)
            if (verbose == True):
                print(self.flowList)
                print(self.packetList)
            info_progEndTime = time.time()
            logging.info("Program execution time: %f s", float(info_progEndTime) - float(info_progInitTime))
        else:
            # ERROR
            file_log_name = self.logfile_path_prefix + 'error' + '.log'
            logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',
                                level=logging.INFO)
            logging.error("Invalid option: %s", capture_method)


def print_title(title):
    print("\n")
    print("###############################################################################")
    print(title)
    print("###############################################################################")


if __name__ == '__main__':
    theSniffer = Sniffer(captureMethod='live', captureTarget='enp3s0', liveTimeout=10, traceID=0)
    # pcapFile='/home/anderson/ProjetoMestrado/Pcap/tese/qualification1.pcap'
    # theSniffer = Sniffer(captureMethod='pcap', captureTarget=pcapFile, traceID=0)
    theSniffer.start(verbose=True)
    print("Sniffer execution has finished")
    packetList = theSniffer.listPacketsProperties()
    flowList = theSniffer.listFlowsProperties()

    print_title('Packet List')
    print(theSniffer.packets_properties_names())
    print(packetList)

    print_title('Flow List')
    print(theSniffer.flows_properties_names())
    print(flowList)
