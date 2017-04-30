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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialization and load data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%inicialization
arg_list = argv ();
%clear; clear all; 
close all; clc; clf;
pkg load statistics;
graphics_toolkit ("gnuplot");
set(0, 'DefaultLineLineWidth', 4);
set(0,'defaulttextfontsize', 14);
set(0,'DefaultAxesFontSize',12)
set(0,'DefaultAxesFontName', 'Times New Roman')
%configuration
ALMOST_ONE = 0.999999;
ALMOST_ZERO = 0.000001;
%INFINITEZIMAL=10E-20;
INFINITEZIMAL=4e-14
%min_time = 0.00000005;
min_time = 5e-8;
#min_time = 0.0000005;
WEIBULL_FITTING = 1;
NORMAL_FITTING = 1;
EXPONENTIAL_FITTING = 1; 
PARETO_FITTING = 1;
CAUCHY_FITTING = 1;
EVAL_REPETITIONS = 30;
%data load
%EXPERIMENT_NAME = "kkk"; %command line arg
EXPERIMENT_NAME = arg_list{1};
DATAFILE_NAME_PREFIX = "../data/matlab_data_";
DATAFILE_NAME_EXT = ".txt";
DATAFILE_NAME = strcat(DATAFILE_NAME_PREFIX,EXPERIMENT_NAME, DATAFILE_NAME_EXT);
PLOT_DIR = "../../plots/";
PLOT_DATA_EXT = ".dat";
%M = dlmread(DATAFILE_NAME, ' ' , 1, 0);
M = load(DATAFILE_NAME);
%interArrival = sort(M(:,4)) + min_time;
%interArrival = abs(sort(M)) + min_time;
interArrival = abs(sort(M));
interArrival(interArrival == 0) =  min_time;
max_time = max(interArrival);
interArrivalCdf = empiricalCdf(interArrival);
m = length(interArrival);
%plot empirical Cumulative distribution function
fprintf("Ploting inter-arrival cumulative distribution\n");
plotData(interArrival, interArrivalCdf, 'interArrival', 'F(interArrival)', 'b-', 'Inter-arrival empirical CDF');
saveas(gca , 'figures/Inter-arrival empirical CDF.png');
title = "Empirical CDF function";
labels = "interArrival(x), interArrivalCdf(y)";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
matrix2File([interArrival interArrivalCdf], filename, title, labels);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Weibull fitting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(WEIBULL_FITTING != 0)
        fprintf("\n*********************\nWeibull data fitting\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        %y = log(-log(1.00 - interArrivalCdf));
        y = log(-log(1.00 - interArrivalCdf));
        x = log(interArrival);
        %dlmwrite('xy.txt',[x y]); %?????????
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-+', 'Linearized data and linear fitting');

        % gradient descendent
        fprintf('Running Gradient Descent ...\n')
        X = [ones(m, 1), x(:,1)]; % Add a column of ones to x
        theta = zeros(2, 1); % initialize fitting parameters
        % gradient descent settings
        iterations = 1500;
        learning_rate = 0.01;
        % run gradient descent
        [theta J_history ] = gradientDescent(X, y, theta, learning_rate, iterations);
        % print theta to screen
        fprintf('Theta found by gradient descent: %f %f \n', theta(1), theta(2));
        fprintf('Initial coast J(1) = %f; Final coast J(end) = %f \n', J_history(1), J_history(end));
        hold on; % keep previous plot visible
        % plot the linear fit over the non-linear (linearized) data
        plot(X(:,2), X*theta, 'r-')
        legend('Training data', 'Linear regression', 'Location','southeast'  ,'Orientation','vertical');
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Weibull - Linearized data and linear fitting.png');

        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Weibull - Cost J(iterations) convergence');
        saveas(gca , 'figures/Weibull - Cost J(iterations) convergence.png');

        %parameter estimation
        weibull_alpha = abs(theta(2));
	if( abs(theta(2)) < INFINITEZIMAL) 
		theta(2) = INFINITEZIMAL;
	endif
        weibull_betha = abs(real(exp(-theta(1)/theta(2))));

        % Plot original data and aproximation fitting
        cdfW = cdfWeibullPlot(weibull_alpha, weibull_betha, max_time,'Weibull aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
	legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical');
        saveas(gca , 'figures/Weibull aproximation vs Original set.png');
        
        hold off;
	
	%linealization plot
	title = "Weibull - Linearized data and linear fitting";
	labels = "Linearized-data(x), Linearized-data(y), Aproximation(x), Aproximation(y)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([x y X(:,2) X*theta], filename, title, labels);
	title = "Weibull - Cost J(iterations) convergence";
	labels = "iterations, J(iterations)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([(1:length(J_history))' J_history], filename, title, labels);
	title = "Weibull aproximation vs Original set";
	labels = "W(x), W(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfW, filename, title, labels);	
	
	
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Normal fitting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(NORMAL_FITTING != 0)
        fprintf("\n*********************\nNormal data fitting\n*********************\n");
        normal_mean = mean(interArrival);
        normal_std = std(interArrival);
        fprintf("Mean = %f \n", normal_mean);
        fprintf("Std = %f \n", normal_std);

        % Plot original data and aproximation fitting
        cdfN = cdfNormalPlot(normal_mean, normal_std, max_time, 'Normal aproximation vs Original set' );
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca, 'figures/Normal aproximation vs Original set.png');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical')
        hold off;
	
	title = "Normal aproximation vs Original set";
	labels = "Normal(x), Normal(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfN, filename, title, labels);		
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Exponential fitting (Linear Regression)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(EXPONENTIAL_FITTING != 0)
        fprintf("\n*********************\nExponential data fitting 1: Linear Regression\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        y = log(1.00 - interArrivalCdf);
        x = interArrival;
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-+', 'Linearized data and linear fitting');

        % gradient descendent
        fprintf('Running Gradient Descent ...\n')
        X = [ones(m, 1), x(:,1)]; % Add a column of ones to x
        theta = zeros(2, 1); % initialize fitting parameters
        % gradient descent settings
        iterations = 1500;
        learning_rate = 0.01;
        % run gradient descent
        [theta J_history ] = gradientDescent(X, y, theta, learning_rate, iterations);
        % print theta to screen
        fprintf('Theta found by gradient descent: %f %f \n', theta(1), theta(2));
        fprintf('Initial coast J(1) = %f; Final coast J(end) = %f \n', J_history(1), J_history(end));
        hold on; % keep previous plot visible
        % plot the linear fit over the non-linear (linearized) data
        plot(X(:,2), X*theta, 'r-')
        legend('Training data', 'Linear regression', 'Location','southeast'  ,'Orientation','vertical')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Exponential (LR) - Linearized data and linear fitting.png');

        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Exponential (LR) - Cost J(iterations) convergence');
        saveas(gca , 'figures/Exponential (LR) - Cost J(iterations) convergence.png');

        %parameter estimation
        exp_lambda = -theta(2);
        exp_mean = mean(interArrival);
        fprintf("exp_lambda = %f \n", exp_lambda);
        %fprintf("Actual mean = %f \n", exp_mean);

        % Plot original data and aproximation fitting
        cdfElr = cdfExponentialPlot(exp_lambda, max_time,'Exponential aproximation (LR) vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca , 'figures/Exponential aproximation (LR) vs Original set.png');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical')
        hold off;
	
	%linealization plot
	title = "Exponential - Linearized data and linear fitting";
	labels = "Linearized-data(x), Linearized-data(y), Aproximation(x), Aproximation(y)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([x y X(:,2) X*theta], filename, title, labels);
	title = "Exponential - Cost J(iterations) convergence";
	labels = "iterations, J(iterations)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([(1:length(J_history))' J_history], filename, title, labels);	
	title = "Exponential aproximation (linear regression) vs Original set";
	labels = "ExpLr(x), ExpLr(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfElr, filename, title, labels);		

endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Exponential fitting (Mean Evaluation)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(EXPONENTIAL_FITTING != 0)
        fprintf("\n*********************\nExponential data fitting 2: Mean evaluation\n*********************\n");
        %parameter estimation
        exp_mean = mean(interArrival);
	
        exp_lambdaMean = 1/exp_mean;
	if( abs(real(exp_lambdaMean)) < INFINITEZIMAL) 
		exp_lambdaMean = INFINITEZIMAL;
	endif
        fprintf("exp_lambdaMean = %f \n", exp_lambdaMean);

        % Plot original data and aproximation fitting
        cdfEme = cdfExponentialPlot(exp_lambdaMean, max_time,'Exponential aproximation (mean) vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca , 'figures/Exponential aproximation (mean) vs Original set.png');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical');
        hold off;

	title = "Exponential aproximation (mean) vs Original set";
	labels = "ExpMe(x), ExpMe(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfEme, filename, title, labels);
	
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Pareto fitting 1 (linear regression - LR)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(PARETO_FITTING != 0)
        fprintf("\n*********************\nPareto data fitting 1: Linear regression LR\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        y = log(1.00 - interArrivalCdf);
        x = log(interArrival);
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-+', 'Linearized data and linear fitting');
        
        % gradient descendent
        fprintf('Running Gradient Descent ...\n')
        X = [ones(m, 1), x(:,1)]; % Add a column of ones to x
        theta = zeros(2, 1); % initialize fitting parameters
        % gradient descent settings
        iterations = 1500;
        learning_rate = 0.01;
        % run gradient descent
        [theta J_history ] = gradientDescent(X, y, theta, learning_rate, iterations);
        % print theta to screen
        fprintf('Theta found by gradient descent: %f %f \n', theta(1), theta(2));
        fprintf('Initial coast J(1) = %f; Final coast J(end) = %f \n', J_history(1), J_history(end));
        hold on; % keep previous plot visible
        % plot the linear fit over the non-linear (linearized) data
        plot(X(:,2), X*theta, 'r-');
        legend('Training data', 'Linear regression', 'Location','southeast'  ,'Orientation','vertical')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Pareto LR - Linearized data and linear fitting.png');
        
        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Pareto LR - Cost J(iterations) convergence');
        saveas(gca , 'figures/Pareto LR - Cost J(iterations) convergence.png');
	
        %parameter estimation
	if(abs(real(theta(2))) < INFINITEZIMAL) 
		theta(2) = INFINITEZIMAL;
	endif
        pareto_alpha = -theta(2);
        pareto_xmf = exp(theta(1)/theta(2))
        pareto_xm = min(interArrival);
        fprintf("pareto_xm (formula) = %f \n", pareto_xmf);
        fprintf("pareto_alpha = %f \n", pareto_alpha);
        fprintf("pareto_xm (estimation) = %f \n", pareto_xm);
        
        % Plot original data and aproximation fitting
        cdfPlr = cdfParetoPlot(pareto_alpha, pareto_xm, max_time,'Pareto aproximation LR vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical');
        saveas(gca , 'figures/Pareto aproximation LR vs Original set.png');
        hold off;
	
	%linealization plot
	title = "Pareto - Linearized data and linear fitting";
	labels = "Linearized-data(x), Linearized-data(y), Aproximation(x), Aproximation(y)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([x y X(:,2) X*theta], filename, title, labels);
	title = "Pareto - Cost J(iterations) convergence";
	labels = "iterations, J(iterations)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([(1:length(J_history))' J_history], filename, title, labels);	
	title = "Pareto aproximation (linear regression) vs Original set";
	labels = "ParetoLr(x), ParetoLr(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfPlr, filename, title, labels);	
	
	
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Pareto fitting 2 (maximum likehood)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(PARETO_FITTING != 0)
        fprintf("\n*********************\nPareto data fitting 2: Maximum Likehood MLH\n*********************\n");
        pareto_mlh_xm = min(interArrival);
	pareto_mlh_alpha_div = sum(log(interArrival) - log(pareto_mlh_xm));
	if( abs(real(pareto_mlh_alpha_div)) < INFINITEZIMAL) 
		pareto_mlh_alpha_div = INFINITEZIMAL;
	endif
        pareto_mlh_alpha = length(interArrival)/(pareto_mlh_alpha_div);
	if( abs(real(pareto_mlh_alpha)) < INFINITEZIMAL) 
		pareto_mlh_alpha = INFINITEZIMAL;
	endif
	
        %parameter estimation
        fprintf("pareto_mlh_xm = %f \n", pareto_mlh_xm);
        fprintf("pareto_mlh_alpha = %f \n", pareto_mlh_alpha);

        % Plot original data and aproximation fitting
        cdfPml = cdfParetoPlot(pareto_mlh_alpha,  pareto_mlh_xm, max_time,'Pareto MLH aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical');
        saveas(gca , 'figures/Pareto MLH aproximation vs Original set.png');

        hold off;
	
	title = "Pareto aproximation (maximum likehood) vs Original set";
	labels = "ParetoMl(x), ParetoMl(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfPml, filename, title, labels);	
	
endif


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cauchy fitting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(CAUCHY_FITTING != 0)
        fprintf("\n*********************\nCauchy data fitting\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        %y = tan(pi*(interArrivalCdf - 0.5));
        %y__max = 1/min_time;
	%y__max = tan(pi/2 - 1e-6);
        %for cnt = 1:length(y)
        %        if( y(cnt) > y__max) 
        %                y(cnt) = y__max;
	%	elseif ( y(cnt) < -y__max )
	%		y(cnt) = -y__max;
        %        endif        
        %endfor
	interArrivalCdfCauchy = interArrivalCdf;
	interArrivalCdfCauchy(interArrivalCdfCauchy > ALMOST_ONE) = ALMOST_ONE;
	interArrivalCdfCauchy(interArrivalCdfCauchy < ALMOST_ZERO) = ALMOST_ZERO;
	y = tan(pi*(interArrivalCdfCauchy - 0.5));
        x = interArrival;
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-+', 'Linearized data and linear fitting');

        % gradient descendent
        fprintf('Running Gradient Descent ...\n')
        X = [ones(m, 1), x(:,1)]; % Add a column of ones to x
        theta = zeros(2, 1); % initialize fitting parameters
        % gradient descent settings
        iterations = 1500;
        learning_rate = 0.01;
        % run gradient descent
        [theta J_history ] = gradientDescent(X, y, theta, learning_rate, iterations);
        % print theta to screen
        fprintf('Theta found by gradient descent: %f %f \n', theta(1), theta(2));
        fprintf('Initial coast J(1) = %f; Final coast J(end) = %f \n', J_history(1), J_history(end));
        hold on; % keep previous plot visible
        % plot the linear fit over the non-linear (linearized) data
        plot(X(:,2), X*theta, 'r-')
        legend('Training data', 'Linear regression', 'Location','southeast'  ,'Orientation','vertical')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Cauchy - Linearized data and linear fitting.png');

        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Cauchy - Cost J(iterations) convergence');
        saveas(gca , 'figures/Cauchy - Cost J(iterations) convergence.png');
	
        %parameter estimation
	
%	if( abs(real(theta(2))) < INFINITEZIMAL) 
%		theta(2) = INFINITEZIMAL;
%	endif
        cauchy_gamma = 1/theta(2);
        cauchy_x0 = -theta(1)/theta(2);
        fprintf("cauchy_gamma = %f \n", cauchy_gamma);
        fprintf("cauchy_x0 = %f \n", cauchy_x0);
        %fprintf("pareto_xm (estimation) = %f \n", pareto_xm);

        % Plot original data and aproximation fitting
        cdfC = cdfCauchyPlot(cauchy_gamma, cauchy_x0, max_time,'Cauchy aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original', 'Location','southeast'  ,'Orientation','vertical');
        saveas(gca , 'figures/Cauchy aproximation vs Original set.png');

        hold off;
	
	%linealization plot
	title = "Cauchy - Linearized data and linear fitting";
	labels = "Linearized-data(x), Linearized-data(y), Aproximation(x), Aproximation(y)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([x y X(:,2) X*theta], filename, title, labels);
	title = "Cauchy - Cost J(iterations) convergence";
	labels = "iterations, J(iterations)";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File([(1:length(J_history))' J_history], filename, title, labels);
	title = "Cauchy aproximation vs Original set";
	labels = "Cauchy(x), Cauchy(CDF) ";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(cdfC, filename, title, labels);	
	
endif


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Selecting the best model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



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

if(WEIBULL_FITTING != 0)
	figure; %new figure
	%plotData( interArrival, weibull_interArrival, 'empirical', 'weibull', '-g', 'QQplot - Weibull');
	qqxy = qqPlot( interArrival, weibull_interArrival, 'empirical', 'weibull', '-g', 'QQplot - Weibull');
	saveas(gca , 'figures/QQplot - weibull.png');

	title = "QQplot - Weibull";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);	
	
endif
if(NORMAL_FITTING != 0)
	figure; %new figure
	%plotData(interArrival, normal_interArrival, 'empirical', 'normal', '-g', 'QQplot - Normal');
	qqxy = qqPlot(interArrival, normal_interArrival, 'empirical', 'normal', '-g', 'QQplot - Normal');
	saveas(gca , 'figures/QQplot - normal.png');
	
	title = "QQplot - Normal";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);	
endif
if(EXPONENTIAL_FITTING != 0)
	figure; %new figure
	%plotData(interArrival, exponential_lr_interArrival, 'empirical', 'exponential (Linear Regression)', '-g', 'QQplot - Exponential (Linear Regression)');
	qqxy = qqPlot(interArrival, exponential_lr_interArrival, 'empirical', 'exponential (Linear Regression)', '-g', 'QQplot - Exponential (Linear Regression)');
	saveas(gca , 'figures/QQplot - exponential_lr.png');
	title = "QQplot - Exponential(LR)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
	
	figure; %new figure
	%plotData(interArrival, exponential_me_interArrival, 'empirical', 'exponential (Mean)', '-g', 'QQplot - Exponential (Mean)');
	qqxy = qqPlot(interArrival, exponential_me_interArrival, 'empirical', 'exponential (Mean)', '-g', 'QQplot - Exponential (Mean)');
	saveas(gca , 'figures/QQplot - exponential_me.png');
	title = "QQplot - Exponential(Me)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
endif
if(PARETO_FITTING != 0)
	figure; %new figure
	%plotData(interArrival, pareto_lr_interArrival, 'empirical', 'pareto (Linear Regression)', '-g', 'QQplot - Pareto (Linear Regression)');
	qqxy = qqPlot(interArrival, pareto_lr_interArrival, 'empirical', 'pareto (Linear Regression)', '-g', 'QQplot - Pareto (Linear Regression)');
	saveas(gca , 'figures/QQplot - pareto_lr.png');
	title = "QQplot - Pareto(LR)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
	
	figure; %new figure
	%plotData(interArrival, pareto_mlh_interArrival, 'empirical', 'pareto (Maximum Likehood)', '-g', 'QQplot - Pareto (Maximum Likehood)');
	qqxy = qqPlot(interArrival, pareto_mlh_interArrival, 'empirical', 'pareto (Maximum Likehood)', '-g', 'QQplot - Pareto (Maximum Likehood)');
	saveas(gca , 'figures/QQplot - pareto_mlh.png');
	title = "QQplot - Pareto(MLH)";
	labels = "Estimatedpoints(x), Empiricalsample(y), xrule yrule";
	filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
	matrix2File(qqxy, filename, title, labels);
endif
if(CAUCHY_FITTING != 0)
	figure; %new figure
	%plotData(interArrival, cauchy_interArrival, 'empirical', 'Cauchy', '-g', 'QQplot - Cauchy');
	qqxy = qqPlot(interArrival, cauchy_interArrival, 'empirical', 'Cauchy', '-g', 'QQplot - Cauchy');
	saveas(gca , 'figures/QQplot - Cauchy.png');
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


clf;
hold on; grid on;
errorbar(corr_x, corr_y, corr_e, 'ro');
%xlabel('Stochastic functions fitting'); 
%ylabel('Correlation');
setxlabels(gca, corr_x_label);
%title('Correlation between stochastic functions and original data');
saveas(gca , 'figures/Correlation.png');
hold off; grid off;


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


clf;
hold on; grid on;
errorbar(mean_x, mean_y, mean_e, 'ro');
%xlabel('Stochastic functions fitting'); 
%ylabel('Mean');
setxlabels(gca, mean_x_label);
%title('Mean inter-packet time');
saveas(gca , 'figures/Mean inter-packet time.png');
hold off; grid off;


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


clf;
hold on; grid on;
errorbar(stddev_x, stddev_y, stddev_e, 'ro');
%xlabel('Stochastic functions fitting'); 
%ylabel('Standard deviation');
setxlabels(gca, stddev_x_label);
%title('Standard deviation of inter-packet time');
saveas(gca , 'figures/Standard deviation of inter-packet time.png');
hold off; grid off;


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

clf;
hurst_x = [1 2 3 4 5 6 7 8];
hurst_x_label = ["Original"; "Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
hurst_y = [mean(M(4,:)) mean(M_w(4,:)) mean(M_n(4,:)) mean(M_elr(4,:)) mean(M_eme(4,:)) mean(M_plr(4,:)) mean(M_pml(4,:)) mean(M_c(4,:))];
hurst_e = [std(M(4,:)) std(M_w(4,:)) std(M_n(4,:)) std(M_elr(4,:)) std(M_eme(4,:)) std(M_plr(4,:)) std(M_pml(4,:)) std(M_c(4,:))];
hurst_e = hurst_e*confidenceFactor;
title = "Hurst Exponent";
labels = "Distribution, Hust, Error";
filename = strcat(PLOT_DIR, title, PLOT_DATA_EXT);
sff2File(filename, title, labels, ',', hurst_x_label, hurst_y, hurst_e);


hold on; grid on;
errorbar(hurst_x, hurst_y, hurst_e, 'ro');
%xlabel('Stochastic functions fitting'); 
%ylabel('Hust exponent');
setxlabels(gca, hurst_x_label);
%title('Estimated Hust exponent of inter-packet time');
saveas(gca , 'figures/Hurst exponent of inter-packet time.png');
hold off; grid off;
