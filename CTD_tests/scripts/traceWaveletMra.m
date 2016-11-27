function [ log2TraceEnergy ] = traceWaveletMra(vetDepertureTimes, granularity)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Returns a log2 (log base two) energy vector of a wavelet multiresolution
% analisis form a given vector of packets inter-deperture/interarrival times
% as proposed by Kashi V. Vishwanath and Mamim Vahdat at 
% "Swing: Realistic and Responsive Network Traffic Generation"
% (http://cseweb.ucsd.edu/~kvishwanath/Swing/)
%
% Licensing:
%
%       This code is distributed under the GNU LGPL license.
%
% Modified:
%
%       10 August 2016
%
% Author:
%
%       Anderson Paschoalon
%
% Parameters:
%
%       Input vetDepertureTimes: vector of interdeperture or interarrival 
%       times, with the times relative to the fist packet (begining at zero).       .
%
%       Input, granularity: smaller amount of time (in milisecons) form 
%       wich the packet rate will be measured. Recomended value: 0.01 (10ms)
%
%       Output, logEnergyBase: vector of log wavelet multiresolution energies.
%
totalTime =  vetDepertureTimes(end);
numberOfDots = floor(totalTime/granularity);
% vars
vetPacketRate = zeros(numberOfDots,1);
vet_time = zeros(numberOfDots,1);
packetCounter = 0;
timeCounter = granularity;
index_vetDepertureTime = 1;
%plot "pointer"
plot1 = 0;
for i = 1:numberOfDots
        packetCounter = 0;
        while(vetDepertureTimes(index_vetDepertureTime) < timeCounter )
                % count number of packets
                packetCounter = packetCounter + 1;
                index_vetDepertureTime = index_vetDepertureTime + 1;
        endwhile
        %plot data
        vet_time(i) = timeCounter;
        vetPacketRate(i) = packetCounter/granularity;
        %update        
        timeCounter = timeCounter + granularity;
endfor
[details TraceEnergy] = haar_1d(length(vetPacketRate), vetPacketRate);
log2TraceEnergy = log2(TraceEnergy);




