#!/usr/bin/python3
########################################################################################################################
# USAGE:
# This was made to automatize the task of execution of a traffic generator on a server interface, and capture
# its incomming and outgoing packets. To run rightly, the file Config.py must be edited properly.
# It may be executed in tow ways:
# ./runServer.py --nrun <int-value>
#     In this mode of execution, the script starts the traffic capture and runs the script of the traffic generator
#     at the server interface
# ./runServer.py --kill
#     In this mode of execution the traffic generator process and tcpdump processes instances are killed.
#     So, any traffic capture is finished. This mode of execution must be run  after the traffic generator
#     execution has ended. This will garantee that no instance is active of tcpdump and the traffic generator
#     is active after the execution of ./runServer.py --nrun <int-value>
# EXAMPLE:
# ./runServer.py --nrun 0
# sleep 5
# ./runServer.py --kill
#
########################################################################################################################

import argparse

from Config import Config as config
from Utils.Terminal import Terminal as term


class RunServer(object):
    @staticmethod
    def run_nth_test(i, topology, host_name):
        # capture pcap
        pcap_filepath = config.server_pcap_file_path_name( nrun=i, topology=topology, host=host_name)
        term.command('  mkdir -p ' + config.capture_dir + "/" + config.capture_name, "green")
        tcpdump_command = "  sudo tcpdump -i {0} -s 65535 -w {1} -G {2} -W 1 ".format(config.ether_interface_server,
                                                                                      pcap_filepath,
                                                                                      str(config.exec_time + 1))
        term.print_h2("Tcpdump", "purple")
        term.print_color(data="  > interface: " + config.ether_interface_server, color="blue")
        term.print_color(data="  > pcap file: " + pcap_filepath , color="blue")
        term.print_color(data="  > tcpdump command: " + tcpdump_command , color="blue")
        term.command(tcpdump_command + " &", color="green")
        # server execution
        term.print_h2(" tg:" + config.traffic_generator_process + ", mode:server ", "purple")
        term.print_color(data="  > script server: " + config.tg_server_script, color="blue")
        if config.toplology_type != "tree" and config.toplology_type != "simple":
            term.print_color(data="  !!!! Invalid topology: " + config.toplology_type + " !!!!", color="red")
            exit()
        term.command(config.tg_server_script, "green")

    @staticmethod
    def kill():
        term.print_h2("killing processes", color="purple")
        kill_tcpdump_command = "  killall tcpdump -9"
        kill_tg_command = "  killall " + config.traffic_generator_process + " -9"
        term.print_color("blue", "  > " + kill_tcpdump_command)
        term.command(kill_tcpdump_command, color="green")
        term.print_color("blue", "  > " + kill_tg_command)
        term.command(kill_tg_command, color="green")

    @staticmethod
    def print_tutorial():
        print(
            "USAGE: \n"
            " This was made to automatize the task of execution of a traffic generator on a server interface, and capture \n"
            " its incomming and outgoing packets. To run rightly, the file Config.py must be edited properly. \n"
            " It may be executed in tow ways: \n"
            " ./runServer.py --nrun <int-value> --topoinfo <string>\n"
            "     In this mode of execution, the script starts the traffic capture and runs the script of the traffic generator \n"
            "     at the server interface \n"
            " ./runServer.py --kill \n"
            "     In this mode of execution the traffic generator process and tcpdump processes instances are killed. \n"
            "     So, any traffic capture is finished. This mode of execution must be run  after the traffic generator \n"
            "     execution has ended. This will garantee that no instance is active of tcpdump and the traffic generator \n"
            "     is active after the execution of ./runServer.py --nrun <int-value> \n"
            " EXAMPLE: \n"
            " ./runServer.py --nrun 0 --topoinfo tree\n"
            " sleep 5 \n"
            " ./runServer.py --kill \n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--kill", help="Ends the packet capture and traffic generation", action="store_true")
    parser.add_argument("--nrun", type=str, help="Number of the run")
    parser.add_argument("--topoinfo", type=str, help="Information about the scenario/topology")
    parser.add_argument("--host", type=str, help="Host name")
    parser.add_argument("--tutorial", help="Script tutorial", action="store_true")
    args = parser.parse_args()
    if args.kill:
        RunServer.kill()
    elif args.nrun and args.topoinfo and args.host:
        RunServer.run_nth_test(int(args.nrun), str(args.topoinfo), str(args.host))
    elif args.tutorial:
        RunServer.print_tutorial()
    else:
        term.print_color(data="!!!! Error: no valid options for this script or missing argument !!!!", color="red")
