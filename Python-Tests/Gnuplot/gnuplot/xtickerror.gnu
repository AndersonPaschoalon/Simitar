#!/usr/bin/gnuplot
# Usage:
# $ gnuplot -e "variable='value'" script.gnu
# $ gnuplot -e "title='kkk'" -e "sizeratio='0.5'" function.gnu

reset

# vars
if (!exists("filename")) filename='../../plots/default'
if (!exists("datafile")) datafile='../../plots/default/xtickerror.dat'
if (!exists("font")) font= 'Helvetica,10'
if (!exists("xlabel")) xlabel='xlabel'
if (!exists("ylabel")) ylabel='ylabel'
if (!exists("title")) title='title'
if (!exists("sizeratio")) sizeratio= '0'
if (!exists("linestyle")) linestyle = '2'
if (!exists("type")) type = 'points'
if (!exists("lw")) lw = '2'

#styles
set style line 1 linecolor rgb "red" linetype 1 linewidth lw pointtype 1 #r-+
set style line 2 linecolor rgb "red" linetype 1 linewidth lw  pointtype 2 #r-x
set style line 3 linecolor rgb "red" linetype 1 linewidth lw  pointtype 3 #r-*
set style line 4 linecolor rgb "red" linetype 1 linewidth lw  pointtype 6 #r-o
set style line 11 linecolor rgb "blue" linetype 1 linewidth lw  pointtype 1 #b-+
set style line 12 linecolor rgb "blue" linetype 1 linewidth lw  pointtype 2 #b-x
set style line 13 linecolor rgb "blue" linetype 1 linewidth lw   pointtype 3 #b-*
set style line 14 linecolor rgb "blue" linetype 1 linewidth lw  pointtype 6 #b-o
set style line 21 linecolor rgb "green" linetype 1 linewidth lw  pointtype 1 #g-+
set style line 22 linecolor rgb "green" linetype 1 linewidth lw  pointtype 2 #g-x
set style line 23 linecolor rgb "green" linetype 1 linewidth lw  pointtype 3 #g-*
set style line 24 linecolor rgb "green" linetype 1 linewidth lw  pointtype 6 #g-o
set style line 31 linecolor rgb "black" linetype 1 linewidth lw  pointtype 1 #k-+
set style line 32 linecolor rgb "black" linetype 1 linewidth lw  pointtype 2 #k-x
set style line 33 linecolor rgb "black" linetype 1 linewidth lw  pointtype 3 #k-*
set style line 34 linecolor rgb "black" linetype 1 linewidth lw  pointtype 6 #k-o
set style line 41 linecolor rgb "violet" linetype 1 linewidth lw  pointtype 1 #v-+
set style line 42 linecolor rgb "violet" linetype 1 linewidth lw  pointtype 2 #v-x
set style line 43 linecolor rgb "violet" linetype 1 linewidth lw  pointtype 3 #v-*
set style line 44 linecolor rgb "violet" linetype 1 linewidth lw  pointtype 6 #v-o
set style line 51 linecolor rgb "orange" linetype 1 linewidth lw  pointtype 1 #v-+
set style line 52 linecolor rgb "orange" linetype 1 linewidth lw  pointtype 2 #v-x
set style line 53 linecolor rgb "orange" linetype 1 linewidth lw  pointtype 3 #v-*
set style line 54 linecolor rgb "orange" linetype 1 linewidth lw  pointtype 6 #v-o

# plot options
set grid
set nokey #no legend
set title title
set ylabel ylabel
set xlabel xlabel
if( sizeratio == '0'){
	set size 1,1
}
else{
	set size ratio sizeratio
} 
set xtics font font
set ytics font font
set label font font
set xlabel font font
set ylabel font font
set title font font
set tics  font font 
set datafile separator ","

#plot png
set terminal pngcairo
set out filename.'.png'
set xtics rotate by 45 righ
if( type eq 'points') \
	plot  datafile using 2:xticlabel(1) with points ls linestyle, \
	datafile using 2:3 with errorbar ls linestyle
if( type eq 'linespoints') \
	plot  datafile using 2:xticlabel(1) with points ls linestyle, \
	datafile using 2:3 with errorbar ls linestyle, \
	datafile using 2:xticlabel(1) with lines ls linestyle
if( type eq 'lines') \
	plot  datafile using 2:xticlabel(1) with lines ls linestyle, \
	datafile using 2:3 with errorbar ls linestyle

#plot pdf
set terminal pdf
set out filename.'.pdf'
replot

reset


