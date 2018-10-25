#!/usr/bin/octave-cli -qf
% Data Processor

% This program:
% - Loads inter-arrival information
% - Use linear regression to fit a set o models
% - Plots all of them, along with the actual data
% - Using maximum likehood function, evaluate the AIC and BIC
% - Test the quality of the estimation using correlation, hurst exponent,
%   mean, and standard deviation of packet rate
% - Save all data in a gnuplot format

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialization
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%arg_list = argv ();
%EXPERIMENT_NAME = arg_list{1};

close all; clc; clf;
pkg load statistics;
format long;
%EXPERIMENT_NAME = "equinix-1s";
EXPERIMENT_NAME = "lanDiurnal";
%configuration
ALMOST_ONE = 0.999999;
ALMOST_ZERO = 0.000001;
INFINITEZIMAL=4e-14
min_time = 5e-8;
WEIBULL_FITTING = 1;
NORMAL_FITTING = 1;
EXPONENTIAL_FITTING = 1; 
PARETO_FITTING = 1;
CAUCHY_FITTING = 1;
EVAL_REPETITIONS = 30;
DATAFILE_NAME_PREFIX = "data/data_";
DATAFILE_NAME_EXT = ".txt";
DATAFILE_NAME = strcat(DATAFILE_NAME_PREFIX, EXPERIMENT_NAME, DATAFILE_NAME_EXT);
DATA_DIR = "data/";
PLOT_DIR = DATA_DIR
PLOT_DATA_EXT = ".dat";

%% Wan Pcap
%weibull_alpha=0.076413; 
%weibull_betha=0.000001;
%normal_mean=0.000002;
%normal_std=0.000001;
%exp_lambda=0.000022;
%exp_lambdaMean=657503.095127;
%pareto_alpha=INFINITEZIMAL; 
%pareto_xm=min_time;
%pareto_mlh_alpha=0.338987; 
%pareto_mlh_xm=min_time;
%cauchy_gamma=828.317809;
%cauchy_x0=-4520.450371;
% Lan Diurnal
weibull_alpha=3.34e-1; 
weibull_betha=1.83e-3;
normal_mean=1.70e-2;
normal_std=8.56e-2;
exp_lambda=8.51e-1;
exp_lambdaMean=58.78;
pareto_alpha=2.55e-1; 
pareto_xm=min_time;
pareto_mlh_alpha=1.15e-1; 
pareto_mlh_xm=min_time;
cauchy_gamma=9.63e-3;
cauchy_x0=-3.61e-3;

%inicialization
%M = dlmread(DATAFILE_NAME, ' ' , 1, 0);
M = load(DATAFILE_NAME);
scale = 1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Run
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
interArrival = abs(sort(M));
interArrival(interArrival == 0) =  min_time;
interArrival = interArrival*scale;

max_time = max(interArrival);
%interArrivalCdf = empiricalCdf(interArrival);
m = length(interArrival);
%plot empirical Cumulative distribution function
fprintf("Ploting inter-arrival cumulative distribution\n");
%plotData(interArrival, interArrivalCdf, 'interArrival', 'F(interArrival)', 'b-', 'Inter-arrival empirical CDF');
%saveas(gca , 'figures/Inter-arrival empirical CDF.png');
title = "Empirical CDF function";
%labels = "interArrival(x), interArrivalCdf(y)";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
%matrix2File([interArrival interArrivalCdf], filename, title, labels);

if (WEIBULL_FITTING != 0)
	weibull_bic = informationCriterion(interArrival, 'weibull', [weibull_alpha weibull_betha], 'bic');
	weibull_aic = informationCriterion(interArrival, 'weibull', [weibull_alpha weibull_betha], 'aic');
endif

if (NORMAL_FITTING != 0)
	normal_bic = informationCriterion(interArrival, 'normal', [normal_mean normal_std], 'bic');
	normal_aic = informationCriterion(interArrival, 'normal', [normal_mean normal_std], 'aic');
endif

if (EXPONENTIAL_FITTING != 0)	
	exponential_lr_bic = informationCriterion(interArrival, 'exponential', [exp_lambda], 'bic');
	exponential_lr_aic = informationCriterion(interArrival, 'exponential', [exp_lambda], 'aic');
	exponential_me_bic = informationCriterion(interArrival, 'exponential', [exp_lambdaMean], 'bic');
	exponential_me_aic = informationCriterion(interArrival, 'exponential', [exp_lambdaMean], 'aic');
