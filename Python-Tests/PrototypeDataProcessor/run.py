import os
from GnuplotScripts.GnuplotScripts import GnuplotScripts
from Cd.Cd import Cd

PCAP_FILE = "../../Pcap/wireshark-wiki_http.pcap"
SIMULATION_NAME = "wombat"


def print_header(title):
    print('')
    print('###############################################################################')
    print ('# ' + title)
    print('###############################################################################')


if __name__ == "__main__":
    pcap_file = localDir = os.path.dirname(os.path.abspath(__file__)) + '/' + PCAP_FILE
    cd = Cd(os.path.dirname(os.path.abspath(__file__)))
    sym_name = SIMULATION_NAME
    font_config='Helvetica,15'

    print_header("Simulations for:" + sym_name + " using pcap:" + pcap_file)

    # clean sim dir
    cd.cd('./dataProcessor/')
    os.system('rm -rf data/*')
    # filter inter-pacekt times
    os.system( './pcap-filter.sh --time-delta ' + pcap_file + ' ' +  sym_name)
    # execute dataProcessor prototype
    os.system( './dataProcessor.m ' + sym_name)
    # calc cost function of each simulation
    os.system( './calcCostFunction.py ' + 'data/')
    # back to working directory
    cd.back()

    print_header("Plot for:" + sym_name + " using pcap:" + pcap_file)

    plots_dir = 'plots/' + sym_name
    os.system('mkdir -p ' + plots_dir)
    os.system('mv dataProcessor/data/* ' +  plots_dir)

    gp = GnuplotScripts(data_dir=plots_dir, plots_dir=plots_dir, font=font_config, linestyle_1='b-', linestyle_2='r-', linestyle_3='g-', linestyle_4='v-' )

    print('Plotting empirical CDF of:' + sym_name + ' from pcap:' + pcap_file)
    gp.plot_config(xlabel='interPacketTime (s)', ylabel='F(interPacketTime)', title='Empirical CDF')
    gp.plot_function(filename='Empirical CDF function', datafile='Empirical CDF function.dat')

    print('Plotting empirical Linearizations of:' + sym_name + ' from pcap:' + pcap_file)

    theTitle = 'Cauchy - Linearized data and linear fitting'
    gp.plot_config(title=theTitle, legend1='linearized data' , legend2='linear approximation')
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle+'.dat')

    theTitle='Weibull - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle+'.dat')

    theTitle='Exponential - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle+'.dat')

    theTitle='Pareto - Linearized data and linear fitting'
    gp.plot_config(title=theTitle)
    gp.plot_2functionxyxy(filename=theTitle, datafile=theTitle+'.dat')

    print('Plotting Cost J(iterations) convergence of:' + sym_name + ' from pcap:' + pcap_file)

    theTitle='Cauchy - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle, ylabel='Cost J(iterations)', xlabel='iterations')
    gp.plot_function(filename=theTitle, datafile=theTitle+'.dat')
    theTitle='Weibull - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle+'.dat')
    theTitle='Exponential - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle+'.dat')
    theTitle='Pareto - Cost J(iterations) convergence'
    gp.plot_config(title=theTitle)
    gp.plot_function(filename=theTitle, datafile=theTitle+'.dat')

    print('Plotting correlation, mean, standard deviation and hurst exponent of:' + sym_name + ' from pcap:' + pcap_file)

    theFile='Correlation'
    gp.plot_config(title='Correlation with Empirical Data', ylabel='Correlation', xlabel='Stochastic function', legend2='linear approximation', linestyle_1='ro')
    gp.plot_xtickerror(filename=theFile, datafile=theFile+'.dat')

    theFile='Standard Deviation'
    gp.plot_config(title='Correlation with Empirical Data', ylabel='Standard Deviation')
    gp.plot_xtickerror(filename=theFile, datafile=theFile+'.dat')

    theFile='Mean'
    gp.plot_config(title='Mean inter packet time', ylabel='Mean')
    gp.plot_xtickerror(filename=theFile, datafile=theFile+'.dat')

    theFile='Hurst Exponent'
    gp.plot_config(title='Hurst Exponent of inter packet time', ylabel='Hurst Exponent')
    gp.plot_xtickerror(filename=theFile, datafile=theFile+'.dat')


