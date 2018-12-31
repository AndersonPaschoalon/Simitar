#!/usr/bin/python

"""
Create a network where different switches are connected to
different controllers, by creating a custom Switch() subclass.
"""

import os
from mininet.net import Mininet
from mininet.node import OVSSwitch, Controller, RemoteController
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.topo import Topo

class SimpleTopoTest(object):
    """
    porperties:
    cOdl: remote controller OpenDayLight. Requires Odl running.
    cmap: map of switches
    topo: mininet topology
    net: mininet network
    h1: host h1
    h2: host h2
    """
    cOdl = RemoteController('OpenDayLight', ip='127.0.0.1', port=6633)
    cmap = {'s1': cOdl}

    class MultiSwitch(OVSSwitch):
        "Custom Switch() subclass that connects to different controllers"
        def start(self, controllers):
            return OVSSwitch.start(self, [SimpleTopoTest.cmap[self.name]])

    @staticmethod
    def createTopo():
        topo=Topo()
        #Create Nodes
        topo.addHost("h1")
        topo.addHost("h2")
        topo.addSwitch('s1')
        #Create links
        topo.addLink('h1','s1')
        topo.addLink('h2','s1')
        return topo

    def __init__(self):
        setLogLevel('info')
        #cOdl = RemoteController('OpenDayLight', ip='127.0.0.1', port=6633)
        #cmap = {'s1': cOdl}
        self.topo = SimpleTopoTest.createTopo()
        self.net = Mininet(topo=self.topo, switch=SimpleTopoTest.MultiSwitch, build=False)
        self.net.addController(SimpleTopoTest.cOdl)
        self.net.build()
        self.net.start()
        self.h1, self.h2 = self.net.hosts[0], self.net.hosts[1]
        # Running a command on host h1
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
    simple_topo = SimpleTopoTest()
    simple_topo.cli()
    simple_topo.finalize()