function plotFig = cdfWeibullPlot(weibull_alpha, weibull_betha, max_time, plotName)
        weibull_x = linspace(0, max_time, 100);
        weibull_y = 1 - exp(-(weibull_x/weibull_betha).^weibull_alpha); %ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plotFig = plot(weibull_x, weibull_y, '-b');
        ylabel('F(t)');
        xlabel('t');
        title(plotName);
        hold off;
end