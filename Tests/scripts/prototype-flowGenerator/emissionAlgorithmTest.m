%#!/usr/bin/octave-cli -qf
% constants 
n_samples = 10000;
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

% session cut time 
session_cut_time = 2.90;


onOff = sessionOnOffTimes(arrival_time, delta_time, session_cut_time, min_time)