endif

if (PARETO_FITTING != 0)
	pareto_lr_bic = informationCriterion(interArrival, 'pareto', [pareto_alpha pareto_xm], 'bic');
	pareto_lr_aic = informationCriterion(interArrival, 'pareto', [pareto_alpha pareto_xm], 'aic');
	pareto_mlh_bic = informationCriterion(interArrival, 'pareto', [pareto_mlh_alpha pareto_mlh_xm], 'bic');
	pareto_mlh_aic = informationCriterion(interArrival, 'pareto', [pareto_mlh_alpha pareto_mlh_xm], 'aic');
endif

if(CAUCHY_FITTING != 0)	
	cauchy_bic = informationCriterion(interArrival, 'cauchy', [cauchy_gamma cauchy_x0], 'bic');
	cauchy_aic = informationCriterion(interArrival, 'cauchy', [cauchy_gamma cauchy_x0], 'aic');
endif


title = "functions-parameters";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
fid = fopen(filename,'wt');
fprintf(fid,'Weibull: weibull_alpha=%f, weibull_betha=%f\n', weibull_alpha, weibull_betha);
fprintf(fid,'Normal: normal_mean=%f, normal_std=%f\n', normal_mean, normal_std);
fprintf(fid,'Exponential(LR)=%f\n', exp_lambda);
fprintf(fid,'Exponential(Me)=%f\n', exp_lambdaMean);
fprintf(fid,'Pareto(LR): pareto_alpha=%f, pareto_xm=%f\n', pareto_alpha, pareto_xm);
fprintf(fid,'Pareto(MLH): pareto_mlh_alpha=%f, pareto_mlh_xm=%f\n', pareto_mlh_alpha, pareto_mlh_xm);
fprintf(fid,'Cauchy: cauchy_gamma=%f, cauchy_x0=%f\n', cauchy_gamma, cauchy_x0);
fprintf(fid,'\n');
fclose(fid);


title = "Aic-Bic";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
fid = fopen(filename,'wt');
fprintf(fid,'\n');
fprintf(fid,'+----------------+--------------+---------------+\n');
fprintf(fid,'|Function        |AIC           |BIC            |\n');
fprintf(fid,'+----------------+--------------+---------------+\n');
if (WEIBULL_FITTING != 0)
	fprintf(fid,'|Weibull         |%f\t|%f\t|\n',weibull_aic, weibull_bic);
endif
if(NORMAL_FITTING != 0)
	fprintf(fid,'|Normal          |%f\t|%f\t|\n',normal_aic, normal_bic);
endif
if(EXPONENTIAL_FITTING != 0)
	fprintf(fid,'|Exponential(LR) |%f\t|%f\t|\n',exponential_lr_aic, exponential_lr_bic);
	fprintf(fid,'|Exponential(Me) |%f\t|%f\t|\n',exponential_me_aic, exponential_me_bic);
endif
if(PARETO_FITTING != 0)
	fprintf(fid,'|Pareto(LR)      |%f\t|%f\t|\n',pareto_lr_aic, pareto_lr_bic);
	fprintf(fid,'|Pareto(MLH)     |%f\t|%f\t|\n',pareto_mlh_aic, pareto_mlh_bic );
endif
if(CAUCHY_FITTING != 0)
	fprintf(fid,'|Cauchy          |%f\t|%f\t|\n',cauchy_aic, cauchy_bic);
endif
fprintf(fid,'+----------------+--------------+---------------+\n');
fclose(fid);


fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Function        |AIC           |BIC            |\n');
fprintf('+----------------+--------------+---------------+\n');
if (WEIBULL_FITTING != 0)
	fprintf('|Weibull         |%f\t|%f\t|\n',weibull_aic, weibull_bic);
endif
if(NORMAL_FITTING != 0)
	fprintf('|Normal          |%f\t|%f\t|\n',normal_aic, normal_bic);
endif
if(EXPONENTIAL_FITTING != 0)
	fprintf('|Exponential(LR) |%f\t|%f\t|\n',exponential_lr_aic, exponential_lr_bic);
	fprintf('|Exponential(Me) |%f\t|%f\t|\n',exponential_me_aic, exponential_me_bic);
endif
if(PARETO_FITTING != 0)
	fprintf('|Pareto(LR)      |%f\t|%f\t|\n',pareto_lr_aic, pareto_lr_bic);
	fprintf('|Pareto(MLH)     |%f\t|%f\t|\n',pareto_mlh_aic, pareto_mlh_bic );
