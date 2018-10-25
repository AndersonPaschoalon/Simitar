function emCdf = empiricalCdf(data)
% empiricalCdf - wrapper for empirical_cdf native function 
%
% Syntax:  emCdf = empiricalCdf(data)
%
% Inputs:
%    data - input data vector
%
% Outputs:
%    emCdf - empirical cdf of data
%
% Example: 
%    emCdf = empiricalCdf([1 2 3])
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
        emCdf = empirical_cdf(data, data);
end