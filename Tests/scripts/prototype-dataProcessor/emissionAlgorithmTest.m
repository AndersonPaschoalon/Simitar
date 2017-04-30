%#!/usr/bin/octave-cli -qf
n_samples = 10000;
SESSION_CUT_TIME = 3;
FILE_CUT_TIME = 0.5;

RAND_DATA = 5*rand(n_samples, 1);
EXPRAND_DATA = exprnd(1, n_samples, 1);
RAND_CUMULATIVE_DATA = cumulativeData(RAND_DATA);
EXPRAND_CUMULATIVE_DATA = cumulativeData(EXPRAND_DATA);