endif
if(CAUCHY_FITTING != 0)
	fprintf('|Cauchy          |%f\t|%f\t|\n',cauchy_aic, cauchy_bic);
endif
fprintf('+----------------+--------------+---------------+\n');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Evaluation of the models
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% generate a random vector of simulatted interarrivals, following the
% generated models

if (WEIBULL_FITTING != 0)
	% wblrnd (SCALE, SHAPE)
	weibull_interArrival = sort(wblrnd(weibull_betha, weibull_alpha, m, 1));
endif

if (NORMAL_FITTING != 0)
	% normrnd (MU, SIGMA)
	normal_interArrival =  sort(normrnd(normal_mean, normal_std, m, 1));
endif
	
if (EXPONENTIAL_FITTING != 0 )
	% exprnd (LAMBDA)
	exponential_lr_interArrival = sort(exprnd (exp_lambda, m, 1 ));
	% exprnd (LAMBDA)
	exponential_me_interArrival = sort(exprnd (exp_lambdaMean, m, 1 ));
endif
if (PARETO_FITTING != 0)
	% gprnd (LOCATION, SCALE, SHAPE)
	% https://en.wikipedia.org/wiki/Generalized_Pareto_distribution
	% https://www.mathworks.com/help/stats/gprnd.html
	gpareto_k = 1/pareto_alpha; %SHAPE
	gpareto_sigma = gpareto_k*pareto_xm; %SCALE
	gpareto_theta = gpareto_sigma/gpareto_k; %LOCATION
	pareto_lr_interArrival = sort(gprnd(gpareto_theta, gpareto_sigma, gpareto_k, m, 1)) ;
	% gprnd (LOCATION, SCALE, SHAPE)
	gpareto_k = 1/pareto_mlh_alpha; %SHAPE
	gpareto_sigma = gpareto_k*pareto_mlh_xm; %SCALE
	gpareto_theta = gpareto_sigma/gpareto_k; %LOCATION
	pareto_mlh_interArrival = sort(gprnd(gpareto_theta, gpareto_sigma, gpareto_k, m, 1)) ;
endif
if (CAUCHY_FITTING != 0)
	%  cauchy_rnd (LOCATION, SCALE)
	% https://en.wikipedia.org/wiki/Cauchy_distribution
	cauchy_interArrival = sort(cauchy_rnd(cauchy_x0, cauchy_gamma, m, 1));
endif

% Normalize data
% the data must be plausibe. the time cant be negative, and the larger time cannot excede the overall time
%sum_interArrival = sum(interArrival);
sum_interArrival = max(interArrival);
if(WEIBULL_FITTING != 0)
	weibull_interArrival(weibull_interArrival < 0) = 0;
	weibull_interArrival(weibull_interArrival > sum_interArrival) =  sum_interArrival;
endif	
if(NORMAL_FITTING != 0)
	normal_interArrival( normal_interArrival < 0) = 0;
	normal_interArrival( normal_interArrival  > sum_interArrival) =  sum_interArrival;
endif
if(EXPONENTIAL_FITTING != 0)
	exponential_lr_interArrival( exponential_lr_interArrival < 0) = 0;
	exponential_me_interArrival( exponential_me_interArrival < 0) = 0;
	exponential_lr_interArrival( exponential_lr_interArrival  > sum_interArrival) =  sum_interArrival;
	exponential_me_interArrival( exponential_me_interArrival  > sum_interArrival) =  sum_interArrival;
endif
if(EXPONENTIAL_FITTING != 0)
	pareto_lr_interArrival( pareto_lr_interArrival < 0) = 0;
	pareto_mlh_interArrival( pareto_mlh_interArrival < 0) = 0;
	pareto_lr_interArrival( pareto_lr_interArrival  > sum_interArrival) =  sum_interArrival;
	pareto_mlh_interArrival( pareto_mlh_interArrival  > sum_interArrival) =  sum_interArrival;
endif
if(CAUCHY_FITTING != 0)
	cauchy_interArrival( cauchy_interArrival < 0) = 0;
	cauchy_interArrival( cauchy_interArrival  > sum_interArrival) =  sum_interArrival;
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QQplots
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('\n');
%
if(WEIBULL_FITTING != 0)
%	figure; %new figure
%	%plotData( interArrival, weibull_interArrival, 'empirical', 'weibull', '-g', 'QQplot - Weibull');
	qqxy = qqPlot( interArrival, weibull_interArrival, 'empirical', 'weibull', '-g', 'QQplot - Weibull');
