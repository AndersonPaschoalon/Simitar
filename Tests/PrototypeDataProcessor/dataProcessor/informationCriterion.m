function criterionVal =  informationCriterion(data, functionName, paramVet, criterion)
% informationCriterion - evaluates the information criterion, AIC or BIC for 
% a dataset data and a given stochastic process defined by a function 
% functionName and a parameter vector paramVet.
% 
% Syntax: criterionVal =  informationCriterion(data, functionName, paramVet, criterion)
%
% Inputs:
%   data - data vector 
%   functionName - weibull, normal, uniform, exponential, pareto, cauchy
%   paramVet - param vector for the function
%   criterion - aic, bic
%
% Outputs:
%    criterionVal - AIC or BIC value
%
% Example: 
%    data = [0.5 0.3 2 5]'
%    criterionVal =  informationCriterion(data, 'weibull', [0.5 0.5]', 'aic');
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% Author: Anderson Paschoalon
% email: anderson.paschoalon@gmail.com
% Sep 2018: Last revision: 16-Sep-2018 
% Initialize some useful values  
        nEstimatedParameters = length(paramVet);
        likehoodLogVal = likehood_log(data, functionName, paramVet);
        
        if(criterion == 'aic')
                criterionVal = 2*nEstimatedParameters - 2*likehoodLogVal;
        else if(criterion == 'bic')
                criterionVal = nEstimatedParameters*log(length(data)) - 2*likehoodLogVal;
        else 
                fprintf('\nInvalid functionName or no functionName selected: %s\n', functionName);
                fprintf('Selecting default criterion: AIC\n');
                criterionVal = 2*nEstimatedParameters - 2*likehoodLogVal;
        endif
                  
end