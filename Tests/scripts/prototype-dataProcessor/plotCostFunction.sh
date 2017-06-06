#!/bin/bash
PLOT_DIR="../../plots";
simName=$1;
font_config="font='Helvetica,15'";

if [[ ${simName} == "" ]];
	then
	simName=$RANDOM;
fi
SIM_DIR="/FINAL_prototype-"${simName}"/";

./calcCostFunction.py ${PLOT_DIR}${SIM_DIR}
gnuplot -e "datafile='${PLOT_DIR}${SIM_DIR}/costFunction.dat'" -e "filename='${PLOT_DIR}${SIM_DIR}/costFunction'" -e "ylabel='cost function'"   -e ${font_config} ../gnuplot/tickbar.gnu


