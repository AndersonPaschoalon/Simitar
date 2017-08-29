function [timeVector bandwidthVector mean_bandwidth] = calc_bandwidth(vetDepertureTimes, vetPacketSizes, sample_size)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Returns the bandwisth over a sequnce of time intervals defined by sample_size.
% It also returns the time sequence of times for this bandwidth values,
% and the mean bandwidth.
% 
% Licensing:
%
%       This code is distributed under the GNU LGPL license.
%
% Modified:
%
%       29 March 2016
%
% Author:
%
%       Anderson Paschoalon
%
% Parameters:
%
%       Input vetDepertureTimes: deperture times of each packet
%	Input vetPacketSizes: list of packet sizes
%	Input sample_size: distance between each time intervall
%	Output timeVector: vector of time intervalls
%	Output bandwidthVector: vector of bandwidth values
%	Output mean_bandwidth: mean bandwidth value 
%
vetDepertureTimes = vetDepertureTimes(:);
vetPacketSizesBits = vetPacketSizes(:)*8;
maxTime = vetDepertureTimes(end);
out_size = floor(maxTime/sample_size);
timeVector = zeros(out_size, 1);
bandwidthVector = zeros(out_size, 1);


actualTime = 0;
j = 1;
for i = 1:out_size
	actualTime = actualTime + sample_size;
	timeVector(i) = actualTime;
	while (actualTime > vetDepertureTimes(j))
		bandwidthVector(i) = bandwidthVector(i) + vetPacketSizes(j);
		j = j + 1;
	endwhile

endfor

bandwidthVector = bandwidthVector/sample_size;
mean_bandwidth = sum(vetPacketSizes)/maxTime;
%est2 = sum(bandwidthVector)/length(bandwidthVector)