"""




#correlation, mean, standard deviation and hurst exponent
gnuplot -e "filename='${PLOT_DIR}/Correlation'" -e "datafile='${PLOT_DIR}/Correlation.dat'" \
	-e "xlabel='Stochastic function'" -e "ylabel='Correlation'" -e "title='Correlation with Empirical Data'" \
	-e "linestyle='4'" -e ${font_config}  ../gnuplot/xtickerror.gnu
gnuplot -e "filename='${PLOT_DIR}/Mean'" -e "datafile='${PLOT_DIR}/Mean.dat'" \
	-e "xlabel='Stochastic function'" -e "ylabel='Mean'" -e "title='Mean inter packet time'" \
	-e "linestyle='4'" -e ${font_config}  ../gnuplot/xtickerror-hline.gnu
gnuplot -e "filename='${PLOT_DIR}/Standard Deviation'" -e "datafile='${PLOT_DIR}/Standard Deviation.dat'" \
	-e "xlabel='Stochastic function'" -e "ylabel='Standard Deviation'" -e "title='Standard Deviation of inter packet time'" \
	-e "linestyle='4'" -e ${font_config}  ../gnuplot/xtickerror-hline.gnu
gnuplot -e "filename='${PLOT_DIR}/Hurst Exponent'" -e "datafile='${PLOT_DIR}/Hurst Exponent.dat'" \
	-e "xlabel='Stochastic function'" -e "ylabel='Hurst Exponent'" -e "title='Hurst Exponent of inter packet time'" \
	-e "linestyle='4'" -e ${font_config}  ../gnuplot/xtickerror-hline.gnu


#Cdf Empirical vs Estimated
gnuplot -e "filename='${PLOT_DIR}/Cauchy aproximation vs Original set" -e "datafile1='${PLOT_DIR}/Cauchy aproximation vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Cauchy aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Exponential aproximation (linear regression) vs Original set'" -e "datafile1='${PLOT_DIR}/Exponential aproximation (linear regression) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Exponential aproximation (linear regression) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Exponential aproximation (mean) vs Original set.dat'" -e "datafile1='${PLOT_DIR}/Exponential aproximation (mean) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Exponential aproximation (mean) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'"  -e ${font_config} ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Normal aproximation vs Original set'" -e "datafile1='${PLOT_DIR}/Normal aproximation vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Normal aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Pareto aproximation (linear regression) vs Original set'" -e "datafile1='${PLOT_DIR}/Pareto aproximation (linear regression) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Pareto aproximation (linear regression) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Pareto aproximation (maximum likehood) vs Original set'" -e "datafile1='${PLOT_DIR}/Pareto aproximation (maximum likehood) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Pareto aproximation (maximum likehood) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu
gnuplot -e "filename='${PLOT_DIR}/Weibull aproximation vs Original set'" -e "datafile1='${PLOT_DIR}/Weibull aproximation vs Original set.dat'"  \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat" -e ${font_config}  -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Weibull aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data.gnu

#Cdf Empirical vs Estimated (log scale)
gnuplot -e "filename='${PLOT_DIR}/Logscale - Cauchy aproximation vs Original set'" -e "datafile1='${PLOT_DIR}/Cauchy aproximation vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Cauchy aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Exponential aproximation (linear regression) vs Original set'" -e "datafile1='${PLOT_DIR}/Exponential aproximation (linear regression) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Exponential aproximation (linear regression) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Exponential aproximation (mean) vs Original set'" -e "datafile1='${PLOT_DIR}/Exponential aproximation (mean) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Exponential aproximation (mean) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'"  -e ${font_config} ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Normal aproximation vs Original set'" -e "datafile1='${PLOT_DIR}/Normal aproximation vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Normal aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Pareto aproximation (linear regression) vs Original set'" -e "datafile1='${PLOT_DIR}/Pareto aproximation (linear regression) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Pareto aproximation (linear regression) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Pareto aproximation (maximum likehood) vs Original set'" -e "datafile1='${PLOT_DIR}/Pareto aproximation (maximum likehood) vs Original set.dat'" \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Pareto aproximation (maximum likehood) vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu
gnuplot -e "filename='${PLOT_DIR}/Logscale - Weibull aproximation vs Original set'" -e "datafile1='${PLOT_DIR}/Weibull aproximation vs Original set.dat'"  \
	-e "datafile2='${PLOT_DIR}/Empirical CDF function.dat'" -e ${font_config}  -e "type='lines'" \
	-e "xlabel='inter packet time (s)'" -e "ylabel='CDF function'" -e "title='Weibull aproximation vs Original set'" \
	-e "legend1='aproximation'" -e "legend2='empirical'" -e ${font_config}  ../gnuplot/2f2data-log.gnu


#QQplots
gnuplot -e "filename='${PLOT_DIR}/QQplot - Cauchy'" -e "datafile='${PLOT_DIR}/QQplot - Cauchy.dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Cauchy: QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Exponential(LR)'" -e "datafile='${PLOT_DIR}/QQplot - Exponential(LR).dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Exponential(LR): QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Exponential(Me)'" -e "datafile='${PLOT_DIR}/QQplot - Exponential(Me).dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Exponential(Me): QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Normal'" -e "datafile='${PLOT_DIR}/QQplot - Normal.dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Normal: QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Pareto(LR)'" -e "datafile='${PLOT_DIR}/QQplot - Pareto(LR).dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Pareto(LR): QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Pareto(MLH).dat'" -e "datafile='${PLOT_DIR}/QQplot - Pareto(MLH).dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title=' Pareto(MLH): QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu
gnuplot -e "filename='${PLOT_DIR}/QQplot - Weibull.dat'" -e "datafile='${PLOT_DIR}/QQplot - Weibull.dat'" \
	-e "xlabel='estimated'" -e "ylabel='samples'" -e "title='Weibull: QQplot'" \
	-e "legend1='QQplot'" -e "legend2='rule'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu


"""