%	saveas(gca , 'test-data/QQplot - weibull.png');
%
	title = "QQplot - Weibull";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);	
%	
endif
if(NORMAL_FITTING != 0)
%	figure; %new figure
%	%plotData(interArrival, normal_interArrival, 'empirical', 'normal', '-g', 'QQplot - Normal');
	qqxy = qqPlot(interArrival, normal_interArrival, 'empirical', 'normal', '-g', 'QQplot - Normal');
%	saveas(gca , 'test-data/QQplot - normal.png');
%	
	title = "QQplot - Normal";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);	
endif
if(EXPONENTIAL_FITTING != 0)
%	figure; %new figure
%	%plotData(interArrival, exponential_lr_interArrival, 'empirical', 'exponential (Linear Regression)', '-g', 'QQplot - Exponential (Linear Regression)');
	qqxy = qqPlot(interArrival, exponential_lr_interArrival, 'empirical', 'exponential (Linear Regression)', '-g', 'QQplot - Exponential (Linear Regression)');
%	saveas(gca , 'test-data/QQplot - exponential_lr.png');
	title = "QQplot - Exponential(LR)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
%	
%	figure; %new figure
%	%plotData(interArrival, exponential_me_interArrival, 'empirical', 'exponential (Mean)', '-g', 'QQplot - Exponential (Mean)');
	qqxy = qqPlot(interArrival, exponential_me_interArrival, 'empirical', 'exponential (Mean)', '-g', 'QQplot - Exponential (Mean)');
%	saveas(gca , 'test-data/QQplot - exponential_me.png');
	title = "QQplot - Exponential(Me)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
endif
if(PARETO_FITTING != 0)
%	figure; %new figure
%	%plotData(interArrival, pareto_lr_interArrival, 'empirical', 'pareto (Linear Regression)', '-g', 'QQplot - Pareto (Linear Regression)');
	qqxy = qqPlot(interArrival, pareto_lr_interArrival, 'empirical', 'pareto (Linear Regression)', '-g', 'QQplot - Pareto (Linear Regression)');
%	saveas(gca , 'test-data/QQplot - pareto_lr.png');
	title = "QQplot - Pareto(LR)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
%	
%	figure; %new figure
%	%plotData(interArrival, pareto_mlh_interArrival, 'empirical', 'pareto (Maximum Likehood)', '-g', 'QQplot - Pareto (Maximum Likehood)');
	qqxy = qqPlot(interArrival, pareto_mlh_interArrival, 'empirical', 'pareto (Maximum Likehood)', '-g', 'QQplot - Pareto (Maximum Likehood)');
%	saveas(gca , 'test-data/QQplot - pareto_mlh.png');
	title = "QQplot - Pareto(MLH)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
endif
if(CAUCHY_FITTING != 0)
	figure; %new figure
%	%plotData(interArrival, cauchy_interArrival, 'empirical', 'Cauchy', '-g', 'QQplot - Cauchy');
	qqxy = qqPlot(interArrival, cauchy_interArrival, 'empirical', 'Cauchy', '-g', 'QQplot - Cauchy');
%	saveas(gca , 'test-data/QQplot - Cauchy.png');
	title = "QQplot - Cauchy";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
endif

fprintf('\n');
fprintf('Mean and std.dev');
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |mean          |std.dev        |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n',mean(interArrival), std(interArrival));
if(WEIBULL_FITTING != 0)
	fprintf('|Weibull         |%f\t|%f\t|\n',mean(weibull_interArrival), std(weibull_interArrival));
endif
if(NORMAL_FITTING != 0)
	fprintf('|Normal          |%f\t|%f\t|\n',mean(normal_interArrival), std(normal_interArrival));
endif
if(EXPONENTIAL_FITTING != 0)
	fprintf('|Exponential(LR) |%f\t|%f\t|\n',mean(exponential_lr_interArrival), std(exponential_lr_interArrival));
	fprintf('|Exponential(Me) |%f\t|%f\t|\n',mean(exponential_me_interArrival), std(exponential_me_interArrival));
endif
if(PARETO_FITTING != 0)
	fprintf('|Pareto(LR)      |%f\t|%f\t|\n',mean(pareto_lr_interArrival), std(pareto_lr_interArrival));
	fprintf('|Pareto(MLH)     |%f\t|%f\t|\n',mean(pareto_mlh_interArrival), std(pareto_mlh_interArrival) );
