function plotfig = cdfNormalPlot(mu, sigma, max_time, plotName)
        norm_x = linspace(0, max_time, 100);
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
end