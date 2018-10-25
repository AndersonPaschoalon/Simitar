#!/usr/bin/python3
# deps install
# pip3 install matplotlib
import os
import csv
import argparse
import numpy as np
import matplotlib.pyplot as plt


########################################################################################################################
# Plot Utilsfunctions
########################################################################################################################

def print_header(title):
    """

    :param title:
    :return:
    """
    print("")
    print("################################################################################")
    print("# "+str(title))
    print("################################################################################")

def table2csv(filename):
    """
    Convert a ASCII table to CSV format
    :param filename:
    :return:
    """
    cmd = "cat {0} |sed 's/\(^|\)\|\(^+\(-\|+\)*\)\|\(|$\)//g' |sed 's/Function/#Function/g' |sed 's/|/,/g'  |sed 's/[[:blank:]]//g' |sed '/^$/d' | awk 'BEGIN{{print(\"# AIC and BIC values\")}}{{print $0}}' > {0}.csv"
    cmd = cmd.format(filename)
    os.system(cmd)


def load_csv(datafile=''):
    """
    Load float CSV file into a matrix.
    mtr_float = load_csv(datafile='file.csv')
    :param datafile: CSV file to be loaded
    :return: matrix with the CSV file data
    """
    with open(datafile) as f:
        lines = (line for line in f if not line.startswith('#'))
        csv_matrix = np.loadtxt(lines, delimiter=',')
    return csv_matrix


def load_csv_str(datafile=''):
    """
    Load a String CSV file into a matrix
    :param datafile:
    :return: string matrix with CSV data
    mtr_str = load_csv_str(datafile='file.csv')
    """
    ifile = open(datafile, "rU")
    reader = csv.reader(ifile, delimiter=",")
    rownum = 0
    a = []
    for row in reader:
        if(len(row)==0 or row[0][0]=='#'):
            continue
        for index in range(0, len(row)-1):
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


def order_matrix(mtr, n_column):
    """
    Order the matrix according to the column n
    m_ordered = order_matrix(m, 1)
    :param mtr:
    :param n_column:
    :return:
    """
    """
    col_str = column(mtr, n_column)
    col_float = [float(i) for i in col_str]
    col_float = sorted(col_float)
    mtr_out = []
    for i in range(0, len(col_float)):
        for j in range(0, len(col_float)):
            if float(mtr[j][n_column]) == col_float[i]:
                mtr_out.append(mtr[j])
    return mtr_out
    """
    mtr = sorted(mtr, key=lambda mtr: float(mtr[n_column]))
    return mtr


def test_order_matrix():
    """
    #
    :return:
    """
    m = [['abacaxi', '3', '5', '6', '7', '7'], ['banana', '0', '4', '5', '6', '7'],
         ['caqui', '1', '3', '4', '5', '6'], ['damasco', '7', '14', '15', '16', '17'],
         ['damasco', '7', '14', '15', '16', '17'], ['caqui', '7', '14', '15', '16', '17'],
         ['figo', '2', '99', '98', '97', '96'], ['goiaba', '9', '10', '11', '12', '13']]
    m_ordered = order_matrix(m, 1)
    print(m_ordered)


def order_matrix_str(mtr, n_column):
    """
    Order the matrix according to the column n
    m_ordered = order_matrix(m, 1)
    :param mtr:
    :param n_column:
    :return:
    """
    col_str = sorted(column(mtr, n_column))
    mtr_out = []
    for i in range(0, len(col_str)):
        for j in range(0, len(col_str)):
            if mtr[j][n_column]==col_str[i]:
                mtr_out.append(mtr[j])
    return mtr_out


def test_order_matrix_str():
    """
    #
    :return:
    """
    mtr = [['pera', '1', '2', '3'], ['uva', '3', '4', '5'],
          ['abacaxi', '7', '6', '5'], ['banana', 'd', 'f', 'g']]
    mtr = order_matrix_str(mtr, 0)
    print(mtr)


def get_mtr_position(mtr, model):
    """
    Return the position of the model
    :param mtr:
    :param model:
    :return:
    """
    pos = -1
    for i in range(0, len(mtr)):
        if model == mtr[i][0]:
            pos=i
            break
    return pos


def test_get_mtr_position():
    """
    #
    :return:
    """
    m = [['banana', '0', '4', '5', '6', '7'],
         ['caqui', '1', '3', '4', '5', '6'],
         ['figo', '2', '99', '98', '97', '96'],
         ['abacaxi', '3', '5', '6', '7', '7'],
         ['damasco', '7', '14', '15', '16', '17'],
         ['goiaba', '9', '10', '11', '12', '13']]
    pos = get_mtr_position(m, 'damasco')
    print('pos='+str(pos))


