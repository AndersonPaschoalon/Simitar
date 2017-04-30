function figPlot = cdfExponentialPlot(exp_mean, max_time, plotName)
        vet_x = linspace(0, max_time, 100);
        vet_exp = 1 - exp(-exp_mean*vet_x);%ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(vet_x, vet_exp, '-b');
        title(plotName);
        hold off;
        
end