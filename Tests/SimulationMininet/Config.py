################################################################################
# simitar options
################################################################################

class Config:
    ############################################################################
    # General Settings
    ############################################################################
    # prefix name that will be given to the pcap, and as pcap directory
    capture_name = "guaxinim_lgw10s"
    # type of topology used in the mininet simulation
    toplology_type = "simple"  # simple or tree
    # ethernet interface where the client will run on mininet
    ether_interface_client = "h1-eth0"
    # ethernet interface where the server will run on mininet
    ether_interface_server = "h2-eth0"
    # Host Server name
    host_server = "h2"
    # Host Client name
    host_client = "h1"
    ############################################################################
    # Application configuration
    ############################################################################
    # used in the name of the pcap generated, and to kill the process at the end of the execution
    traffic_generator_process = "simitar-gen"
    # script/command used on the execution of the server-side of the traffic generator
    tg_server_script = \
        "cd ../../SIMITAR/; " \
        "source data/config/simitar-workspace-config.sh; " \
        "sudo -E ./bin/simitar-gen --tool {0} --mode server --ether {1} --xml {2} ".format(
            "iperf", ether_interface_server, "./data/xml/skype.sec.xml")
    tg_client_script = \
        "cd ../../SIMITAR/; " \
        "source data/config/simitar-workspace-config.sh; " \
        "sudo -E ./bin/simitar-gen --tool {0} --mode client --ether {1} --xml {2} --dst-ip {3}".format(
            "iperf", ether_interface_client, "./data/xml/skype.sec.xml", "10.0.0.2")
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
    # application controll
    ############################################################################
    open_day_light_path = "/home/anderson/Install/distribution-karaf-0.4.0-Beryllium"
    ############################################################################
    # experiment configuration
    ############################################################################
    exec_time = 15
    capture_dir = "./pcaps/"
    n_runs = 3
    ############################################################################
    # do not change
    ############################################################################
    pcap_name_server = capture_name + "_" + toplology_type + "_" \
                  + traffic_generator_process + '_host-' + host_server
    pcap_name_client = capture_name + "_" + toplology_type + "_" \
                  + traffic_generator_process + '_host-' + host_client



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

