function Eplt = cdfExponentialPlot(exp_lambda, max_time, plotName)
        %vet_x = linspace(0, max_time, 100);
	vet_x = logspace(-8, 1, 1000);
        vet_exp = 1 - exp(-exp_lambda*vet_x);%ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plot(vet_x, vet_exp, '-b');
        title(plotName);
        hold off;
        Eplt = [vet_x' vet_exp'];
end