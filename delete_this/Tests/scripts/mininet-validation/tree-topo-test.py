#!/usr/bin/python

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

class MultiSwitch( OVSSwitch ):
    "Custom Switch() subclass that connects to different controllers"
    def start( self, controllers ):
        return OVSSwitch.start( self, [ cmap[ self.name ] ] )

setLogLevel( 'info' )
c2 = RemoteController( 'OpenDayLight', ip='127.0.0.1', port=6633 )
cmap = { 's1': c2, 's2': c2, 's3': c2, 's4' : c2, 's5': c2, 's6': c2, 's7': c2, 's8': c2, 's9': c2, 's10': c2,  's11': c2, 's12': c2, 's13': c2}
topo = TreeTopo( depth=3, fanout=2 )
net = Mininet( topo=topo, switch=MultiSwitch, build=False )
net.addController(c2)
net.build()
net.start()
CLI( net )
net.stop()
os.system('mn -c')