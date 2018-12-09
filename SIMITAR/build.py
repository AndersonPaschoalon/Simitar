#!/usr/bin/python3
import sys
import os
from imp import find_module
import apt

list_python_libs = {
    'argparse',
    'pyshark',
    'rstr',
    'numpy',
    'fnvhash',
    'termcolor'
}
list_tools = {
    'python3-pip',
    'cmake',
    'wireshark',
    'tshark',
    'iperf'
}
list_cpp_libs = {
    'librapidxml-dev',
    'sqlite3',
    'libsqlite3-dev',
    'liblapack-dev',
    'libblas-dev',
    'libopenblas-base',
    'libarmadillo-dev',
    'libtclap-dev',
    'libpcap-dev',
    'libssl-dev'
}

class Utils(object):
    _DISABLE_INSTALL = False

    @staticmethod
    def DISABLE_INSTALL():
        return Utils._DISABLE_INSTALL

    # Print a string with the collor given in the first argument.
    # print_color("red", "APPLE")
    # print_color("green", "grass", end="\n")
    @staticmethod
    def print_color(color, data, end='\n'):
        color_def = {
            # Reset
            "reset": "\033[0m",  # Text Reset
            # Regular Colors
            "black": "\033[0;30m",  # Black
            "red": "\033[0;31m",  # Red
            "green": "\033[0;32m",  # Green
            "yellow": "\033[0;33m",  # Yellow
            "blue": "\033[0;34m",  # Blue
            "purple": "\033[0;35m",  # Purple
            "cyan": "\033[0;36m",  # Cyan
            "white": "\033[0;37m"  # White
        }
        color_code = color_def.get("reset") if color_def.get(color) == "" else color_def.get(color)
        print(color_code + data + color_def.get("reset"), end=end)

    # Install a list of Python Packages
    @staticmethod
    def pip_install(lib_list):
        Utils.print_color('cyan', '\n$ sudo apt-get install python3-pip')
        os.system('sudo apt-get install python3-pip')
        Utils.print_color('cyan', '\n$ sudo python3 -m pip install --user --upgrade pip==9.0.3')
        os.system('sudo python3 -m pip install --user --upgrade pip==9.0.3')
        Utils.print_color('cyan', '\n$ pip3 install setuptools')
        os.system('pip3 install setuptools')
        #os.system('pip install --upgrade pip')
        #Utils.print_color('cyan', '$ sudo pip install --upgrade pip')
        #os.system('sudo pip install --upgrade pip')
        #Utils.print_color('cyan', '$ sudo pip3 install setuptools')
        #os.system('sudo pip3 install setuptools')
        for item in lib_list:
            if item != '':
                pip_cmd = 'pip3 install ' + item
                print()
                Utils.print_color("purple", "$ " + pip_cmd)
                if not Utils.DISABLE_INSTALL():
                    os.system(pip_cmd)

    @staticmethod
    def check_python_pkg(mod):
        try:
            find_module(mod)
            return True
        except ImportError:
            return False

    @staticmethod
    def check_apt_pkg(package_name):
        cache = apt.Cache()
        if cache[package_name].is_installed:
            # print("YES it's installed")
            return True
        else:
            # print("NO it's NOT installed")
            return False

    @staticmethod
    def print_pkg_status(list_pkg, check_function):
        maxlen = 0
        for item in list_pkg:
            if maxlen < len(item):
                maxlen = len(item)
        padding_size_header = maxlen - 3 + 1
        header = "pkg" + " " * padding_size_header + ":  Status"
        hline = "-" * (padding_size_header + 3 + 10)
        print(header)
        print(hline)
        for item in list_pkg:
            padding_size = maxlen - len(item) + 1
            padding = ' ' * padding_size
            pkg_status = check_function(item)
            if pkg_status:
                Utils.print_color("cyan", item + padding + ":  " + "Installed", end="\n")
            else:
                Utils.print_color("red", item + padding + ":  " + "Missing!", end="\n")

    @staticmethod
    def print_pkg_status(list_pkg, tool):
        if tool == 'apt':
            Utils.print_pkg_status(list_pkg, Utils.check_apt_pkg)
        elif tool == 'pip':
            Utils.print_pkg_status(list_pkg, Utils.check_python_pkg)
        else:
            Utils.print_color('red', 'select apt or pip as tool')

    @staticmethod
    def apt_install(lib_list):
        apt_up = 'sudo apt-get update'
        Utils.print_color("cyan", "\n$ " + apt_up)
        if not Utils.DISABLE_INSTALL():
            os.system(apt_up)
        for item in lib_list:
            print(item)
            if item != '':
                apt_cmd = 'sudo apt-get install ' + item
                Utils.print_color("cyan", "\n$ " + apt_cmd)
                if not Utils.DISABLE_INSTALL():
                    os.system(apt_cmd)


