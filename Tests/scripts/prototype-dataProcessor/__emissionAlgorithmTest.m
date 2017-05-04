%#!/usr/bin/octave-cli -qf
% constants 
n_samples = 10000;
SESSION_CUT_TIME = 2.90;
FILE_CUT_TIME = 0.5;
RAND_DATA = 5*rand(n_samples, 1);
EXPRAND_DATA = exprnd(1, n_samples, 1);
RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);
DELTA_SAMPLE = [0.1 3 2 0.2 5 1.1 0.5 4 0.9]';
ARRIVAL_SAMPLE = [0.1 3.1 5.1 5.3 10.3 11.4 11.9 15.9 16.8]';


% in: list of packet arrival time relative to the first
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
delta_time = DELTA_SAMPLE; 

% in: number of inter packet times
m = length(delta_time);

% in: min time for ON
min_time = 0.1;

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
	if(delta_time(i) > SESSION_CUT_TIME)
		if(i == 1) % if the first is session-off
			j++;
			onOff(j) = min_on;
			j++;
			onOff(j) = delta_time(i);
			last_off = i;
		endif
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
			if(onOff(j) < min_time)
				onOff(j) = min_time;
			endif
			j++;
			onOff(j) = delta_time(i);
			last_off = i;
		endif
	endif
	if(i == m) % last case
		if(last_off == m) % if last is session-off 
			j++;
			onOff(j) = min_time;
		else % base last case
			j++;
			onOff(j) = arrival_time(i) - arrival_time(last_off);
		endif
	endif
endfor




