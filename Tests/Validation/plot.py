#!/usr/bin/python3.5
import csv
import argparse
import numpy as np
import matplotlib.pyplot as plt
import math
import sys
import collections
from Utils.Terminal import Terminal as term
from Utils.Csv import Csv
from Utils.Matrix import Matrix
from Config import Config as config


########################################################################################################################
# Utils
########################################################################################################################

def load_csv(datafile=''):
    """
    Load float CSV file into a matrix.
    mtr_float = load_csv(datafile='file.csv')
    :param datafile: CSV file to be loaded
    :return: matrix with the CSV file data
    """
    try:
        with open(datafile) as f:
            lines = (line for line in f if not line.startswith('#'))
            csv_matrix = np.loadtxt(lines, delimiter=',')
        return csv_matrix
    except:
        term.print_color(color="red", data="File {" + datafile + "} not found.")
        sys.exit("File not found")



def load_csv_str(datafile=''):
    """
    Load a String CSV file into a matrix
    :param datafile:
    :return: string matrix with CSV data
    mtr_str = load_csv_str(datafile='file.csv')
    """
    ifile = ""
    try:
        ifile = open(datafile, "rU")
    except:
        term.print_color(color="red", data="File {" + datafile + "} not found.")
        sys.exit("File not found")
    reader = csv.reader(ifile, delimiter=",")
    rownum = 0
    a = []
    for row in reader:
        if len(row) == 0 or row[0][0] == '#':
            continue
        for index in range(0, len(row) - 1):
            row[index] = row[index].strip()
        a.append(row)
        rownum += 1
    ifile.close()
    return a


def column(matrix, i):
    """
    Returns a column of a two dimensional matrix
    mtr_col = column(mtr, 2):
    :param matrix: matrix
    :param i: column index
    :return: vector
    """
    return [row[i] for row in matrix]


def saver_helper(figure_object, file_name="default"):
    """
    Helper for saving figure in many formats
    :param figure_object: object fig
    :param file_name: file name to be saved
    :return: void
    """
    figure_object.savefig(fname=file_name + '.pdf')
    # figure_object.savefig(fname=file_name+'.svg')
    figure_object.savefig(fname=file_name + '.png')
    figure_object.savefig(fname=file_name + '.eps')


def plt_free():
    """
    """
    plt.cla()
    plt.clf()
    plt.close()


def print_info(title="title", location="path-file"):
    """

    :param title:
    :param location:
    :return:
    """
    print("Plotting `{0}` > `{1}`".format(title, location))


########################################################################################################################
# Plot functions
########################################################################################################################

def plot_data1_data2yerr(title, d1_label, d2_label, x_axis_label, y_axis_label,
                         data1_x, data1_y, data2_x, data2_y, data2_yerr,
                         plot_file, plot_dir):
    # plotting
    print_info(title=plot_file, location=plot_dir)
    fig1, ax1 = plt.subplots()
    ax1.plot(data1_x, data1_y, '-x', color="darkblue", label=d1_label, linewidth=3)
    ax1.errorbar(data2_x, data2_y, yerr=data2_yerr, fmt='-o', color="red", label=d2_label, linewidth=3)
    ax1.legend(loc='best')
    plt.xlabel(x_axis_label)
    plt.ylabel(y_axis_label)
    plt.grid(color='black', linestyle=':')
    plt.title(title)
    saver_helper(fig1, file_name=plot_dir + plot_file)
    plt_free()



########################################################################################################################
# Plot scripts
########################################################################################################################

