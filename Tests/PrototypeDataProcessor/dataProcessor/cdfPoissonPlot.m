# ?  not used
function Pplt = cdfPoissonPlot(poisson_mean, max_time)
% cdfPoissonPlot - generate a CDF vector of a Poisson function
%
% Syntax:  Pplt = cdfPoissonPlot(poisson_mean, max_time)
%
% Inputs:
%    poisson_mean - function param 
%    max_time - max time on the plot 
%
% Outputs:
%    Pplt - x and y values of the CDF 
%
% Example: 
%    Pplt = cdfNormalPlot(2, 15, 'test')
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        vet_x = linspace(0, max_time, 100);
        min(vet_x)
        vet_poisson = (exp(-poisson_mean)*poisson_mean.^vet_x)/factorial(round(vet_x)) %ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(vet_x, vet_poisson);
        hold off;
        Pplt = [vet_x' vet_poisson'];
end