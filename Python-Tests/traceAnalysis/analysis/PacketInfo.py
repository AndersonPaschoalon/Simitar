import pyshark
import sys
import os.path
import logging

DEBUG_PacketInfo = False
verbose = True
# capture_method = "--live-test"
capture_method = "--live"
internetIf = 'enp3s0'
# internetIf='wlan0'


########################################################################################################################
# Network Constants
########################################################################################################################
# Network Protocols
# usual
ETHERTYPE_NONE = 0x0
ETHERTYPE_IP = 0x0800
ETHERTYPE_ARP = 0x0806
ETHERTYPE_REVARP = 0x8035
ETHERTYPE_IPV6 = 0x86dd
# exoteric
ETHERTYPE_PUP = 0x0200
ETHERTYPE_NS = 0x0600
ETHERTYPE_SPRITE = 0x0500
ETHERTYPE_TRAIL = 0x1000
ETHERTYPE_MOPDL = 0x6001
ETHERTYPE_MOPRC = 0x6002
ETHERTYPE_DN = 0x6003
ETHERTYPE_LAT = 0x6004
ETHERTYPE_SCA = 0x6007
ETHERTYPE_LANBRIDGE = 0x8038
ETHERTYPE_DECDNS = 0x803c
ETHERTYPE_DECDTS = 0x803e
ETHERTYPE_VEXP = 0x805b
ETHERTYPE_VPROD = 0x805c
ETHERTYPE_ATALK = 0x809b
ETHERTYPE_AARP = 0x80f3
ETHERTYPE_8021Q = 0x8100
ETHERTYPE_IPX = 0x8137
ETHERTYPE_MPLS = 0x8847
ETHERTYPE_MPLS_MULTI = 0x8848
ETHERTYPE_PPPOED = 0x8863
ETHERTYPE_PPPOES = 0x8864
ETHERTYPE_8021AD = 0x88a8
ETHERTYPE_LOOPBACK = 0x9000
ETHERTYPE_8021QINQ = 0x9100

