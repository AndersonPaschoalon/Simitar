
% Data Processor

% This program:
% - Loads inter-arrival information
% - Use linear regression to fit a set o models
% - Plots all of them, along with the actual data
% - Using maximum likehood function, evaluate the AIC and BIC

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Initialization and load data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%inicialization
%clear; clear all; 
close all; clc; clf;
pkg load statistics;
graphics_toolkit ("gnuplot");
set(0, 'DefaultLineLineWidth', 4);
set(0,'defaulttextfontsize', 10);
set(0,'DefaultAxesFontSize',10)
%configuration
min_time = 0.0000005;
WEIBULL_FITTING = 1;
NORMAL_FITTING = 1;
EXPONENTIAL_FITTING_1 = 1; 
EXPONENTIAL_FITTING_2 = 1; 
PARETO_FITTING_1 = 1;
PARETO_FITTING_2 = 1;
CAUCHY_FITTING = 1;
%data load
M = dlmread('tests/data.txt', ' ' , 1, 0);
interArrival = sort(M(:,4)) + min_time;
max_time = max(interArrival);
interArrivalCdf = empiricalCdf(interArrival);
m = length(interArrival);
%plot empirical Cumulative distribution function
fprintf("Ploting inter-arrival cumulative distribution\n");
plotData(interArrival, interArrivalCdf, 'interArrival', 'F(interArrival)', 'b-', 'Inter-arrival empirical CDF');
saveas(gca , 'figures/Inter-arrival empirical CDF.png');

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
        dlmwrite('xy.txt',[x y]);
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-', 'Linearized data and linear fitting');

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
        legend('Training data', 'Linear regression')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Weibull - Linearized data and linear fitting.png');

        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Weibull - Cost J(iterations) convergence');
        saveas(gca , 'figures/Weibull - Cost J(iterations) convergence.png');

        %parameter estimation
        weibull_alpha = theta(2)
        weibull_betha = exp(-theta(1)/theta(2))

        % Plot original data and aproximation fitting
        cdfWeibullPlot(weibull_alpha, weibull_betha, max_time,'Weibull aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca , 'figures/Weibull aproximation vs Original set.png');
        legend('aproximation', 'original')
        hold off;
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
        cdfNormalPlot(normal_mean, normal_std, max_time, 'Normal aproximation vs Original set' );
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca, 'figures/Normal aproximation vs Original set.png');
        legend('aproximation', 'original')
        hold off;
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Exponential fitting (Linear Regression)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(EXPONENTIAL_FITTING_1 != 0)
        fprintf("\n*********************\nExponential data fitting 1: Linear Regression\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        y = log(1.00 - interArrivalCdf);
        x = interArrival;
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-', 'Linearized data and linear fitting');

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
        legend('Training data', 'Linear regression')
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
        cdfExponentialPlot(exp_lambda, max_time,'Exponential aproximation (LR) vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca , 'figures/Exponential aproximation (LR) vs Original set.png');
        legend('aproximation', 'original')
        hold off;
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Exponential fitting (Mean Evaluation)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(EXPONENTIAL_FITTING_2 != 0)
        fprintf("\n*********************\nExponential data fitting 2: Mean evaluation\n*********************\n");
        %parameter estimation
        exp_mean = mean(interArrival);
        exp_lambdaMean = 1/exp_mean;
        fprintf("exp_lambdaMean = %f \n", exp_lambdaMean);

        % Plot original data and aproximation fitting
        cdfExponentialPlot(exp_lambdaMean, max_time,'Exponential aproximation (mean) vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        saveas(gca , 'figures/Exponential aproximation (mean) vs Original set.png');
        legend('aproximation', 'original')
        hold off;
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Pareto fitting 1 (linear regression - LR)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(PARETO_FITTING_1 != 0)
        fprintf("\n*********************\nPareto data fitting 1: Linear regression LR\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        y = log(1.00 - interArrivalCdf);
        x = log(interArrival);
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-', 'Linearized data and linear fitting');
        
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
        legend('Training data', 'Linear regression')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Pareto LR - Linearized data and linear fitting.png');
        
        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Pareto LR - Cost J(iterations) convergence');
        saveas(gca , 'figures/Pareto LR - Cost J(iterations) convergence.png');
        
        %parameter estimation
        pareto_alpha = -theta(2);
        pareto_xmf = exp(theta(1)/theta(2))
        pareto_xm = min(interArrival);
        fprintf("pareto_xm (formula) = %f \n", pareto_xmf);
        fprintf("pareto_alpha = %f \n", pareto_alpha);
        fprintf("pareto_xm (estimation) = %f \n", pareto_xm);
        
        % Plot original data and aproximation fitting
        cdfParetoPlot(pareto_alpha, pareto_xm, max_time,'Pareto aproximation LR vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original');
        saveas(gca , 'figures/Pareto aproximation LR vs Original set.png');
        hold off;
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Pareto fitting 2 (maximum likehood)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(PARETO_FITTING_2 != 0)
        fprintf("\n*********************\nPareto data fitting 2: Maximum Likehood MLH\n*********************\n");
        pareto_mlh_xm = min(interArrival);
        pareto_mlh_alpha = length(interArrival)/(sum(log(interArrival) - log(pareto_mlh_xm)));

        %parameter estimation
        fprintf("pareto_mlh_xm = %f \n", pareto_mlh_xm);
        fprintf("pareto_mlh_alpha = %f \n", pareto_mlh_alpha);

        % Plot original data and aproximation fitting
        cdfParetoPlot(pareto_mlh_alpha,  pareto_mlh_xm, max_time,'Pareto MLH aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original');
        saveas(gca , 'figures/Pareto MLH aproximation vs Original set.png');

        hold off;
endif


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cauchy fitting
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(CAUCHY_FITTING != 0)
        fprintf("\n*********************\nCauchy data fitting\n*********************\n");
        %linearized data
        fprintf("Data linearization plot\n");
        y = tan(pi*(interArrivalCdf - 0.5));
        y__max = 1/min_time;
        for cnt = 1:length(y)
                if( y(cnt) > y__max) 
                        y(cnt) = y__max;
                endif        
        endfor
        x = interArrival;
        figure; %new figure
        plotData(x, y, 'x', 'y', 'b-', 'Linearized data and linear fitting');

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
        legend('Training data', 'Linear regression')
        hold off % don't overlay any more plots on this figure
        saveas(gca , 'figures/Cauchy - Linearized data and linear fitting.png');

        % plot Cost J() convergence
        figure; %new figure
        plotData(1:length(J_history), J_history, 'iterations', 'J(iterations)', '-g', 'Cauchy - Cost J(iterations) convergence');
        saveas(gca , 'figures/Cauchy - Cost J(iterations) convergence.png');

        %parameter estimation
        cauchy_gamma = 1/theta(2);
        cauchy_x0 = -theta(1)/theta(2);
        fprintf("cauchy_gamma = %f \n", cauchy_gamma);
        fprintf("cauchy_x0 = %f \n", cauchy_x0);
        %fprintf("pareto_xm (estimation) = %f \n", pareto_xm);

        % Plot original data and aproximation fitting
        cdfCauchyPlot(cauchy_gamma, cauchy_x0, max_time,'Cauchy aproximation vs Original set');
        hold on;
        plot(interArrival, interArrivalCdf, '-r');
        legend('aproximation', 'original');
        saveas(gca , 'figures/Cauchy aproximation vs Original set.png');

        hold off;
endif


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Selecting the best model
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

weibull_bic = informationCriterion(interArrival, 'weibull', [weibull_alpha weibull_betha], 'bic');
weibull_aic = informationCriterion(interArrival, 'weibull', [weibull_alpha weibull_betha], 'aic');
normal_bic = informationCriterion(interArrival, 'normal', [normal_mean normal_std], 'bic');
normal_aic = informationCriterion(interArrival, 'normal', [normal_mean normal_std], 'aic');
exponential_lr_bic = informationCriterion(interArrival, 'exponential', [exp_lambda], 'bic');
exponential_lr_aic = informationCriterion(interArrival, 'exponential', [exp_lambda], 'aic');
exponential_me_bic = informationCriterion(interArrival, 'exponential', [exp_lambdaMean], 'bic');
exponential_me_aic = informationCriterion(interArrival, 'exponential', [exp_lambdaMean], 'aic');
pareto_lr_bic = informationCriterion(interArrival, 'pareto', [pareto_alpha pareto_xm], 'bic');
pareto_lr_aic = informationCriterion(interArrival, 'pareto', [pareto_alpha pareto_xm], 'aic');
pareto_mlh_bic = informationCriterion(interArrival, 'pareto', [pareto_mlh_alpha pareto_mlh_xm], 'bic');
pareto_mlh_aic = informationCriterion(interArrival, 'pareto', [pareto_mlh_alpha pareto_mlh_xm], 'aic');
cauchy_bic = informationCriterion(interArrival, 'cauchy', [cauchy_gamma cauchy_x0], 'bic');
cauchy_aic = informationCriterion(interArrival, 'cauchy', [cauchy_gamma cauchy_x0], 'aic');

fprintf('\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Function        |AIC           |BIC            |\n');
fprintf('+----------------+--------------+---------------+\n');
fprintf('|Weibull         |%f\t|%f\t|\n',weibull_aic, weibull_bic);
fprintf('|Normal          |%f\t|%f\t|\n',normal_aic, normal_bic);
fprintf('|Exponential(LR) |%f\t|%f\t|\n',exponential_lr_aic, exponential_lr_bic);
fprintf('|Exponential(Me) |%f\t|%f\t|\n',exponential_me_aic, exponential_me_bic);
fprintf('|Pareto(LR)      |%f\t|%f\t|\n',pareto_lr_aic, pareto_lr_bic);
fprintf('|Pareto(MLH)     |%f\t|%f\t|\n',pareto_mlh_aic, pareto_mlh_bic );
fprintf('|Cauchy          |%f\t|%f\t|\n',cauchy_aic, cauchy_bic);
fprintf('+----------------+--------------+---------------+\n');

























