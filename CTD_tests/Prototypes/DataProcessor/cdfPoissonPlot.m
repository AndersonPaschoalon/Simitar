function cdfPoissonPlot(poisson_mean, max_time)
        vet_x = linspace(0, max_time, 100);
        min(vet_x)
        vet_poisson = (exp(-poisson_mean)*poisson_mean.^vet_x)/factorial(round(vet_x)) %ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(vet_x, vet_poisson);
        hold off;

end