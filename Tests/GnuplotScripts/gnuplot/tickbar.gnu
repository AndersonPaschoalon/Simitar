#!/usr/bin/gnuplot
# Usage:
# $ gnuplot -e "variable='value'" script.gnu
# $ gnuplot -e "title='kkk'" -e "sizeratio='0.5'" function.gnu

reset

# vars
if (!exists("font")) font= 'Helvetica,10'
#if (!exists("xlabel")) xlabel='xlabel'
if (!exists("ylabel")) ylabel='ylabel'
#if (!exists("title")) title='title'
if (!exists("sizeratio")) sizeratio= '0'
if (!exists("linestyle1")) linestyle1 = '1'
if (!exists("linestyle2")) linestyle2 = '12'
if (!exists("type")) type = 'lines'

# plot options
set key inside left top vertical Left noreverse noenhanced autotitle nobox
set style fill solid 1.00 border 0
set style data histogram
set xtics rotate by -45
set grid ytics
#set title title
set ylabel ylabel
#set xlabel xlabel
if( sizeratio == '0'){
	set size 1,1
}
else{
	set size ratio sizeratio
} 
#set xtics font font
set ytics font font
set label font font
#set xlabel font font
set ylabel font font
set title font font
set tics font font 
set datafile separator ","
set style fill solid
set key off

#plot png
set terminal pngcairo
set out filename.'.png'
plot  datafile  u 2: xtic(1) with histogram notitle
#plot pdf
set terminal pdf
set out  filename.'.pdf'
replot

reset
