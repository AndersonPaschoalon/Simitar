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
## @deftypefn {Function File} {@var{retval} =} emissionSimulation (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: anderson <anderson@duvel-ThinkCentre-M93p>
## Created: 2017-05-03

function [list_generated] = emissionSimulation (onTimes, offTimes, lambdaOnOffInterfile, lambdaFile)
	list_generated = [0];
	lambdaOn = lambdaOnOffInterfile(1);
	lambdaOff = lambdaOnOffInterfile(2);

	
	%debug 
	onoffsum =  0;
	DIFF_current_file_time_file_time_on = 0;
	
	i = 0;
	current_time = 0;
	%while current_time < max_time
	while i < (length(onTimes) - 1)
		% counter
		i = i + 1;
		%%debug
		%fprintf("i = %d; onl = %d , offl = %d\n", i, length(onTimes) , length(offTimes) );
		% session
		session_time = onTimes(i);
		
		% reset
		current_session_time = 0;
		while( current_session_time < session_time)
			% get random on time
			
			file_time_on = exprnd(1/lambdaOn);
			current_session_time = 0;
			
			%EMULATE-TG:BEGUIN%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			% from now, this while actually do not represent what 
			% MesserTG will actually do, since, it do not controll
			% this part, but the high level API.
			% it just tries to emulate the expected behavior
			current_file_time = 0;
			flag_end_file_transference = 0;
			while(flag_end_file_transference == 0 )
				if(current_file_time > file_time_on)
					fprintf("\t\tThis point should not be reached(1)....\n");
					% to avoid bugs...
					break;
				endif
			
				%calc time left to end the file transference
				time_file_left = file_time_on - current_file_time;
				if(time_file_left < 0)
					time_file_left = 0;
					% This is the last execution of this while 
					% if it runs correcetely, this point actually
					% should not be reached, since the flag should 
					% be setted while evaluating the next 
					% inter pacekt time... but in any case
					flag_end_file_transference = 1;
					fprintf("\t\tThis point should not be reached(2)....\n");
				endif
				
				%calc actual inter packet time
				interPacketTime = exprnd(1/lambdaFile);
				if(interPacketTime > time_file_left)
					interPacketTime = time_file_left;
					% this is the last execution
					flag_end_file_transference = 1;
				endif
				
				%debug 
				list_generated = [list_generated ; interPacketTime];
				current_file_time = current_file_time + interPacketTime;
			endwhile
			% the emulated part is ended, now the simulated... :P
			%EMULATE-TG:end%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			
			time_session_left = current_file_time - current_session_time;
			
			% Now, file off time
			file_time_off = exprnd(1/lambdaOff);
			%TODO, >>>>>um if else pra ver se esse off gerado e muio grande <<<<<<< 
			list_generated = [list_generated ; file_time_off];
			%two ways to do this, they should do the same
			%current_session_time = current_session_time + file_time_on + file_time_off;
			%or....current_file_time
			current_session_time = current_session_time + current_file_time + file_time_off;
			%debug 
			%fprintf("\tcurrent_file_time is %f, and it should be %f \n",current_file_time, file_time_on);
			DIFF_current_file_time_file_time_on = sum(DIFF_current_file_time_file_time_on + current_file_time - file_time_on);
			
			time_session_left = current_file_time - current_session_time;
		
		endwhile
		list_generated = [list_generated ; offTimes(i)];
		current_time = current_time + current_session_time + offTimes(i);
		% debug
		onoffsum = onoffsum + offTimes(i) + onTimes(i);
		%debug 
		fprintf("current_session_time is %f, and it should be about %f \n",current_session_time, onTimes(i));
		%fprintf("current_time = %f, onoffsum = %f, max_time = %f\n", current_time, onoffsum, max_time);
	
	endwhile
	list_generated = list_generated(2:end);
	DIFF_current_file_time_file_time_on
endfunction
