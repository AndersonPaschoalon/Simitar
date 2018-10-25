function Nplt = cdfNormalPlot(mu, sigma, max_time, plotName)
% cdfNormalPlot - generate a CDF vector of a normal function, and plot 
% its figure
%
% Syntax:  Nplt = cdfNormalPlot(mu, sigma, max_time, plotName)
%
% Inputs:
%    mu - function param 
%    sigma - function param 
%    max_time - max time on the plot 
%    plotName - figure name 
%
% Outputs:
%    Nplt - x and y values of the CDF 
%
% Example: 
%    Nplt = cdfNormalPlot(2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        %norm_x = linspace(0, max_time, 100);
        norm_x = logspace(-8, 1, 1000);
        cdf_x = normcdf(norm_x,mu,sigma);
        figure;
        hold on;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plotFig = plot(norm_x, cdf_x, '-b', 'MarkerSize', 10);
        ylabel('F(t)');
        xlabel('t');
        title(plotName);
        hold off;
        Nplt = [norm_x' cdf_x'];
end