# Transpot Protocols
# usual
PROTOCOL_HOPOPT = 0  # usual
PROTOCOL_ICMP = 1  # usual
PROTOCOL_IGMP = 2  # usual
PROTOCOL_GGP = 3
PROTOCOL_IP_in_IP = 4
PROTOCOL_ST = 5
PROTOCOL_TCP = 6  # usual
PROTOCOL_CBT = 7
PROTOCOL_EGP = 8
PROTOCOL_IGP = 9
PROTOCOL_BBN_RCC_MON = 10
PROTOCOL_NVP_II = 11
PROTOCOL_PUP = 12
PROTOCOL_ARGUS = 13
PROTOCOL_EMCON = 14
PROTOCOL_XNET = 15
PROTOCOL_CHAOS = 16
PROTOCOL_UDP = 17  # usual
PROTOCOL_MUX = 18
PROTOCOL_DCN_MEAS = 19
PROTOCOL_HMP = 20
PROTOCOL_PRM = 21
PROTOCOL_XNS_IDP = 22
PROTOCOL_TRUNK_1 = 23
PROTOCOL_TRUNK_2 = 24
PROTOCOL_LEAF_1 = 25
PROTOCOL_LEAF_2 = 26
PROTOCOL_RDP = 27
PROTOCOL_IRTP = 28
PROTOCOL_ISO_TP4 = 29
PROTOCOL_NETBLT = 30
PROTOCOL_MFE_NSP = 31
PROTOCOL_MERIT_INP = 32
PROTOCOL_DCCP = 33  # usual
PROTOCOL_3PC = 34
PROTOCOL_IDPR = 35
PROTOCOL_XTP = 36
PROTOCOL_DDP = 37
PROTOCOL_IDPR_CMTP = 38
PROTOCOL_TP_PLUS_PLUS = 39
PROTOCOL_IL = 40
PROTOCOL_IPv6 = 41  # usual
PROTOCOL_SDRP = 42
PROTOCOL_Ipv6_Route = 43
PROTOCOL_Ipv6_Frag = 44
PROTOCOL_IDRP = 45
PROTOCOL_RSVP = 46
PROTOCOL_GRE = 47  # usual
PROTOCOL_DSR = 48
PROTOCOL_BNA = 49
PROTOCOL_ESP = 50
PROTOCOL_AH = 51
PROTOCOL_I_NLSP = 52
PROTOCOL_SWIPE = 53
PROTOCOL_NARP = 54
PROTOCOL_MOBILE = 55
PROTOCOL_TLSP = 56
PROTOCOL_SKIP = 57
PROTOCOL_Ipv6_ICMP = 58  # usual
PROTOCOL_Ipv6_NoNxt = 59
PROTOCOL_Ipv6_Opts = 60
PROTOCOL_ANY_HOST_PROTOCOL = 61
PROTOCOL_CFTP = 62
PROTOCOL_ANY_LAN = 63
PROTOCOL_SAT_EXPAK = 64
PROTOCOL_KRYPTOLAN = 65
PROTOCOL_RVD = 66
PROTOCOL_IPPC = 67
PROTOCOL_DISTRIBUTED_FILE_SYSTEM = 68
PROTOCOL_SAT_MON = 69
PROTOCOL_VISA = 70
PROTOCOL_IPCU = 71
PROTOCOL_CPNX = 72
PROTOCOL_CPHB = 73
PROTOCOL_WSN = 74
PROTOCOL_PVP = 75
PROTOCOL_BR_SAT_MON = 76
PROTOCOL_SUN_ND = 77
PROTOCOL_WB_MON = 78
PROTOCOL_WB_EXPAK = 79
PROTOCOL_ISO_IP = 80
PROTOCOL_VMTP = 81
PROTOCOL_SECURE_VMTP = 82
PROTOCOL_VINES = 83
PROTOCOL_TTP = 84
PROTOCOL_IPTM = 84
PROTOCOL_NSFNET_IGP = 85
PROTOCOL_DGP = 86
PROTOCOL_TCF = 87
PROTOCOL_EIGRP = 88
PROTOCOL_OSPF = 89
PROTOCOL_Sprite_RPC = 90
PROTOCOL_LARP = 91
PROTOCOL_MTP = 92
PROTOCOL_AX_25 = 93
PROTOCOL_OS = 94
PROTOCOL_MICP = 95
PROTOCOL_SCC_SP = 96
PROTOCOL_ETHERIP = 97
PROTOCOL_ENCAP = 98
PROTOCOL_AnyPrivateEncryptionScheme = 99
PROTOCOL_GMTP = 100
PROTOCOL_IFMP = 101
PROTOCOL_PNNI = 102
PROTOCOL_PIM = 103
PROTOCOL_ARIS = 104
PROTOCOL_SCPS = 105
PROTOCOL_QNX = 106
PROTOCOL_A_N = 107
PROTOCOL_IPComp = 108
PROTOCOL_SNP = 109
PROTOCOL_Compaq_Peer = 110
PROTOCOL_IPX_in_IP = 111
PROTOCOL_VRRP = 112
PROTOCOL_PGM = 113
PROTOCOL_Any0hopProtocol = 114
PROTOCOL_L2TP = 115
PROTOCOL_DDX = 116
PROTOCOL_IATP = 117
PROTOCOL_STP = 118
PROTOCOL_SRP = 119
PROTOCOL_UTI = 120
PROTOCOL_SMP = 121
PROTOCOL_SM = 122
PROTOCOL_PTP = 123
PROTOCOL_IS_IS_over_Ipv4 = 124
PROTOCOL_FIRE = 125
PROTOCOL_CRTP = 126
PROTOCOL_CRUDP = 127
PROTOCOL_SSCOPMCE = 128
PROTOCOL_IPLT = 129
PROTOCOL_SPS = 130
PROTOCOL_PIPE = 131
PROTOCOL_SCTP = 132  # usual
PROTOCOL_FC = 133
PROTOCOL_RSVP_E2E_IGNORE = 134
PROTOCOL_Mobility_Header = 135
PROTOCOL_UDPLite = 136
PROTOCOL_MPLS_in_IP = 137
PROTOCOL_manet = 138
PROTOCOL_HIP = 139
PROTOCOL_Shim6 = 140
PROTOCOL_WESP = 141
PROTOCOL_ROHC = 142
PROTOCOL_RESERVED_FOR_TESTING1 = 253
PROTOCOL_RESERVED_FOR_TESTING2 = 254
PROTOCOL_RESERVED_FOR_EXTRA = 255


# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/lan_diurnalFirewallCapture.pcap'
# filebasename = os.path.basename(file_name)
# file_log_name = 'fileCapture_' + filebasename + '.log'
# logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',level=logging.INFO)


class Print:
    def printf(format, *args):
        sys.stdout.write(format % args)


class PacketInfo:
    # def __init__(self, pkt, reference_time=0):
    def __init__(self, pkt):
        self.flowID = 0
        # actual_time = float(pkt.sniff_timestamp) - float(reference_time)
        # self.time = actual_time
        self.time = float(pkt.frame_info.time_relative)
        self.time_delta = float(pkt.frame_info.time_delta)
        self.number = int(pkt.number)
        self.length = int(pkt.captured_length)
        self.prot_link = ''
        # self.mac_src = pkt.eth.src
        # self.mac_dst = pkt.eth.dst
        self.mac_src = ''
        self.mac_dst = ''
        # init members
        self.prot_network = ETHERTYPE_NONE
        self.ip_dst = ''
        self.ip_src = ''
        self.transport = 0
        self.port_src = 0
        self.port_dst = 0
        self.ttl = 0
        try:
            self.prot_network = int(pkt.eth.type, 16)
            self.prot_link = 'ether'
            try:
                # IPv4 packet
                if self.prot_network == ETHERTYPE_IP:
                    self.ip_src = pkt.ip.src
                    self.ip_dst = pkt.ip.dst
                    self.ttl = pkt.ip.ttl
                    self.transport = int(pkt.ip.proto)
                    # '''
                    try:
                        self.port_dst = pkt[pkt.transport_layer].dstport
                        self.port_src = pkt[pkt.transport_layer].srcport
                    except (AttributeError, TypeError) as detail:
                        self.port_dst = 0
                        self.port_src = 0
                    '''
                    # tranport layer
                    if self.transport == PROTOCOL_TCP:
                        self.port_dst = pkt.tcp.dstport
                        self.port_src = pkt.tcp.srcport
                    elif self.transport == PROTOCOL_UDP:
                        self.port_dst = pkt.udp.dstport
                        self.port_src = pkt.udp.srcport
                    elif self.transport == PROTOCOL_ICMP:
                        pass
                    elif self.transport == PROTOCOL_DCCP:
                        self.port_dst = pkt.dccp.dstport
                        self.port_src = pkt.dccp.srcport
                    elif self.transport == PROTOCOL_SCTP:
                        self.port_dst = pkt.sctp.dstport
                        self.port_src = pkt.sctp.srcport
                    elif self.transport == PROTOCOL_HOPOPT:
                        pass
                    elif (self.transport <= PROTOCOL_ROHC) | (
                                    PROTOCOL_RESERVED_FOR_TESTING1 <=
                                    self.transport <= PROTOCOL_RESERVED_FOR_EXTRA):
                        self.port_dst = 0
                        self.port_src = 0
                    else:  # Error
                        print(dir(pkt), pkt)
                        print(dir(pkt.ip), pkt.ip)
                        self.print_error_message(
                            "[" + str(str(self.number)) + "] " + "An strange tranport protocol number was captured : ",
                            self.transport)
                    #'''
                # IPv6 packet
                elif self.prot_network == ETHERTYPE_IPV6:
                    # print(dir( pkt.ipv6))
                    self.ip_src = pkt.ipv6.addr
                    self.ip_dst = pkt.ipv6.dst
                    self.transport = int(pkt.ipv6.nxt)
                    self.ttl = int(pkt.ipv6.hlim)
                    try:
                        self.port_dst = pkt[pkt.transport_layer].dstport
                        self.port_src = pkt[pkt.transport_layer].srcport
                    except (AttributeError, TypeError) as detail:
                        self.port_dst = 0
                        self.port_src = 0
                    '''
                    # tranport layer
                    if self.transport == PROTOCOL_TCP:
                        self.port_dst = pkt.tcp.dstport
                        self.port_src = pkt.tcp.srcport
                    elif self.transport == PROTOCOL_UDP:
                        self.port_dst = pkt.udp.dstport
                        self.port_src = pkt.udp.srcport
                    elif self.transport == PROTOCOL_Ipv6_ICMP:
                        self.port_dst = 0
                        self.port_src = 0
                    elif self.transport == PROTOCOL_DCCP:
                        self.port_dst = pkt.dccp.dstport
                        self.port_src = pkt.dccp.srcport
                    elif self.transport == PROTOCOL_SCTP:
                        self.port_dst = pkt.sctp.dstport
                        self.port_src = pkt.sctp.srcport
                    elif self.transport == PROTOCOL_HOPOPT:
                        pass
                    elif (self.transport <= PROTOCOL_ROHC) | (
                                    PROTOCOL_RESERVED_FOR_TESTING1 <= self.transport <= PROTOCOL_RESERVED_FOR_EXTRA):
                        pass
                    else:
                        print(dir(pkt), pkt)
                        print(dir(pkt.ip), pkt.ip)
                        self.print_error_message(
                            "[" + str(str(self.number)) + "] " + "An strange tranport protocol number was captured : ",
                            str(self.transport))
                    '''
                # Other protocols, like ARP and REVARP
                else:
                    pass
            except (AttributeError, TypeError)  as detail:
                logging.error("[%s] Invalid packet attribute: %s \n %s\n\n", str(self.number), detail, str(pkt))

        except (AttributeError, TypeError)  as detail:
            # Spanning tree packet
            if ('stp' in dir(pkt)):
                self.prot_link = 'stp'
            else:
                logging.error("[%s] Invalid packet attribute: %s \n %s\n\n", str(self.number), detail, str(pkt))

    def __repr__(self):
        return (
            '(numb:' + str(self.number) + ' flowID:' + str(self.flowID) + ' time:' + str(self.time) + ' delta:' + str(
                self.time_delta) + ' length:' + str(
                self.length) + ' prot_link:' + self.prot_link + ' mac_src:' + self.mac_src + ' mac_dst:' + self.mac_dst + ' prot_network:' + str(
                self.prot_network) + ' ip_src:' + self.ip_src + ' ip_dst:' + self.ip_dst + ' ttl:' + str(
                self.ttl) + ' transport:' + str(
                self.transport) + ' port_src:' + str(self.port_src) + ' port_dst:' + str(self.port_dst) + ')')

    def print_error_message(text_message, data_val):
        logging.error("%s %s", text_message, str(data_val))

    def flow_str(self):
        return (
            # self.prot_link + str(self.prot_network) + self.ip_src + self.ip_dst + str(self.transport) + str(self.port_src) + str(
            #    self.port_dst))
            str(self.prot_network) + self.ip_src + self.ip_dst + str(self.transport) + str(self.port_src) + str(
                self.port_dst))

    def setFlowId(self, fid=0):
        self.flowID = fid


if DEBUG_PacketInfo == True:
    internetIf = 'enp3s0'
    pcap_buffer = []
    capture = pyshark.LiveCapture(interface=internetIf)
    capture.sniff(timeout=0)

    # print(capture.sniff_timestamp)
    i = 0
    for pkt in capture.sniff_continuously():
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        pktInfo = PacketInfo(pkt, initial_time)
        print(pktInfo)
