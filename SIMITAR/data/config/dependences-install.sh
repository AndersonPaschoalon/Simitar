#!/bin/bash

arg1=$1

#constants
OPT_SW="--software"
OPT_DEP="--dependencies"
OPT_HLP="--help"

function main
{
	if [[ $arg1 == $OPT_SW ]];
		then

		exec; cd /opt/

		echo_installApp "Htop";
		sudo apt-get install htop;

		echo_installApp "Iperf";
		sudo apt-get install iperf;

		echo_installApp "Tcpreplay";
		sudo apt-get install tcpreplay;
	

		echo_installApp "TCPtrace";
		sudo apt-get install tcptrace;
	
		#TODO Swing-install
		#echo_installApp "ModelNet";
		#wget http://issg.cs.duke.edu/modelnet/debian/dists/sarge/main/binary-i386/net/modelnet_0.99-1_i386.deb;
		#sudo dpkg -i modelnet_0.99-1_i386.deb;
		#
		#echo_installApp "Authd";
		#wget http://issg.cs.duke.edu/modelnet/debian/dists/woody/main/binar%C3%85%E2%80%9Cy-i386/net/authd_0.2.1-2_i386.deb;
		#sudo dpkg -i authd_0.2.1-2_i386.deb;
		#
		#echo_installApp "Gexec";
		#wget http://issg.cs.duke.edu/modelnet/debian/dists/woody/main/binary-i386/net/gexec_0.3.5-2_i386.deb;
		#sudo dpkg -i gexec_0.3.5-2_i386.deb;
		#
		#echo_installApp "Swing";
		#wget http://cseweb.ucsd.edu/~kvishwanath/Swing/software/Swingxficgenerator-0.3.1.tar.gz;
		#tar -zxvf Swingxficgenerator-0.3.1.tar.gz;

	elif [[ $arg1 == $OPT_DEP ]];
		then

		echo_installApp "Python dependencies"
		sudo pip install sqlite3
		sudo pip install pyshark
		sudo pip install rstr
		sudo pip install numpy
		sudo pip install fnvhash
		sudo pip install termcolor
		sudo -H pip install python-ostinato;
			
		echo_installApp "Ostinato";
		sudo apt-get install ostinato;
		#sudo -H pip install python-ostinato;
	
		echo_installApp "Wireshark"
		sudo apt-get install wireshark
		sudo apt-get install tshark
		#sudo pip install pyshark

		echo_installApp "Octave"
		sudo apt-get update                                                             
		sudo apt-add-repository ppa:octave/stable                                       
		sudo apt-get update                                                             
		sudo apt-get install octave
		exec; cd ~                                                                            
		exec; cd .config/octave                                                               
		sudo chown <your-user-name> qt-settings		

		echo_installAll "Sqlite3"
		sudo apt-get install sqlite3                                                    
		sudo apt-get install libsqlite3-dev 

		echo_installApp "Armadillo"
		sudo apt-get install liblapack-dev                                              
		sudo apt-get install libblas-dev                                                
		sudo apt-get install libboost-dev 

		exec; cd /opt/
		git clone https://github.com/xianyi/OpenBLAS
		exec; cd OpenBLAS                                                                     
		make                                                                            
		sudo make install
		apt-get install libarmadillo-dev
	
		sudo apt-get install liblog4cpp-doc liblog4cpp5-dev liblog4cpp5v5

		echoInstallApp "D-ITG"
		exec; cd /opt/
		wget http://www.grid.unina.it/software/ITG/codice/D-ITG-2.8.1-r1023-src.zip
        unzip D-ITG-2.8.1-r1023-src.zip                                         
        sudo apt-get install libsctp-dev lksctp-tools                           
		exec; cd D-ITG-2.8.1-r1023/src/                                               
		make clean                                                              
		make multiport=on bursty=on dccp=on sctp=on all                         
		sudo make install                                                       
		sudo cp src/libITG/ITGapi.h /usr/include                                
		sudo ldconfig                                                           

	else

		echo_help;
	fi;
}


function echo_installApp
{
	application=$1;
	echo ""
	echo "#################################################################"
	echo "# Installing " $1 "..." 
	echo "#################################################################"

	return 0;	
}

function echo_help
{
	echo "./dependencies-tools.sh <opt>"
	echo "     ""<opts>"
	echo "     " $OPT_SW
	echo "     " $OPT_DEP
	echo "     " $OPT_HLP

}

main;
