#!/usr/bin/octave-cli -qf


printf("Testing command-line args\n");

arg_list = argv ();

for i = 1:nargin
  printf (" %s", arg_list{i});
endfor

printf ("\n");


arg_list

arg_list{1}
