#!/usr/bin/octave-cli -qf

%clear 
clear all; clc; clf;
%set plot toolkit
graphics_toolkit ("gnuplot");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%plot directory whre the plots will be saved
PLOT_DIR='../plots/';

%prefix of the plot name
PLOT_PREFIX_NAME='qualification';

%name of file data
SIMULATION_DATA='data/plot_data_qualification';

%original trace data file
BASE_TRACE_DATA='data/plot_data_0.txt';

%repetitions
REPETITIONS=30;

%min mumber of packets
MIN_PACKETS = 15;

%load basic data 
DataBase = dlmread(BASE_TRACE_DATA, ' ' , 2, 0);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Hurst Exponent plot 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%set repetitions
n = REPETITIONS;

%capture duration: max time
time_max = DataBase(end,5);

%basic unity of time: 100 ms 
time_min = 0.125;

%number of samples 
m = floor(log2(time_max/time_min)) + 1;

%vector m of each time spacing
PlotTime = zeros(m,1);
PlotTimeBase = zeros(m,1);

%matrix m-n, where m is the number of time samples, and n is the number of 
%repetitions. Initialize. If the values of the first and second lines are
%the same, the function fail to execute. 
PlotHurst = zeros(m, n);
PlotHurstBase = zeros(m, 1);
%Error bar and plot values
e = zeros(m,1);
y = zeros(m,1);

i = 0;
%Init PlotTime
current_time = time_min;
for i = 1:m 
        PlotTime(i) = current_time;
        current_time = current_time*2;
end

i = 0;
PacketArrival = DataBase(:,5);
for i = 1:m
        current_time = PlotTime(i);
        PacketArrival_partial = PacketArrival ( (PacketArrival() < current_time ));
        PlotHurstBase(i) = hurst(PacketArrival_partial);
end


j = 0;
i = 0;
for j = 1:n
        %set data to be loaded
        file_name = strcat(SIMULATION_DATA, num2str(j));
        file_name = strcat(file_name, '.txt');        
        %load data
        Data = dlmread(file_name, ' ' , 2, 0);
        %inter-arrival times
        PacketArrival = Data(:,5);
        
        current_time = 0;
        for i = 1:m
               current_time = PlotTime(i);
               PacketArrival_partial = PacketArrival ( (PacketArrival() < current_time ));
               PlotHurst(i, j) = hurst(PacketArrival_partial);
        end
end

%plot Data 
y = mean(PlotHurst, 2);
e = std(PlotHurst, 1, 2);

%normalizing time 
log_time = log2(PlotTime/time_min);

%begin
hold on; grid on;

%settings
set(gca,'Fontname','Timesnewroman');
set(gca, 'fontsize', 20);
ylabel("Hurst Exponent");
xlabel("log2(time / 0.125 s)");
set(gca, 'fontsize', 18);
set(gca, 'LineWidth', 2);
xlim([-0.5 log_time(end)]);
ylim([0 1.15]);

%plotdata
plot1 = plot(log_time, PlotHurstBase, '-^r');
plot2 = errorbar(log_time, y, e, '-xb');
%legend
legend('Original trace','Synthetic trace','Location','southoutside','Orientation','horizontal');

%additional settings
set(plot1, 'LineWidth', 3);
set(plot2, 'LineWidth', 3);

%save plot 
figure_name = strcat(PLOT_DIR, PLOT_PREFIX_NAME, '-', 'HustExponent', '.png' );
saveas(gca , figure_name);
%saveas(gca , '../plots/qualification-HustExponent.png');

%end
hold off; grid off;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Flow-Bandwidth plot 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%set repetitions
n = REPETITIONS;

%Flow-PacketSize
allFlowsPacketSize = [DataBase(:,2) DataBase(:,3)];

%Flow - Time
allFlowsTime = [DataBase(:,2) DataBase(:,5)];

% max number of flows
max_flow = max(DataBase(:,2)) + 1;
%max number of flows for each unitary test
max_flow_unitary = 0;
% flow bandwidth
flowBw = zeros(max_flow , 1);


for i = 1:max_flow
        flowTime = allFlowsTime( (allFlowsTime(:,1) == (i - 1)) ,:);
        %in case the result was a vector of size zero (fix of a bug)
        if( size(flowTime, 1) < MIN_PACKETS )
                nbytes = 0;
                deltaTime = 1;
        else
                deltaTime = max(flowTime(:,2)) - min(flowTime(:,2));

                flowPacketSize  =  allFlowsPacketSize((allFlowsTime(:,1) == (i - 1)) ,:);
                nbytes = sum(flowPacketSize(:,2));
        end
        
        flowBw(i) = nbytes/deltaTime;
        %just for tests, it preints the resulting grapy
        %printf("flowBw[%f] = %f\n", i, nbytes/(deltaTime)); 
end
% reject flows with evalueted Bandwidth zero 
flowBw = flowBw( (flowBw(:,1) != 0 ));
size_flowBw = size( flowBw, 1);

%init all flows data matrix
allFlowsBw = zeros(size_flowBw, n);

