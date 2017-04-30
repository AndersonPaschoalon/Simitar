function J = computeCost(X, y, theta)
%COMPUTECOST Compute cost for linear regression
%   J = COMPUTECOST(X, y, theta) computes the cost of using theta as the
%   parameter for linear regression to fit the data points in X and y

m = length(y); % number of training examples

J = 0; %coast

temp = 0;
for i = 1:m
	temp = temp + (theta(1) + theta(2)*X(i,2) - y(i) )^2 ;
end
J = (1/(2*m))*temp;

end