endif
if(CAUCHY_FITTING != 0)
	fprintf('|Cauchy          |%f\t|%f\t|\n',mean(cauchy_interArrival), std(cauchy_interArrival));
endif
fprintf('+----------------+--------------+---------------+\n');

hust_org = hurst(interArrival);

if(WEIBULL_FITTING != 0)
	hust_weibull = hurst(weibull_interArrival);
endif
if(NORMAL_FITTING != 0)
	hust_normal = hurst(normal_interArrival);
endif
if(EXPONENTIAL_FITTING != 0)
	hust_exponential_lr = hurst(exponential_lr_interArrival);
	hust_exponential_me = hurst(exponential_me_interArrival);
endif
if(PARETO_FITTING != 0)
	hust_pareto_lr = hurst(pareto_lr_interArrival);
	hust_pareto_mlh = hurst(pareto_mlh_interArrival);
endif
if(CAUCHY_FITTING != 0)
	hust_cauchy = hurst(cauchy_interArrival);
endif

fprintf('\n');
fprintf('Hust Exponent');
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |hust          |diff           |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n',hust_org, adiff(hust_org, hust_org));
if(WEIBULL_FITTING != 0)
	fprintf('|Weibull         |%f\t|%f\t|\n',hust_weibull, adiff(hust_org, hust_weibull));
endif
if(NORMAL_FITTING != 0)
	fprintf('|Normal          |%f\t|%f\t|\n',hust_normal, adiff(hust_org, hust_normal));
endif
if(EXPONENTIAL_FITTING != 0)
	fprintf('|Exponential(LR) |%f\t|%f\t|\n',hust_exponential_lr, adiff(hust_org, hust_exponential_lr));
	fprintf('|Exponential(Me) |%f\t|%f\t|\n',hust_exponential_me, adiff(hust_org, hust_exponential_me));
endif
if(PARETO_FITTING != 0)
	fprintf('|Pareto(LR)      |%f\t|%f\t|\n',hust_pareto_lr, adiff(hust_org, hust_pareto_lr));
	fprintf('|Pareto(MLH)     |%f\t|%f\t|\n',hust_pareto_mlh, adiff(hust_org, hust_pareto_mlh) );
endif
if(CAUCHY_FITTING != 0)
	fprintf('|Cauchy          |%f\t|%f\t|\n',hust_cauchy, adiff(hust_org, hust_cauchy));
endif
fprintf('+----------------+--------------+---------------+\n');

fprintf('\n');

%repetition Matrix M
% M(1,:) -> correlation
% M(2,:) -> mean
% M(2,:) -> std.dev 
% M(2,:) -> hurst
M = zeros(4, 1);
M(1) = 0;
M(2) = mean(interArrival);
M(3) = std(interArrival);
M(4) = hurst(interArrival);
M_w = zeros(4, EVAL_REPETITIONS);
M_n = zeros(4, EVAL_REPETITIONS);
M_elr = zeros(4, EVAL_REPETITIONS);
M_eme = zeros(4, EVAL_REPETITIONS);
M_plr = zeros(4, EVAL_REPETITIONS);
M_pml = zeros(4, EVAL_REPETITIONS);
M_c = zeros(4, EVAL_REPETITIONS);


