function Cplt = cdfCauchyPlot(cauchy_gamma, cauchy_x0, max_time, plotName)
% cdfCauchyPlot - generate a CDF vector of a cauchy function, and plot 
% its figure
%
% Syntax:  value = adiff(a1, a2)
%
% Inputs:
%    cauchy_gamma - function param 
%    cauchy_x0 - function param 
%    max_time - max time on the plot 
%    plotName - figure name 
%
% Outputs:
%    Cplt - x and y values of the CDF 
%
% Example: 
%    Cplt = cdfExponentialPlot(2, 2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        %linspace_size = 100;
	linspace_size = 1000;
        %cauchy_x = linspace(0, max_time, linspace_size);
	cauchy_x = logspace(-8, 1, linspace_size);
        cauchy_y = (1/pi)*atan((cauchy_x - cauchy_x0)/cauchy_gamma) + 0.5; %ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plotFig = plot(cauchy_x, cauchy_y, '-b');
        ylabel('F(t)');
        xlabel('t');
        title(plotName);
        hold off;
	Cplt = [cauchy_x' cauchy_y'];
end