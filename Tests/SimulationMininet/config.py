################################################################################
# simitar options
################################################################################

class config:
	############################################################################
	# execution controll
	############################################################################
	tool_name = "tins" # tins, iperf, ditg
	toplology_type = "simple" # simple or tree
	capture_name = "guaxinim_lgw10s" # prefix name that will be given to the pcap. Sugestion use animal names :P 
	#ctd_xml_file = "../data/xml/skype.sec.xml"
	#ctd_xml_file = "../data/xml/skype.ms.xml"
	ctd_xml_file = "../data/xml/lgw10s.sec.xml" # Compact trace descriptor
	ether_interface_client = "h1-eth0"
	ether_interface_server = "h2-eth0"
	host_name = "h1"
	dst_ip_addr = "10.0.0.2" # used for a single hop (simple) topology
	dst_ip_file = "../data/csv/ip-addrs-list1.csv" # used for a tree topology
	############################################################################
	# application controll
	############################################################################
	simitargen_app_dir = "../../SIMITAR/simitar-gen/"
	############################################################################
	# experiment configuration
	############################################################################
	exec_time = 15 
	#exec_time = 10
	capture_dir = './pcaps/'
	############################################################################
	# do not change
	############################################################################
	pcap_name = capture_name + "_" + toplology_type + "_" + tool_name + '_host-' + host_name