def plot_bandwidth(plot_dir, pcap_name):
    file = plot_dir + "/" + config.fileplot_bandwidth()
    wavelet_csv = Csv.load_csv(datafile=file)
    title = "Bandwidth for " + pcap_name
    d1_label = "original"
    d2_label = "simulated"
    x_axis_label = "Time"
    y_axis_label= "Mbps per second"
    data1_x = Matrix.column(wavelet_csv, 0)
    data1_y = Matrix.column(wavelet_csv, 1)
    data2_x = Matrix.column(wavelet_csv, 2)
    data2_y = Matrix.column(wavelet_csv, 3)
    data2_yerr = Matrix.column(wavelet_csv, 4)
    plot_file = "Bandwidth.plot"
    plot_data1_data2yerr(title=title, d1_label=d1_label, d2_label=d2_label, x_axis_label=x_axis_label,
                         y_axis_label=y_axis_label, data1_x=data1_x, data1_y=data1_y, data2_x=data2_x,
                         data2_y=data2_y, data2_yerr=data2_yerr, plot_file=plot_file,
                         plot_dir=plot_dir)


def plot_flow(plot_dir, pcap_name):
    # load data
    file_flow_cdf = plot_dir + "/" + config.fileplot_flowcdf()
    file_flow_ps = plot_dir + "/" + config.fileplot_flowps()
    m_flow_cdf_csv = Csv.load_csv(datafile=file_flow_cdf)
    m_flow_ps_csv = Csv.load_csv(datafile=file_flow_ps)
    # labels for the plot
    title_cdf = "Flow CDF for " + pcap_name
    y_axis_label_cdf= "Flow CDF"
    title_ps = "Flow per second for " + pcap_name
    y_axis_label_ps = "Flow per second"
    d1_label = "original"
    d2_label = "simulated"
    x_axis_label = "Time"
    # load data
    cdf_data1_x = Matrix.column(m_flow_cdf_csv, 0)
    cdf_data1_y = Matrix.column(m_flow_cdf_csv, 1)
    cdf_data2_x = Matrix.column(m_flow_cdf_csv, 2)
    cdf_data2_y = Matrix.column(m_flow_cdf_csv, 3)
    cdf_data2_yerr = Matrix.column(m_flow_cdf_csv, 4)
    ps_data1_x = Matrix.column(m_flow_ps_csv, 0)
    ps_data1_y = Matrix.column(m_flow_ps_csv, 1)
    ps_data2_x = Matrix.column(m_flow_ps_csv, 2)
    ps_data2_y = Matrix.column(m_flow_ps_csv, 3)
    ps_data2_yerr = Matrix.column(m_flow_ps_csv, 4)
    # plot data
    plot_file_cdf = "FlowsCdf.plot"
    plot_data1_data2yerr(title=title_cdf, d1_label=d1_label, d2_label=d2_label, x_axis_label=x_axis_label,
                         y_axis_label=y_axis_label_cdf, data1_x=cdf_data1_x, data1_y=cdf_data1_y, data2_x=cdf_data2_x,
                         data2_y=cdf_data2_y, data2_yerr=cdf_data2_yerr, plot_file=plot_file_cdf,
                         plot_dir=plot_dir)
    plot_file_ps = "FlowPs.plot"
    plot_data1_data2yerr(title=title_ps, d1_label=d1_label, d2_label=d2_label, x_axis_label=x_axis_label,
                         y_axis_label=y_axis_label_ps, data1_x=ps_data1_x, data1_y=ps_data1_y, data2_x=ps_data2_x,
                         data2_y=ps_data2_y, data2_yerr=ps_data2_yerr, plot_file=plot_file_ps,
                         plot_dir=plot_dir)


