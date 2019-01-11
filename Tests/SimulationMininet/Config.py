################################################################################
# simitar options
################################################################################

class Config:
    ############################################################################
    # General Settings
    ############################################################################
    # prefix name that will be given to the pcap, and as pcap directory
    capture_name = "Alce"
    # type of topology used in the mininet simulation
    toplology_type = "simple"  # simple or tree
    # ethernet interface where the client will run on mininet
    #ether_interface_client = "h1-eth0"
    ether_interface_client = "lo"
    # ethernet interface where the server will run on mininet
    #ether_interface_server = "h2-eth0"
    ether_interface_server = "lo"
    # Host Server name
    host_server = "h2"
    # Host Client name
    host_client = "h1"
    ############################################################################
    # Application configuration:
    ############################################################################
    # Name of the process of the Traffic generator. It is used on the name of the pcap generated,
    # and to kill the process at the end of the execution
    traffic_generator_process = "simitar-gen"
    # script/command used on the execution of the server-side of the traffic generator. This defines how to
    # startup the packet generator at the server side.
    #tg_server_script = \
    #    "cd ../../SIMITAR/; " \
    #    "source data/config/simitar-workspace-config.sh; " \
    #    "sudo -E ./bin/simitar-gen --tool {0} --mode server --ether {1} --xml {2} & ".format(
    #        "iperf", ether_interface_server, "./data/xml/skype.sec.xml")
    tg_server_script = \
        "echo '*** DUMMY SERVER SCRIPT ***'"
    # script/command used on the execution of the client-side of the traffic generator. This defines how to
    # startup the packet generator at the client side.
    #tg_client_script = \
    #    "cd ../../SIMITAR/; " \
    #    "source data/config/simitar-workspace-config.sh; " \
    #    "sudo -E ./bin/simitar-gen --tool {0} --mode client --ether {1} --xml {2} --dst-ip {3} & ".format(
    #        "iperf", ether_interface_client, "./data/xml/skype.sec.xml", "10.0.0.2")
    tg_client_script = \
        "echo '*** DUMMY CLIENT SCRIPT ***'"
    # tg_client_script = \
    #    "cd ../../SIMITAR/; " \
    #    "source data/config/simitar-workspace-config.sh; " \
    #    "sudo -E ./bin/simitar-gen --tool {0} --mode client --ether {1} --xml {2} --dst-list-ip {3}".format(
    #        "iperf", ether_interface_client, "./data/xml/skype.sec.xml", "./data/csv/ip-addrs-list1.csv")
    #tg_client_script = \
    #    "cd ../../SIMITAR/; " \
    #    "source data/config/simitar-workspace-config.sh; " \
    #    "sudo -E ./bin/simitar-gen --tool {0} --mode client --ether {1} --xml {2} ".format(
    #        "tins", ether_interface_client, "./data/xml/skype.sec.xml")
    ############################################################################
    # experiment configuration
    ############################################################################
    # controller calc routes time
    controller_time = 5
    # execution time of the test
    exec_time = 15
    # directory where the pcap files generated will be stored
    capture_dir = "./pcaps/"
    # number of times the experiment will be repeated
    n_runs = 3
    ############################################################################
    # do not change
    ############################################################################
    @staticmethod
    def server_pcap_file_path_name(nrun, topology="simple", host=""):
        return Config.capture_dir + "/" + Config.capture_name + "/" + topology + \
            "_" + host + "_" + Config.traffic_generator_process + \
            "." + str(nrun) + "." + Config.ether_interface_server + ".server" + ".pcap"

    @staticmethod
    def client_pcap_file_path_name(nrun, topology="simple", host=""):
        return Config.capture_dir + "/" + Config.capture_name + "/" + topology + \
            "_" + host + "_" + Config.traffic_generator_process + \
            "." + str(nrun) + "." + Config.ether_interface_client + ".client" + ".pcap"



"""
class Config:
    ############################################################################
    # execution control
    ############################################################################
    # prefix name that will be given to the pcap. Sugestion use animal names :P
    capture_name = "guaxinim_lgw10s"
    tool_name = "tins" # tins, iperf, ditg
    toplology_type = "simple" # simple or tree

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
    open_day_light_path = "/home/anderson/Install/distribution-karaf-0.4.0-Beryllium"
    ############################################################################
    # experiment configuration
    ############################################################################
    exec_time = 15
    capture_dir = './pcaps/'
    n_runs = 3
    ############################################################################
    # do not change
    ############################################################################
    pcap_name = capture_name + "_" + toplology_type + "_" + tool_name + '_host-' + host_name

"""