def calc_relative_position_rank_diff(mtr_costfunction, mtr_aicbic):
    """
    #
    :param mtr_costfunction:
    :param mtr_aicbic:
    :return:
    """
    mtr_costfunction = order_matrix(mtr_costfunction, 1)
    mtr_aicbic = order_matrix(mtr_aicbic, 1)
    #print("    Cost Function=" + str(mtr_costfunction))
    #print("    Aic/BIC="+ str(mtr_aicbic))
    vet_relative_rank_diff = []
    for i in range(0, len(mtr_costfunction)):
        model = mtr_costfunction[i][0]
        pos_costfunction = get_mtr_position(mtr_costfunction, model)
        pos_aicbic = get_mtr_position(mtr_aicbic, model)
        vet_relative_rank_diff.append(pos_costfunction - pos_aicbic)
        #print("model:"+model + ", pos_costfunction:"+str(pos_costfunction)+ ", pos_aicbic:"+str(pos_aicbic))
    return vet_relative_rank_diff


def test_calc_relative_position_rank_diff():
    """
    #
    :return:
    """
    # banana, caqui, figo, abacaxi, damasco, goiaba
    m1 = [['banana', '0', '4', '5', '6', '7'],
          ['caqui', '1', '3', '4', '5', '6'],
          ['figo', '2', '99', '98', '97', '96'],
          ['abacaxi', '3', '5', '6', '7', '7'],
          ['damasco', '7', '14', '15', '16', '17'],
          ['goiaba', '9', '10', '11', '12', '13']]
    # banana, figo, caqui, goiaba, abacaxi, damasco
    m2 = [['figo', '0', '4', '5', '6', '7'], ['caqui', '3', '3', '4', '5', '6'],
          ['banana', '-2', '99', '98', '97', '96'],
          ['abacaxi', '5', '5', '6', '7', '7'],
          ['damasco', '7', '14', '15', '16', '17'],
          ['goiaba', '4', '10', '11', '12', '13']]
    # expected : 0, -1, 1, -1, -1, 2
    vet_relative_rank_diff = calc_relative_position_rank_diff(m1, m2)
    print(vet_relative_rank_diff)


def plotter_helper(ax, data1, data2, fmt, param_dict="", legend=True):
    """
    A helper function to make a graph
    :param ax: The axes to draw to
    :param data1: The x data
    :param data2: The y data
    :param fmt : plot format
    :param param_dict:
    :return: Dictionary of kwargs to pass to ax.plot
    """
    out = ax.plot()
    if param_dict=="":
        out = ax.plot(data1, data2, fmt)
    else:
        out = ax.plot(data1, data2, fmt, **param_dict)
    if legend:
        ax.legend()
    return out


def errorbar_helper(ax, xdata, ydata, yerror, param_dict, legend=True):
    """
    #
    :param ax: AxesSubplot object
    :param xdata: x data
    :param ydata: y data
    :param yerror: vertical errorbar
    :param param_dict: list of plot parameters
    :param legend:
    :return:
    """
    out = ax.errorbar(xdata, ydata, yerror, **param_dict)
    if legend: ax.legend()
    return out


def saver_helper(figure_object, file_name="default"):
    """
    Helper for saving figure in many formats
    :param figure_object: object fig
    :param file_name: file name to be saved
    :return: void
    """
    figure_object.savefig(fname=file_name+'.pdf')
    #figure_object.savefig(fname=file_name+'.svg')
    figure_object.savefig(fname=file_name+'.png')
    figure_object.savefig(fname=file_name+'.eps')


def plt_free(figure_object):
    """
    #
    :param figure_object:
    :return:
    """
    figure_object.clf()
    figure_object.close()


def test_saver_helper():
    """
    #
    :return:
    """
    os.system('mkdir -p test')
    data1, data2, data3, data4 = np.random.randn(4, 100)
    fig, ax = plt.subplots(1, 1)
    plotter_helper(ax, data1, data2, param_dict=dict(color='green', marker='v'))
    plotter_helper(ax, 0.5*data1, 1.5*data2, param_dict=dict(marker='^', color='cyan', label='quadratic'))
    ax.legend(dict(loc='best', fancyvox=True, shadow=True))
    plt.title('Sample title')
    plt.grid()
    saver_helper(fig, file_name="test/dispersion")


########################################################################################################################
# plot scrits
########################################################################################################################