def install_libtins():
    Utils.print_color("cyan", "\n# install libtins " )
    os.system('tar -xvzf deps/libtins.tar.gz  -C deps/; '
        'mkdir deps/libtins/build; '
        'cd deps/libtins/build; '
        'cmake ../ -DLIBTINS_ENABLE_CXX11=1; '
        'make; '
        'sudo make install; '
        'sudo ldconfig; ')


def install_plog():
    Utils.print_color("cyan", "\n# install plog")
    os.system('tar -xvzf deps/plog.tar.gz -C deps/; '
        'sudo cp  -r  deps/plog /usr/include/ ;')


def install_rapdxml():
    Utils.print_color("cyan", "\n# install rapidxml-1.13")
    os.system('tar -xvzf deps/rapidxml-1.13.tar.gz -C deps/; '
    'sudo cp  -r  deps/rapidxml-1.13 /usr/include/ ;')


def directory_tree():
    os.system('rm -rf RemoteSystemsTempFiles')
    os.system('mkdir -p libsimitar/obj')
    os.system('mkdir -p tests/xml')
    os.system('mkdir -p pcaps')
    os.system('mkdir -p trace-analyzer/obj')
    os.system('mkdir -p data/config')
    os.system('mkdir -p data/db')
    os.system('mkdir -p data/log')
    os.system('mkdir -p data/test')
    os.system('mkdir -p data/xml')


def clean():
    print_header("Building directory tree")
    directory_tree()
    print_header("Clean all components")
    os.system('make -C libsimitar/ clean')
    os.system('make -C  trace-analyzer/ clean')
    os.system('make -C  tests/ clean')
    os.system('make -C simitar-gen/ clean')
    os.system('rm -rf data/log/*.log')
    os.system('rm -rf bin/*')


def build():
    print_header("Directory tree")
    directory_tree()
    print_header("Libsimitar")
    os.system('make -C libsimitar/')
    print_header("Sniffer")
    os.system('ln -s `readlink -f  sniffer/sniffer-cli.py` bin/simitar-sniffer')
    print_header("Trace Analyzer trace-analyzer")
    os.system('make -C trace-analyzer/')
    os.system('ln -s `readlink -f  trace-analyzer/trace-analyzer` bin/simitar-trace-analyzer')
    print_header("Tests")
    os.system('make -C tests/')
    print_header("SIMITAR traffic generator simitar-gen")
    os.system('make -C simitar-gen/')
    os.system('ln -s `readlink -f  simitar-gen/simitar-gen` bin/simitar-gen')


def print_header(component_name):
    print("")
    print("################################################################################")
    print("# " + component_name)
    print("################################################################################")


def deps(install):
    # pip install argcomplete
    print_header("Tools dependencies")

    if install=='libs':
        Utils.apt_install(list_cpp_libs)
        install_libtins()
        install_plog()
        install_rapdxml()
    elif install=='tools':
        Utils.apt_install(list_tools)
    elif install=='pkg':
        Utils.pip_install(list_python_libs)
    elif install=='all':
        Utils.apt_install(list_tools)
        Utils.apt_install(list_cpp_libs)
        Utils.pip_install(list_python_libs)
        install_libtins()
        install_plog()
        install_rapdxml()

    else:
        Utils.print_color("red", "Wrong option: "+install)


def menu_options():
    print("Welcome to SIMITAR builder helper. Choose your option:\n"
          "--deps-install/-d [option] : install dependencies, and display wich were installed successefully.\n"
          "                             option: [all]   all dependencies \n"
          "                                     [tools] software tools\n"
          "                                     [libs]  C++ libraries\n"
          "                                     [pkg] python packeges\n"
          "--build/-b                 : build SIMITAR\n"
          "--clean/-c                 : clean SIMITAR\n"
          "--rebuild/-r               : clean and build SIMITAR\n"
          "--help/-h                  : print this options menu\n")


if __name__ == '__main__':
    list_args = sys.argv
    if len(list_args) == 1:
        menu_options()
    elif list_args[1] == "-d" or list_args[1] == "--deps-install":
        deps(list_args[2])
    elif list_args[1] == "-b" or list_args[1] == "--build":
        build()
    elif list_args[1] == "-c" or list_args[1] == "--clean":
        clean()
    elif list_args[1] == "-r" or list_args[1] == "--rebuild":
        clean()
        build()
    elif list_args[1] == "-h" or list_args[1] == "--help":
        menu_options()
    else:
        Utils.print_color(color="red", data="Invalid argument :" + list_args[1])
        menu_options()
