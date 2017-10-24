################################################################################
# simitar options
################################################################################

class config:
	############################################################################
	# execution controll
	############################################################################
	tool_name = "iperf" # tins, iperf, ditg
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
	pcap_name = capture_name + "_" + toplology_type + "_" + tool_name

################################################################################
# simitar coomands
################################################################################
#cd_dir = " cd " + simitargen_app_dir = "; "
#binary_command_client = cd_dir + " sudo -E ./simitar-gen --tool " + tool_name + " --mode client --ether " + ether_interface_client + " --xml " + ctd_xml_file + " --dst-ip " + dst_ip_addr
#binary_command_server = cd_dir + " sudo -E ./simitar-gen --tool " + tool_name + " --mode server --ether " + ether_interface_server + " --xml " + ctd_xml_file
#binary_command_client = cd_dir + " sudo -E ./simitar-gen --tool tins --mode  "  + operation_mode + " --ether " + ether_interface +" --xml " + ctd_xml_file 
#binary_command_server = cd_dir + " sudo -E ./simitar-gen --tool tins --mode  "  + operation_mode + " --ether " + ether_interface +" --xml " + ctd_xml_file



