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

class MultiSwitch( OVSSwitch ):
    "Custom Switch() subclass that connects to different controllers"
    def start( self, controllers ):
        return OVSSwitch.start( self, [ cmap[ self.name ] ] )

setLogLevel( 'info' )
cOdl = RemoteController( 'OpenDayLight', ip='127.0.0.1', port=6633 )
cmap = { 's1': cOdl}
topo =  createTopo()
net = Mininet( topo=topo, switch=MultiSwitch, build=False )
net.addController(cOdl)
net.build()
net.start()
h1, h2  = net.hosts[0], net.hosts[1]
#Running a command on host h1
print(h1.cmd('ifconfig'))
CLI( net )
net.stop()
os.system('mn -c')