def plot_cdf_fitting(plot_dir, fitting_data, original_datafile, plot_title, plot_file):
    """
    #
    :param plot_dir:
    :param fitting_data:
    :param original_datafile:
    :param plot_title:
    :param plot_file:
    :return:
    """
    PLOT_DIR=plot_dir
    # load data
    original_data = load_csv(datafile=PLOT_DIR+original_datafile)
    fitting_data = load_csv(datafile=PLOT_DIR+fitting_data)
    ox = column(original_data, 0)
    oy = column(original_data, 1)
    fx = column(fitting_data, 0)
    fy = column(fitting_data, 1)
    olabel = "empirical"
    flabel = "approximation"
    xlabel = "Inter packet time (s)"
    ylabel = "CDF function"
    # plotting
    print("Plotting "+plot_file+" > "+plot_dir)
    fig1, ax1 = plt.subplots()
    ax1.plot(ox, oy, 'r-', label=olabel, linewidth=2)
    ax1.plot(fx, fy, '-.', color="darkblue", label=flabel, linewidth=2.5)
    ax1.legend(loc='lower right')
    plt.xlim([-0.1, 10])
    plt.ylim([0, 1.01])
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(color='black', linestyle=':')
    plt.title(plot_title)
    saver_helper(fig1, file_name=plot_dir+"Linear - "+plot_file)
    fig2, ax2 = plt.subplots()
    ax2.plot(ox, oy, 'r-', label=olabel, linewidth=2)
    ax2.plot(fx, fy, '-.', color="darkblue", label=flabel, linewidth=2.5)
    ax2.legend(loc='upper left')
    plt.semilogx()
    plt.ylim([0, 1.01])
    plt.grid(color='black', linestyle=':')
    plt.title(plot_title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    saver_helper(fig2, file_name=plot_dir+"Log - "+plot_file)
    plt_free(plt)


def plot_linear_regression(plot_dir, datafile, plot_title, plot_file):
    """
    #
    :param plot_dir:
    :param datafile:
    :param plot_title:
    :param plot_file:
    :return:
    """
    # load data
    original_data = load_csv(datafile=plot_dir+datafile)
    fitting_data = load_csv(datafile=plot_dir+datafile)
    lx = column(original_data, 0)
    ly = column(original_data, 1)
    ax = column(fitting_data, 2)
    ay = column(fitting_data, 3)
    llabel = "linearized data"
    alabel = "linear approximation"
    xlabel = "interPacketTime (s)"
    ylabel = "F(interPacketTime)"
    # plotting
    print("Plotting: `"+datafile+"` > "+plot_dir)
    fig1, ax1 = plt.subplots()
    ax1.plot(lx, ly, 'x', color="darkblue", label=llabel, linewidth=3)
    ax1.plot(ax, ay, 'r-', label=alabel, linewidth=3)
    ax1.legend(loc='best')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(color='black', linestyle=':')
    plt.title(plot_title)
    saver_helper(fig1, file_name=plot_dir+plot_file)
    plt_free(plt)


def plot_cost_history(plot_dir, datafile, plot_title, plot_file):
    """
    #
    :param plot_dir:
    :param datafile:
    :param plot_title:
    :param plot_file:
    :return:
    """
    # load data
    original_data = load_csv(datafile=plot_dir+datafile)
    x = column(original_data, 0)
    y = column(original_data, 1)
    xlabel = "iterations"
    ylabel = "Cost J(iterations)"
    # plotting
    print("Plotting "+plot_file+" > "+plot_dir)
    fig1, ax1 = plt.subplots()
    ax1.plot(x, y, 'g-', linewidth=2)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(color='black', linestyle=':')
    plt.title(plot_title)
    saver_helper(fig1, file_name=plot_dir+plot_file)
    plt_free(plt)


def qqplot(plot_dir, datafile, plot_title, plot_file):
    """
    #
    :param plot_dir:
    :param datafile:
    :param plot_title:
    :param plot_file:
    :return:
    """
    # load data
    original_data = load_csv(datafile=plot_dir+datafile)
    fitting_data = load_csv(datafile=plot_dir+datafile)
    lx = column(original_data, 0)
    ly = column(original_data, 1)
    ax = column(fitting_data, 2)
    ay = column(fitting_data, 3)
    llabel = "QQplot"
    alabel = "linear"
    xlabel = "estimated"
    ylabel = "samples"
    # plotting
    print("Plotting: `"+datafile+"` > "+plot_dir)
    fig1, ax1 = plt.subplots()
    ax1.plot(lx, ly, 'o', color="darkblue", label=llabel, linewidth=3)
    ax1.plot(ax, ay, 'r-', label=alabel, linewidth=2)
    ax1.legend(loc='best')
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(color='black', linestyle=':')
    plt.title(plot_title)
    saver_helper(fig1, file_name=plot_dir+plot_file)
    plt_free(plt)


def plot_correlation(plot_dir, datafile, title, plotfile):
    """
    #
    :param plot_dir:
    :param datafile:
    :param title:
    :param plotfile:
    :return:
    """
    # load hurst data
    hustdata = load_csv_str(datafile=plot_dir+datafile)
    bars1 = [float(number) for number in column(hustdata, 1)]
    yer1 = [float(number) for number in column(hustdata, 2)]
    xticks = column(hustdata, 0)
    hline = 1
    # width of the bars
    bar_width = 0.3
    ylabel = 'Correlation'
    # plotting
    print("Plotting: `"+datafile+"` > "+plot_dir)
    xpos = np.arange(len(bars1))
    fig, ax = plt.subplots()
    ax.bar(xpos, bars1, width=bar_width, color='yellow', edgecolor='black', yerr=yer1, capsize=7)
    plt.axhline(hline, color="red")
    plt.xticks(xpos, xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.tight_layout()
    saver_helper(fig, file_name=plot_dir+plotfile)
    plt_free(plt)


def plot_hurst(plot_dir, datafile, title, plotfile):
    """
    #
    :param plot_dir:
    :param datafile:
    :param title:
    :param plotfile:
    :return:
    """
    # load hurst data
    hustdata = load_csv_str(datafile=plot_dir+datafile)
    bars1 = [float(number) for number in column(hustdata, 1)]
    yer1 = [float(number) for number in column(hustdata, 2)]
    xticks = column(hustdata, 0)
    # filter data
    hline = bars1[0]
    bars1 = bars1[1:]
    yer1 = yer1[1:]
    xticks = xticks[1:]
    # width of the bars
    bar_width = 0.3
    ylabel = 'Hurst Exponent'
    print("Plotting: `" + datafile + "` > " + plot_dir)
    xpos = np.arange(len(bars1))
    fig, ax = plt.subplots()
    ax.bar(xpos, bars1, width=bar_width, color='cyan', edgecolor='black', yerr=yer1, capsize=7)
    ax.text(1.02, hline, str(hline), va='center', ha="left", bbox=dict(facecolor="w", alpha=0.5),
            transform=ax.get_yaxis_transform())
    plt.axhline(hline, color="red")
    plt.xticks(xpos, xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.tight_layout()
    saver_helper(fig, file_name=plot_dir+plotfile)
    plt_free(plt)


def plot_std_dev(plot_dir, datafile, title, plotfile):
    """
    #
    :param plot_dir:
    :param datafile:
    :param title:
    :param plotfile:
    :return:
    """
    # load hurst data
    hustdata = load_csv_str(datafile=plot_dir+datafile)
    bars1 = [float(number) for number in column(hustdata, 1)]
    yer1 = [float(number) for number in column(hustdata, 2)]
    xticks = column(hustdata, 0)
    # filter data
    hline = bars1[0]
    bars1 = bars1[1:]
    yer1 = yer1[1:]
    xticks = xticks[1:]
    # width of the bars
    bar_width = 0.3
    ylabel = 'Standard Deviation'
    print("Plotting: `" + datafile + "` > " + plot_dir)
    xpos = np.arange(len(bars1))
    fig, ax = plt.subplots()
    ax.bar(xpos, bars1, width=bar_width, color='lime', edgecolor='black', yerr=yer1, capsize=7)
    ax.text(1.02, hline, str(hline), va='center', ha="left", bbox=dict(facecolor="w", alpha=0.5),
            transform=ax.get_yaxis_transform())
    plt.axhline(hline, color="red")
    plt.xticks(xpos, xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.tight_layout()
    saver_helper(fig, file_name=plot_dir+plotfile)
    plt_free(plt)


def plot_mean(plot_dir, datafile, title, plotfile):
    """
    #
    :param plot_dir:
    :param datafile:
    :param title:
    :param plotfile:
    :return:
    """
    # load hurst data
    hustdata = load_csv_str(datafile=plot_dir+datafile)
    bars1 = [float(number) for number in column(hustdata, 1)]
    yer1 = [float(number) for number in column(hustdata, 2)]
    xticks = column(hustdata, 0)
    # filter data
    hline = bars1[0]
    bars1 = bars1[1:]
    yer1 = yer1[1:]
    xticks = xticks[1:]
    # width of the bars
    bar_width = 0.3
    ylabel = 'Avarage inter-packet time'
    print("Plotting: `" + datafile + "` > " + plot_dir)
    xpos = np.arange(len(bars1))
    fig, ax = plt.subplots()
    ax.bar(xpos, bars1, width=bar_width, color='magenta', edgecolor='black', yerr=yer1, capsize=7)
    ax.text(1.02, hline, str(hline), va='center', ha="left", bbox=dict(facecolor="w", alpha=0.5),
            transform=ax.get_yaxis_transform())
    plt.axhline(hline, color="red")
    plt.xticks(xpos, xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.tight_layout()
    saver_helper(fig, file_name=plot_dir+plotfile)
    plt_free(plt)


def plot_cost_function(plot_dir, datafile, title, plotfile):
    """
    #
    :param plot_dir:
    :param datafile:
    :param title:
    :param plotfile:
    :return:
    """
    # load hurst data
    hustdata = load_csv_str(datafile=plot_dir+datafile)
    bars1 = [float(number) for number in column(hustdata, 1)]
    xticks = column(hustdata, 0)
    bar_width = 0.3
    ylabel = 'Correlation'
    print("Plotting: `" + datafile + "` > " + plot_dir)
    # The x position of bars
    xpos = np.arange(len(bars1))
    fig, ax = plt.subplots()
    # Create
    ax.bar(xpos, bars1, width=bar_width, color='purple', edgecolor='black', capsize=7)
    plt.xticks(xpos, xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.tight_layout()
    saver_helper(fig, file_name=plot_dir+plotfile)
    plt_free(plt)


def plot_cost_function_all(costfunction1="", costfunction2="", costfunction3="", costfunction4="",
                           pcapname1="", pcapname2="", pcapname3="", pcapname4="",
                           title="title", plotfile="plotfile"):
    """
    #
    :param costfunction1:
    :param costfunction2:
    :param costfunction3:
    :param costfunction4:
    :param pcapname1:
    :param pcapname2:
    :param pcapname3:
    :param pcapname4:
    :param title:
    :param plotfile:
    :return:
    """
    costfunction_data1 = order_matrix_str(load_csv_str(datafile=costfunction1), 0)
    costfunction_data2 = order_matrix_str(load_csv_str(datafile=costfunction2), 0)
    costfunction_data3 = order_matrix_str(load_csv_str(datafile=costfunction3), 0)
    costfunction_data4 = order_matrix_str(load_csv_str(datafile=costfunction4), 0)
    bars1 = [float(i) for i in column(costfunction_data1, 1)]
    bars2 = [float(i) for i in column(costfunction_data2, 1)]
    bars3 = [float(i) for i in column(costfunction_data3, 1)]
    bars4 = [float(i) for i in column(costfunction_data4, 1)]
    xticks = column(costfunction_data1, 0)
    bar_width = 0.2
    ylabel = 'Cost Function'
    bar1label = pcapname1
    bar2label = pcapname2
    bar3label = pcapname3
    bar4label = pcapname4
    # The x position of bars
    r1 = np.arange(len(bars1))
    r2 = [x + bar_width for x in r1]
    r3 = [x + 2*bar_width for x in r1]
    r4 = [x + 3*bar_width for x in r1]
    fig, ax = plt.subplots()
    # Create blue bars
    ax.bar(r1, bars1, width=bar_width, color='springgreen', edgecolor='black', capsize=7, label=bar1label)
    # Create cyan bars
    ax.bar(r2, bars2, width=bar_width, color='fuchsia', edgecolor='black', capsize=7, label=bar2label)
    ax.bar(r3, bars3, width=bar_width, color='mediumblue', edgecolor='black', capsize=7, label=bar3label)
    ax.bar(r4, bars4, width=bar_width, color='gold', edgecolor='black', capsize=7, label=bar4label)
    ax.text(1.02, 6, "6", va='center', ha="left", bbox=dict(facecolor="w", alpha=0.5),
             transform=ax.get_yaxis_transform())
    plt.xticks([r + bar_width for r in range(len(bars1))], xticks, rotation=45)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    saver_helper(fig, file_name=plotfile)
    plt_free(plt)


def plot_cost_function_all_pcap():
    """
    #
    :param costfunction1:
    :param costfunction2:
    :param costfunction3:
    :param costfunction4:
    :param pcapname1:
    :param pcapname2:
    :param pcapname3:
    :param pcapname4:
    :param title:
    :param plotfile:
    :return:
    """
    PLOT_DIR = "./plots/"
    costfunction1 = PLOT_DIR + "skype/costFunction.dat"
    pcaptitle1 = "skype"
    costfunction2 = PLOT_DIR + "bigFlows/costFunction.dat"
    pcaptitle2 = "lan gateway"
    costfunction3 = PLOT_DIR + "lanDiurnal2/costFunction.dat"
    pcaptitle3 = "lan firewall diurnal"
    costfunction4 = PLOT_DIR + "equinix-1s/costFunction.dat"
    pcaptitle4 = "wan"
    costfunction_data1 = order_matrix(load_csv_str(datafile=costfunction1), 1)
    costfunction_data2 = order_matrix(load_csv_str(datafile=costfunction2), 1)
    costfunction_data3 = order_matrix(load_csv_str(datafile=costfunction3), 1)
    costfunction_data4 = order_matrix(load_csv_str(datafile=costfunction4), 1)
    data1 = create_plot_data_costfunction(costfunction_data1)
    data2 = create_plot_data_costfunction(costfunction_data2)
    data3 = create_plot_data_costfunction(costfunction_data3)
    data4 = create_plot_data_costfunction(costfunction_data4)
    print(data1)
    print(data2)
    print(data3)
    print(data4)

    fig, axs = plt.subplots(nrows=2, ncols=2, sharex=True)

    ax00 = axs[0][0].bar(column(data1, 0), column(data1, 1))
    ax10 = axs[1][0].bar(column(data2, 0), column(data2, 1))
    ax01 = axs[0][1].bar(column(data3, 0), column(data3, 1))
    ax11 = axs[1][1].bar(column(data4, 0), column(data4, 1))
    ax11.plt.tight_layout(45)
    ax11.set_horizontalalignment("right")
    #plt.rotation = 45
    for i in range(0, len(ax00)):
        ax00[i].set_color(column(data1, 2)[i])
        ax10[i].set_color(column(data2, 2)[i])
        ax01[i].set_color(column(data3, 2)[i])
        ax11[i].set_color(column(data4, 2)[i])


   # for label in axs[0][0].get_xmajorticklabels() + axs[0][1].get_xmajorticklabels() + \
   #         axs[1][0].get_xmajorticklabels() + axs[1][1].get_xmajorticklabels():
    #    label.set_rotation(45)
     #   label.set_horizontalalignment("right")

    #ax00[0].set_color('r')
    # ax.bar([1,2,3,4], [1,2,3,4])
    plt.tight_layout()
    plt.show()
    print(costfunction_data1)
    print(costfunction_data2)
    print(costfunction_data3)
    print(costfunction_data4)

def map_model_color(model):
    color = "white"
    if model == "Cauchy":
        color = "red"
    elif model == "Exponential(LR)":
        color = "dodgerblue"
    elif model == "Exponential(Me)":
        color = "yellow"
    elif model == "Normal":
        color = "blue"
    elif model == "Pareto(LR)":
        color = "limegreen"
    elif model == "Pareto(MLH)":
        color = "deeppink"
    elif model == "Weibull":
        color = "indigo"
    else:
        print("Error, model not found: "+str(model))
    return color


def create_plot_data_costfunction(costfunction_vector):
    data_vector = []
    for i in range (0, len(costfunction_vector)):
        data1 = []
        data1.append(costfunction_vector[i][0])
        data1.append(float(costfunction_vector[i][1]))
        data1.append(map_model_color(costfunction_vector[i][0]))
        data_vector.append(data1)
    return data_vector

def test_plot_cost_function_all():
    """
    #
    :return:
    """
    PLOT_DIR = "./plots/skype/"
    plot_cost_function_all(costfunction1=PLOT_DIR + "costFunction1.dat", costfunction2=PLOT_DIR + "costFunction1.dat",
                           costfunction3=PLOT_DIR + "costFunction1.dat", costfunction4=PLOT_DIR + "costFunction1.dat",
                           pcapname1="pcaptitle1", pcapname2="pcaptitle1",
                           pcapname3="pcaptitle1", pcapname4="pcaptitle1",
                           title="title-example", plotfile="plotfile-all-functions")


def plot_costfunction_vs_aicbic(aicbic1, costfunction1, pcaptitle1,
                                aicbic2, costfunction2, pcaptitle2,
                                aicbic3, costfunction3, pcaptitle3,
                                aicbic4, costfunction4, pcaptitle4,
                                title, plotfile):
    """
    Plots the relative difference between the model accuracy order of the cost
    function and AIC/BIC order of model selection
    :param aicbic1:
    :param costfunction1:
    :param pcaptitle1:
    :param aicbic2:
    :param costfunction2:
    :param pcaptitle2:
    :param aicbic3:
    :param costfunction3:
    :param pcaptitle3:
    :param aicbic4:
    :param costfunction4:
    :param pcaptitle4:
    :param title:
    :param plotfile:
    :return:
    """
    # create AIC and BIC csv file
    table2csv(aicbic1)
    table2csv(aicbic2)
    table2csv(aicbic3)
    table2csv(aicbic4)
    aicbic_data1 = load_csv_str(datafile=aicbic1+'.csv')
    aicbic_data2 = load_csv_str(datafile=aicbic2+'.csv')
    aicbic_data3 = load_csv_str(datafile=aicbic3+'.csv')
    aicbic_data4 = load_csv_str(datafile=aicbic4+'.csv')
    costfunction_data1 = load_csv_str(datafile=costfunction1)
    costfunction_data2 = load_csv_str(datafile=costfunction2)
    costfunction_data3 = load_csv_str(datafile=costfunction3)
    costfunction_data4 = load_csv_str(datafile=costfunction4)
    # plot
    #print("* " + pcaptitle1)


    bars1 = calc_relative_position_rank_diff(costfunction_data1, aicbic_data1)
    #print("* " + pcaptitle2)
    bars2 = calc_relative_position_rank_diff(costfunction_data2, aicbic_data2)
    #print("* " + pcaptitle3)
    bars3 = calc_relative_position_rank_diff(costfunction_data3, aicbic_data3)
    #print("* " + pcaptitle4)
    bars4 = calc_relative_position_rank_diff(costfunction_data4, aicbic_data4)
    # Horizontal line
    hline1 = len(costfunction_data4)/2
    hline2 = -hline1
    xticks = ['0', '1', '2', '3', '4', '5', '6']
    bar_width = 0.2
    ylabel = 'height'
    bar1label = pcaptitle1
    bar2label = pcaptitle2
    bar3label = pcaptitle3
    bar4label = pcaptitle4
    # The x position of bars
    r1 = np.arange(len(bars1))
    r2 = [x + bar_width for x in r1]
    r3 = [x + 2*bar_width for x in r1]
    r4 = [x + 3*bar_width for x in r1]
    fig, ax = plt.subplots()
    # Create blue bars
    print('r2='+str(len(r2)))
    print('bars2='+str(len(bars2)))
    print(bars2)
    ax.bar(r1, bars1, width=bar_width, color='springgreen', edgecolor='black', capsize=7, label=bar1label)
    ax.bar(r2, bars2, width=bar_width, color='fuchsia', edgecolor='black', capsize=7, label=bar2label)
    ax.bar(r3, bars3, width=bar_width, color='mediumblue', edgecolor='black', capsize=7, label=bar3label)
    ax.bar(r4, bars4, width=bar_width, color='gold', edgecolor='black', capsize=7, label=bar4label)
    #ax.text(1.02, 6, "6", va='center', ha="left", bbox=dict(facecolor="w", alpha=0.5),
    #         transform=ax.get_yaxis_transform())
    # create hline
    plt.axhline(hline1, color="red")
    plt.axhline(hline2, color="red")
    # general layout
    plt.xticks([r + bar_width for r in range(len(bars1))], xticks)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    saver_helper(fig, file_name=plotfile)
    plt_free(plt)


def test_plot_costfunction_vs_aicbic():
    """
    #
    """
    PLOT_DIR = "./plots/skype/"
    plot_costfunction_vs_aicbic(PLOT_DIR + "Aic-Bic1.dat", PLOT_DIR + "costFunction1.dat", "pcaptitle1",
                                PLOT_DIR + "Aic-Bic2.dat", PLOT_DIR + "costFunction2.dat", "pcaptitle2",
                                PLOT_DIR + "Aic-Bic3.dat", PLOT_DIR + "costFunction3.dat", "pcaptitle3",
                                PLOT_DIR + "Aic-Bic4.dat", PLOT_DIR + "costFunction4.dat", "pcaptitle4",
                                "title", "plotfile")


def dataprocessor_simulation_plot(plot_dir):
    """
    #
    :param plot_dir:
    :return:
    """
    PLOT_DIR=plot_dir
    # Plot CDF fitting
    print_header("Plot CDF fitting")
    # Weibull
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Weibull aproximation vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Weibull aproximation vs Original set",
                     plot_file="Weibull aproximation vs Original set")
    # Exponential (LR)
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Exponential aproximation (linear regression) vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Exponential aproximation (linear regression) vs Original set",
                     plot_file="Exponential aproximation (linear regression) vs Original set")
    # Exponential (Me)
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Exponential aproximation (mean) vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Exponential aproximation (mean) vs Original set",
                     plot_file="Exponential aproximation (mean) vs Original set")
    # Normal
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Normal aproximation vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Normal aproximation vs Original set",
                     plot_file="Normal aproximation vs Original set")
    # Pareto (LR)
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Weibull aproximation vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Weibull aproximation vs Original set",
                     plot_file="Weibull aproximation vs Original set")
    # Pareto (MLH)
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Pareto aproximation (maximum likehood) vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Pareto aproximation (maximum likehood) vs Original set",
                     plot_file="Pareto aproximation (maximum likehood) vs Original set")
    # Cauchy
    plot_cdf_fitting(plot_dir=PLOT_DIR, fitting_data="Cauchy aproximation vs Original set.dat",
                     original_datafile="Empirical CDF function.dat",
                     plot_title="Cauchy aproximation vs Original set",
                     plot_file="Cauchy aproximation vs Original set")

    print_header("Plot Linear Regression graphs")
    # Weibull
    plot_linear_regression(plot_dir=PLOT_DIR, datafile="Weibull - Linearized data and linear fitting.dat",
                           plot_title="Weibull - Linearized data and linear fitting",
                           plot_file="Weibull - Linearized data and linear fitting")
    plot_cost_history(plot_dir=PLOT_DIR, datafile="Weibull - Cost J(iterations) convergence.dat",
                      plot_title="Weibull: Linear Regression Cost History",
                      plot_file="Weibull - Cost J(iterations) convergence")
    # Exponential (LR)
    plot_linear_regression(plot_dir=PLOT_DIR, datafile="Exponential - Linearized data and linear fitting.dat",
                           plot_title="Exponential - Linearized data and linear fitting",
                           plot_file="Exponential - Linearized data and linear fitting")
    plot_cost_history(plot_dir=PLOT_DIR, datafile="Exponential - Cost J(iterations) convergence.dat",
                      plot_title="Exponential: Linear Regression Cost History",
                      plot_file="Exponential - Cost J(iterations) convergence")
    # Pareto (LR)
    plot_linear_regression(plot_dir=PLOT_DIR, datafile="Pareto - Linearized data and linear fitting.dat",
                           plot_title="Pareto: Linearized data and linear fitting",
                           plot_file="Pareto - Linearized data and linear fitting.dat")
    plot_cost_history(plot_dir=PLOT_DIR, datafile="Pareto - Cost J(iterations) convergence.dat",
                      plot_title="Pareto: Linear Regression Cost History",
                      plot_file="Pareto - Cost J(iterations) convergence")
    # Cauchy
    plot_linear_regression(plot_dir=PLOT_DIR, datafile="Pareto - Linearized data and linear fitting.dat",
                           plot_title="Pareto: Linearized data and linear fitting",
                           plot_file="Pareto - Linearized data and linear fitting.dat")
    plot_cost_history(plot_dir=PLOT_DIR, datafile="Cauchy - Linearized data and linear fitting.dat",
                      plot_title="Cauchy: Linear Regression Cost History",
                      plot_file="Cauchy - Linearized data and linear fitting")
    # Plot QQplots
    print_header("Plot QQplots")
    # Weibull
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Weibull.dat", plot_title="QQplot - Weibull",
           plot_file="QQplot - Weibull")
    # Exponential (LR)
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Exponential(LR).dat", plot_title="QQplot - Exponential(LR)",
           plot_file="QQplot - Exponential(LR)")
    # Exponential (Me)
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Exponential(Me).dat", plot_title="QQplot - Exponential(Me)",
           plot_file="QQplot - Exponential(Me)")
    # Normal
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Normal.dat", plot_title="QQplot - Normal",
           plot_file="QQplot - Normal")
    # Pareto (LR)
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Pareto(LR).dat", plot_title="QQplot - Pareto(LR)",
           plot_file="QQplot - Pareto(LR)")
    # Pareto (MLH)
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Pareto(MLH).dat", plot_title="QQplot - Pareto(MLH)",
           plot_file="QQplot - Pareto(MLH)")
    # Cauchy
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Cauchy.dat", plot_title="QQplot - Cauchy",
           plot_file="QQplot - Cauchy")
    # Model Evaluation Plots
    print_header("Model Evaluation Plots")
    plot_hurst(PLOT_DIR, 'Hurst Exponent.dat', 'Hurst Exponent', 'Hurst Exponent')
    plot_mean(PLOT_DIR, 'Mean.dat', 'Avarage inter-packet time', 'Mean')
    plot_std_dev(PLOT_DIR, 'Standard Deviation.dat', 'Standard Deviation', 'Standard Deviation')
    plot_correlation(PLOT_DIR, 'Correlation.dat', 'Correlation', 'Correlation')
    plot_cost_function(PLOT_DIR, 'costFunction.dat', 'Cost Function', 'costFunction')


