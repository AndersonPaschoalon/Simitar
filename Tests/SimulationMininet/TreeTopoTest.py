"""
Create a network where different switches are connected to
different controllers, by creating a custom Switch() subclass.
"""

import os
from mininet.net import Mininet
from mininet.node import OVSSwitch, Controller, RemoteController
from mininet.topolib import TreeTopo
from mininet.log import setLogLevel
from mininet.cli import CLI


class TreeTopoTest(object):
    """

    """

    c2 = RemoteController('OpenDayLight', ip='127.0.0.1', port=6633)
    cmap = {'s1': c2, 's2': c2, 's3': c2, 's4': c2, 's5': c2, 's6': c2, 's7': c2, 's8': c2, 's9': c2, 's10': c2,
            's11': c2, 's12': c2, 's13': c2}

    class MultiSwitch(OVSSwitch):
        "Custom Switch() subclass that connects to different controllers"

        def start(self, controllers):
            return OVSSwitch.start(self, [TreeTopoTest.cmap[self.name]])

    def __init__(self):
        setLogLevel('info')
        self.topo = TreeTopo( depth=3, fanout=2 )
        self.net = Mininet( topo=self.topo, switch=TreeTopoTest.MultiSwitch, build=False )
        self.net.addController(TreeTopoTest.c2)
        self.net.build()
        self.net.start()
        self.h1 = self.net.hosts[0]
        self.h2 = self.net.hosts[1]
        self.h3 = self.net.hosts[2]
        self.h4 = self.net.hosts[3]
        self.h5 = self.net.hosts[4]
        self.h6 = self.net.hosts[5]
        self.h7 = self.net.hosts[6]
        self.h8 = self.net.hosts[7]
        print(self.h1.cmd('ifconfig'))
        self.net.pingAll(timeout=1)

    def cli(self):
        CLI(self.net)

    def finalize(self):
        """

        :return:
        """
        try:
            self.net.stop()
            os.system('mn -c')
            return True
        except AttributeError as error:
            print("Error executiong finalize(), self.net was not propperly defined" )
            print(error)
            os.system('mn -c')
            return False

if __name__ == "__main__":
    tree_topo = TreeTopoTest()
    tree_topo.cli()
    tree_topo.finalize()

