#!/usr/bin/python3.5
import os
import sys
import time
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/..')

import GnuplotScripts.GnuplotScripts as gps
import Cd.Cd as dir

PCAP_FILE1 = "../../Pcap/wireshark-wiki_http.pcap"
PCAP_FILE2 = "../../Pcap/wireshark-wiki_ospf.pcap"
TEST_NAME = "lemur"


def main(args):
    pcap1 = args[0]
    pcap2 = args[1]
    analyzis_name = args[2]
    # input arguments
    pcap_file1 = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + pcap1
    pcap_file2 = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + pcap2
    plots_dir = 'plots/' + analyzis_name
    # making sure the program is being executed in the source location, so it can be executed from anyware
    cd = dir.Cd(os.path.dirname(os.path.abspath(__file__)))
    run_analyzis(pcap_file1=pcap_file1, pcap_file2=pcap_file2, analyzis_name=analyzis_name, plots_dir=plots_dir, cd=cd)
    plot_data('http', 'ospf', analyzis_name, plots_dir)

def validation_help():
    print('./run.py <pcap_file_base> <pcap_file_synthetic> <validation_name>')
    print('\tEg.: ./run.py ../pcaps/wireshark-wiki_http.pcap ../pcaps/wireshark-wiki_ospf.pcap lemur')

def print_header(title):
    print('')
    print('###############################################################################')
    print('# ' + title)
    print('###############################################################################')


def run_analyzis(pcap_file1, pcap_file2, analyzis_name, plots_dir, cd):
    print_header("Analysis for:" + analyzis_name + " using pcaps: " + pcap_file1 + ' and ' + pcap_file2)
    # go to script analysis dir
    cd.cd('./analysis/')
    # clean sim dir
    os.system('mkdir -p ./data')
    os.system('rm -rf data/*')
    # filter packet data
    print_header('Filtering data from pcap ' + pcap_file1)
    os.system('./analysis-pkt-filter.py ' + analyzis_name + '1 ' + pcap_file1)
    print_header('Filter inter-pacekt data from pcap ' + pcap_file2)
    os.system('./analysis-pkt-filter.py ' + analyzis_name + '2 ' + pcap_file2)
    datafiles = os.listdir('./data/')
    datafile1 = datafiles[0]
    datafile2 = datafiles[1]
    print('(datafile1, datafile2) = ', datafile1, datafile2)
    # run analyzis
    os.system('./analysis-waveletMra.m ' + datafile1 + ' ' + datafile2 + ' ' + analyzis_name)
    os.system('./analysis-hustExponent.m  ' + datafile1 + ' ' + datafile2)
    os.system('./analysis-bandwidth.m ' + datafile1 + ' ' + datafile2 + ' "1" "10^6"')
    os.system('./analysis-flow.m ' + datafile1 + ' ' + datafile2 + ' "1"')
    # back to root dir
    cd.back()
    # creating plots dir
    os.system('rm -rf ' + plots_dir)
    os.system('mkdir -p ' + plots_dir)
    os.system('mv analysis/data/* ' + plots_dir)
    str_about = 'Analysis:' + analyzis_name + " using pcaps " + pcap_file1 + ' and ' + pcap_file2 + ' '
    str_date = '@ ' + str(time.localtime().tm_mday) + '/' + str(time.localtime().tm_mon) + '/' + str(
        time.localtime().tm_year) + '-' + str(time.localtime().tm_hour) + ':' + str(
        time.localtime().tm_min) + ':' + str(time.localtime().tm_sec)
    os.system('echo \"' + str_about + '\" >>' + plots_dir + '/about.log')
    os.system('echo \"' + str_date + '\" >>' + plots_dir + '/about.log')


def plot_data(trace_name1, trace_name2, analyzis_name, plots_dir):
    font_config = 'Helvetica,15'
    print_header("Plots for:" + analyzis_name + " using traces " + trace_name1 + ' and ' + trace_name2)
    gp = gps.GnuplotScripts(data_dir=plots_dir, plot_dir=plots_dir, font=font_config, linestyle_1='b+',
                            linestyle_2='rx',
                            linestyle_3='g-', linestyle_4='v-', type='linespoints', line_width=2)

    print('Ploting Wavelet Multiresolution Analisis')
    gp.plot_config(xlabel='Time scale j', ylabel='log2(Energy(j))', legend1=trace_name1, legend2=trace_name2,
                   type='linespoints')
    gp.plot_2functionxyxy(datafile='WaveletMREA.dat', filename='WaveletMREA')

    print('Ploting Bandwidth')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Mbps', legend1=trace_name1, legend2=trace_name2, type='linespoints')
    gp.plot_2function(datafile='Bandwidth.dat', filename='Bandwidth')

    print('Ploting Flow data (FlowPs and FlowCDF)')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Number of Flows', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2function(datafile='FlowsPs.dat', filename='FlowsPs')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Flow CDF function', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2function(datafile='FlowCdf.dat', filename='FlowCdf')


if __name__ == "__main__":
    if (len(sys.argv) == 1) or (len(sys.argv) == 2):
        validation_help()
    else:
        main(sys.argv[1:])