for i = 1:EVAL_REPETITIONS

	if (WEIBULL_FITTING != 0)
		% wblrnd (SCALE, SHAPE)
		weibull_interArrival = sort(wblrnd(weibull_betha, weibull_alpha, m, 1));
	endif

	if (NORMAL_FITTING != 0)
		% normrnd (MU, SIGMA)
		normal_interArrival =  sort(normrnd(normal_mean, normal_std, m, 1));
	endif
		
	if (EXPONENTIAL_FITTING != 0 )
		% exprnd (LAMBDA)
		exponential_lr_interArrival = sort(exprnd (1/exp_lambda, m, 1 ));
		% exprnd (LAMBDA)
		exponential_me_interArrival = sort(exprnd (1/exp_lambdaMean, m, 1 ));
	endif
	if (PARETO_FITTING != 0)
		% gprnd (LOCATION, SCALE, SHAPE)
		% https://en.wikipedia.org/wiki/Generalized_Pareto_distribution
		% https://www.mathworks.com/help/stats/gprnd.html
		gpareto_k = 1/pareto_alpha; %SHAPE
		gpareto_sigma = gpareto_k*pareto_xm; %SCALE
		gpareto_theta = gpareto_sigma/gpareto_k; %LOCATION
		pareto_lr_interArrival = sort(gprnd(gpareto_theta, gpareto_sigma, gpareto_k, m, 1)) ;
		% gprnd (LOCATION, SCALE, SHAPE)
		gpareto_k = 1/pareto_mlh_alpha; %SHAPE
		gpareto_sigma = gpareto_k*pareto_mlh_xm; %SCALE
		gpareto_theta = gpareto_sigma/gpareto_k; %LOCATION
		pareto_mlh_interArrival = sort(gprnd(gpareto_theta, gpareto_sigma, gpareto_k, m, 1)) ;
	endif
	if (CAUCHY_FITTING != 0)
		%  cauchy_rnd (LOCATION, SCALE)
		% https://en.wikipedia.org/wiki/Cauchy_distribution
		cauchy_interArrival = sort(cauchy_rnd(cauchy_x0, cauchy_gamma, m, 1));
	endif

	% Normalize data
	% the data must be plausibe. the time cant be negative, and the larger time cannot excede the overall time
	%sum_interArrival = sum(interArrival);
	
	if(WEIBULL_FITTING != 0)
		weibull_interArrival(weibull_interArrival < 0) = 0;
		weibull_interArrival(weibull_interArrival > sum_interArrival) =  sum_interArrival;
	endif	
	if(NORMAL_FITTING != 0)
		normal_interArrival( normal_interArrival < 0) = 0;
		normal_interArrival( normal_interArrival  > sum_interArrival) =  sum_interArrival;
	endif
	if(EXPONENTIAL_FITTING != 0)
		exponential_lr_interArrival( exponential_lr_interArrival < 0) = 0;
		exponential_me_interArrival( exponential_me_interArrival < 0) = 0;
		exponential_lr_interArrival( exponential_lr_interArrival  > sum_interArrival) =  sum_interArrival;
		exponential_me_interArrival( exponential_me_interArrival  > sum_interArrival) =  sum_interArrival;
	endif
	if(EXPONENTIAL_FITTING != 0)
		pareto_lr_interArrival( pareto_lr_interArrival < 0) = 0;
		pareto_mlh_interArrival( pareto_mlh_interArrival < 0) = 0;
		pareto_lr_interArrival( pareto_lr_interArrival  > sum_interArrival) =  sum_interArrival;
		pareto_mlh_interArrival( pareto_mlh_interArrival  > sum_interArrival) =  sum_interArrival;
	endif
	if(CAUCHY_FITTING != 0)
		cauchy_interArrival( cauchy_interArrival < 0) = 0;
		cauchy_interArrival( cauchy_interArrival  > sum_interArrival) =  sum_interArrival;
	endif

	
	if(WEIBULL_FITTING != 0)
		%compute correlation
		M_w(1, i) = corr(interArrival, weibull_interArrival);
		M_w(2, i) = mean(weibull_interArrival);
		M_w(3, i) = std(weibull_interArrival);
		M_w(4, i) = hurst(weibull_interArrival);
		
	endif	
	if(NORMAL_FITTING != 0)
		M_n(1, i) = corr(interArrival, normal_interArrival);
		M_n(2, i) = mean(normal_interArrival);
		M_n(3, i) = std(normal_interArrival);
		M_n(4, i) = hurst(normal_interArrival);

	endif
	if(EXPONENTIAL_FITTING != 0)
		M_elr(1, i) = corr(interArrival, exponential_lr_interArrival);
		M_elr(2, i) = mean(exponential_lr_interArrival);
		M_elr(3, i) = std(exponential_lr_interArrival);
		M_elr(4, i) = hurst(exponential_me_interArrival);
		
		M_eme(1, i) = corr(interArrival, exponential_me_interArrival);
		M_eme(2, i) = mean(exponential_me_interArrival);
		M_eme(3, i) = std(exponential_me_interArrival);
		M_eme(4, i) = hurst(exponential_me_interArrival);

	endif
	if(EXPONENTIAL_FITTING != 0)
		M_plr(1, i) = corr(interArrival, pareto_lr_interArrival);
		M_plr(2, i) = mean(pareto_lr_interArrival);
		M_plr(3, i) = std(pareto_lr_interArrival);
		M_plr(4, i) = hurst(pareto_lr_interArrival); 
		
		M_pml(1, i) = corr(interArrival, pareto_mlh_interArrival);
		M_pml(2, i) = mean(pareto_mlh_interArrival);
		M_pml(3, i) = std(pareto_mlh_interArrival);
		M_pml(4, i) = hurst(pareto_mlh_interArrival); 

	endif
	if(CAUCHY_FITTING != 0)
		M_c(1, i) = corr(interArrival, cauchy_interArrival);
		M_c(2, i) = mean(cauchy_interArrival);
		M_c(3, i) = std(cauchy_interArrival);
		M_c(4, i) = hurst(cauchy_interArrival);

	endif

