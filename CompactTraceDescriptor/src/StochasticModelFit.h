/*
 * StochasticModelFit.h
 *
 *  Created on: 6 de nov de 2016
 *      Author: apaschoalon
 */

#ifndef STOCHASTICMODELFIT_H_
#define STOCHASTICMODELFIT_H_

#include <string>
using std::string;

typedef struct stochastic_model_fitting
{
	double aic;
	double bic;
	string modelName;
	double param1;
	double param2;
	int size;
} StochasticModelFit;

int compareBic(const void* a, const void* b);
int compareAic(const void* a, const void* b);



#endif /* STOCHASTICMODELFIT_H_ */
