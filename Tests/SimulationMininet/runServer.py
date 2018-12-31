#!/usr/bin/python3
import os
import argparse
from Config import Config as config
from Utils.Terminal import Terminal as term


class runServer(object):
    @staticmethod
    def run_nth_test(i):
        # capture pcap
        tcpdump_command = "  sudo tcpdump -i {0} -s 65535 -w {1} ".format(config.ether_interface_server,
                                                                          config.capture_dir + config.pcap_name + "_" +
                                                                          config.ether_interface_server + '.server' +
                                                                          str(i) + '.pcap')
        term.command('  mkdir -p ' + config.capture_dir, "green")
        term.print_header("Tcpdump", "purple")
        term.print_color("  > interface: " + config.ether_interface_server)
        term.print_color("  > pcap file: " + config.pcap_name)
        term.print_color("  > tcpdump command: " + tcpdump_command)
        term.command(tcpdump_command + " &", color="green")
        # server execution
        term.print_header(" simitar-gen, mode:server", "purple")
        cd_dir = "  cd " + config.simitargen_app_dir + "; "
        script_server = cd_dir + "  sudo -E ./simitar-gen --tool " + config.tool_name + " --mode server --ether " + \
                        config.ether_interface_server + " --xml " + config.ctd_xml_file;
        term.print_color("  > script server: " + script_server, "blue")
        if config.tool_name != "iperf" and config.tool_name != "ditg" and config.tool_name != "tins":
            term.print_color("    !!!! Invalid tool name: " + config.tool_name + " !!!!", color="red")
            exit()
        if config.toplology_type != "tree" and config.toplology_type != "simple":
            term.print_color("  !!!! Invalid topology: " + config.toplology_type + " !!!!", color="red")
            exit()
        term.command(script_server + ' &', "green")

    @staticmethod
    def kill():
        term.print_header("killing processes", color="purple")
        kill_tcpdump_command = "  killall tcpdump -9"
        kill_simitargen_command = "  killall simitar-gen -9"
        term.print_color("blue", "  > " + kill_tcpdump_command)
        term.command(kill_tcpdump_command, color="green")
        term.print_color("blue", "  > " + kill_simitargen_command)
        term.command(kill_simitargen_command, color="green")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--kill", help="Ends the packet capture and traffic generation", action="store_true")
    parser.add_argument("--nrun", type=int, help="Number of the run")
    args = parser.parse_args()
    if args.kill:
        runServer.kill()
    if args.nrun:
        runServer.run_nth_test(args.nrun)

