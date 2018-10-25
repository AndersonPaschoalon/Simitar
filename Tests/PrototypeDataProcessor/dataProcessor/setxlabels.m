function setxlabels(fig_gca, xticklabel)
% setxlabels - set xtick on figure 
%
% Syntax:  setxlabels(fig_gca, xticklabel)
%
% Inputs:
%    fig_gca - figure 
%    xticklabel - tick label
%
% Outputs:
%    none
%
% Example: 
%    stddev_x_label = ["Original"; "Weibull"; "Normal"; "Exponential(LR)"; "Exponential(Me)"; "Pareto(LR)"; "Pareto(MLH)"; "Cauchy"];
%    setxlabels(gca, stddev_x_label);
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018  
	%https://lists.gnu.org/archive/html/help-octave/2009-07/msg00273.html
	xtick = 1:size(xticklabel,1);
	set(fig_gca,'xtick',xtick);
	set(fig_gca,'xticklabel',xticklabel);
end