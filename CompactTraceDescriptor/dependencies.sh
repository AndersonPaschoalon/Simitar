#/bin/bash

function hline()
{
	echo "################################################################################"
}

function main()
{
	hline;
	echo "Armadillo"
	hline;
	echo 
	
	sudo apt-get install cmake
	sudo apt-get install liblapack-dev
	sudo apt-get install libblas-dev
	sudo apt-get install libboost-dev

	git clone https://github.com/xianyi/OpenBLAS
	cd OpenBLAS
	make
	sudo make install

	wget http://sourceforge.net/projects/arma/files/armadillo-7.700.0.tar.xz
	#todo
	cmake .
	make 


}



