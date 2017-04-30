function L = likehood_log(data, functionName, paramVet)
% LIKEHOOD_LOG compute the logarithm of likehood function value
%       LIKEHOOD_LOG(data, functionName, paramVet) evaluete the logarithm of 
% the maximum likehood function of a set of data, of a stochastic function.
%
% Parameters:
% data  
%       A vector of data wich will be used to evaluate the maximum likehood 
%       function.
% functionName
%       A lower case string of the name of the stochastic function, wich will 
%       be used to to compute the maximum likehood function. The supported 
%       functions are: 'weibull', 'normal', 'uniform', 'exponential', 'normal',
%       'pareto', cauchy', 'poison', 'gamma', 'lognormal' and 'beta'. Any other 
%       string than these ones, will return a maximum likehood of -inf, and print 
%       a warning message.  
% paramVet
%       A vector with a list of parameters used on the stochastic function. They
%       should be placed in alphabetical order (beguining at 1 position) of 
%       their typical notation found in the literature. They are listed below:
%       Weibull 
%               paramVet(1) = alpha (shape)
%               paramVet(2) = betha (scale)
%       Normal
%               paramVet(1) = mu (mean)
%               paramVet(2) = sigma (std deviation)
%       Uniform
%               any vector of size two
%       Exponential
%               paramVet(1) = lambda (mean)
%       Pareto
%               paramVet(1) = alpha (shape)
%               paramVet(2) = xm (scale)
%       Cauchy
%               paramVet(1) = gamma (scale)
%               paramVet(2) = x0 (location)
%
data_prob = zeros(size(data));
if(isequal(functionName, 'weibull'))
        alpha = paramVet(1);
        betha = paramVet(2);
        data_prob = (alpha/(betha^alpha))*data.^(alpha - 1).*exp(-(data/betha).^alpha);

elseif(isequal(functionName, 'normal'))
        mu = paramVet(1);
        sigma = paramVet(2);
        data_prob = (1/(sigma*sqrt(2*pi)))*exp(-0.5*((data - mu).^2)/(sigma^2));

elseif(isequal(functionName,'uniform'))
        max_value = max(data);
        min_value = min(data);
        data_prob = ones(length(data),1)*1./(max_value - min_value);

elseif(isequal(functionName, 'exponential'))
        lambda = paramVet(1);
        data_prob = lambda*exp(-lambda*data);

elseif(isequal(functionName, 'pareto'))
        alpha = paramVet(1);
        xm = paramVet(2);
        % aparentemente esta linha esta errada. A operacao de divisao element wise usa \
        data_prob = (alpha*(xm^(alpha)))./(data.^(alpha+1));
        
elseif(isequal(functionName, 'cauchy'))
        gamma = paramVet(1);%TODO checar se e zero
        x0 = paramVet(2);
        data_prob = 1/(pi*gamma)*(gamma^2./((data - x0).^2 + gamma^2) );

else
        fprintf('Warning, no valid stochastic function selected: %s\n', functionName);
        fprintf('Likehood logarithm seted to -Inf (worst as possible)\n');
        data_prob = 0;

endif
        
log_data_prob = sum(log(data_prob));
L = log_data_prob;

end