# CompactTraceDescriptor
This software is part of my Master degree project in development

#Dependencies

Before instaling it, you have to install some 3rd parties softwares and lybraries.

* Octave
TODO

* Armadillo

Armadillo is alinear algebra library for the C++ language. To install it, you have first to intall its dependencies.

```
sudo apt-get install liblapack-dev
sudo apt-get install libblas-dev
sudo apt-get install libboost-dev
```
For a best performance, you should also intall OpenBLAS (http://www.openblas.net/, https://github.com/xianyi/OpenBLAS). Download, and install doing:
```
git clone https://github.com/xianyi/OpenBLAS
cd OpenBLAS
make
sudo make install
```

To install Armadillo directely from the source, download the last version at http://arma.sourceforge.net/download.html. Unzip, go to de generated directory, and execute:
```
cmake .
make 
  
```
Alternaively, you may execute:
```
apt-get install libarmadillo-dev
```

* D-ITG

1. Download D-ITG zip file and install at components/
	wget http://www.grid.unina.it/software/ITG/codice/D-ITG-2.8.1-r1023-src.zip
	unzip D-ITG-2.8.1-r1023-src.zip
2. Build and install
	cd D-ITG-2.8.1-r1023/src/
	make clean
	make multiport=on bursty=on dccp=on sctp=on all
	sudo make install







