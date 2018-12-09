# SIMITAR: SniffIng ModellIng and TrAffic geneRation
<p align="center">
	<img src="https://github.com/AndersonPaschoalon/ProjetoMestrado/blob/master/Docs/Figures/large.jpg" width="200" >
</p>

SIMITAR stands for SIMITAR: SnIffing, ModellIng and TrAffic geneRation. SIMITAR is a tool for creating synthetic and realist network traffic. It uses actual netowork traffic (live captures or pcap files) for creating a flow-oriented traffic model. This model is used for creating network traffic, and is provided as parameter for the traffic generator. It is self-configurated because you dont have to care about adjusting stochastic parameters such as exponenetial rates, protocol, ports, or traffic rates as input parameters. It is all contained inside te traffic model created.

<p align="center">
	<img src="https://github.com/AndersonPaschoalon/ProjetoMestrado/blob/master/SIMITAR/data/misc/digram-project-cycle.png" width="400" >
</p>

The traffic generator is not attached to a especific technology. It has a flow scheduler, which creates a thread for each flow. As traffic generator engine we can use from applications to low-level C/C++ lybraries. Currently we have extended it to [Libtins](http://libtins.github.io/)(C++ packet frafter lyrbrary) and [Iperf](https://iperf.fr/).  

<p align="center">
	<img src="https://github.com/AndersonPaschoalon/ProjetoMestrado/blob/master/SIMITAR/data/misc/arch1.svg" width="400" >
</p>

## Quick installation Guide

Clone this project directory:
```bash
git clone https://github.com/AndersonPaschoalon/ProjetoMestrado
```
Go to `SIMITAR root directory`
```bash
cd cd Projeto/Mestrado/SIMITAR/
```
Run the `build.py` script. This is a script used to simplify the installarion of dependencies and build process. Type:
```
./build.py --deps
```
Types `y/Yes` for any request of confimation. To build type:
```
./build.py --clean
./build.py --build
```
These commands will ensure all required directories are created, and run `make clean` and `make` for each component in the right order. Link for all the binaries will be placed at `bin/`. This application use absoluthe paths for the files, so you may execute any executable from any place. These links and executables are equivalent:


| executable                    | link                       |
|-------------------------------|----------------------------|
| sniffer/sniffer-cli.py        | bin/simitar-sniffer        |
| trace-analyzer/trace-analyzer | bin/simitar-trace-analyzer |
| simitar-gen/simitar-gen       | bin/simitar-gen            |

## Components and apps

SIMITAR is composed of 4 components:

- Sniffer (sniffer/sniffer-cli.py or bin/simitar-sniffer) : Capture data from the pcap files or live captures.
- Database (data/db/Trace.db): local database for the capture traces.
- Trace Analyzer (trace-analyzer/trace-analyzer or bin/trace-analyzer):  creates the XML file (Compact Trace Descriptor) used by simitar-gen to create a synthetic traffic. The files are placed at the directory `/data/xml/`. Some pre-generated Compact Trace Descriptor files are already placed there. 
- Traffic Generator (simitar-gen/simitar-gen or bin/simitar-gen): creates the sysnthetic traffic. A component diagram of the wole project is placed in the image below.

<p align="center">
	<img src="https://github.com/AndersonPaschoalon/ProjetoMestrado/blob/master/SIMITAR/data/misc/architecture-diagram.png" width="400" >
</p>

## Basic Execution

Before executing any command, you must load the enviroment variables:
```bash
source data/config/simitar-workspace-config.sh
```
Sniffer works collecting information about an input traffic such as a pcap file
or a live traffic, and stores it in a sqlite3 database. It can be executed on
the directory sniffer/. Eg.:
```bash
#
./sniffer-cli.py new "intrig-traffic" live eth0 --timeout 15
```
This command will start and store a new capture trace on the local database. This capture will least for 15 seconds.  Ather this execution, use this command to show the capture information on the database:
```bash
./sniffer-cli.py list
```
Trace Analyzer creates a compact trace descriptor in XML file using a saved 
in the database. It salves the xml on the directory data/xml/. It can be 
executed on the directory trace-analyzer/. Eg.:
```bash
./trace-analyzer --trace "intrig-traffic"
```
The name passed in the `--trace` option must be the same as the one stored in the local database. Many others options are available(you may check tem typing `--help`) but none is mandatory. They may be used to control the parameters on the modelling process. After the execution, you may type on the root directory this command do check if the compact traffic trace was created:
```bash
ls data/xml/* |grep "intrig-traffic"
```
It must show two files:  `intrig-traffic.sec.xml` and `intrig-traffic.ms.xml`. The first was parameterized using a time-scale of seconds, and the second of milliseconds. Some tools, like D-ITG use milliseconds as parameter input for its stochastic models.
The traffic generator simitar-gen is able to create traffic based on the model
created by the traffic generator. It can be executed on the directory 
simitar-gen/. To generate and receive the traffic, execute:
```bash
sudo -E ./simitar-gen --tool iperf --mode client --ether eth0 --xml ../data/xml/intrig-traffic.sec.xml --dst-ip 10.0.0.2
sudo -E ./simitar-gen --tool tins --mode client --ether eth0 --xml ../data/xml/intrig-traffic.sec.xml
sudo -E ./simitar-gen --tool iperf --mode server --ether eth0 --xml ../data/xml/intrig-traffic.sec.xml
```
Iperf and D-ITG  require the use of a client and a server, since it creates a 
connection before sending any packets. Others tools like tins, require
just the operation as a client, since since it crafts packets "on the wire". It is important the use of the `-E` option on `sudo` to export the enviroment variables.

## Demo

todo


## Directories and files

- build.py 
Python script to helpd the installation of dependencies and build/clean process
```bash
./build.py --deps       # check and install (if they are not) all the dependencies
./build --build		# build SIMITAR
./build --clean		# clean 
./build --remake	# clean and build
```

- bin 

- data/
Directory to store SIMITAR data.
	* config: enviroment variables and dependencies scripts.
	* csv: directory to store csv files of IP/MAC addrs.
	* db: Stores the Trace.db file
	* log: store the logfiles generated by the components
	* test: store files used by the unity and integration tests.
	* xml: stores the Compact Trace Descriptors files.

- desps/
Third parties software code used on this project

- libsimitar/
SIMITAR library and classes used by simitar components and apps.

- pcaps/
Used to store pcap files

- README.md
This description

- simitar-gen/
Simitar traffic generator directory

- sniffer/
Sniffer component directory, used to capture traffic data

- tests/
Unity and integration testes

- trace-analyzer/
Trace Analyzer directory










