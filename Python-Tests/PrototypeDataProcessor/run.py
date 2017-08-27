import os
import time
from GnuplotScripts.GnuplotScripts import GnuplotScripts
from Cd.Cd import Cd

PCAP_FILE = "../../Pcap/wireshark-wiki_http.pcap"
SIMULATION_NAME = "wombat"


def print_header(title):
    print('')
    print('###############################################################################')
    print('# ' + title)
    print('###############################################################################')


def run_simulations(pcap_file, sym_name, plots_dir):
    print_header("Simulations for:" + sym_name + " using pcap:" + pcap_file)
    # clean sim dir
    cd.cd('./dataProcessor/')
    os.system('rm -rf data/*')
    # filter inter-pacekt times
    os.system('./pcap-filter.sh --time-delta ' + pcap_file + ' ' + sym_name)
    # execute dataProcessor prototype
    os.system('./dataProcessor.m ' + sym_name)
    # calc cost function of each simulation
    os.system('./calcCostFunction.py ' + 'data/')
    # back to working directory
    cd.back()
    # creating plots dir
    os.system('rm -rf ' + plots_dir)
    os.system('mkdir -p ' + plots_dir)
    os.system('mv dataProcessor/data/* ' + plots_dir)
    str_about = 'Simulation:' + sym_name + " using pcap:" + pcap_file
    str_date = '@ ' + str(time.localtime().tm_mday) + '/' + str(time.localtime().tm_mon) + '/' + str(
        time.localtime().tm_year) + '-' + str(time.localtime().tm_hour) + ':' + str(
        time.localtime().tm_min) + ':' + str(time.localtime().tm_sec)
    os.system('echo \"' + str_about + '\" >>' + plots_dir + '/about.log')
    os.system('echo \"' + str_date + '\" >>' + plots_dir + '/about.log')


def plot_data(pcap_file, sym_name, plots_dir):
    font_config = 'Helvetica,15'
    print_header("Plot for:" + sym_name + " using pcap:" + os.path.basename(pcap_file))

    gp = GnuplotScripts(data_dir=plots_dir, plot_dir=plots_dir, font=font_config, linestyle_1='b-', linestyle_2='r-',
                        linestyle_3='g-', linestyle_4='v-')

    print('Plotting empirical CDF of:' + sym_name + ' from pcap:' + os.path.basename(pcap_file))
    gp.plot_config(xlabel='interPacketTime (s)', ylabel='F(interPacketTime)', title='Empirical CDF', type='lines')
    gp.plot_function(filename='Empirical CDF function', datafile='Empirical CDF function.dat')

    print('Plotting empirical Linearizations of:' + sym_name + ' from pcap:' + os.path.basename(pcap_file))
    theTitle = 'Cauchy - Linearized data and linear fitting'
    gp.plot_config(title=theTitle, legend1='linearized data', legend2='linear approximation', linestyle_1='bx',
                   linestyle_2='r-', type='points-lines')
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Weibull - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Exponential - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Pareto - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle + '.dat')

    print('Plotting Cost J(iterations) convergence of:' + sym_name + ' from pcap:' + os.path.basename(pcap_file))
    theTitle = 'Cauchy - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle, ylabel='Cost J(iterations)', xlabel='iterations', type='lines', linestyle_1='g-')
    gp.plot_function(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Weibull - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Exponential - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle + '.dat')
    theTitle = 'Pareto - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle + '.dat')

    print('Plotting correlation, mean, standard deviation and hurst exponent of:' + sym_name +
          ' from pcap:' + os.path.basename(pcap_file))
    theFile = 'Correlation'
    gp.plot_config(title='Correlation with Empirical Data', ylabel='Correlation', xlabel='Stochastic function',
                   legend2='linear approximation', linestyle_1='ro', type='points')
    gp.plot_xtickerror(filename=theFile, datafile=theFile + '.dat')
    theFile = 'Standard Deviation'
    gp.plot_config(title='Correlation with Empirical Data', ylabel='Standard Deviation')
    gp.plot_xtickerror(filename=theFile, datafile=theFile + '.dat')
    theFile = 'Mean'
    gp.plot_config(title='Mean inter packet time', ylabel='Mean')
    gp.plot_xtickerror(filename=theFile, datafile=theFile + '.dat')
    theFile = 'Hurst Exponent'
    gp.plot_config(title='Hurst Exponent of inter packet time', ylabel='Hurst Exponent')
    gp.plot_xtickerror(filename=theFile, datafile=theFile + '.dat')

    print('Plotting Original vs Approximate CDF function of:' + sym_name + ' from pcap:'
          + os.path.basename(pcap_file))
    original_dataset = 'Empirical CDF function.dat'
    gp.plot_config(ylabel='CDF function', xlabel='inter packet time (s)', legend1='aproximation',
                   legend2='empirical', linestyle_1='b-', linestyle_2='r-', type='lines')
    theTitle = 'Cauchy aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Exponential aproximation (linear regression) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Exponential aproximation (mean) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Normal aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Pareto aproximation (linear regression) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Pareto aproximation (maximum likehood) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Weibull aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data(theTitle, theTitle + '.dat', original_dataset)

    print('Plotting Original vs Approximate CDF function of:' + sym_name + ' from pcap:'
          + os.path.basename(pcap_file))
    original_dataset = 'Empirical CDF function.dat'
    gp.plot_config(ylabel='CDF function', xlabel='inter packet time (s)', legend1='aproximation',
                   legend2='empirical', linestyle_1='b-', linestyle_2='r-', type='lines')
    theTitle = 'Cauchy aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Exponential aproximation (linear regression) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Exponential aproximation (mean) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Normal aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Pareto aproximation (linear regression) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Pareto aproximation (maximum likehood) vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)
    theTitle = 'Weibull aproximation vs Original set'
    gp.plot_config(title=theTitle)
    gp.plot_2f2data_log(theTitle, theTitle + '.dat', original_dataset)

    print('Plotting QQplots of:' + sym_name + ' from pcap:'
          + os.path.basename(pcap_file))
    gp.plot_config(ylabel='samples', xlabel='estimated', legend1='QQplot',
                   legend2='rule', linestyle_1='bx', linestyle_2='r-', type='points-lines')
    theTitle = 'QQplot - Cauchy'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Exponential(LR)'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Exponential(Me)'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Normal'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Pareto(LR)'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Pareto(LR)'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')
    theTitle = 'QQplot - Weibull'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(theTitle, theTitle + '.dat')


if __name__ == "__main__":
    # input arguments
    pcap_file = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + PCAP_FILE
    sym_name = SIMULATION_NAME

    # making sure the program is being executed in the source location, so it can be executed from anyware
    cd = Cd(os.path.dirname(os.path.abspath(__file__)))
    plots_dir = 'plots/' + sym_name

    # run simulations
    run_simulations(pcap_file, sym_name, plots_dir)

    # plot data
    plot_data(pcap_file, sym_name, plots_dir)