def plot_wavelet(plot_dir, pcap_name):
    file = plot_dir + "/" + config.fileplot_wavelet()
    wavelet_csv = Csv.load_csv(datafile=file)
    title = "Wavelet Multiresolution Energy Analizis for " + pcap_name
    d1_label = "original"
    d2_label = "simulated"
    x_axis_label = "resolution"
    y_axis_label= "energy"
    data1_x = Matrix.column(wavelet_csv, 0)
    data1_y = Matrix.column(wavelet_csv, 1)
    data2_x = Matrix.column(wavelet_csv, 2)
    data2_y = Matrix.column(wavelet_csv, 3)
    data2_yerr = Matrix.column(wavelet_csv, 4)
    plot_file = "WaveletMREA.plot"
    plot_data1_data2yerr(title=title, d1_label=d1_label, d2_label=d2_label, x_axis_label=x_axis_label,
                         y_axis_label=y_axis_label, data1_x=data1_x, data1_y=data1_y, data2_x=data2_x,
                         data2_y=data2_y, data2_yerr=data2_yerr, plot_file=plot_file,
                         plot_dir=plot_dir)


def generateHtmlDisplay(plot_dir, simulationName, listFileNames):
    f = open("scripts/display_template.html", "r")
    htmlFile = f.read()
    f.close()
    appendJavascript = 'generateTitle("' + simulationName + '");\n'
    for fname in listFileNames:
        appendJavascript += 'generateImageNode("' + fname + '");\n'
    term.print_color(color="green", data="Generated Javascript: \n" + appendJavascript);
    htmlFile = htmlFile.replace("###AUTO_GENERATED_CODE###", appendJavascript)
    text_file = open(plot_dir+"index.html", "w")
    text_file.write(htmlFile)
    text_file.close()


def validation_plot(plot_dir):
    """
    Do all plots
    :param plot_dir:
    :return:
    """
    pcap_name = config.pcap_name_1
    plot_bandwidth(plot_dir, pcap_name)
    plot_flow(plot_dir, pcap_name)
    plot_wavelet(plot_dir, pcap_name)
    simulationName = plot_dir.replace("/", "").replace("plots", "")
    generateHtmlDisplay(plot_dir=plot_dir, simulationName=simulationName,
                        listFileNames=["Bandwidth.plot", "Bandwidth.plot", "WaveletMREA.plot",
                                       "FlowPs.plot", "FlowsCdf.plot"])


########################################################################################################################
# Help tutorial/tests
########################################################################################################################

def help_menu():
    print("todo")


def run_tests():
    plot_dir = "plots/Abacate-2019-2-13-1-25-25/"
    # validation_plot(plot_dir)
    # pcap_name = "test001"
    # plot_wavelet(plot_dir, pcap_name)
    validation_plot(plot_dir)


########################################################################################################################
# Main
########################################################################################################################

if __name__ == "__main__":
    # arg parser
    parser = argparse.ArgumentParser(description='Run plotter for validation or paper plots')
    parser.add_argument("--validation", type=str, nargs="+",
                        help="Plot the data generated by the validation",
                        required=False)
    parser.add_argument("--paper", action='store_true',
                        help="nothing to do",
                        required=False)

    parser.add_argument("--man", action='store_true', help="Manual", required=False)
    parser.add_argument("--test", action='store_true', help="Run plots being developed", required=False)

    args = vars(parser.parse_args())  # convert parser object to a dictionary
    # args = args = {'paper': False, 'test': True, 'validation': 'plots/skype/', 'test2': None}
    # args = args = {'paper': False, 'paper2': False, 'test': True, 'validation': 'plots/skype/', 'test2': None}
    # args = {"paper": False, "test": True, "validation": None, "man": None}
    if args["validation"]:
        # ./plot.py --validation "./plots/<sim-name>/"
        # ./plot.py --validation "plots/Abacate-2019-2-13-1-25-25/"
        term.print_color(color="green", data='./plots.py --validation "{0}"'.format(args.get("validation")[0]))
        validation_plot(args.get('validation')[0])
    elif args["paper"]:
        # ./plots.py --paper
        term.print_color(color="green", data="./plots.py --paper")
        print("todo")
    elif args["man"]:
        # ./plots.py --help
        term.print_color(color="green", data="./plots.py --man")
        help_menu()
    elif args["test"]:
        # ./plots.py --test
        term.print_color(color="green", data="./plots.py --test")
        run_tests()


