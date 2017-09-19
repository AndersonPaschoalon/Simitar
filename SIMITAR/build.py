#!/usr/bin/python3.5
import argparse
import argcomplete
import os

def directory_tree():
	os.system('rm -rf apps/RemoteSystemsTempFiles')
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
	print_header("Directory tree");
	directory_tree()
	os.system('make -C libsimitar/ clean')
	os.system('make -C  trace-analyzer/ clean')
	os.system('make -C  tests/ clean')
	# os.system('make -C clean apps/')


def build():
	print_header("Directory tree");
	directory_tree()
	print_header("Libsimitar");
	os.system('make -C libsimitar/')
	print_header("Trace Analyzer");
	os.system('make -C trace-analyzer/')
	print_header("Tests");
	os.system('make -C tests/')
	#print_header("FlowGen Apps");
	# os.system('make -C apps/')


def print_header(component_name):
	print("");
	print("################################################################################")
	print("# " + component_name)
	print("################################################################################")	


def print_tutorial():
	print_header("Tutorial")
	print('(1) Now run, at the workspace dir (SIMITAR/), run:\n source data/config/simitar-workspace.config.sh\nIt will set the enviroment variables needed.')
	print("(2) To install in the operational system runs:\n ./build --install \nIt will compile, save the enviroment variables in the .bashrc file, and create links to the binaries in the /usr/bin/ directory. So, there will be no need for running the simitar-workspace.config.sh script.")


def install():
	print("TODO")


def unninstall():
	print("TODO")


def deps():
	print_header("Tools dependencies")
	os.system('sudo apt-get install ostinato;')
	os.system('sudo apt-get install wireshark')
	os.system('sudo apt-get install tshark')
	os.system('')
	os.system('')
	os.system('')
	os.system('')
	os.system('')
	print_header("Python dependencies")
	os.system('sudo pip install sqlite3')
	os.system('sudo pip install pyshark')
	os.system('sudo pip install rstr')
	os.system('sudo pip install numpy')
	os.system('sudo pip install fnvhash')
	os.system('sudo pip install termcolor')
	os.system('sudo -H pip install python-ostinato;')		
	print_header("C/C++ lybraries")
	os.system('sudo apt-get install librapidxml-dev ')
	os.system('sudo apt-get install sqlite3 ')
	os.system('sudo apt-get install libsqlite3-dev ')
	os.system('sudo apt-get install liblapack-dev ')
	os.system('sudo apt-get install libblas-dev ')
	os.system('sudo apt-get install libboost-dev ')
	os.system('sudo apt-get install libopenblas-base')
	os.system('apt-get install libarmadillo-dev')
	os.system('apt-get install libtclap-dev')
	os.system('')
	os.system('')
	os.system('')
	os.system('')
	os.system('')


if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument("--build", help="Build project", action="store_true")
	parser.add_argument("--remake", help="Clean and build", action="store_true")
	parser.add_argument("--clean", help="Clean", action="store_true")
	parser.add_argument("--install", help="TODO", action="store_true")
	parser.add_argument("--unninstall", help="TODO", action="store_true")
	argcomplete.autocomplete(parser)
	args = parser.parse_args()
	if args.remake:
		clean()
		build()
		print_tutorial()
	elif args.clean:
		clean()
	elif args.install:
		#build()
		install()
	elif args.unninstall:
		unninstall()
	elif args.build:
		build()
	else:
		build()
		print_tutorial()


