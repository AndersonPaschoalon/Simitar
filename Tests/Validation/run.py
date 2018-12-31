#!/usr/bin/python3.5
import os
import sys
import datetime
from Config import Config as config
from Utils.Cd import Cd
from Utils.Terminal import Terminal as term

def main():
    run_validation()


def run_validation():
    init_time = datetime.datetime.now()
    cd = Cd()
    term.print_header("Analysis " + config.analysis_name + " using pcaps: " + config.pcap_file_1 + ' and ' + \
                 config.pcap_file_2('*'), "purple")
    list_pcap_names_2 = []
    for i in range(0, config.n_runs):
        list_pcap_names_2.append(config.pcap_file_2(i))
    term.print_color("blue", "  Original pcap  : " + config.pcap_file_1)
    term.print_color("blue", "  Synthetic pcaps: " + str(list_pcap_names_2))
    term.print_color("blue", '  > pcap_file1: ' + config.pcap1() )
    term.print_color("blue", '  > pcap_name1: ' + config.pcap_name_1)
    term.print_color("blue", '  > pcap_file2: ' + config.pcap2('*'))
    term.print_color("blue", '  > pcap_name1: ' + config.pcap_name_2('*'))
    # go to script analysis dir
    cd.cd('./scripts/')
    term.print_color("blue", '  @ directory:')
    cd.pwd()
    # clean sim dir
    term.command('  mkdir -p ./data', 'yellow')
    term.command('  rm -rf data/*', 'yellow')
    # filter original data
    term.print_color("blue", '  --- Filtering inter-packet data from pcap ../' + config.pcap1())
    term.command('  ./analysis-pkt-filter.py ' + config.pcap_name_1 + " ../" + config.pcap1(), 'green')
    for i in range(0, config.n_runs):
        term.print_header("  --- iteration " + str(i), "purple")
        # filter packet (iteration) data
        term.print_color("blue", '  --- Filtering inter-packet data from pcap ../' + config.pcap2(i))
        term.command(' ./analysis-pkt-filter.py ' + config.pcap_name_2(i) + " ../" + config.pcap2(i))
        datafile1 = config.pktfilter_out_file(config.pcap_name_1)
        datafile2 = config.pktfilter_out_file(config.pcap_name_2(i))
        term.print_color("blue", '  --- (datafile1, datafile2) = (' + datafile1 + ', ' + datafile2 + ')')
        # individual tests
        term.command('  ./analysis-bandwidth.m ' + datafile1 + ' ' + datafile2 + ' "1" "10^6"', 'green')
        term.command('  mv ./data/Bandwidth.dat ./data/Bandwidth' +str(i) + '.dat', 'green')
        term.command('  ./analysis-flow.m ' + datafile1 + ' ' + datafile2 + ' "1"', 'green')
        term.command('  mv ./data/FlowCdf.dat ./data/FlowCdf' + str(i) + '.dat', 'green')
        term.command('  mv ./data/FlowCumulative.dat ./data/FlowCumulative' + str(i) + '.dat', 'green')
        term.command('  mv ./data/FlowMaxflows.dat ./data/FlowMaxflows' + str(i) + '.dat', 'green')
        term.command('  mv ./data/FlowsPs.dat ./data/FlowsPs' + str(i) + '.dat', 'green')
        # repeated testes
        term.command('  ./analysis-waveletMra.m ' + datafile1 + ' ' + datafile2 + ' ' + config.analysis_name, 'green')
        term.command('  mv ./data/WaveletMREA.dat ./data/WaveletMREA' + str(i) + '.dat', 'green')
        term.command('  ./analysis-hustExponent.m  ' + datafile1 + ' ' + datafile2, 'green')
        term.command('  mv ./data/hurst_exponent.dat ./data/hurst_exponent' + str(i) + '.dat', 'green')
        term.command('  ./analysis-pcapinfo.sh ' + '../' + config.pcap1() + ' ' + '../' + config.pcap2(i), 'green')
        term.command('  mv ./data/pcapsinfo.txt ./data/pcapsinfo' + str(i) + '.txt', 'green')
    # about test
    end_time = datetime.datetime.now()
    hline = '  -------------------------------------------------------------------------------\n'
    str_about = hline + '  -- Analysis:' + config.analysis_name + " using pcaps " + config.pcap1() + ' --\n' + hline + \
                '\n  @ ' + str(end_time.year) + '/' + str(end_time.month) + '/' + str(end_time.day) + ' ' +\
                str(end_time.hour) + ':' + str(end_time.minute) + ':' + str(end_time.second) + \
                '\n  Simulation duration: ' + str(end_time - init_time) + \
                '\n  Settings: ' + 'n_runs: ' + str(config.n_runs) + ' pcap_file_1: ' + \
                config.pcap_file_1 + ' pcap_name_1:' + config.pcap_name_1 + ' pcap_file_2_prefix:' + \
                config.pcap_file_2_prefix + ' pcap_name_2_prefix:' + config.pcap_name_2_prefix + \
                ' pcap1_type: ' + config.pcap1_type + ' pcap2_type: ' + config.pcap2_type +  \
                ' \n  Comments: ' + config.comments + ' '
    term.print_color("blue", '  About: ' + str_about)
    term.command('  echo \"' + str_about + '\" >> ./data/about.log', 'green')
    # back to  Validation root directory
    cd.back()
    term.print_color("blue", '  @ directory:')
    cd.pwd()
    # move files
    plotdir_name = config.plots_dir + config.analysis_name + "-" + str(end_time.year) + '-' + str(end_time.month) + \
                   '-' + str(end_time.day) + '-' +  str(end_time.hour) + '-' +  str(end_time.minute) + '-' + \
                   str(end_time.second)
    term.command('  mkdir -p ' + plotdir_name, 'yellow')
    term.command('  mv scripts/data/* ' + plotdir_name, 'yellow')
    term.command('  mkdir -p ' + plotdir_name + '/octave-figs/', 'yellow')
    term.command('  mv scripts/figures/* ' + plotdir_name + '/octave-figs/', 'yellow')


if __name__ == "__main__":
    main()


