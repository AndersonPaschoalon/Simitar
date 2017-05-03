## Copyright (C) 2017 anderson
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} interFileParam (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: anderson <anderson@duvel-ThinkCentre-M93p>
## Created: 2017-05-03

function [lambda c_mean] = interFileParam_expConst (delta_time, file_cut_time, min_on_time)
	% discard session off times
	delta_time = delta_time(delta_time < file_cut_time);
	% calc arrival times, as if there was only one file tranfered on all
	% section
	arrival_time = cumulativeData(delta_time);
	% max length possible
	m = length(delta_time);
	
	[onOff onTimes offTimes] = calcOnOffTimes (arrival_time, delta_time, file_cut_time, min_on_time)
	
	meanOn = mean(onTimes);
	lambdaOn = 1/meanOn;
	
	meanOff = mean(offTimes);
	lambdaOff = 1/meanOff;
	
	lambda = [lambdaOn lambdaOff]';
	c_mean = [meanOn meanOff]';
	
endfunction