endfor


confidenceFactor = 1.960/sqrt(EVAL_REPETITIONS); %95%

fprintf('\n');
fprintf('Correlation [repetitions: %d]\n',EVAL_REPETITIONS);
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |correlation   | corr std.dev  |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n', 0, 0);
fprintf('|Weibull         |%f\t|%f\t|\n', mean(M_w(1,:)), std(M_w(1,:)));
fprintf('|Normal          |%f\t|%f\t|\n', mean(M_n(1,:)), std(M_n(1,:)));
fprintf('|Exponential(LR) |%f\t|%f\t|\n', mean(M_elr(1,:)), std(M_elr(1,:)));
fprintf('|Exponential(Me) |%f\t|%f\t|\n', mean(M_eme(1,:)), std(M_eme(1,:)));
fprintf('|Pareto(LR)      |%f\t|%f\t|\n', mean(M_plr(1,:)), std(M_plr(1,:)));
fprintf('|Pareto(MLH)     |%f\t|%f\t|\n', mean(M_pml(1,:)), std(M_pml(1,:)));
fprintf('|Cauchy          |%f\t|%f\t|\n', mean(M_c(1,:)), std(M_c(1,:)));
fprintf('+----------------+--------------+---------------+\n');
fprintf('\n');


corr_x = [1 2 3 4 5 6 7];
corr_x_label = ["Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
corr_y = [mean(M_w(1,:)) mean(M_n(1,:)) mean(M_elr(1,:)) mean(M_eme(1,:)) mean(M_plr(1,:)) mean(M_pml(1,:)) mean(M_c(1,:))]';
corr_e = [std(M_w(1,:)) std(M_n(1,:)) std(M_elr(1,:)) std(M_eme(1,:)) std(M_plr(1,:)) std(M_pml(1,:)) std(M_c(1,:))]';
corr_e = corr_e*confidenceFactor;
title = "Correlation";
labels = "Distribution, Correlation, Error";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
sff2File(filename, title, labels, ',', corr_x_label, corr_y, corr_e);



fprintf('\n');
fprintf('Mean [repetitions: %d]\n',EVAL_REPETITIONS);
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |mean          | mean std.dev |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n', mean(M(2,:)), std(M(2,:)));
fprintf('|Weibull         |%f\t|%f\t|\n', mean(M_w(2,:)), std(M_w(2,:)));
fprintf('|Normal          |%f\t|%f\t|\n', mean(M_n(2,:)), std(M_n(2,:)));
fprintf('|Exponential(LR) |%f\t|%f\t|\n', mean(M_elr(2,:)), std(M_elr(2,:)));
fprintf('|Exponential(Me) |%f\t|%f\t|\n', mean(M_eme(2,:)), std(M_eme(2,:)));
fprintf('|Pareto(LR)      |%f\t|%f\t|\n', mean(M_plr(2,:)), std(M_plr(2,:)));
fprintf('|Pareto(MLH)     |%f\t|%f\t|\n', mean(M_pml(2,:)), std(M_pml(2,:)));
fprintf('|Cauchy          |%f\t|%f\t|\n', mean(M_c(2,:)), std(M_c(2,:)));
fprintf('+----------------+--------------+---------------+\n');
fprintf('\n');


mean_x = [1 2 3 4 5 6 7 8];
mean_x_label = ["Original"; "Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
mean_y = [mean(M(2,:)) mean(M_w(2,:)) mean(M_n(2,:)) mean(M_elr(2,:)) mean(M_eme(2,:)) mean(M_plr(2,:)) mean(M_pml(2,:)) mean(M_c(2,:))];
mean_e = [std(M(2,:)) std(M_w(2,:)) std(M_n(2,:)) std(M_elr(2,:)) std(M_eme(2,:)) std(M_plr(2,:)) std(M_pml(2,:)) std(M_c(2,:))];
mean_e = mean_e*confidenceFactor;
title = "Mean";
labels = "Distribution, Mean, Error";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
sff2File(filename, title, labels, ',', mean_x_label, mean_y, mean_e);

fprintf('\n');
fprintf('Std.dev [repetitions: %d]\n',EVAL_REPETITIONS);
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |std.dev       |std.dev std.dev|\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n', mean(M(3,:)), std(M(3,:)));
fprintf('|Weibull         |%f\t|%f\t|\n', mean(M_w(3,:)), std(M_w(3,:)));
fprintf('|Normal          |%f\t|%f\t|\n', mean(M_n(3,:)), std(M_n(3,:)));
fprintf('|Exponential(LR) |%f\t|%f\t|\n', mean(M_elr(2,:)), std(M_elr(3,:)));
fprintf('|Exponential(Me) |%f\t|%f\t|\n', mean(M_eme(3,:)), std(M_eme(3,:)));
fprintf('|Pareto(LR)      |%f\t|%f\t|\n', mean(M_plr(3,:)), std(M_plr(3,:)));
fprintf('|Pareto(MLH)     |%f\t|%f\t|\n', mean(M_pml(3,:)), std(M_pml(3,:)));
fprintf('|Cauchy          |%f\t|%f\t|\n', mean(M_c(3,:)), std(M_c(3,:)));
fprintf('+----------------+--------------+---------------+\n');
fprintf('\n');

stddev_x = [1 2 3 4 5 6 7 8];
stddev_x_label = ["Original"; "Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
stddev_y = [mean(M(3,:))  mean(M_w(3,:)) mean(M_n(3,:)) mean(M_elr(3,:)) mean(M_eme(3,:)) mean(M_plr(3,:)) mean(M_pml(3,:)) mean(M_c(3,:))];
stddev_e = [std(M(3,:)) std(M_w(3,:)) std(M_n(3,:)) std(M_elr(3,:)) std(M_eme(3,:)) std(M_plr(3,:)) std(M_pml(3,:)) std(M_c(3,:))];
stddev_e = stddev_e*confidenceFactor;
title = "Standard Deviation";
labels = "Distribution, StdDev, Error";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
sff2File(filename, title, labels, ',', stddev_x_label, stddev_y, stddev_e);

fprintf('\n');
fprintf('Hurst Exponent [repetitions: %d]\n',EVAL_REPETITIONS);
fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Distribution    |hust          | hurst std.dev |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Original        |%f\t|%f\t|\n', mean(M(4,:)), std(M(4,:)));
fprintf('|Weibull         |%f\t|%f\t|\n', mean(M_w(4,:)), std(M_w(4,:)));
fprintf('|Normal          |%f\t|%f\t|\n', mean(M_n(4,:)), std(M_n(4,:)));
fprintf('|Exponential(LR) |%f\t|%f\t|\n', mean(M_elr(4,:)), std(M_elr(4,:)));
fprintf('|Exponential(Me) |%f\t|%f\t|\n', mean(M_eme(4,:)), std(M_eme(4,:)));
fprintf('|Pareto(LR)      |%f\t|%f\t|\n', mean(M_plr(4,:)), std(M_plr(4,:)));
fprintf('|Pareto(MLH)     |%f\t|%f\t|\n', mean(M_pml(4,:)), std(M_pml(4,:)));
fprintf('|Cauchy          |%f\t|%f\t|\n', mean(M_c(4,:)), std(M_c(4,:)));
fprintf('+----------------+--------------+---------------+\n');
fprintf('\n');


hurst_x = [1 2 3 4 5 6 7 8];
hurst_x_label = ["Original"; "Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
hurst_y = [mean(M(4,:)) mean(M_w(4,:)) mean(M_n(4,:)) mean(M_elr(4,:)) mean(M_eme(4,:)) mean(M_plr(4,:)) mean(M_pml(4,:)) mean(M_c(4,:))];
hurst_e = [std(M(4,:)) std(M_w(4,:)) std(M_n(4,:)) std(M_elr(4,:)) std(M_eme(4,:)) std(M_plr(4,:)) std(M_pml(4,:)) std(M_c(4,:))];
hurst_e = hurst_e*confidenceFactor;
title = "Hurst Exponent";
labels = "Distribution, Hust, Error";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
sff2File(filename, title, labels, ',', hurst_x_label, hurst_y, hurst_e);


