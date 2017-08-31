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
## @deftypefn {Function File} {@var{retval} =} calcOnOnffSimplified (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: anderson <anderson@duvel-ThinkCentre-M93p>
## Created: 2017-05-31

%% calcOnOff algotithem simplified. Just calc on and off times
function [onOff onTimes offTimes] = calcOnOffTimes (arrival_time, delta_time, cut_time, min_on_time)
	m = length(delta_time); % in: number of inter packet times
	last_off = 0; i = 0; j = 0;
	for i = 1:m % Calc list of OnOff times
		if((delta_time(i) > cut_time))
			if(i == 1) % if the first is session-off
				j++;
				onOff(j) = min_on_time; % on time
				j++;
				onOff(j) = delta_time(i);
				last_off = i;
			else 
				if(j == 0) % base first case
					j++;
					onOff(j) = arrival_time(i - 1); % on time
					j++;
					onOff(j) = delta_time(i);
					last_off = i;
				else %base case
					j++;
					%onOff(j) = delta_time(i-1) - delta_time(last_off);
					onOff(j) = arrival_time(i-1) - arrival_time(last_off); % on time				
					if(onOff(j) < min_on_time)
						onOff(j) = min_on_time; % on time
					endif
					j++;
					onOff(j) = delta_time(i);
					last_off = i;
				endif		
			endif
		endif
	endfor
	i = m + 1; % calc the last On time
	if(last_off == m ) % if last is session-off 
		j++;
		onOff(j) = min_on_time; % on time
	else % base last case
		j++;
		if(last_off != 0)
			onOff(j) = arrival_time(m) - arrival_time(last_off); % on time
		else 
			onOff(j) = arrival_time(m); % on time
		endif
	endif

endfunction
