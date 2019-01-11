#!/usr/bin/python3
########################################################################################################################
# USAGE:
# This was made to automatize the task of execution of a traffic generator on a server interface, and capture
# its incomming and outgoing packets. To run rightly, the file Config.py must be edited properly.
# It has only one mode of execution, wich is executed by the command:
# ./runClient.py --nrun <int-value>
# In this way, it start capturing packets from the client interface, and starts the executon of the packet
# generator tool. All its fithg configuration depends on the propper setting of the Config.py file.
########################################################################################################################

import argparse
import time

from Config import Config as config
from Utils.Terminal import Terminal as term


class RunClient(object):
    @staticmethod
    def run_nth_test(i, topology, host_name):
        # capture pcap
        pcap_filepath = config.client_pcap_file_path_name(nrun=i, topology=topology, host=host_name)
        term.command('  mkdir -p ' + config.capture_dir + "/" + config.capture_name, "green")
        tcpdump_command = "  sudo tcpdump -i {0} -s 65535 -w {1} -G {2} -W 1 ".format(config.ether_interface_client,
                                                                                      pcap_filepath,
                                                                                      str(config.exec_time))
        term.command('  mkdir -p ' + config.capture_dir + "/" + config.capture_name + "/", color='green')
        term.print_h3(title=" tcpdump", color="purple")
        term.print_color(color="blue", data="  > interface: " + config.ether_interface_client)
        term.print_color(color="blue", data="  > pcap file: " + pcap_filepath)
        term.print_color(color="blue", data="  > tcpdump command: " + tcpdump_command)
        term.command(cmd=tcpdump_command + " &", color="green")
        # client execution
        term.print_h3(color="purple", title=" " + config.traffic_generator_process + ", mode:client")
        term.print_color(color="blue", data="  > Execution mode: client")
        if config.toplology_type != "tree" and config.toplology_type != "simple":
            term.print_color(data="  !!!! Invalid topology: " + config.toplology_type + " !!!!", color="red")
            exit()
        term.print_color(color="blue", data="  > Toplology type: " + config.toplology_type)
        term.print_color(color="blue", data="  > Script client:" +  config.tg_client_script)
        term.command( config.tg_client_script, "green")
        # sleep until finishes
        time.sleep(config.exec_time + 1)  # <-- There's no time.wait, but time.sleep.
        # kill tcpdump/simitar-gen
        term.print_h3("killing processes", color="purple")
        kill_tcpdump_command = "  killall tcpdump -9"
        kill_simitargen_command = "  killall " + config.traffic_generator_process + " -9"
        term.print_color(color="blue", data="  > " + kill_tcpdump_command)
        term.command(kill_tcpdump_command, color="green")
        term.print_color("blue", "  > " + kill_simitargen_command)
        term.command(kill_simitargen_command, color="green")

    @staticmethod
    def print_tutorial():
        print (
            " This was made to automatize the task of execution of a traffic generator on a server interface, and capture"
            " its incomming and outgoing packets. To run rightly, the file Config.py must be edited properly."
            " It has only one mode of execution, wich is executed by the command:"
            " ./runClient.py --nrun <int-value>"
            " In this way, it start capturing packets from the client interface, and starts the executon of the packet"
            " generator tool. All its fithg configuration depends on the propper setting of the Config.py file.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--nrun", type=str, help="Number of the run")
    parser.add_argument("--topoinfo", type=str, help="Information about the scenario/topology")
    parser.add_argument("--host", type=str, help="Host name")
    parser.add_argument("--tutorial", help="Script tutorial", action="store_true")
    args = parser.parse_args()
    if args.nrun and args.topoinfo and args.host:
        RunClient.run_nth_test(int(args.nrun), str(args.topoinfo), str(args.host))
    elif args.tutorial:
        RunClient.print_tutorial()
    else:
        term.print_color(data="!!!! Error: no valid options for this script or missing argument !!!!", color="red")
        RunClient.print_tutorial()





"""

class runClient(object):
    @staticmethod
    def run_nth_test(i):
        # capture pcap
        tcpdump_command = "  sudo tcpdump -i {0} -s 65535 -w {1} -G {2} -W 1 ".format(config.ether_interface_client,
                                                                          config.capture_dir + config.pcap_name + \
                                                                          "_" + config.ether_interface_client + \
                                                                          ".client"+str(i)+".pcap",
                                                                          str(config.exec_time))
        term.command('  mkdir -p ' + config.capture_dir + "/" + config.capture_name + "/", color='green')
        term.print_h1(" tcpdump", "purple")
        term.print_color("blue", "  > interface: " + config.ether_interface_client)
        term.print_color("blue", "  > pcap file: " + config.pcap_name)
        term.print_color("blue", "  > tcpdump command: " + tcpdump_command)
        term.command(tcpdump_command + " &", "green")
        # client execution
        term.print_h1("purple",  " " + config.traffic_generator_process + ", mode:client")
        script_client = "cd {0}; sudo -E ./simitar-gen --tool {1} --mode client --ether {2} --xml {3} ;".format(
            config.simitargen_app_dir, config.tool_name, config.ether_interface_client, config.ctd_xml_file)
        term.print_color("blue", "  > Execution mode: client")
        if (config.tool_name == "iperf" or config.tool_name == "ditg"):
            print("  > Tool name: " + config.tool_name)
            if (config.toplology_type == "tree"):
                script_client += " --dst-list-ip " + config.dst_ip_file
            elif (config.toplology_type == "simple"):
                script_client += " --dst-ip " + config.dst_ip_addr
            else:
                term.print_color("red", "  > Invalid topology: " + config.toplology_type)
                exit()
        elif config.tool_name == "tins":
            term.print_color("blue", "  > Tool name: " + config.tool_name)
        else:
            term.print_color("red", "  > Invalid tool name: " + config.tool_name)
            exit()
        term.print_color("blue", "  > Toplology type: " + config.toplology_type)
        term.print_color("blue", "  > Script client:" + script_client)
        term.command(script_client + " &", "green")
        # sleep until finishes
        time.sleep(config.exec_time + 1)  # <-- There's no time.wait, but time.sleep.
        # kill tcpdump/simitar-gen
        term.print_h1("killing processes", color="purple")
        kill_tcpdump_command = "  killall tcpdump -9"
        kill_simitargen_command = "  killall simitar-gen -9"
        term.print_color("blue", "  > " + kill_tcpdump_command)
        term.command(kill_tcpdump_command, color="green")
        term.print_color("blue", "  > " + kill_simitargen_command)
        term.command(kill_simitargen_command, color="green")
  title="Running test #" + str(i), color="purple")
        runClient.run_nth_test(i)

"""