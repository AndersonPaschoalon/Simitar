#!/bin/bash

#./ctd-shell.sh prototype "../pcaps/wireshark-wiki_SkypeIRC.pcap" "wireshark-wiki_SkypeIRC"
./ctd-shell.sh prototype "../pcaps/live_background-traffic-1.pcap" "001_live_background-traffic-1"
./ctd-shell.sh prototype "../pcaps/tcpreplay_bigFlows.pcap" "001_tcpreplay_bigFlows"
/ctd-shell.sh prototype "../pcaps/lan_diurnalServerRouterCapture.pcap" "001_lan_diurnalServerRouterCapture"
./ctd-shell.sh prototype "../pcaps/http-chunked-gzip.pcap" "001_http-chunked-gzip"
#/ctd-shell.sh prototype-flow "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "flow2-equinix-chicago.dirB.20160121-135641.UTC.anon" "(ip.src==69.12.209.118)&&(ip.dst==153.193.117.110)&&(tcp.srcport==80)&&(tcp.dstport==58902)"
#/ctd-shell.sh prototype-flow "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "flow1-equinix-chicago.dirB.20160121-135641.UTC.anon" '(ip.src==43.252.226.5)&&(ip.dst==125.6.107.157)&&(tcp.srcport==80)&&(tcp.dstport==64834)'
./ctd-shell.sh prototype "../pcaps/live_ping-backgound-1.pcap" "001_live_ping-backgound-1"
#/ctd-shell.sh prototype "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "equinix-chicago.dirB.20160121-135641.UTC.anon"


#./ctd-shell.sh prototype-flow "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "flow1-equinix-chicago.dirB.20160121-135641.UTC.anon" '(ip.src==43.252.226.5)&&(ip.dst==125.6.107.157)&&(tcp.srcport==80)&&(tcp.dstport==64834)'
#./ctd-shell.sh prototype "../pcaps/wireshark-wiki_SkypeIRC.pcap" "wireshark-wiki_SkypeIRC"
#./ctd-shell.sh prototype-flow "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "flow2-equinix-chicago.dirB.20160121-135641.UTC.anon" "(ip.src==69.12.209.118)&&(ip.dst==153.193.117.110)&&(tcp.srcport==80)&&(tcp.dstport==58902)"
#./ctd-shell.sh prototype "../pcaps/lan_diurnalFirewallCapture.pcap" "lan_diurnalFirewallCapture"
#./ctd-shell.sh prototype "../pcaps/live_ping-backgound-1.pcap" "live_ping-backgound-1"
#./ctd-shell.sh prototype "../pcaps/equinix-chicago.dirB.20160121-135641.UTC.anon.pcap.gz" "equinix-chicago.dirB.20160121-135641.UTC.anon"

