% constants 
n_samples = 10000;
SESSION_CUT_TIME = 2.90;
FILE_CUT_TIME = 0.5;
RAND_DATA = 5*rand(n_samples, 1);
EXPRAND_DATA = exprnd(1, n_samples, 1);
RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);


% First Example
fprintf("Default Example\n");

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = [0.1 3.1 5.1 5.3 10.3 11.4 11.9 15.9 16.8]';
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = [0.1 3 2 0.2 5 1.1 0.5 4 0.9]';
delta_time = DELTA_SAMPLE; 

% in: min time for ON
min_time = 0.1;

calcOnOffTimes(arrival_time, delta_time, SESSION_CUT_TIME, min_time)
fprintf("Soma on+off = %d\n", sum(calcOnOffTimes(arrival_time, delta_time, SESSION_CUT_TIME, min_time)));


% Exponential Example
fprintf("Exponential\n");

% redef
SESSION_CUT_TIME = 7.0;

% in: list of packet arrival time relative to the first
ARRIVAL_SAMPLE = EXPRAND_CUMULATIVE_DATA;
arrival_time = ARRIVAL_SAMPLE;
 
% in: list of inter packet times
DELTA_SAMPLE = EXPRAND_DATA;
delta_time = DELTA_SAMPLE; 

% in: min time for ON
min_time = 0.1;


[onoff ontimes offtimes] = calcOnOffTimes(arrival_time, delta_time, SESSION_CUT_TIME, min_time);

onoff 
ontimes 
offtimes
fprintf("Soma on+off = %f arrival_time=%f\n", sum(calcOnOffTimes(arrival_time, delta_time, SESSION_CUT_TIME, min_time)), sum(delta_time));


% Exponential Example
fprintf("Exponential file data\n");

%from load data
delta_time = load("data/exp_interarrival_times.txt");
arrival_time = cumulativeData(delta_time);
cut_time = 7;
min_time = 0.1;

[onoff ontimes offtimes] = calcOnOffTimes(arrival_time, delta_time, cut_time, min_time);

onoff

ontimes

offtimes

fprintf("SAMPLE NOW LOL");


delta_sample_data = [30.00551800,30.00527800,30.00600200,30.00594800,30.00571400];
cumulative_sample_data = cumulativeData(arrival_sample_data);
arrival_time = cumulative_sample_data;
delta_time = delta_sample_data;
cut_time = 7;
[onoff ontimes offtimes] = calcOnOffTimes(arrival_time, delta_time, cut_time, min_time);

onoff

ontimes

offtimes















