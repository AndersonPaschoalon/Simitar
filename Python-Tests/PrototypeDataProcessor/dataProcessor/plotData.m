function fig = plotData(x, y, x_label, y_label, LineType, plotTitle)
%PLOTDATA Plots the data points x and y into a new figure 
%   PLOTDATA(x,y) plots the data points and gives the figure axes labels of
%   population and profit.
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
