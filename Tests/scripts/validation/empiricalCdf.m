function emCdf = empiricalCdf(data)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% A wrapper for empirical CDF octace function
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

        emCdf = empirical_cdf(data, data);
end