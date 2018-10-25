#!/usr/bin/octave-cli -qf
% Script used by pcap-filter.sh to calc time relative

arg_list = argv ();

EXPERIMENT_NAME = arg_list{1};
DATAFILE_NAME_PREFIX = './data/';
DATAFILE_NAME_EXT = '.txt';
DATAFILE_NAME = strcat(DATAFILE_NAME_PREFIX,EXPERIMENT_NAME, DATAFILE_NAME_EXT);

%a = sort([1 2 3 4 5 6 7 7 8 9 10 11 1 2 3 5 3 4 2 ])';
a = sort(load(DATAFILE_NAME))';

adelta = zeros(length(a) - 1, 1);

for i = 1:(length(a) - 1)
	adelta(i) = a(i + 1) - a(i);
end

dlmwrite(DATAFILE_NAME, adelta);


