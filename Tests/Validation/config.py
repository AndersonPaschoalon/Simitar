################################################################################
# simitar options
################################################################################

class config:
    # pcap directory (all pcaps must be in the same directory)
    pcaps_dir = "pcaps/"

    # pcap1 file name
    #pcapfile_1 = "skype.pcap"
    pcapfile_1 = "lan-gateway-10s.pcap"

    # pcap2 file name
    pcapfile_2 = "pangolin03_skype_simple_tins_host-h2_h1-eth0.client.pcap"
    pcapfile_2 = "coala_skype_simple_iperf_host-h2_h1-eth0.client.pcap"
    #pcapfile_2 = "wombat03_skype_simple_iperf_host-h1_h1-eth0.client.pcap"
    #pcapfile_2 = ""
    #pcapfile_2 = "wombat01_skype_simple_tins_h1-eth0.client.pcap"
    #pcapfile_2 = "wombat01_skype_simple_iperf_h1-eth0.client.pcap"
    #pcapfile_2 = "wombat01_skype_tree_iperf_h1-eth0.client.pcap"
    #pcapfile_2 = "ospf.pcap"

    # analyzis name. this name will name the directory where the plots will be saved
    analysis_name = "abacate_tins"

    # pcap1 name that will be used as legend on the plot
    pcap1_type = "lgw10s-pcap"

    # pcap2 name that will be used as legend on the plot
    pcap2_type = "simitar-tins"

    # just some information that will be recorded on the file about.log
    #comments = "Neste esperimento executei o simitar utilizando como ferramenta o iperf, em uma topologia arvore SDN. O cliente (gerador de pacotes) era o host h1, e os clientes os hosts h2-h8."
    comments = "Neste esperimento executei o simitar utilizando como ferramenta iperf, em uma topologia one-hop SDN. O cliente (gerador de pacotes) era o host h1, e o servidor é o host h2"


    ############################################################################
    # do not change
    ############################################################################
    # analysis-pkt-filter.py csv prefix
    pktfilter_prefix = "packetsinfo_"
    pcap1 = pcaps_dir + pcapfile_1
    pcap2 = pcaps_dir + pcapfile_2
