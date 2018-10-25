function val = adiff(a1, a2)
%adiff - evaluate the absolute difference between two numbers
%
% Syntax:  value = adiff(a1, a2)
%
% Inputs:
%    a1 - First value
%    a2 - Second value
%
% Outputs:
%    val - absolute value of the difference
%    output2 - Description
%
% Example: 
%    value = adiff(3, 5) % value is 5
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018  
        val = abs(a1 - a2);
end