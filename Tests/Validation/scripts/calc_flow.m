function [timeVector nFlowsVector flowCdfVector flowCumulativeVector nflows] = calc_flow(vetDepertureTimes, vetFlows, sample_size)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Returns the number of flows over a sequnce of time intervals defined by 
% sample_size, and the Empirical CDF of flows. It also returns the time 
% sequence of times for the number of flows values.
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
%	Input vetDepertureTimes: list of inter packet times for each packet
%	Input vetFlows: list of flows ID of each packet
%   Input sample_size: number of packets
%	Output timeVector: vector of time intervalls
%	Output nFlowsVector: vector of flow per sample_size
%	Output flowCdfVector: flow cumulative distribution
%	Output nflows: number of flows
%
vetDepertureTimes = vetDepertureTimes(:);
vetFlows = vetFlows(:);
maxTime = vetDepertureTimes(end);
out_size = floor(maxTime/sample_size);
in_size = length(vetDepertureTimes);
nflows = max(vetFlows);

%numberOfFlows = max(vetFlows);
%oldValsList = zeros(numberOfFlows, 1);
nFlowsVector = zeros(out_size, 1);
timeVector = zeros(out_size, 1);
flowCdfVector = zeros(out_size, 1);
flowCumulativeVector = zeros(out_size, 1);
newFlowsVector = zeros(in_size, 1);
actualTime = 0;
firstIndex = 0;
lastIndex = 0;

% eval newsFlows vector
larger_flow = 0;
for i = 1:in_size
	flowNumber = vetFlows(i);
	if(flowNumber > larger_flow)
		larger_flow = flowNumber;
	endif
	newFlowsVector(i) = larger_flow;
endfor

% Flows per seconds
j = 1; %input index
i = 1; %output index
for i = 1:out_size
	actualTime = actualTime + sample_size;
	timeVector(i) = actualTime;
	firstIndex = j;
	while(actualTime > vetDepertureTimes(j))
		j = j + 1;
	endwhile
	lastIndex = j;
	uniqueFlows = length(unique(vetFlows(firstIndex:lastIndex)));
	nFlowsVector(i) = uniqueFlows;
	flowCumulativeVector(i) = newFlowsVector(j);
	
	%i
	%firstIndex
	%lastIndex
	%vetFlows(firstIndex:lastIndex)
	%unique(vetFlows(firstIndex:lastIndex))
	%uniqueFlows
	%pause;
	
endfor
flowCdfVector = flowCumulativeVector/max(flowCumulativeVector);


