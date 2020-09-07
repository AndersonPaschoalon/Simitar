#!/usr/bin/python3
import argparse
import re
import sys
import os
import logging
from termcolor import colored
from SnifferManager import SnifferManager

logging.basicConfig(level=logging.DEBUG, format='%(relativeCreated)6d %(threadName)s %(message)s')

def load_env_var_error(env_var_name):
    print(colored('Error: enviroment variable ' + env_var_name + ' not defined.', 'red'))
    print('Execute `source data/config envvariables.config` or `export ' + env_var_name + '=<var-name>`')
    exit()

# Load env variables
DATABASE = ''
LOGFILE_PATH = '.'
try:
    DATABASE = os.environ["SIMITAR_DATABASE"]
except KeyError:
    load_env_var_error("SIMITAR_DATABASE")
try:
    LOG_DIR = os.environ["SIMITAR_LOG_DIR"]
except KeyError:
    load_env_var_error("SIMITAR_LOG_DIR")


def livepcap_regex_type(s, pat=re.compile(r"(pcap|live)$")):
    if not pat.match(s):
        raise argparse.ArgumentTypeError
    return s

def requires_sudo():
    if os.geteuid() != 0:
        print(colored("You need to have root privileges to run this script.\n", 'red') +
             colored("\tPlease try again, this time using 'sudo'. Exiting.", 'green'))
        exit()

def subcommand_new(args):
    requires_sudo()
    if args.comment == None:
        args.comment = ""
    if args.timeout == None:
        args.timeout = 10
    SnifferManager.new(database_name=DATABASE, trace_name=args.trace_name, trace_type=args.trace_type,
                       target_name=args.target_name, live_timeout=int(args.timeout), verbose=True,
                       logfile_path=LOG_DIR)


def subcommand_rm(args):
    for trace in args.list:
        print(colored('> Deleting trace '+trace, 'yellow'))
        SnifferManager.rm(database_name=DATABASE, trace_name=trace)


def subcommand_list(args):
    SnifferManager.list(database_name=DATABASE)


if __name__ == '__main__':
    # create the top-level parser
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers()

    # create the parse for the "new" command
    parser_new = subparsers.add_parser('new', help='Process a new traffic trace eigter live or pcap')
    parser_new.add_argument('trace_name', type=str, default='trace-name',
                            help='Trace name that will be recorded in the database')
    parser_new.add_argument('trace_type', type=livepcap_regex_type, default='live',
                            help='Input trace type, live or pcap')
    parser_new.add_argument('target_name', type=str, default='eth0',
                            help='Target trace, the internet interface (eg. eth0) name or the pcap file')
    parser_new.add_argument('--comment', help='description of the trace')
    parser_new.add_argument('--timeout', help='Live capture timeout time. Default: 10s', default=10)
    parser_new.set_defaults(func=subcommand_new)

    # create the parser for the "rm" command
    parser_rm = subparsers.add_parser('rm', help='Remove a trace from the database')
    #parser_rm.add_argument('trace_name')
    parser_rm.add_argument('-l', '--list', nargs='+', help='Traces to be removed from database.', required=True)
    parser_rm.set_defaults(func=subcommand_rm)

    # create the parser for the "list" command
    parser_list = subparsers.add_parser('list', help='Display all the trace capture table')
    parser_list.set_defaults(func=subcommand_list)

    # parse the args and call whatever function was selected
    try:
        args = parser.parse_args()
        args.func(args)
    except:
        parser.print_help()
        sys.exit(0)
