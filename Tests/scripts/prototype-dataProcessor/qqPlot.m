function [qqxy] = qqPlot(empirical, theoretical, empirical_label, theoretical_label, LineType, plotTitle)
%PLOTDATA Plots the data points x and y into a new figure 
%   PLOTDATA(x,y) plots the data points and gives the figure axes labels of
%   population and profit.
	%set(gca,'fontsize',10);
	%set(gca,'Fontname','Timesnewroman');
        hold on;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
	qqplot(empirical, theoretical);
        [qqSam qqEsti] = qqplot(empirical, theoretical);
        title(plotTitle);
        ylabel(empirical_label);
        xlabel(theoretical_label);
	x_max = max(empirical);
	
	qqx = reshape(qqSam, [], 1);
	qqy = reshape(qqEsti, [], 1);
	xlin = linspace(0, x_max, length(empirical))';
	ylin = linspace(0, x_max, length(empirical))';

	plot(xlin, ylin, '-r')
        hold off;

	
	qqxy = [qqx qqy xlin ylin];
end