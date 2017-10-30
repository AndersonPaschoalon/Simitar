################################################################################
# simitar options
################################################################################

class config:
    pcaps_dir = "pcaps/"
    pcapfile_1 = "skype.pcap"
    #pcapfile_2 = "wombat01_skype_simple_tins_h1-eth0.client.pcap"
    pcapfile_2 = "wombat01_skype_simple_iperf_h1-eth0.client.pcap"
    #pcapfile_2 = "ospf.pcap"
    analysis_name = "uva_iperf"
    pcap1_type = "skype-pcap"
    pcap2_type = "simitar-iperf"
    ############################################################################
    # do not change
    ############################################################################
    # analysis-pkt-filter.py csv prefix
    pktfilter_prefix = "packetsinfo_"
    pcap1 = pcaps_dir + pcapfile_1
    pcap2 = pcaps_dir + pcapfile_2