%loop at all collected date
for j = 1:n
        %load and init basic data 
        file_name = strcat(SIMULATION_DATA, num2str(j));
        file_name = strcat(file_name, '.txt');
        Data = dlmread(file_name, ' ' , 2, 0);
        allFlowsPacketSize = [Data(:,2) Data(:,3)];
        allFlowsTime = [Data(:,2) Data(:,5)];
        max_flow = max(Data(:,2)) + 1;
        max_flow_unitary = 0;
        flowBw2 = zeros(max_flow , 1);

        for i = 1:max_flow
                flowTime = allFlowsTime( (allFlowsTime(:,1) == (i - 1)) ,:);
                %in case the result was a vector of size zero (fix of a bug)
                if( size(flowTime, 1) < MIN_PACKETS )
                        nbytes = 0;
                        deltaTime = 1;
                else
                        deltaTime = max(flowTime(:,2)) - min(flowTime(:,2));

                        flowPacketSize  =  allFlowsPacketSize((allFlowsTime(:,1) == (i - 1)) ,:);
                        nbytes = sum(flowPacketSize(:,2));
                end
                
                flowBw2(i) = nbytes/deltaTime;

        end
        % reject flows with evalueted Bandwidth zero 
        flowBw2 = flowBw2( (flowBw(:,1) != 0 ));
        flowBw2 = sort(flowBw2, 'descend');

        size_flowBw2 = size( flowBw2,1);
        if( size_flowBw2 >=  size_flowBw)
                flowBw2 = flowBw2(1:size_flowBw , :);
        else
                temp_flowBw2 = zeros(size_flowBw,1);
                temp_flowBw2(1:size_flowBw2, :) = flowBw2;
                flowBw2 = temp_flowBw2;  
        end
        
        allFlowsBw(:,j) = flowBw2;
end

plot1 = 0;
plot2 = 0;

%plot data
clf;
hold on; grid on; 
graphics_toolkit ("gnuplot");

set(gca,'Fontname','Timesnewroman');
set(gca, 'fontsize', 20);
ylabel("Flow mean bandwidth (byte/s)");
xlabel("flow");
set(gca, 'fontsize', 18);
set(gca, 'LineWidth', 2);

y = mean(allFlowsBw , 2);
e = std(allFlowsBw')';

plot1 = plot(1:size_flowBw, flowBw, '--xb');
plot2 = errorbar(1:size_flowBw, y, e, '--xr');

%additional settings
set(plot1, 'MarkerSize', 10);
set(plot2, 'MarkerSize', 10);
set(plot1, 'LineWidth', 3);
set(plot2, 'LineWidth', 3);

%legend
legend('Original trace','Synthetic trace','Location','southoutside','Orientation','horizontal');

%save plot 
%saveas(gca , '../plots/qualification-bw.png');
%save plot 
figure_name = strcat(PLOT_DIR, PLOT_PREFIX_NAME, '-', 'bw', '.png' );
saveas(gca , figure_name);

%end
hold off; grid off;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Wavelet multiresolution energy analizis (MREA)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% constants
n = REPETITIONS;
granularity = 0.01; % 10 ms
vetArrivalTimes = DataBase(:,5);
logEnergyBase = traceWaveletMra(vetArrivalTimes, granularity);
resolutionLen = length(logEnergyBase);
% inits
logEnergySym = zeros(resolutionLen, n);

j = 0;
for j = 1:n
        %set data to be loaded
        file_name = strcat(SIMULATION_DATA, num2str(j));
        file_name = strcat(file_name, '.txt');        
        %load data
        Data = dlmread(file_name, ' ' , 2, 0);
        %inter-arrival times
        vetArrivalTimes = Data(:,5);
        
        %logEnergySym(:,j) = traceWaveletMra(vetArrivalTimes, granularity);
        lesTemp = traceWaveletMra(vetArrivalTimes, granularity);
        logEnergySym(:,j) = lesTemp(1:resolutionLen);
end

%plot Data 
y = mean(logEnergySym, 2);
e = std(logEnergySym, 1, 2);
res = 1:resolutionLen;

%begin
clf;
hold on; grid on;

%settings
set(gca,'Fontname','Timesnewroman');
set(gca, 'fontsize', 20);
ylabel("log2(Energy(j))");
xlabel("Time scale j");
set(gca, 'fontsize', 18);
set(gca, 'LineWidth', 2);
%xlim([-0.5 log_time(end)]);
%ylim([0 1.15]);

%plotdata
plot1 = plot(res, logEnergyBase, '-^r');
plot2 = errorbar(res, y, e, '-xb');
%legend
legend('Original trace','Synthetic trace','Location','southoutside','Orientation','horizontal');

%additional settings
set(plot1, 'LineWidth', 3);
set(plot2, 'LineWidth', 3);

%save plot 
%saveas(gca , '../plots/wavelet-mrea.png');
%save plot 
figure_name = strcat(PLOT_DIR, PLOT_PREFIX_NAME, '-', 'WaveletMREA', '.png' );
saveas(gca , figure_name);

%end
hold off; grid off;













































