################################################################################
# simitar options
################################################################################
# operation_mode = "server"
tool_name = "iperf"
capture_name = "wombat01_iperf_skype"
ctd_xml_file = "../data/xml/skype.sec.xml"
#ether_interface = "enp3s0"
ether_interface_client = "h1-eth0"
ether_interface_server = "h2-eth0"
dst_ip_addr = "10.0.0.2"
#dst_ip_file = "../data/csv/ip-addrs-list1.csv"

################################################################################
# simitar coomands
################################################################################
cd_dir = "cd ../../SIMITAR/simitar-gen/; "
binary_command_client = cd_dir + " sudo -E ./simitar-gen --tool iperf --mode client --ether " + ether_interface_client + " --xml " + ctd_xml_file + " --dst-ip " + dst_ip_addr
binary_command_server = cd_dir + " sudo -E ./simitar-gen --tool iperf --mode server --ether " + ether_interface_server + " --xml " + ctd_xml_file
#binary_command_client = cd_dir + " sudo -E ./simitar-gen --tool tins --mode  "  + operation_mode + " --ether " + ether_interface +" --xml " + ctd_xml_file 
#binary_command_server = cd_dir + " sudo -E ./simitar-gen --tool tins --mode  "  + operation_mode + " --ether " + ether_interface +" --xml " + ctd_xml_file

################################################################################
# experiment configuration
################################################################################
#exec_time = 323
exec_time = 10
CAPTURE_DIR = './pcaps/'

