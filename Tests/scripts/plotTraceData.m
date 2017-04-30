#!/usr/bin/octave-cli -qf
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plotTraceData.m plots information of individual traces. It plots:
% - Packet size histogram distribution
% - Inter-deperture time histogram distribution
% - Mbits per second (granularity 1ms)
% - Packets per second (granularity 1ms)
% - Flows per second (granularity 1s)
% It uses command line arguments. Eg.:
% ./plotTraceData.m ./data/plot_data_qualification10.txt qualification
%
% Licensing:
%
%       This code is distributed under the GNU LGPL license.
%
% Author:
%
%       Anderson Paschoalon
%
% Modified:
%
% 13/09/2016 -> header documentation and command line args support
%
% Parameters:
% arg1 String file name. File with the data to be loaded, including the path.
%
% arg2 String file experiment sufix and directory name. This is the directory 
%      where the generated files will be saved (under plot/ dir), and the 
%      sufix of the generated file. 
%

%clear
clf;

%set plot toolkit
graphics_toolkit ("gnuplot");

%command line args
arg_list = argv (); 
FILE_PLOT_DATA = arg_list{1};

% Files names
FILE_PLOT_PREFIX = arg_list{2} ;

printf("ploting... ");

FILE_PACKET_SIZE_PLT = ['../plots/'  FILE_PLOT_PREFIX '_packetSize.png'];
FILE_INTERDEPERTURE_PLT = ['../plots/' FILE_PLOT_PREFIX '_interDep.png'];
FILE_PACKETS_PER_SECOND_PLT = ['../plots/'  FILE_PLOT_PREFIX '_packetsPerSecond.png'];
FILE_MBPS_PLT = ['../plots/' FILE_PLOT_PREFIX '_Mbps.png'];
FILE_FLOWS_PLT = ['../plots/'  FILE_PLOT_PREFIX '_Flows.png'];
%load data
Data = dlmread(FILE_PLOT_DATA, ' ' , 2, 0);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Packet size histogram
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clf;
hold on;
hist(Data(:, 3), 100);
set(gca, 'fontsize', 20);
set(gca,'Fontname','Timesnewroman');
ylabel("Frequency");
xlabel("Packet Size");
xlim([0 max(Data(:, 3))]);
saveas(gca , FILE_PACKET_SIZE_PLT);
hold off;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Interdeperture histogram
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% percentage of values that are going to be used in the plot
usageFactor = 0.8;
numberOfbars = 100;
% interdeperture vector
interDep = 0; 
interDep_raw = sort(Data(:, 4)); 
interDep_len = length(interDep_raw);
% last value to be used on the plot 
usageIndex = round(interDep_len*usageFactor);
% vector that is going to be plotted
interDep = interDep_raw(1:usageIndex); 
% plot...
clf;
hold on;
hist(interDep, numberOfbars);
%histfit(interDep, numberOfbars,'weibull');
set(gca, 'fontsize', 20);
set(gca,'Fontname','Timesnewroman');
ylabel("Frequency");
xlabel("interDep");
xlim([0 max(interDep)]);
saveas(gca , FILE_INTERDEPERTURE_PLT);
hold off;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Packets per second
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% constants
granularity = 0.01; % 10 ms
numberOfPackets = Data(end, 1);
totalTime =  Data(end, 5);
numberOfDots = floor(totalTime/granularity);
vet_depertureTime = Data(:,5);
% vars
vet_packetRate = zeros(numberOfDots,1);
vet_time = zeros(numberOfDots,1);
packetCounter = 0;
timeCounter = granularity;
index_vetDepertureTime = 1;
%plot "pointer"
plot1 = 0;
for i = 1:numberOfDots
        packetCounter = 0;
        while(vet_depertureTime(index_vetDepertureTime) < timeCounter )
                % count number of packets
                packetCounter = packetCounter + 1;
                index_vetDepertureTime = index_vetDepertureTime + 1;
        endwhile
        %plot data
        vet_time(i) = timeCounter;
        vet_packetRate(i) = packetCounter/granularity;
        %update        
        timeCounter = timeCounter + granularity;
endfor
% plot...
clf;
hold on;
grid on;
plot1 = plot(vet_time,vet_packetRate );
set(gca, 'fontsize', 20);
set(gca,'Fontname','Timesnewroman');
set(plot1, 'LineWidth', 1);
xlabel('time (seconds)'); 
ylabel('Packets per second');
saveas(gca, FILE_PACKETS_PER_SECOND_PLT);
hold off;
grid off;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Mbits per second
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% constants
granularity = 0.01; % 10 ms
numberOfPackets = Data(end, 1);
totalTime =  Data(end, 5);
numberOfDots = floor(totalTime/granularity);
vet_depertureTime = Data(:,5);
vet_packetLen = Data(:,3)*8;
scale = 10^6;
% vars
vet_mbitRate = zeros(numberOfDots,1);
vet_time = zeros(numberOfDots,1);
bitsCounter = 0;
timeCounter = granularity;
index_vetDepertureTime = 1;
plot1 = 0;
for i = 1:numberOfDots
        bitsCounter = 0;
        while(vet_depertureTime(index_vetDepertureTime) < timeCounter )
                % count number of packets
                bitsCounter = bitsCounter + vet_packetLen(index_vetDepertureTime);
                index_vetDepertureTime = index_vetDepertureTime + 1;
        endwhile
        %plot data
        vet_time(i) = timeCounter;
        vet_mbitRate(i) = (bitsCounter/granularity)/(scale);
        %update        
        timeCounter = timeCounter + granularity;
endfor
% plot...
clf;
hold on;
grid on;
plot1 = plot(vet_time,vet_mbitRate );
set(gca, 'fontsize', 20);
set(plot1, 'LineWidth', 1);
set(gca,'Fontname','Timesnewroman');
xlabel('time (seconds)'); 
ylabel('Mbps');
saveas(gca, FILE_MBPS_PLT);
hold off;
grid off;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Number of flows
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%constant
granularity = 1; % 1 s
vet_sec = round(Data(:, 5)/granularity);
vet_flow = Data(:, 2);
mat_flow = [vet_sec vet_flow];
maxTime = mat_flow(end, 1);
matSize = length(vet_flow);
%vars
vet_plotFlows = zeros(maxTime+1, 1);
j0 = 0;
j = 1;
nflows = 0;
for i = 0:maxTime
        j0 = j;
        if(mat_flow(j,1) == i)
                while(mat_flow(j,1) == i)
                        if(j < matSize)
                                j = j +1;
                        else
                                break;
                        endif
                endwhile
                subvet = mat_flow(j0:j, 2);
                j = j+1;
                nflows = length(unique(subvet));
                vet_plotFlows(i+1) = nflows;
        endif
endfor
% plot...
clf;
hold on;
grid on;
plot1 = plot(0:maxTime, vet_plotFlows);
set(gca, 'fontsize', 20);
set(plot1, 'LineWidth', 1);
set(gca,'Fontname','Timesnewroman');
xlabel('time (seconds)'); 
ylabel('Number of flows');
saveas(gca, FILE_FLOWS_PLT);
hold off;
grid off;

printf("done\n");


        
