#!/usr/bin/python3
import time
from Config import Config as config
from Utils.Terminal import Terminal as term


class runClient(object):
    @staticmethod
    def run_nth_test(i):
        # capture pcap
        tcpdump_command = "  sudo tcpdump -i {0} -s 65535 -w {1} ".format(config.ether_interface_client,
                                                                          config.capture_dir + config.pcap_name + \
                                                                          "_" + config.ether_interface_client + \
                                                                          ".client"+str(i)+".pcap")
        term.command('  mkdir -p ' + config.capture_dir, color='green')
        term.print_header("  Tcpdump", "purple")
        term.print_color("blue", "  > interface: " + config.ether_interface_client)
        term.print_color("blue", "  > pcap file: " + config.pcap_name)
        term.print_color("blue", "  > tcpdump command: " + tcpdump_command)
        term.command(tcpdump_command + " &", "green")
        # client execution
        term.print_header("purple", "  simitar-gen, mode:client")
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
        term.print_header("killing processes", color="purple")
        kill_tcpdump_command = "  killall tcpdump -9"
        kill_simitargen_command = "  killall simitar-gen -9"
        term.print_color("blue", "  > " + kill_tcpdump_command)
        term.command(kill_tcpdump_command, color="green")
        term.print_color("blue", "  > " + kill_simitargen_command)
        term.command(kill_simitargen_command, color="green")

if __name__ == "__main__":
    for i in range(0, config.n_runs):
        term.print_header(title="Running test #" + str(i), color="purple")
        runClient.run_nth_test(i)
