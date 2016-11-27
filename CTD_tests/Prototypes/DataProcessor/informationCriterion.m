function criterionVal =  informationCriterion(data, functionName, paramVet, criterion)
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