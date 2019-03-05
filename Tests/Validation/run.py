#!/usr/bin/python3.5
import os
import sys
import datetime
import numpy as np
import subprocess
from Utils.Cd import Cd
from Utils.Csv import Csv
from Utils.Matrix import Matrix
from Utils.Terminal import Terminal as term
from Config import Config as config


def main():
    Validation.run()


class Validation:

    ### Main method ###

    @staticmethod
    def run():
        file_dir = Validation.generate_validation_datasets()
        Validation.generate_datafiles_pcapsinfo(plot_dir=file_dir)
        dat="dat"
        Validation.generate_datafiles_pcapsinfo(plot_dir=file_dir)
        p_bandwidth = config.bandwidth_file
        p_flowcdf = config.flow_cdf_file
        p_flow_cumulative = config.flow_cumulative_file
        p_flow_max_flows = config.flow_max_flows_file
        p_hust_exponent = config.hurst_exponent_file
        p_flows_ps = config.flows_ps_file
        p_wavelet_mrea =  config.wavelet_mrea_file
        p_average_pkt_rate = config.average_packet_rate_file
        p_average_pkt_size = config.average_packet_size_file
        p_duration = config.capture_duration_file
        p_data_bit_rate = config.data_bit_rate_file
        p_data_byte_rate = config.data_byte_rate_file
        p_number_pkts = config.number_of_packets_file
        # Wavelet MREA
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_wavelet_mrea, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=3, sim_data_column_x=2,
            csv_legend=" x1[resolution], y1[energy_log], x2[resolution), y2[energy_log], y2err")
        # Flow CDF
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flowcdf, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[cdf original], y2[cdf sim], y2err")
        # Bandwidth
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_bandwidth, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[bandwidth original], y2[bandwidth sim], y2err")
        # Flow Per second
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flows_ps, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[flows-per-second original], y2[flows-per-second sim], y2err")
        # Flow Cumulative distribution
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flow_cumulative, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[flows-cululative-dirstribution original], y2[flows-cumulative-distributon sim], y2err")
        # Hurst Exponent
        Validation.generate_errorvalue_files(file_dir, filename=p_hust_exponent, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of flows], y[sim number of flows], yerr")
        # Max Flows
        Validation.generate_errorvalue_files(file_dir, filename=p_flow_max_flows, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of flows], y[sim number of flows], yerr")
        # Average packet rate
        Validation.generate_errorvalue_files(file_dir, filename=p_average_pkt_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Average packet rate], y[sim Average packet rate], yerr")
        # Average Packet Size
        Validation.generate_errorvalue_files(file_dir, filename=p_average_pkt_size, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Average Packet Size], y[sim Average Packet Size], yerr")
        # Duration
        Validation.generate_errorvalue_files(file_dir, filename=p_duration, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Duration], y[sim Duration], yerr")
        # Data bit rate
        Validation.generate_errorvalue_files(file_dir, filename=p_data_bit_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Data bit rate], y[sim Data bit rate], yerr")
        # Data byte rate
        Validation.generate_errorvalue_files(file_dir, filename=p_data_byte_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Data byte rate], y[sim Data byte rate], yerr")
        # Number of packets
        Validation.generate_errorvalue_files(file_dir, filename=p_number_pkts, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of packets], y[sim number of packets], yerr")
        # Print plot cmd
        Validation.print_plot_cmd(file_dir)

    ### Public methods ###

    @staticmethod
    def print_plot_cmd(data_dir):
        print("")
        term.print_h1("Plotting the data")
        term.print_color(color="cyan", data="To plot the graphs for the generated data, run: ")
        term.print_color(color="cyan", data = "    ./plot.py --validation  " + data_dir)

    @staticmethod
    def generate_validation_datasets():
        """
        :return: directory where the data is saved
        """
        init_time = datetime.datetime.now()
        cd = Cd()
        term.print_h1("Analysis " + config.analysis_name + " using pcaps: " + config.pcap_file_1 + ' and ' + \
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
            term.print_h2("  --- iteration " + str(i), "purple")
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
        # name of the plot directory
        return plotdir_name

    @staticmethod
    def generate_errorvalue_files(file_dir, filename, file_extension, original_data_column, sim_data_column,
            csv_legend="csv-legend"):
        """
        #
        :param file_dir:
        :param filename:
        :param file_extension:
        :param original_data_column:
        :param sim_data_column:
        :param csv_legend:
        :return:
        """
        # constants
        file = file_dir + "/" + filename
        ex = file_extension
        nruns = config.n_runs
        term.print_h1("Generating errorbar datafile for {" + filename + "}")
        # loading reference data
        term.print_color(color="yellow", data="> Loading datafile {" + Validation.__getfilename(file, 0, ex) + "}")
        file_matrix_0 =  Csv.load_csv(datafile=Validation.__getfilename(file, 0, ex))
        term.print_color(color="blue", data="> Setting refference values for original data and sim data")
        #original_data = Matrix.column(file_matrix_0, original_data_column)
        original_data = file_matrix_0[original_data_column]
        term.print_color(color="blue", data="> Preparing data for calc error ..\nSetting zero matrix:")
        sym_data = np.zeros(nruns)
        term.print_color(color="blue", data="> Zero matrix created: sym_y.shape=" + str(sym_data.shape) )
        for i in range(0, nruns):
            term.print_color(color="yellow", data="\n# run: " + str(i))
            ith_filename = Validation.__getfilename(file, i, ex)
            term.print_color(color="blue", data="    > Loading datafile {" + ith_filename + "}")
            file_matrix_ith = Csv.load_csv(datafile=ith_filename)
            term.print_color(color="blue", data="    > loading column {" + str(sim_data_column) +
                                                "} from {" + ith_filename + "}")
            sym_data[i] = file_matrix_ith[sim_data_column]
        # endfor
        term.print_color(color="blue", data="> Creating error matrix")
        term.print_color(color="yellow", data="> Calculating error ...")
        [data_sim, data_err] = Validation.__confidence_interval(sym_data[:])
        sym_data_mean_err = np.matrix([[original_data, data_sim, data_err]])
        plot_err_filename = file + ".errplot.csv"
        term.print_color(color="yellow", data="> Salving error matrix into file {" + plot_err_filename + "}")
        #cd = Cd()
        #cd.cd(file_dir)
        #term.command("mkdir raw-data")
        #term.command("mv *.log *.dat *.csv *.txt raw-data/")
        #cd.back()
        Validation.__save_csv(np_matrix=sym_data_mean_err, header=csv_legend, directory=".",
                 file_name=plot_err_filename,  fmt='%f')


    @staticmethod
    def generate_errorbar_files(file_dir, filename, file_extension, original_data_column_y, original_data_column_x,
            sim_data_column_y, sim_data_column_x, csv_legend="csv-legend"):
        """
        #
        :param nruns: nuber of runs, starting from 0
        :param file_dir: directory where the file is located
        :param filename: name of the datafile, without the n-run and file extension
        :param file_extension: file extension, without the dot (.), (dat, csv)
        :param original_data_column_y:
        :param sim_data_column:
        :param csv_legend:
        :return:
        """
        # constants
        file = file_dir + "/" + filename
        ex = file_extension
        nruns = config.n_runs
        term.print_h1("Generating errorbar datafile for {" + filename + "}")
        # loading reference data
        term.print_color(color="yellow", data="> Loading datafile {" + Validation.__getfilename(file, 0, ex) + "}")
        file_matrix_0 =  Csv.load_csv(datafile=Validation.__getfilename(file, 0, ex))
        term.print_color(color="blue", data="> Setting refference values for original_x, orignal_y, and sim_x")
        original_x = Matrix.column(file_matrix_0, original_data_column_x)
        original_y = Matrix.column(file_matrix_0, original_data_column_y)
        sim_x = Matrix.column(file_matrix_0, sim_data_column_x)
        term.print_color(color="blue", data="> Preparing data for calc error bars..\nSetting zero matrix:")
        sym_y = np.zeros(shape=(len(sim_x), nruns))
        term.print_color(color="blue", data="> Zero matrix created: sym_y.shape=" + str(sym_y.shape) )
        for i in range(0, nruns):
            term.print_color(color="yellow", data="\n# run: " + str(i))
            ith_filename = Validation.__getfilename(file, i, ex)
            term.print_color(color="blue", data="    > Loading datafile {" + ith_filename + "}")
            file_matrix_ith = Csv.load_csv(datafile=ith_filename)
            term.print_color(color="blue", data="    > loading column {" + str(sim_data_column_y) +
                                                "} from {" + ith_filename + "}")
            sym_y[:, i] = Matrix.column(file_matrix_ith, sim_data_column_y)
            # print("column " + ith_filename + "["  + str(i) + "] " + str(Matrix.column(file_matrix_ith, sim_data_column_y)))
        term.print_color(color="blue", data="> Creating error bar matrix")
        plt_mtr_len = Validation.__len(original_x, original_y, sim_x)
        term.print_color(color="blue", data="> plt_mtr_len:" + str(plt_mtr_len))
        sym_y_mean_err =  np.zeros(shape=(plt_mtr_len, 5))
        term.print_color(color="blue", data="> Matrix sym_y_mean_err created sym_y_mean_err.shape=" +
                                            str(sym_y_mean_err.shape))
        term.print_color(color="yellow", data="> Calculating error bar...")
        for i in range(0, plt_mtr_len):
            print('.', end='')
            [y_s, y_err] = Validation.__confidence_interval(sym_y[i, :])
            [x_o, y_o, x_s, y_s, y_err] = [original_x[i], original_y[i], sim_x[i], y_s, y_err]
            sym_y_mean_err[i, :] = [x_o, y_o, x_s, y_s, y_err]
        print("")
        plot_err_filename = file + ".errplot.csv"
        term.print_color(color="yellow", data="> Salving errorbar matrix into file {" + plot_err_filename + "}")
        #cd = Cd()
        #cd.cd(file_dir)
        #term.command("mkdir raw-data")
        #term.command("mv *.log *.dat *.csv *.txt raw-data/")
        #cd.back()
        Validation.__save_csv(np_matrix=sym_y_mean_err, header=csv_legend, directory=".",
                 file_name=plot_err_filename)

    @staticmethod
    def generate_datafiles_pcapsinfo(plot_dir='plot-dir-name'):
        """
        This function generate the csv datafiles for the parameters stored on the datafiles
        pcapsinfo<i>.txt
        :return:
        """
        # go to plot dir
        if plot_dir == "plot-dir-name":
            raise ValueError("No argument or a invalid argument was provided @ Validation.generate_datafiles_pcapsinfo():"
                             + " plot_dir:" + plot_dir)
        term.print_h1("Generating datafiles form pcapsinfo files")
        cd = Cd()
        cd.cd(plot_dir)
        term.print_color(color="yellow", data="Changing to plot directory")
        cd.pwd()
        term.print_color(color="blue", data="> moving into plot directory")
        info_average_packet_size_1 = "Average packet size"
        info_average_packet_rate_2 = "Average packet rate"
        info_data_byte_rate_3 = "Data byte rate"
        info_data_bit_rate_4 = "Data bit rate"
        info_number_of_packets_5 = "Number of packets"
        info_capture_duration_6 = "Capture duration"
        file_av_pkt_size = config.average_packet_size_file + "{0}." + config.average_packet_size_ex
        file_av_pkt_rate = config.average_packet_rate_file + "{0}." +config.average_packet_rate_ex
        file_byte_rate = config.data_byte_rate_file + "{0}." + config.data_byte_rate_ex
        file_bit_rate = config.data_bit_rate_file + "{0}." + config.data_bit_rate_ex
        file_n_packets = config.number_of_packets_file + "{0}." + config.number_of_packets_ex
        file_duration = config.capture_duration_file + "{0}." + config.capture_duration_ex
        for i in range(0, config.n_runs):
            term.print_h3("Creating datafiles from pcapsinfo file run:[" + str(i) + "]")
            term.print_color(color="blue", data=" > " + info_average_packet_size_1)
            [o1, s1, u1] = Validation.__get_pcapsinfo(i, info_average_packet_size_1, "float")
            term.print_color(color="blue", data=" > " + info_average_packet_rate_2)
            [o2, s2, u2] = Validation.__get_pcapsinfo(i, info_average_packet_rate_2, "float")
            term.print_color(color="blue", data=" > " + info_data_byte_rate_3)
            [o3, s3, u3] = Validation.__get_pcapsinfo(i, info_data_byte_rate_3, "float")
            term.print_color(color="blue", data=" > " + info_data_bit_rate_4)
            [o4, s4, u4] = Validation.__get_pcapsinfo(i, info_data_bit_rate_4, "float")
            term.print_color(color="blue", data=" > " + info_number_of_packets_5)
            [o5, s5, u5] = Validation.__get_pcapsinfo(i, info_number_of_packets_5, "int")
            term.print_color(color="blue", data=" > " + info_capture_duration_6)
            [o6, s6, u6] = Validation.__get_pcapsinfo(i, info_capture_duration_6, "float")
            f1 = file_av_pkt_size.format(i)
            f2 = file_av_pkt_rate.format(i)
            f3 = file_byte_rate.format(i)
            f4 = file_bit_rate.format(i)
            f5 = file_n_packets.format(i)
            f6 = file_duration.format(i)
            np.savetxt(f1, np.matrix([o1, s1]), delimiter=",", header= info_average_packet_size_1 +
                       "[" + u1 + "] : originalData, simulatedData", fmt='%f')
            np.savetxt(f2, np.matrix([o2, s2]), delimiter=",", header=info_average_packet_rate_2 +
                       "[" + u2 + "] : originalData, simulatedData", fmt='%f')
            np.savetxt(f3, np.matrix([o3, s3]), delimiter=",", header=info_data_byte_rate_3 +
                       "[" + u3 + "] : originalData, simulatedData", fmt='%f')
            np.savetxt(f4, np.matrix([o4, s4]), delimiter=",", header=info_data_bit_rate_4 +
                       "[" + u4 + "] : originalData, simulatedData", fmt='%f')
            np.savetxt(f5, np.matrix([o5, s5]), delimiter=",", header=info_number_of_packets_5 +
                       "[" + u5 + "] : originalData, simulatedData", fmt='%d')
            np.savetxt(f6, np.matrix([o6, s6]), delimiter=",", header=info_capture_duration_6 +
                       "[" + u6 + "] : originalData, simulatedData", fmt='%f')
        term.print_color(color="yellow", data="Returning to the root directory")
        cd.back()
        cd.pwd()


    ### Aux(private) methods ###
    @staticmethod
    def __get_pcapsinfo(ith_pcapsinfo, info_to_grep, type):
        # 0: ith-pcapsinfo file, 1:information to catch, 2: 1(original) 2(sim pcap), 3:1(value) 2(unity)
        bash_filter_cmd = 'cat pcapsinfo{0}.txt |grep "^{1}" |sed "s/.*:\s*//g" |awk \'NR=={2}{{print(${3})}}\''
        bash_first_val = bash_filter_cmd.format(ith_pcapsinfo, info_to_grep, 1, 1)
        bash_second_val = bash_filter_cmd.format(ith_pcapsinfo, info_to_grep, 2, 1)
        bash_unity = bash_filter_cmd.format(ith_pcapsinfo, info_to_grep, 1, 2)
        if type == "int" :
            first_val = int(subprocess.check_output(bash_first_val, shell=True).decode('ascii').replace(",", "."))
            second_val = int(subprocess.check_output(bash_second_val, shell=True).decode('ascii').replace(",", "."))
            unity = str(subprocess.check_output(bash_unity, shell=True).decode('ascii').strip())
        elif type == "float" :
            first_val = float(subprocess.check_output(bash_first_val, shell=True).decode('ascii').replace(",", "."))
            second_val = float(subprocess.check_output(bash_second_val, shell=True).decode('ascii').replace(",", "."))
            unity = str(subprocess.check_output(bash_unity, shell=True).decode('ascii').strip())
        else:
            first_val = str(subprocess.check_output(bash_first_val, shell=True).decode('ascii').replace(",", ".").strip())
            second_val = str(subprocess.check_output(bash_second_val, shell=True).decode('ascii').replace(",", ".").strip())
            unity = str(subprocess.check_output(bash_unity, shell=True).decode('ascii').strip())

        return [first_val, second_val, unity]

    @staticmethod
    def __getfilename(data_file, i_th, ex):
        return str(data_file + str(i_th) +'.' + ex)

    @staticmethod
    def __confidence_interval(list_values):
        z = 1.96
        n = len(list_values)
        mean_value = np.mean(list_values)
        std_dev = np.std(list_values)
        return  [mean_value, z*std_dev/(np.sqrt(n))]

    @staticmethod
    def __save_csv(np_matrix, header, directory, file_name, fmt='%f'):
        data_file = directory + "/" + file_name
        np.savetxt(data_file, np_matrix, delimiter=",", header=header, fmt=fmt)

    @staticmethod
    def __len(*args, **kwargs):
        nargs = len(args)
        if nargs == 0:
            term.print_color(color="red", data="*** ERROR *** no argument was provided!! nargs:" + nargs)
            return -1 ;
        min_len0 = len(args[0])
        min_len = min_len0
        for i in range(0, nargs):
            if len(args[i]) < min_len:
                min_len = len(args[i])
                term.print_color(color="red", data="**** !! WARNING !! **** Something is not right. " +
                                 "The lenght of the <" + str(i) + "-th> vector passed to Validation.__len() is " +
                                 "smaller then the first. min_len0:" + str(min_len0) + ", min_len" + str(i) +
                                 ":" + str(min_len) + ". They should have the same lenght.")
        return min_len

    @staticmethod
    def test_generate_errorbar_files():
        """
        Method for testing the scripts
        :return:
        """
        file_dir = "plots/Abacate-2019-2-13-1-25-25/"
        dat="dat"
        Validation.generate_datafiles_pcapsinfo(plot_dir=file_dir)
        p_bandwidth = config.bandwidth_file
        p_flowcdf = config.flow_cdf_file
        p_flow_cumulative = config.flow_cumulative_file
        p_flow_max_flows = config.flow_max_flows_file
        p_hust_exponent = config.hurst_exponent_file
        p_flows_ps = config.flows_ps_file
        p_wavelet_mrea =  config.wavelet_mrea_file
        p_average_pkt_rate = config.average_packet_rate_file
        p_average_pkt_size = config.average_packet_size_file
        p_duration = config.capture_duration_file
        p_data_bit_rate = config.data_bit_rate_file
        p_data_byte_rate = config.data_byte_rate_file
        p_number_pkts = config.number_of_packets_file
        # Wavelet MREA
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_wavelet_mrea, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=3, sim_data_column_x=2,
            csv_legend=" x1[resolution], y1[energy_log], x2[resolution), y2[energy_log], y2err")
        # Flow CDF
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flowcdf, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[cdf original], y2[cdf sim], y2err")
        # Bandwidth
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_bandwidth, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[bandwidth original], y2[bandwidth sim], y2err")
        # Flow Per second
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flows_ps, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[flows-per-second original], y2[flows-per-second sim], y2err")
        # Flow Cumulative distribution
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flow_cumulative, file_extension="dat",
            original_data_column_y=1, original_data_column_x=0, sim_data_column_y=2, sim_data_column_x=0,
            csv_legend=" x[time(s)], y1[flows-cululative-dirstribution original], y2[flows-cumulative-distributon sim], y2err")
        # Hurst Exponent
        Validation.generate_errorvalue_files(file_dir, filename=p_hust_exponent, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of flows], y[sim number of flows], yerr")
        # Max Flows
        Validation.generate_errorvalue_files(file_dir, filename=p_flow_max_flows, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of flows], y[sim number of flows], yerr")
        # Average packet rate
        Validation.generate_errorvalue_files(file_dir, filename=p_average_pkt_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Average packet rate], y[sim Average packet rate], yerr")
        # Average Packet Size
        Validation.generate_errorvalue_files(file_dir, filename=p_average_pkt_size, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Average Packet Size], y[sim Average Packet Size], yerr")
        # Duration
        Validation.generate_errorvalue_files(file_dir, filename=p_duration, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Duration], y[sim Duration], yerr")
        # Data bit rate
        Validation.generate_errorvalue_files(file_dir, filename=p_data_bit_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Data bit rate], y[sim Data bit rate], yerr")
        # Data byte rate
        Validation.generate_errorvalue_files(file_dir, filename=p_data_byte_rate, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original Data byte rate], y[sim Data byte rate], yerr")
        # Number of packets
        Validation.generate_errorvalue_files(file_dir, filename=p_number_pkts, file_extension=dat,
                original_data_column=0, sim_data_column=1,
                csv_legend=" x[original number of packets], y[sim number of packets], yerr")



if __name__ == "__main__":
    main()


