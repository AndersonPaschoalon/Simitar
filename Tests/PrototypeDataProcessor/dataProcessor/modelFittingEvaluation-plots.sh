#!/bin/bash
PLOT_DIR="../../plots";
#PLOT_DIR="../../plots/(3)wireshark-wiki_SkypeIRC/";
simName=$1;
font_config="font='Helvetica,15'";

if [[ ${simName} == "" ]];
	then
	simName=$RANDOM;
fi
SIM_DIR="prototype-"${simName};



mkdir ${PLOT_DIR}/${SIM_DIR};

#plot CDF empirica
gnuplot -e "filename='${PLOT_DIR}/Empirical CDF function'" -e "datafile='${PLOT_DIR}/Empirical CDF function.dat'" \
	-e "xlabel='interPacketTime (s)'" -e "ylabel='F(interPacketTime)'" -e "title='Empirical CDF'" \
	-e "linestyle='12'" -e ${font_config} ../gnuplot/function.gnu 


#plots: linearização
gnuplot -e "filename='${PLOT_DIR}/Cauchy - Linearized data and linear fitting'" -e "datafile='${PLOT_DIR}/Cauchy - Linearized data and linear fitting.dat'" \
	-e "xlabel='linearized x'" -e "ylabel='linearized y'" -e "title='Cauchy: Linearized data and linear fitting'" \
	-e "legend1='linearized data'" -e "legend2='linear approximation'" -e ${font_config} ../gnuplot/2functionxyxy.gnu 
gnuplot -e "filename='${PLOT_DIR}/Weibull - Linearized data and linear fitting'" -e "datafile='${PLOT_DIR}/Weibull - Linearized data and linear fitting.dat'" \
	-e "xlabel='linearized x'" -e "ylabel='linearized y'" -e "title='Weibull: Linearized data and linear fitting'" \
	-e "legend1='linearized data'" -e "legend2='linear approximation'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu 
gnuplot -e "filename='${PLOT_DIR}/Exponential - Linearized data and linear fitting'" -e "datafile='${PLOT_DIR}/Exponential - Linearized data and linear fitting.dat'" \
	-e "xlabel='linearized x'" -e "ylabel='linearized y'" -e "title='Exponential: Linearized data and linear fitting'" \
	-e "legend1='linearized data'" -e "legend2='linear approximation'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu 
gnuplot -e "filename='${PLOT_DIR}/Pareto - Linearized data and linear fitting'" -e "datafile='${PLOT_DIR}/Pareto - Linearized data and linear fitting.dat'" \
	-e "xlabel='linearized x'" -e "ylabel='linearized y'" -e "title='Pareto: Linearized data and linear fitting'" \
	-e "legend1='linearized data'" -e "legend2='linear approximation'" -e ${font_config}  ../gnuplot/2functionxyxy.gnu 

#plots custo J()
gnuplot -e "filename='${PLOT_DIR}/Cauchy - Cost J(iterations) convergence'" -e "datafile='${PLOT_DIR}/Cauchy - Cost J(iterations) convergence.dat'" \
	-e "xlabel='iterations'" -e "ylabel='Cost J(iterations)'" -e "title='Cauchy: Cost J(iterations)'" \
	-e "linestyle='21'" -e ${font_config}  ../gnuplot/function.gnu
gnuplot -e "filename='${PLOT_DIR}/Weibull - Cost J(iterations) convergence'" -e "datafile='${PLOT_DIR}/Weibull - Cost J(iterations) convergence.dat'" \
	-e "xlabel='iterations'" -e "ylabel='Cost J(iterations)'" -e "title='Weibull: Cost J(iterations)'" \
	-e "linestyle='21'" -e ${font_config}  ../gnuplot/function.gnu
gnuplot -e "filename='${PLOT_DIR}/Exponential - Cost J(iterations) convergence'" -e "datafile='${PLOT_DIR}/Exponential - Cost J(iterations) convergence.dat'" \
	-e "xlabel='iterations'" -e "ylabel='Cost J(iterations)'" -e "title='Exponential: Cost J(iterations)'" \
	-e "linestyle='21'" -e ${font_config}  ../gnuplot/function.gnu
gnuplot -e "filename='${PLOT_DIR}/Pareto - Cost J(iterations) convergence'" -e "datafile='${PLOT_DIR}/Pareto - Cost J(iterations) convergence.dat'" \
	-e "xlabel='iterations'" -e "ylabel='Cost J(iterations)'" -e "title='Pareto: Cost J(iterations)'" \
	-e "linestyle='21'" -e ${font_config}  ../gnuplot/function.gnu

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

mv ${PLOT_DIR}/*.pdf ${PLOT_DIR}/*.png ${PLOT_DIR}/${SIM_DIR};
mv ${PLOT_DIR}/*.dat ${PLOT_DIR}/${SIM_DIR};
