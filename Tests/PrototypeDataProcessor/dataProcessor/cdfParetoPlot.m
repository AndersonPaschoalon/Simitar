function Pplt = cdfParetoPlot(pareto_alpha, pareto_xm, max_time, plotName)
% cdfParetoPlot - generate a CDF vector of a pareto function, and plot 
% its figure
%
% Syntax:  value = adiff(a1, a2)
%
% Inputs:
%    pareto_alpha - function param 
%    pareto_xm - function param 
%    max_time - max time on the plot 
%    plotName - figure name 
%
% Outputs:
%    Nplt - x and y values of the CDF 
%
% Example: 
%    Eplt = cdfParetoPlot(2, 2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        %linspace_size = 100;
        %pareto_x = linspace(0, max_time, linspace_size)';
	linspace_size = 1000;
        pareto_x = logspace(-8, 1, linspace_size)';
        pareto_y = zeros(linspace_size, 1);
        for i = 1:linspace_size
                if(pareto_x(i) < pareto_xm)
                        pareto_y(i) = 0;
                else
                        pareto_y(i) = 1 - (pareto_xm/pareto_x(i))^pareto_alpha; %ok
                endif
        end
        
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plotFig = plot(pareto_x, pareto_y, '-b');
        ylabel('F(t)');
        xlabel('t');
        title(plotName);
        hold off;
	Pplt = [pareto_x pareto_y];
end