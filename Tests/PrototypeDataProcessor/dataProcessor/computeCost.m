function J = computeCost(X, y, theta)
% computeCost - Compute cost for linear regression. Computes the cost of 
% using theta as the  parameter for linear regression to fit the data points 
% in X and y
% 
% Syntax:  J = computeCost(X, y, theta)
%
% Inputs:
%    X - data poing x
%    y - data point y 
%    theta - slope 
%
% Outputs:
%    J - cost function 
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
m = length(y); % number of training examples

J = 0; %coast

temp = 0;
for i = 1:m
	temp = temp + (theta(1) + theta(2)*X(i,2) - y(i) )^2 ;
end
J = (1/(2*m))*temp;

end
