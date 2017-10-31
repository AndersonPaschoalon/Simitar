# Simulation Tutorial

## 1. Install Opendaylight Beryllium on home directory
Follow this tutorial:
https://blinkingnetwork.wordpress.com/2016/08/03/install-opendaylight-ubuntu-16/


## 2. Run Opendaylight
```
cd ~/distribution-karaf-0.4.0-Beryllium
./bin/karaf
```


## 3. Install features on Opendaylight

feature:install odl-restconf odl-l2switch-switch odl-mdsal-apidocs odl-dlux-core
feature:install odl-dlux-all odl-openflowplugin-flow-services-ui
feature:install  odl-dlux-core odl-dlux-node odl-dlux-yangui odl-dlux-yangvisualizer


## 4. You may open the web interface of Opendaylight using:
```
#http://localhost:8181/dlux/index.html
http://localhost:8181/index.html
```

## 5. Clean up mininet and run

- Clean up mininet
    sudo mn -c
- On Tests/SimulationMininet/ directory, run 
    sudo ./simple-topo-test.py or
    sudo ./tree-topo-test.py
- On mininet, to check and to Opendaylight discover all hosts, run:
    mininet> pingall


## 6. Trying simitar-gen

Typing on mininet "xterm h1" you may execute commands using SIMITAR/simitar-gen/simitar-gen app, and may exec
    ./simitar-gen --help
to look at the options. For example:
    ./simitar-gen --tool tins --mode client --ether h1-eth0 --xml ../data/xml/skype.sec.xml
The compact trace descriptors (XML) files are geneated by SIMITAR/trace-analyzer/trace-analyzer and salved at
SIMITAR/data/xml/


## 7. Run simulation

* Edit config.py, changing is arguments, such as tool and simulation name.
* Go to SIMITAR/ and execute:
```
source data/config/config/simitar-workspace-config.sh
```
* Execute the run-server.py scripts on the destination hosts, and run-client.py on the source destination. The pcaps
are salved on the directory ./pcaps/


