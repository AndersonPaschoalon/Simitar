function Pplt = cdfParetoPlot(pareto_alpha, pareto_xm, max_time, plotName)
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