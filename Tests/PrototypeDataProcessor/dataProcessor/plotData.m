function fig = plotData(x, y, x_label, y_label, LineType, plotTitle)
% plotData - Wrapper for plotting  x and y data into a new figure 
% PLOTDATA(x,y) plots the data points and gives the figure axes labels of
% population and profit.
%
% Syntax:  fig = plotData(x, y, x_label, y_label, LineType, plotTitle)
%
% Inputs:
%    x -  x axis data
%    y -  y axis data
%    x_label -  x legend
%    y_label - y legend  
%    LineType -  line type, matlab convension
%    plotTitle - plot title 
%
% Outputs:
%    fig - figure object
%
% Example: 
%    plotData([1 2 3]', [1 4 9]', 'x values', 'y values', 'b-', 'plot title')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018  
        hold on;
	    %set(gcf,'fontsize', 10);
	    %set(gcf ,'Fontname','Timesnewroman');
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(x, y, 'MarkerSize', 10, LineType);
        title(plotTitle);
        ylabel(y_label);
        xlabel(x_label);
        hold off;
	
end
