#!/usr/bin/python3
import time
import multiprocessing
from Config import Config as config
from Utils.Terminal import Terminal as term
from Utils.Cd import Cd
from SimpleTopoTest import SimpleTopoTest
from TreeTopoTest import TreeTopoTest
from runClient import runClient
from runServer import runServer






def worker(num, wait):
    """thread worker function"""
    print("Thread {0}, Time: {1}".format(num, time.ctime()) )
    time.sleep(wait)
    print ('{0}~Worker:'.format(' '*num))
    return


def tests_process():
    jobs = []
    wait = 1
    for i in range(5):
        p = multiprocessing.Process(target=worker, args=(i, wait))
        jobs.append(p)
        p.start()
        time.sleep(wait)



def run_OpenDayLight():
    cd = Cd()
    cd.cd(config.open_day_light_path)
    term.command("./bin/karaf &")
    term.command('firefox -new-tab "http://localhost:8181/index.htm" &')
    cd.back()

if __name__ == "__main__":
    term.print_header(" Open Day Light", "purple")
    run_OpenDayLight()
    simple_topo = SimpleTopoTest()
    term.print_header(" SimpleTopoTest tests", "purple")

    simple_topo.h2.cmd("sudo ./runServer.py &")
    simple_topo.h1.cmd("sudo ./runClient.py")
    simple_topo.finalize()
    tree_topo = TreeTopoTest()
    term.print_header(" TreeTopoTest tests", "purple")
    tree_topo.h8.cmd("sudo ./runServer.py &")
    tree_topo.h1.cmd("sudo ./runClient.py")
    tree_topo.finalize()



