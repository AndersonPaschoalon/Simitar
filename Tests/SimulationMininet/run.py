#!/usr/bin/python2.7
import time
from Config import Config as config
from Utils.Cd import Cd
from Utils.Terminal import Terminal as term

def opendaylight_alert():
    term.print_h1("This simulation requires OpenDayLight Running", color="purple")
    term.print_color(color="yellow", data="Go to OpenDayLight instalation directory, and run:")
    term.print_color(color="yellow", data="    ./bin/karaf")
    term.print_color(color="yellow", data="Install the follow featues on OpenDayLight, using these commands:")
    term.print_color(color="yellow", data="    feature:install odl-restconf odl-l2switch-switch odl-mdsal-apidocs odl-dlux-core")
    term.print_color(color="yellow", data="    feature:install odl-dlux-all odl-openflowplugin-flow-services-ui")
    term.print_color(color="yellow", data="    feature:install  odl-dlux-core odl-dlux-node odl-dlux-yangui odl-dlux-yangvisualizer")
    term.print_color(color="yellow", data="You also may open the OpenDayLight Web interface with the URL:")
    term.print_color(color="yellow", data="    http://localhost:8181/index.html")
    term.user_confirmation(msg="OpenDayLight is running?")

def clean():
    term.print_color(color="yellow", data="finalizing Mininet...")
    term.command(color="yellow", cmd="mn -c")


term.requires_sudo()
opendaylight_alert()
if __name__ == "__main__":
    from SimpleTopoTest import SimpleTopoTest
    from TreeTopoTest import TreeTopoTest

    server_cmd_template = "./runServer.py --nrun {0} --topoinfo {1} --host {2} & "
    client_cmd_template = "./runClient.py --nrun {0} --topoinfo {1} --host {2} & "
    server_kill = "./runServer.py --kill"

    # run simple topo test
    simple_topo = SimpleTopoTest()
    term.wait(config.controller_time)
    simple_topo.net.pingAll(timeout=2)
    topology = "simple"
    host_server = "h8"
    host_client = "h1"
    term.print_h1(" SimpleTopoTest tests", "purple")
    for i in range(0, config.n_runs):
        term.print_h1(color="yellow", title="@run n:" + str(i) + ", topology:" + topology)

        # run server
        server_cmd = server_cmd_template.format(str(i), topology, host_server)
        term.print_color(color="yellow", data=server_cmd)
        print(simple_topo.h2.cmd(server_cmd))

        # run client
        client_cmd = client_cmd_template.format(str(i), topology, host_client)
        term.print_color(color="yellow", data=client_cmd)
        print(simple_topo.h1.cmd(client_cmd))

        # wait finish and kill
        term.wait(config.exec_time + 5)
        term.print_color(color="yellow", data=server_kill)
        print(simple_topo.h2.cmd(server_kill))
    simple_topo.finalize()

    # run tree topo test
    tree_topo = TreeTopoTest()
    term.wait(config.controller_time)
    tree_topo.net.pingAll(timeout=2)
    topology = "tree"
    host_server = "h8"
    host_client = "h1"
    term.print_h1(" TreeTopoTest tests", "purple")
    for i in range(0, config.n_runs):
        term.print_h1(color="yellow", title="@run n:" + str(i) + ", topology:" + topology)

        # run server
        server_cmd = server_cmd_template.format(str(i), topology, host_server)
        term.print_color(color="yellow", data=server_cmd)
        print(tree_topo.h8.cmd(server_cmd))

        # run client
        client_cmd = client_cmd_template.format(str(i), topology, host_client)
        term.print_color(color="yellow", data=client_cmd)
        print(tree_topo.h1.cmd(client_cmd))

        # wait finish and kill
        term.wait(config.exec_time + 5)
        term.print_color(color="yellow", data=server_kill)
        print(tree_topo.h8.cmd(server_kill))
    tree_topo.finalize()




