#!/bin/bash

pcapfile1=$1
pcapfile2=$2
data_dir='./data/'
info_file=${data_dir}'pcapsinfo.txt'
hline='-------------------------------------------------------------'

# capinfos ../pcaps/skype.pcap  
echo ${hline} >> ${info_file}
capinfos ${pcapfile1} >> ${info_file}
echo ${hline} >> ${info_file}
capinfos ${pcapfile2} >> ${info_file}
cat ${info_file}

