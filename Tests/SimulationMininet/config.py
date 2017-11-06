################################################################################
# simitar options
################################################################################

class config:
	############################################################################
	# execution controll
	############################################################################
	tool_name = "iperf" # tins, iperf, ditg
	toplology_type = "simple" # simple, tree
	capture_name = "coala_skype"
	#ctd_xml_file = "../data/xml/skype.sec.xml"
	#ctd_xml_file = "../data/xml/skype.ms.xml"
	ctd_xml_file = "../data/xml/lgw10s.sec.xml"
	ether_interface_client = "h1-eth0"
	ether_interface_server = "h2-eth0"
	host_name = "h2"
	dst_ip_addr = "10.0.0.2" # used for a single hop (simple) topology
	dst_ip_file = "../data/csv/ip-addrs-list1.csv" # used for a tree topology
	############################################################################
	# application controll
	############################################################################
	simitargen_app_dir = "../../SIMITAR/simitar-gen/"
	############################################################################
	# experiment configuration
	############################################################################
	exec_time = 11
	#exec_time = 10
	capture_dir = './pcaps/'
	############################################################################
	# do not change
	############################################################################
	pcap_name = capture_name + "_" + toplology_type + "_" + tool_name + '_host-' + host_name





