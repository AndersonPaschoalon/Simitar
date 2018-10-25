function Eplt = cdfExponentialPlot(exp_lambda, max_time, plotName)
% cdfExponentialPlot - generate a CDF vector of a exponential function, and plot 
% its figure
%
% Syntax:  value = adiff(a1, a2)
%
% Inputs:
%    exp_lambda - function param 
%    max_time - max time on the plot 
%    plotName - figure name 
%
% Outputs:
%    Eplt - x and y values of the CDF 
%
% Example: 
%    Eplt = cdfExponentialPlot(2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        %vet_x = linspace(0, max_time, 100);
        vet_x = logspace(-8, 1, 1000);
        vet_exp = 1 - exp(-exp_lambda*vet_x);%ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(vet_x, vet_exp, '-b');
        title(plotName);
        hold off;
        Eplt = [vet_x' vet_exp'];
end