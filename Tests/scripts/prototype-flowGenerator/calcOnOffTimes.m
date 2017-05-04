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
## @deftypefn {Function File} {@var{retval} =} sessionOnOffTimes (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: anderson <anderson@duvel-ThinkCentre-M93p>
## Created: 2017-05-03

function [onOff onTimes offTimes] = a__calcOnOffTimes (arrival_time, delta_time, cut_time, min_on_time)

	% in: number of inter packet times
	m = length(delta_time);

	% in: min time for ON
	%min_on_time = 0.1;

	% out: vector of on/off times
	onOff = zeros(m, 1);

	% vars inity
	on_beguin = 0;
	on_end = 0;
	last_off = 0;
	i = 0;
	j = 0;

	% Calc list of OnOff times
	for i = 1:m
		if(delta_time(i) > cut_time)
			if(i == 1) % if the first is session-off
				j++;
				onOff(j) = min_on_time;
				j++;
				onOff(j) = delta_time(i);
				last_off = i;
			elseif (i == m)
				if(last_off == m) % if last is session-off 
					j++;
					onOff(j) = min_on_time;
				else % base last case
					j++;
					onOff(j) = arrival_time(i) - arrival_time(last_off);
				endif				
			else 
				if(j == 0) % base first case
					j++;
					onOff(j) = arrival_time(i - 1);
					j++;
					onOff(j) = delta_time(i);
					last_off = i;
				else %base case
					j++;
					%onOff(j) = delta_time(i-1) - delta_time(last_off);
					onOff(j) = arrival_time(i-1) - arrival_time(last_off);
					if(onOff(j) < min_on_time)
						onOff(j) = min_on_time;
					endif
					j++;
					onOff(j) = delta_time(i);
					last_off = i;
				endif		
			endif
		endif
	endfor

	i = 0;
	onOff = onOff(onOff != 0);
	m = length(onOff); % update onOff length
	onTimes = zeros(m, 1);
	offTimes = zeros(m, 1);
	for i = 1:m
		if( mod(i, 2) == 1 ) % on-times, since the index starts with 1
			onTimes(i) = onOff(i);
		else 
			offTimes(i) = onOff(i);
		endif
	endfor

	onTimes = onTimes(onTimes != 0);
	offTimes = offTimes(offTimes != 0);
	

endfunction
