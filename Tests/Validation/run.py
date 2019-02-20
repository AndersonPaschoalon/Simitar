#!/usr/bin/python3.5
import os
import sys
import datetime
import numpy as np
from Utils.Cd import Cd
from Utils.Csv import Csv
from Utils.Matrix import Matrix
from Utils.Terminal import Terminal as term
from Config import Config as config


def main():
    #Validation.run()
    Validation.test_generate_errorbar_files()
    """
    plot_directory_name = run_validation()
    p_bandwidth = "Bandwidth"
    p_flowcdf = "FlowCdf"
    p_flow_cumulative = "FlowCumulative"
    p_flow_max_flows = "FlowMaxflows"
    p_wavelet_mrea = "WaveletMREA"

    generate_errorbar_files(file_dir=plot_directory_name, filename=p_wavelet_mrea,
                            file_extension="dat", original_data_column_y=1,
                            original_data_column_x=0, sim_data_column_y=3,
                            sim_data_column_x=2)
    """

class Validation:

    # run validation

    @staticmethod
    def run():
        # file base names
        p_bandwidth = "Bandwidth"
        p_flowcdf = "FlowCdf"
        p_flow_cumulative = "FlowCumulative"
        p_flow_max_flows = "FlowMaxflows"
        p_flows_ps = "FlowsPs"
        p_wavelet_mrea = "WaveletMREA"
        plot_directory_name = Validation.generate_validation_datasets()
        Validation.generate_errorbar_files(file_dir=plot_directory_name, filename=p_wavelet_mrea,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=3,
                                sim_data_column_x=2)
        Validation.generate_errorbar_files(file_dir=plot_directory_name, filename=p_flowcdf,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)
        Validation.generate_errorbar_files(file_dir=plot_directory_name, filename=p_bandwidth,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)
        Validation.generate_errorbar_files(file_dir=plot_directory_name, filename=p_flows_ps,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)

    # Main methods

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
    def generate_errorbar_files(file_dir, filename, file_extension, original_data_column_y, original_data_column_x,
            sim_data_column_y, sim_data_column_x):
        """

        :param nruns: nuber of runs, starting from 0
        :param file_dir: directory where the file is located
        :param filename: name of the datafile, without the n-run and file extension
        :param file_extension: file extension, without the dot (.), (dat, csv)
        :param original_data_column_y:
        :param sim_data_column:
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
        term.print_color(color="blue", data="> Creating error bar matrix")
        sym_y_mean_err =  np.zeros(shape=(len(sim_x), 2))
        term.print_color(color="blue", data="> Matrix sym_y_mean_err created sym_y_mean_err.shape=" +
                                            str(sym_y_mean_err.shape))
        term.print_color(color="yellow", data="> Calculating error bar...")
        for i in range(0, len(sim_x)):
            print('.', end='')
            [mu, err] = Validation.__confidence_interval(sym_y[i, :])
            sym_y_mean_err[i, :] = [mu, err]
        print("")
        plot_err_filename = file + ".errplot.csv"
        term.print_color(color="yellow", data="> Salving errorbar matrix into file {" + plot_err_filename + "}")
        #cd = Cd()
        #cd.cd(file_dir)
        #term.command("mkdir raw-data")
        #term.command("mv *.log *.dat *.csv *.txt raw-data/")
        #cd.back()
        Validation.__save_csv(np_matrix=sym_y_mean_err, header="wavelet, error", directory=".",
                 file_name=plot_err_filename)


    # Aux(private) methods
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
    def __save_csv(np_matrix, header, directory, file_name):
        data_file = directory + "/" + file_name
        np.savetxt(data_file, np_matrix, delimiter=",", header=header)

    @staticmethod
    def test_generate_errorbar_files():
        file_dir = "plots/Abacate-2019-2-13-1-25-25/"
        p_bandwidth = "Bandwidth"
        p_flowcdf = "FlowCdf"
        p_flow_cumulative = "FlowCumulative"
        p_flow_max_flows = "FlowMaxflows"
        p_flows_ps = "FlowsPs"
        p_wavelet_mrea = "WaveletMREA"
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_wavelet_mrea,
                                file_extension="dat", original_data_column_y=1, original_data_column_x=0,
                                sim_data_column_y=3, sim_data_column_x=2)
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flowcdf,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_bandwidth,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)
        Validation.generate_errorbar_files(file_dir=file_dir, filename=p_flows_ps,
                                file_extension="dat", original_data_column_y=1,
                                original_data_column_x=0, sim_data_column_y=2,
                                sim_data_column_x=0)


if __name__ == "__main__":
    main()


