#!/bin/bash

function print_header 
{
	echo ""
	echo "################################################################################"
	echo $1
	echo "################################################################################"
}

function install_armadillo
{
	print_header "Armadillo"	
	sudo apt-get install cmake liblapack-dev libblas-dev libboost-dev

	git clone https://github.com/xianyi/OpenBLAS
	cd OpenBLAS
	make
	sudo make install

	#wget http://sourceforge.net/projects/arma/files/armadillo-7.700.0.tar.xz
	#tar xf armadillo-7.700.0.tar.xz
	#cmake .
	#make

	sudo apt-get install libarmadillo-dev 

}

function install_wireshark
{
	print_header "Wireshark"
	sudo apt-get install wireshark tshark
	sudo pip install pyshark
}

function install_sqlite
{
	print_header "Sqlite3"
	sudo apt-get install sqlite3 libsqlite3-dev 
}

function install_log4cpp
{
	print_header "Log4cpp"
	sudo apt-get install liblog4cpp-doc liblog4cpp5-dev liblog4cpp5v5

}

function install_ditg
{
	print_header "D-ITG"
	sudo apt-get install unzip
	wget http://www.grid.unina.it/software/ITG/codice/D-ITG-2.8.1-r1023-src.zip
	unzip D-ITG-2.8.1-r1023-src.zip
	sudo apt-get install libsctp-dev lksctp-tools
	cd D-ITG-2.8.1-r1023/src/
	make clean
	make multiport=on bursty=on dccp=on sctp=on all
	sudo make install
	sudo cp libITG/ITGapi.h /usr/include/
	sudo ldconfig
}

function install_ostinato
{
	print_header "Ostinato"
	sudo apt-get install ostinato
	sudo -H pip install python-ostinato
}

function install_iperf
{
	print_header "Iperf"
	sudo apt-get install iperf
}

function install_octave
{
	print_header "Octave"	
	sudo apt-get update
	sudo apt-add-repository ppa:octave/stable
	sudo apt-get update
	sudo apt-get install octave
}


functio install_libtins
{
	print_header "Libtins"
	sudo apt-get install libpcap-dev libssl-dev cmake
	sudo apt-get install libtins-dev libtins3.4
}

function main()
{
	#install_armadillo
	install_wireshark
	install_sqlite
	install_log4cpp
	#install_ditg
	install_ostinato
	install_iperf
	install_octave
	install_libtins
}

main;
