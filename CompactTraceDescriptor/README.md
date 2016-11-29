# CompactTraceDescriptor
This software is part of my Master degree project in development

##Dependencies

Before instaling it, you have to install some 3rd parties softwares and lybraries.

###Octave
TODO

###Armadillo

Armadillo is a free algebra library for the C++ language. To install it, you have first to intall its dependencies.

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

###D-ITG

D-ITG is a internet traffic generation. It can be dawnloaded for free on their webpage (http://www.grid.unina.it/software/ITG/). As described by the authors: 

> D-ITG (Distributed Internet Traffic Generator) is a platform capable to produce traffic at packet level accurately replicating appropriate stochastic processes for both IDT (Inter Departure Time) and PS (Packet Size) random variables (exponential, uniform, cauchy, normal, pareto, ...).

To use if along with this software:

1. Download D-ITG zip file and install at `Components/` in the root directory:
```
	wget http://www.grid.unina.it/software/ITG/codice/D-ITG-2.8.1-r1023-src.zip
	unzip D-ITG-2.8.1-r1023-src.zip
```
2. Dependencies: it uses DCCP and SCTP protocols.
```
	sudo apt-get install libsctp-dev lksctp-tools
```
3. Build and install
```
	cd D-ITG-2.8.1-r1023/src/
	make clean
	make multiport=on bursty=on dccp=on sctp=on all
	sudo make install
```

##About the releases names

The releases are named, in alphabetical order, with the scientific name of Lemurs species from the family Lemuridae.
No special reason, just because they are awsome, there is a plenty of names avaliable, and Zubumafu is a Lemur.
The names were taken from wikipedia: https://en.wikipedia.org/wiki/List_of_lemur_species.






