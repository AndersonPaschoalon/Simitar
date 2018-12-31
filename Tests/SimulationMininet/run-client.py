#!/usr/bin/python3

import subprocess
import time
import os
import sys
from config import config
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/..')
from SimulationMininet.Config import Config
from Utils.Terminal import Terminal as term
from Utils.Cd import Cd

def main():
    # capture pcap
    tcpdump_command = "tcpdump -i " + config.ether_interface_client + " -s 65535 -w " + config.capture_dir + config.pcap_name + "_" + config.ether_interface_client  + ".client.pcap"
    os.system('mkdir -p ' + config.capture_dir)
    term.print_header("  Tcpdump", color="purple")
    term.print_color("blue", "  > interface: " + config.ether_interface_client)
    term.print_color("blue", "  > pcap file: " +config.pcap_name)
    term.print_color("blue", "  > tcpdump command: " + tcpdump_command)
    term.command(tcpdump_command + " &", "green")
    # client execution
	term.print_header("  simitar-gen, mode:client", color="blue")
    cd = Cd()
    cd()
    #cd_dir = " cd " + config.simitargen_app_dir + "; "
	script_client = cd_dir + " sudo -E ./simitar-gen --tool " + config.tool_name + " --mode client --ether " + config.ether_interface_client + " --xml " + config.ctd_xml_file  + " ";
    print("> Execution mode: client")
    if(config.tool_name == "iperf" or config.tool_name == "ditg"):
        print("> Tool name: " + config.tool_name)
        if(config.toplology_type == "tree"):
            print("> Toplology type: " + config.toplology_type)
            script_client = script_client + " --dst-list-ip " + config.dst_ip_file
        elif (config.toplology_type == "simple"):
            print("> Toplology type: " + config.toplology_type)
            script_client = script_client + " --dst-ip " + config.dst_ip_addr
        else:
            print("> Invalid topology: " + config.toplology_type)
            exit()
    elif(config.tool_name == "tins"):
        print("> Tool name: " + config.tool_name)
        print("> Toplology type: " + config.toplology_type)
        # nothing to configure
    else:
        print("> Invalid tool name: " + config.tool_name)
        exit()
    print("> Script client:" + script_client)
    os.system(script_client + " &")
    # sleep until finishes
    time.sleep(config.exec_time + 1)  # <-- There's no time.wait, but time.sleep.
    # kill tcpdump
	term.print_header('killing processes')
    kill_tcpdump_command = "killall tcpdump -9"
    kill_simitargen_command = "killall simitar-gen -9"
    print("> " + kill_tcpdump_command)
    os.system(kill_tcpdump_command)
    print("> " + kill_simitargen_command)
    os.system(kill_simitargen_command)

if __name__ == "__main__":
    main()
