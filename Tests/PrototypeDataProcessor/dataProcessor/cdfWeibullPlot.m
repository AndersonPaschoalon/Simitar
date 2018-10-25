function Wplt = cdfWeibullPlot(weibull_alpha, weibull_betha, max_time, plotName)
% cdfNormalPlot - generate a CDF vector of a normal function, and plot 
% its figure
%
% Syntax:  Wplt = cdfWeibullPlot(weibull_alpha, weibull_alpha, max_time, plotName)
%
% Inputs:
%    weibull_alpha - function param 
%    weibull_betha - function param 
%    max_time - max time on the plot 
%    plotName - figure name 
%
% Outputs:
%    Wplt - x and y values of the CDF 
%
% Example: 
%    Wplt = cdfWeibullPlot(2, 2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
%weibull_x = linspace(0, max_time, 100);
    weibull_x = logspace(-8, 1, 1000);
    weibull_y = 1 - exp(-(weibull_x/weibull_betha).^weibull_alpha); %ok
    hold on;
    figure;
    %set(gca, 'LineWidth', 4);
    %set(gca, 'fontsize', 16);
    plotFig = plot(weibull_x, weibull_y, '-b');
    ylabel('F(t)');
    xlabel('t');
    title(plotName);
    hold off;
    Wplt = [weibull_x' weibull_y'];
end