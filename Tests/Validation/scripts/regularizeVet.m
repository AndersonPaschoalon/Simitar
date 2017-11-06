function [ v1 ] = regularizeVet(vet1, m)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Make a vector have a specified size. If the vector is larger, the larger 
% index values will be discarted. If the vector is smaller, the lest value will
% be repeated with zeros.
%
% Licensing:
%
%       This code is distributed under the GNU LGPL license.
%
% Modified:
%
%       27 March 2016
%
% Author:
%
%       Anderson Paschoalon
%
% Parameters:
%
%       Input, vet1: input vector 1      .
%       Input, m: desired size 
%
%       Output, v1: regularized vector vet1
%
vet1 = vet1(:);
vetSize = size(vet1, 1);
v1 = zeros(m, 1);

for i = 1:m
	if (i <= vetSize)
		v1(i) = vet1(i);
	else
		v1(i) = vet1(vetSize);
	endif

endfor
