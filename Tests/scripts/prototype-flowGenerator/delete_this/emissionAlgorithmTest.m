%#!/usr/bin/octave-cli -qf

% this script intend to simulate the emission, but was not finished

% constants 
%n_samples = 10000;
%FILE_CUT_TIME = 0.5;
%RAND_DATA = 5*rand(n_samples, 1);
%EXPRAND_DATA = exprnd(1, n_samples, 1);
%RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
%EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);
%DELTA_SAMPLE = [0.1 3 2 0.2 5 1.1 0.5 4 0.9]';
%ARRIVAL_SAMPLE = [0.1 3.1 5.1 5.3 10.3 11.4 11.9 15.9 16.8]';

%main constants to be defined
session_cut_time = 6;
file_cut_time = 1;

ExpData = load('data/exp_interarrival_times.txt');
RandData = load('data/rand_interarrival_times.txt');
% LAN diurnal pcap
%FlowData = load('data/flow_interarrival_times.txt');

% in: list of packet arrival time relative to the first
arrival_time = cumulativeData(ExpData);
 
% in: list of inter packet times
delta_time = ExpData; 

% in: number of inter packet times
m = length(delta_time);

% in: min time for ON
min_on_time = 0.1;

% max time
max_time = max(arrival_time);

% session cut time 
%session_cut_time = 2.90;


[sessionOnOff onTimes offTimes]= calcOnOffTimes(arrival_time, delta_time, session_cut_time, min_on_time);
[lambdaOnOffInterfile c_mean] = interFileParam_expConst (delta_time, session_cut_time, file_cut_time, min_on_time);
[lambdaFile meanTime] = fileParam_expConst (delta_time, file_cut_time);


[list_generated] = emissionSimulation (onTimes, offTimes, lambdaOnOffInterfile, lambdaFile);

%
meanSimulated = 0;
hustSimulated = 0;

%correlation = corr()
meanOriginal = mean(ExpData);
hustOriginal = hurst(ExpData);

meanSimulated = mean(list_generated);
hustSimulated = hurst(list_generated);

printf("Mean (Original, Simulated) = (%f, %f)\n", meanOriginal, meanSimulated);
printf("Hurst (Original, Simulated) = (%f, %f)\n", hustOriginal, hustSimulated);







