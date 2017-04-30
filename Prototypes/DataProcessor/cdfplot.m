function [h,stats] = cdfplot(data)

        data_len = length(data);
        data = sort(data);
        count = (1:data_len)/data_len;
        
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        h = plot(data, count);
        data_mean = mean(data);
        data_std = std(data);
        data_median = median(data);
        data_max = max(data);
        data_min = min(data);
        stats = [data_mean, data_std, data_median, data_min, data_max];
        hodl off;

end