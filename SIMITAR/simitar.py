#!/bin/bash

import sys
import os
import re

def title(title_str):
    print("")
    print("###############################################################################")
    print(title_str)
    print("###############################################################################")

def check_dependencies_libs(lib_list):
    for lib_name in lib_list:
        dependency_check_out = os.popen('ldconfig -p | grep ' +  lib_name).read()
        dependency_check_out = ''.join(dependency_check_out.split()).replace("\n", "")

        if dependency_check_out == '':
            print('Missing lybrary ' + lib_name)
            exit()
        else:
            print(lib_name + ' ok')

def check_dependencies_tools(tools_list):
    for tool_name in tools_list:
        dependency_check_out = os.popen('command -v ' + tool_name + ' -v').read()
        dependency_check_out = ''.join(dependency_check_out.split()).replace("\n", "")

        if dependency_check_out == '':
            print('Missing tool ' + tool_name)
            exit()
        else:
            print(tool_name + ' ok')

def check_dependencies_python(pkg_list):
    for pkg in pkg_list:
        try:
            import pkg
            print()
        except ImportError:
            print('Missing Python package ' + pkg)
            exit()

def trick_eclipse(projec_dir):
    """
    Trick eclipse, letting the binaries be built in a bin directory
    :return:
    """
    os.system('cd ' + projec_dir)
    os.system('rm -rf Debug')
    os.system('rm -rf Release')
    os.system('mkdir bin')
    os.system('ln -s bin Debug')
    os.system('ln -s bin Release')


if __name__ == '__main__':
    title('Checking dependencies')
    lib_list = ('armadillo', 'ITG', 'sqlite3', 'libboost', 'libblas', 'liblapack', 'openblas', 'sctp', 'log4cpp')
    tool_list = ('tshark', 'wireshark', 'octave', 'sqlite3', 'cmake', 'iperf', 'ostinato')
    python_dps = ('sqlite3', 'pyshark', 'rstr', 'numpy', 'fnvhash', 'termcolor')
    check_dependencies_libs(lib_list)
    check_dependencies_tools(tool_list)
    #check_dependencies_python(python_dps)

    title('Building libsimicar')
    #os.system('make -C common/')

    title('Building trace-analyzer')
    #os.system('make -C trace-analyzer')

    kkk = os.listdir('apps/')
    print(kkk)









