#!/usr/bin/python3.5
import os
import time
from GnuplotScripts.GnuplotScripts import GnuplotScripts
from Cd.Cd import Cd

PCAP_FILE1 = "../../Pcap/wireshark-wiki_http.pcap"
PCAP_FILE2 = "../../Pcap/wireshark-wiki_ospf.pcap"
TEST_NAME = "lemur"


def print_header(title):
    print('')
    print('###############################################################################')
    print('# ' + title)
    print('###############################################################################')

def run_analyzis(pcap_file1, pcap_file2, test_name, plots_dir):
    print_header("Analysis for:" + test_name + " using pcaps: " + pcap_file1 + ' and ' + pcap_file2)
    # clean sim dir
    cd.cd('./analysis/')
    os.system('mkdir -p ./data')
    os.system('rm -rf data/*')
    # filter packet data
    print_header('Filter inter-pacekt data from pcap ' + pcap_file1 )
    os.system('./analysis-pkt-filter.py ' + test_name + '1 ' + pcap_file1)
    print_header('Filter inter-pacekt data from pcap ' + pcap_file2)
    os.system('./analysis-pkt-filter.py ' + test_name + '2 ' + pcap_file2)
    datafiles = os.listdir('./data/')
    datafile1 = datafiles[0]
    datafile2 = datafiles[1]
    os.system('./analysis-waveletMra.m ' + datafile1 + ' ' + datafile2 + ' ' +test_name)
    os.system('./analysis-hustExponent.m  ' + datafile1 + ' ' + datafile2 )
    os.system('./analysis-bandwidth.m ' + datafile1 + ' ' + datafile2 + ' 1')
    os.system('./analysis-flow.m ' + datafile1 + ' ' + datafile2 + ' 1')
    cd.back()
    # creating plots dir
    os.system('rm -rf ' + plots_dir)
    os.system('mkdir -p ' + plots_dir)
    os.system('mv analysis/data/* ' + plots_dir)
    str_about = 'Analysis:' + sym_name + " using pcaps " + pcap_file1 + ' and ' + pcap_file2 + ' '
    str_date = '@ ' + str(time.localtime().tm_mday) + '/' + str(time.localtime().tm_mon) + '/' + str(
        time.localtime().tm_year) + '-' + str(time.localtime().tm_hour) + ':' + str(
        time.localtime().tm_min) + ':' + str(time.localtime().tm_sec)
    os.system('echo \"' + str_about + '\" >>' + plots_dir + '/about.log')
    os.system('echo \"' + str_date + '\" >>' + plots_dir + '/about.log')


def plot_data(trace_name1, trace_name2, analyzis_name, plots_dir):
    font_config = 'Helvetica,15'
    print_header("Plots for:" + sym_name + " using traces " + trace_name1 + ' and ' + trace_name2)
    gp = GnuplotScripts(data_dir=plots_dir, plot_dir=plots_dir, font=font_config, linestyle_1='b-', linestyle_2='r-',
                        linestyle_3='g-', linestyle_4='v-')

    print('Ploting Wavelet Multiresolution Analisis')
    gp.plot_config(xlabel='Time scale j', ylabel='log2(Energy(j))', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2functionxyxy(datafile='WaveletMREA.dat', filename='WaveletMREA')

    print('Ploting Bandwidth')
    gp.plot_config(xlabel='Time(seconds)', ylabel='bps', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2functionxyxy(datafile='Bandwidth.csv', filename='Bandwidth')

    print('Ploting Bandwidth')
    gp.plot_config(xlabel='Time(seconds)', ylabel='bps', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2functionxyxy(datafile='Bandwidth.csv', filename='Bandwidth')

    print('Ploting Flow data (FlowPs and FlowCDF)')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Number of Flows', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2functionxyxy(datafile='FlowsPs.dat ', filename='FlowsPs')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Flow CDF function', legend1=trace_name1, legend2=trace_name2)
    gp.plot_2functionxyxy(datafile='FlowCdf.dat', filename='FlowCdf')


if __name__ == "__main__":
    # input arguments
    pcap_file1 = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + PCAP_FILE1
    pcap_file2 = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + PCAP_FILE2
    sym_name = TEST_NAME

    # making sure the program is being executed in the source location, so it can be executed from anyware
    cd = Cd(os.path.dirname(os.path.abspath(__file__)))
    plots_dir = 'plots/' + sym_name
    test_name = TEST_NAME
    run_analyzis(pcap_file1, pcap_file2, test_name, plots_dir)

# TODO 1: conferir na parte de largura de banda, e adicionar a opção de escala nos dados para se plotar
# TODO 2: fazer os scripts rodarem corretamente... dai eu acabo eles, e só irá faltar o final da implementação