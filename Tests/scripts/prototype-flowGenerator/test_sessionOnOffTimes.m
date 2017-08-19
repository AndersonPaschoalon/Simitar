%#!/usr/bin/octave-cli -qf
% constants 
n_samples = 10000;
SESSION_CUT_TIME = 2.90;
FILE_CUT_TIME = 0.5;
RAND_DATA = 5*rand(n_samples, 1);
EXPRAND_DATA = exprnd(1, n_samples, 1);
RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);


% First Example
fprintf("\n===================================\n1)Default Example \n===================================\n");

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = [0.1 3.1 5.1 5.3 10.3 11.4 11.9 15.9 16.8]';
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = [0.1 3 2 0.2 5 1.1 0.5 4 0.9]';
delta_time = DELTA_SAMPLE; 

% example of pslist
psList = [delta_time;  1];


% in: min time for ON
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, SESSION_CUT_TIME, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));

% Exponential Example
fprintf("\n===================================\n1)Exponential Random\n===================================\n");

% redef
SESSION_CUT_TIME = 7.0;

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = EXPRAND_CUMULATIVE_DATA;
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = EXPRAND_DATA;
delta_time = DELTA_SAMPLE; 

% example of pslist
psList = [delta_time; 1];

% in: min time for ON
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, SESSION_CUT_TIME, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));

% Exponential Example
fprintf("\n===================================\n1)Exponential file data 1\n===================================\n");

%from load data
delta_time = load("data/exp_interarrival_times.txt");
arrival_time = cumulativeData(delta_time);
psList = [delta_time; 1];
cut_time = 7;
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] =  calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));

% Bord case example 1
fprintf("\n===================================\n1)Bord case example 1\n===================================\n");

delta_sample_data = [30.00551800,30.00527800,30.00600200,30.00594800,30.00571400]';
cumulative_sample_data = cumulativeData(delta_sample_data);
arrival_time = cumulative_sample_data;
delta_time = delta_sample_data;
psList = [delta_time; 1];
cut_time = 7;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));

% Bord case example 2
fprintf("\n===================================\n1)Bord case example 2\n===================================\n");

delta_sample_data = [0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 ]';
cumulative_sample_data = cumulativeData(delta_sample_data);
arrival_time = cumulative_sample_data;
delta_time = delta_sample_data;
psList = [delta_time; 1];
cut_time = 7;
[onoff ontimes offtimes  pktCounter fileSize] =  calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\n1)nPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% constants 
n_samples = 10000;
SESSION_CUT_TIME = 2.90;
FILE_CUT_TIME = 0.5;
RAND_DATA = 5*rand(n_samples, 1);
EXPRAND_DATA = exprnd(1, n_samples, 1);
RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);



% First Example
fprintf("\n===================================\n2)Default Example \n===================================\n");

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = [0.1 3.1 5.1 5.3 10.3 11.4 11.9 15.9 16.8]';
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = [0.1 3 2 0.2 5 1.1 0.5 4 0.9]';
delta_time = DELTA_SAMPLE; 

% example of pslist
psList = ones(length(delta_time) + 1, 1) * 3;

% in: min time for ON
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, SESSION_CUT_TIME, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
%printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(delta_time) + 1, sum(fileSize));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(ones(length(delta_time) + 1, 1) * 3), sum(fileSize));

% Exponential Example
fprintf("\n===================================\n2)Exponential Random\n===================================\n");

% redef
SESSION_CUT_TIME = 7.0;

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = EXPRAND_CUMULATIVE_DATA;
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = EXPRAND_DATA;
delta_time = DELTA_SAMPLE; 

% example of pslist
psList = ones(length(delta_time) + 1, 1) * 3;

% in: min time for ON
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, SESSION_CUT_TIME, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(ones(length(delta_time) + 1, 1) * 3), sum(fileSize));

% Exponential Example
fprintf("\n===================================\n2)Exponential file data 1\n===================================\n");

%from load data
delta_time = load("data/exp_interarrival_times.txt");
arrival_time = cumulativeData(delta_time);
psList = ones(length(delta_time) + 1, 1) * 3;
cut_time = 7;
min_time = 0.1;

[onoff ontimes offtimes  pktCounter fileSize] =  calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(ones(length(delta_time) + 1, 1) * 3), sum(fileSize));

% Bord case example 1
fprintf("\n===================================\n2)Bord case example 1\n===================================\n");

delta_sample_data = [30.00551800,30.00527800,30.00600200,30.00594800,30.00571400]';
cumulative_sample_data = cumulativeData(delta_sample_data);
arrival_time = cumulative_sample_data;
delta_time = delta_sample_data;
psList = ones(length(delta_time) + 1, 1) * 3;
cut_time = 7;

[onoff ontimes offtimes  pktCounter fileSize] = calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\nnPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(ones(length(delta_time) + 1, 1) * 3), sum(fileSize));

% Bord case example 2
fprintf("\n===================================\n2)Bord case example 2\n===================================\n");

delta_sample_data = [0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 ]';
cumulative_sample_data = cumulativeData(delta_sample_data);
arrival_time = cumulative_sample_data;
delta_time = delta_sample_data;
psList = ones(length(delta_time) + 1, 1) * 3;
cut_time = 7;
[onoff ontimes offtimes  pktCounter fileSize] =  calcOnOffTimes(arrival_time, delta_time, psList, cut_time, min_time)
%Debug
printf("Debug (The results should be the same.)\n2)nPackets=%d, pktCounterSum=%d\n", length(arrival_time) + 1, sum(pktCounter));
printf("SizeTransfered=%d, sizeEstimation=%d\n", sum(ones(length(delta_time) + 1, 1) * 3), sum(fileSize));