def paper_aicbic_plots():
    """
    #
    """
    PLOT_DIR = "./plots/"
    os.system("mkdir -p "+PLOT_DIR+'paper/')
    costfunction1 = "skype/costFunction.dat"
    pcaptitle1 = "skype"
    costfunction2 = "bigFlows/costFunction.dat"
    pcaptitle2 = "lan gateway"
    costfunction3 = "lanDiurnal/costFunction.dat"
    pcaptitle3 = "lan firewall diurnal"
    costfunction4 = "equinix-1s/costFunction.dat"
    pcaptitle4 = "wan"
    plot_cost_function_all(costfunction1=PLOT_DIR + costfunction1, costfunction2=PLOT_DIR + costfunction2,
                           costfunction3=PLOT_DIR + costfunction3, costfunction4=PLOT_DIR + costfunction4,
                           pcapname1=pcaptitle1, pcapname2=pcaptitle2, pcapname3=pcaptitle3,
                           pcapname4=pcaptitle4, title="AIC and BIC summary", plotfile=PLOT_DIR + "paper/aic-bic-summary")
    aicbic1 = "skype/Aic-Bic.dat"
    aicbic2 = "bigFlows/Aic-Bic.dat"
    aicbic3 = "lanDiurnal/Aic-Bic.dat"
    aicbic4 = "equinix-1s/Aic-Bic.dat"
    plot_costfunction_vs_aicbic(aicbic1=PLOT_DIR + aicbic1, costfunction1=PLOT_DIR + costfunction1, pcaptitle1=pcaptitle1,
                                aicbic2=PLOT_DIR + aicbic2, costfunction2=PLOT_DIR + costfunction2, pcaptitle2=pcaptitle2,
                                aicbic3=PLOT_DIR + aicbic3, costfunction3=PLOT_DIR + costfunction3, pcaptitle3=pcaptitle3,
                                aicbic4=PLOT_DIR + aicbic4, costfunction4=PLOT_DIR + costfunction4, pcaptitle4=pcaptitle4,
                                title="Cost Function and AIC/BIC relative difference",
                                plotfile=PLOT_DIR + "paper/aicbic-costfunction-relative-diff")


