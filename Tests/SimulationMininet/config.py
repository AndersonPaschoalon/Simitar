################################################################################
# simitar options
################################################################################

class config:
	############################################################################
	# execution controll
	############################################################################
	tool_name = "tins" # tins, iperf, ditg
	toplology_type = "simple" # simple, tree
	capture_name = "wombat01_skype"
	ctd_xml_file = "../data/xml/skype.sec.xml"
	ether_interface_client = "h1-eth0"
	ether_interface_server = "h2-eth0"
	dst_ip_addr = "10.0.0.2"
	dst_ip_file = "../data/csv/ip-addrs-list1.csv"
	############################################################################
	# application controll
	############################################################################
	simitargen_app_dir = "../../SIMITAR/simitar-gen/"
	############################################################################
	# experiment configuration
	############################################################################
	exec_time = 323
	#exec_time = 10
	capture_dir = './pcaps/'
	############################################################################
	# do not change
	############################################################################
	pcap_name = capture_name + "_" + toplology_type + "_" + tool_name





