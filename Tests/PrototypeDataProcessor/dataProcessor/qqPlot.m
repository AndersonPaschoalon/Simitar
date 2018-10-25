function [qqxy] = qqPlot(empirical, theoretical, empirical_label, theoretical_label, LineType, plotTitle)
% qqPlot - QQplot wrapper
%
% Syntax:  [qqxy] = qqPlot(empirical, theoretical, empirical_label, 
%                       theoretical_label, LineType, plotTitle)
%
% Inputs:
%    empirical - 
%    theoretical -
%    empirical_label -
%    theoretical_label -
%    LineType -
%    plotTitle -
%
% Outputs:
%    qqxy -  x and y axis 
%
% Example: 
%     [qqxy] = qqPlot(empirical, theoretical, empirical_label, theoretical_label, LineType, plotTitle)
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018  
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