def run_test(plot_dir):
    """

    :param plot_dir:
    :return:
    """
    PLOT_DIR = plot_dir
    qqplot(plot_dir=PLOT_DIR, datafile="QQplot - Weibull.dat", plot_title="QQplot - Weibull",
           plot_file="QQplot - Weibull")


if __name__ == "__main__":
    # arg parser
    parser = argparse.ArgumentParser(description='Run plotter for simulations or paper plots')
    parser.add_argument("--simulation", type=str, nargs="+", help="run Pcap simulation plots", required=False)
    parser.add_argument("--paper", action='store_true',
                        help="run sumarry plots for 4 the 4 experiments used on the paper..",
                        required=False)
    parser.add_argument("--test", type=str, nargs="+", help="run test", required=False)
    parser.add_argument("--test2", type=str, nargs="+", help="run test2", required=False)

    # call functions
    args = vars(parser.parse_args())
    if args["simulation"]:
        # ./plots.py --simulation "./plots/skype/"
        dataprocessor_simulation_plot(args.get("simulation")[0])
    elif args['paper']:
        # ./plots.py --paper
        #test_order_matrix()
        paper_aicbic_plots()
    #elif args['test']:
    #    run_test(args.get("test")[0])
    #else:
    #    parser.print_help()
    #plot_cost_function_all_pcap()

